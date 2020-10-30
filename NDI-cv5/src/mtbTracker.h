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
            
            finder.setMinArea(minArea*minArea);
            finder.setMaxArea(maxArea*maxArea);
            finder.setSimplify(bSimplify);
            finder.setFindHoles(bFindHoles);

            ofxCv::RectTracker & tracker = finder.getTracker();
            tracker.setSmoothingRate(smoothingRate);
            tracker.setMaximumDistance(maxDistance);
            tracker.setPersistence(persistence);

            finder.findContours(foregroundImage);
            
            // Process Dead blobs
            auto & deads = tracker.getDeadLabels();
            auto itrD = deads.begin();
            for(; itrD<deads.end(); ++itrD){
                int label = *itrD;
                if(selectedBlobs.count(label) != 0){
                    if(selectedBlobs[label] == true){
                        // this one need NoteOff
                        sendNoteOff(label, maxBlobNum);
                    }
                }
            }
            
            // Copy
            map<int, bool> prevSelectedBlobs(selectedBlobs);
            selectedBlobs.clear();

            // process Current blobs
            auto currs = tracker.getCurrentLabels();
            
            if(currs.size()>1){
                // elder first
                std::sort(
                          currs.begin(),
                          currs.end(),
                          [&](const int & a,
                              const int & b){
                    int ageA = tracker.getAge(a);
                    int ageB = tracker.getAge(b);
                    return ageA > ageB;
                });
            }
            
            auto itrC = currs.begin();

            // debug code
            //for(; itrC!=currs.end(); ++itrC){
            //    int age = tracker.getAge(*itrC);
            //    cout << age << ", ";
            //}
            //cout << endl;

//            for(; itrC!=currs.end(); ++itrC){
//                int label = *itrC;
//                selectedBlobs.insert(make_pair(label, true));
//                if(selectedBlobs.size() >= maxBlobNum){
//                    break;
//                }
//            }

            for(; itrC!=currs.end(); ++itrC){
                int label = *itrC;
                bool noteOnSent = false;
                if(prevSelectedBlobs.count(label) != 0){
                    noteOnSent = prevSelectedBlobs[label];
                }else{
                    noteOnSent = false;
                }
                selectedBlobs.emplace(make_pair(label, noteOnSent));

                if(noteOnSent == false){
                    int age = tracker.getAge(label);
                    if(minAge <= age){
                        selectedBlobs[label] = true;
                        sendNoteOn(label, maxBlobNum);
                    }
                }else{
                    // we send osc update val from drawToFbo()
                }

                if(selectedBlobs.size() >= maxBlobNum) break;
            }
        }

        void drawToFbo(float receiverW, float receiverH, float processW, float processH) override{
            
            ofxCv::RectTracker & tracker = finder.getTracker();
            
            senderBlob.begin();
            
            float sx = (float)processW / receiverW;
            float sy = (float)processH / receiverH;
            ofPushMatrix();
            ofScale(sx, sy);
            
            // Candidates
            if(bDrawCandidates){
                ofPushStyle();
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofSetColor(0, 255, 0);
                ofNoFill();
                const auto & rects = finder.getBoundingRects();
                for(int i=0; i<rects.size(); i++){
                    const cv::Rect & rect = rects[i];
                    glm::vec2 center(rect.x + rect.width/2, rect.y + rect.height/2);
                    
                    ofPushMatrix();
                    ofTranslate(center.x, center.y);
                    ofDrawRectangle(0, 0, rect.width, rect.height);
                    
                    // text
                    int label = tracker.getCurrentLabels()[i];
                    drawLabelAndAge(label, -rect.width/2, rect.height/2+15);
                    ofPopMatrix();
                }
                ofPopStyle();
            }
            
            // Selected
            auto itr = selectedBlobs.begin();
            for(; itr!=selectedBlobs.end(); ++itr){
                
                int label = itr->first;
                bool bNoteOnSent = itr->second;

                int age = tracker.getAge(label);
                const cv::Rect& rect = tracker.getCurrent(label);
                glm::vec2 center(rect.x+rect.width/2, rect.y+rect.height/2);
                float area = (rect.width * rect.height) / (receiverW*receiverH);

                // this index might not be really reliable
                int index = tracker.getIndexFromLabel(label);
                ofPolyline & poly = finder.getPolyline(index);
                
                ofPushStyle();
                ofPushMatrix();
                ofSetLineWidth(1);
                ofNoFill();
                bNoteOnSent ? ofSetColor(255, 0, 0) : ofSetColor(255);
                poly.draw();
                ofTranslate(center.x, center.y);
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofDrawRectangle(0, 0, rect.width+5, rect.height+4);
                drawLabelAndAge(label, -rect.width/2, rect.height/2+15);
                ofPopMatrix();
                ofPopStyle();
                
                // osc
                if(bNoteOnSent){
                    glm::vec2 vel(0,0);// = ofxCv::toOf(tracker.getVelocity(index));
                    glm::vec2 xyrate(center.x/receiverW, center.y/receiverH);
                    glm::vec2 inputSize(receiverW, receiverH);
                    sendVal(label, maxBlobNum, vel, area, age, center, inputSize);
                }
                
                // Heatmap
                addPointToHeatmap(center.x/receiverW, center.y/receiverH, area);
            }
            
            ofPopMatrix();
            senderBlob.end();
        }
        
        void drawReference(int x, int y, int w, int h) override{
            foregroundImage.draw(x, y, w, h);
        }
        
    
        ofPixels foregroundPix;
        ofxCvGrayscaleImage foregroundImage;
        
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
