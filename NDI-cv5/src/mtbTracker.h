//
//  mtbBlobTracker.h
//

#pragma once

#include "ofMain.h"
#include "mtbTrackerBase.h"
#include "NDISender.h"        // my own helper class
#include "ofxOpenCv.h"
#include "ofxCv.h"

class NDISource;

namespace mtb{

    class mtbTracker : public mtbTrackerBase{
        
    public:
        
        mtbTracker(){
            listenerHolder.push(bgAlgo.newListener([&](int& algo) { changeBG(); }));
        }        
        
        void registerUser(NDISource * s) override;

        void setup(string name, int w, int h, bool ndiOut) override{
            
            foregroundImage.clear();
            foregroundImage.allocate(w,h);
            senderBlob.setup(name, w, h, ndiOut);
            changeBG();
        }
        
        void changeBG(){
            if (bgAlgo == 0) {
                pBackSub = cv::createBackgroundSubtractorMOG2();
            }
            else {
                pBackSub = cv::createBackgroundSubtractorKNN();
            }
        }
        
        void update(ofxCvColorImage & currentImage) override{
            currentMat = ofxCv::toCv(currentImage);
            pBackSub->apply(currentMat, foregroundMat);
            ofxCv::toOf(foregroundMat, foregroundPix);
            foregroundImage.setFromPixels(foregroundPix);
            if(0<blurAmt) foregroundImage.blur(blurAmt);
            findContour();
        }
        
        void findContour() override{
            if(!foregroundImage.bAllocated) return;
            
            contourFinder.findContours(foregroundImage, minArea*minArea, maxArea*maxArea, maxBlobCandidate, bFindHoles, bSimplify);
            
            rects.clear();
            for(auto & b : contourFinder.blobs){
                rects.push_back(ofxCv::toCv(b.boundingRect));
            }

            tracker.setSmoothingRate(smoothingRate);
            tracker.setMaximumDistance(maxDistance);
            tracker.setPersistence(persistence);
            tracker.track(rects);
            
            // Process Dead blobs
            auto & deads = tracker.getDeadLabels();
            auto itrD = deads.begin();
            for(; itrD<deads.end(); ++itrD){
                int label = *itrD;
                if(selectedBlobs.count(label) != 0){
                    if(selectedBlobs[label] == true){
                        // this one need NoteOff
                    }
                }
            }
            
            // Copy
            map<int, bool> prevSelectedBlobs(selectedBlobs);
            selectedBlobs.clear();

            // process Current blobs
            const auto & currs = tracker.getCurrentLabels();
            auto itrC = currs.begin();
            for(; itrC!=currs.end(); ++itrC){
                int label = *itrC;
                if(prevSelectedBlobs.count(label) != 0){
                    bool noteOnSent = prevSelectedBlobs[label];
                    selectedBlobs.emplace(make_pair(label, noteOnSent));
                }else{
                    selectedBlobs.emplace(make_pair(label, false));
                }
                
                int age = tracker.getAge(label);
                if(minAge <= age){
                    // noteOn
                    selectedBlobs[label] = true;
                }
                
                if(selectedBlobs.size() >= maxBlobNum) break;
            }
        }

        void drawToFbo(float receiverW, float receiverH, float processW, float processH) override;
        
        void drawReference(int x, int y, int w, int h) override{
            foregroundImage.draw(x, y, w, h);
        }
        
    
        ofPixels foregroundPix;
        ofxCvGrayscaleImage foregroundImage;
        ofxCvContourFinder contourFinder;        
        
        // cv::BackgroundSubtractor
        cv::Ptr<cv::BackgroundSubtractor> pBackSub;
        cv::Mat currentMat, foregroundMat;
        
        ofParameter<int> bgAlgo{"Background Subtractor Algo", 1, 0, 1};
        ofParameter<float> blurAmt{ "Blur amount", 3, 1, 20 };

        // CV::Contor, CV::Tracker
        ofParameter<float> minArea{ "minArea", 5, 0, 500 };
        ofParameter<float> maxArea{ "maxArea", 10, 0, 500 };
        ofParameter<bool> bFindHoles{ "find holes", false };
        ofParameter<bool> bSimplify{ "simplify", false };
        ofParameter<int> persistence{ "persistence (frames)", 15, 1, 60 };
        ofParameter<float> maxDistance{ "max distance (pix)", 100, 0, 500 };
        ofParameter<float> smoothingRate{ "smoothingRate", 0.5, 0, 1.0 };
        ofParameter<int> maxBlobCandidate{ "Max blob candidate", 10, 1, 100 };
        ofParameter<bool> bDrawCandidates{ "Draw Candidates", true};
        ofParameter<int> maxBlobNum{ "Max blob num", 3, 1, 10 };
        ofParameter<int> minAge{ "Min age", 10, 0, 60 };
        ofParameterGroup grp{ "Tracker", bgAlgo, blurAmt, minArea, maxArea, bFindHoles, bSimplify, persistence, maxDistance, smoothingRate, bDrawCandidates, maxBlobCandidate, maxBlobNum, minAge, /*blobScale */};
    };
    
}
