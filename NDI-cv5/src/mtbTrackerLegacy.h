//
//  mtbTrackerLegacy.h
//
//

#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "NDISender.h"        // my own helper class
#include "mtbTrackerBase.h"

namespace mtb{
    
    class mtbTrackerLegacy : public mtbTrackerBase{
      
    public:

        void registerUser(NDISource * s) override;
        
        void setup(string name, int w, int h, bool ndiOut) override{
            
            grayImage.allocate(w,h);
            grayBg.allocate(w,h);
            grayFinal.allocate(w,h);
            grayDiff.allocate(w,h);
            
            // NDI sender
            senderBlob.setup(name, w, h, ndiOut);

             listenerHolder.push(bUseBG.newListener([&](bool & b){
                if(bUseBG){
                    grayBg = grayImage;
                    grayFinal.clear();
                }else{
                    grayBg.clear();
                    grayFinal.clear();
                }
            }));
        }
        
        void update(ofxCvColorImage & img) override{
            grayImage.setFromColorImage(img);
            
            if(bUseBG){
                
                grayDiff.absDiff(grayBg, grayImage);
                
                grayDiff.threshold(bgThreshold);
                
                switch(bgMode){
                    case 0:
                        // single frame difference
                        grayFinal = grayDiff;
                        break;
                    case 1:
                        // additive background
                        grayFinal += grayDiff;
                        break;
                    case 2:
                    {
                        cv::Mat diffMat = ofxCv::toCv(grayDiff);
                        cv::Mat finalMat = ofxCv::toCv(grayFinal);
                        diffMat.convertTo(finalMat, CV_32F);
                        cv::accumulateWeighted(diffMat, finalMat, acmWeight);
                        break;
                    }
                }
                
                if(bgMode >= 1){
                    if (frameCounter >= bgUpdateFrame) {
                        grayBg = grayImage;
                        frameCounter =0;
                        grayFinal = grayDiff;
                    }
                }
            }else{
                grayBg.clear();
                grayFinal = grayImage;
            }
            
            if(blurAmt!=0) grayFinal.blur(blurAmt);
            
            frameCounter++;
            
            findContour();
        }
        
        void findContour() override{
            // contour finder
            if(grayFinal.bAllocated){
                contourFinder.findContours(grayFinal, minArea, maxArea, maxBlobNum, bFindHoles, bSimplify);
                
                rects.clear();
                for(auto & b : contourFinder.blobs){
                    rects.push_back(ofxCv::toCv(b.boundingRect));
                }
                tracker.setSmoothingRate(smoothingRate);
                tracker.setMaximumDistance(maxDistance);
                tracker.setPersistence(persistence);
                tracker.track(rects);
            }
        }
        
        void drawToFbo(float receiverW, float receiverH, float processW, float processH) override;
        
        void drawReference(int x, int y, int w, int h) override{
            if(bUseBG){
                ofSetColor(255);
                //grayImage.draw(x,y,w,h);
                //grayBg.draw(x,y,w,h);
                grayFinal.draw(x,y,w,h);
            }else{
                ofNoFill();
                ofSetColor(255);
                ofDrawRectangle(x, y, w, h);
                ofDrawLine(x, y, x+w, y+h);
                ofDrawLine(x, y, x, y+h);
                grayImage.draw(x, y, w, h);
            }
        }

        void drawInfo(){
            
        }

        
    public:
        int frameCounter = 0;
        
        ofxCvGrayscaleImage grayImage;
        ofxCvGrayscaleImage grayImageFixed;
        ofxCvGrayscaleImage grayBg;
        ofxCvGrayscaleImage grayDiff;
        ofxCvGrayscaleImage grayFinal;
        ofxCvContourFinder contourFinder;
        
        ofParameter<bool> bUseBG{"Use BG", false};
        ofParameter<int>  bgThreshold{"Threshold", 80, 10, 300};
        ofParameter<int> bgUpdateFrame{"Update Frame", 10, 0, 300};
        ofParameter<int> bgMode{"Background Mode", 0, 0, 2}; // 0: instant diff, 1: add, 2: accumlate
        ofParameter<float> acmWeight{"Accumulate Weight", 0.5, 0, 1.0};
        ofParameter<float> blurAmt{"Blur Amount", 0, 0, 10};
        ofParameterGroup bgGrp{"Background", bUseBG, bgThreshold, bgUpdateFrame, bgMode, acmWeight, blurAmt};

        // CV::Contor, CV::Tracker
        ofParameter<float> minArea{ "minArea", 5, 0, 100*100 };
        ofParameter<float> maxArea{ "maxArea", 10, 0, 300*300 };
        ofParameter<bool> bFindHoles{ "find holes", false };
        ofParameter<bool> bSimplify{ "simplify", false };
        ofParameter<int> persistence{ "persistence (frames)", 15, 1, 60 };
        ofParameter<float> maxDistance{ "max distance (pix)", 100, 0, 300 };
        ofParameter<float> smoothingRate{ "smoothingRate", 0.5, 0, 1.0 };
        ofParameter<int> maxBlobNum{ "Max blob num", 3, 1, 30 };
        ofParameterGroup trackerGrp{ "Tracker", minArea, maxArea, bFindHoles, bSimplify, persistence, maxDistance, smoothingRate,  maxBlobNum };
        
        ofParameterGroup grp{"Tracker Rg", bgGrp, trackerGrp};

    };
}
