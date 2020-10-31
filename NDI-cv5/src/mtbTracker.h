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
            
            grp.add(bgGrp);
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
            if(0<blurAmt) foregroundImage.blur(blurAmt*2+1);
            findContour();
        }
        
        void findContour() override{
            if(!foregroundImage.bAllocated) return;
            
            finder.setMinArea(minArea*minArea);
            finder.setMaxArea(maxArea*maxArea);
            finder.setSimplify(bSimplify);
            finder.setFindHoles(bFindHoles);

            ofxCv::RectTracker & tracker = finder.getTracker();
            //tracker.setSmoothingRate(smoothingRate);
            tracker.setMaximumDistance(maxDistance);
            tracker.setPersistence(persistence);

            finder.findContours(foregroundImage);
            
            // Process Dead blobs, just mark bDead
            auto & deads = tracker.getDeadLabels();
            auto itrD = deads.begin();
            for(; itrD<deads.end(); ++itrD){
                int label = *itrD;
                if(noteOnSentMap.count(label) != 0){
                    noteOnSentMap[label].bDead = true;
                    noteOnSentMap[label].framesAfterDeath = 0;
                }
            }

            
            // dead check
            vector<int> dels;
            auto itrM = noteOnSentMap.begin();
            for(; itrM!=noteOnSentMap.end(); ++itrM){
                int label = itrM->first;
                NoteOnInfo & info = itrM->second;
                bool bSent = info.bSent;
                bool bDead = info.bDead;
                
                if(bSent && bDead){
                    int afterDeath = info.framesAfterDeath;
                    if( persistence < afterDeath ){
                        if(needNoteOff(label)){
                            sendNoteOff(label);
                            cout << "NoteOff " << label << endl;
                        }
                        dels.push_back(label);
                    }else{
                        info.framesAfterDeath++;
                    }
                }
            }
            
            for_each(dels.begin(),dels.end(),
                     [&](const int & label){ noteOnSentMap.erase(label);});
            
            // Copy
            vector<int> prevSelectedBlobs(selectedBlobs);
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
                selectedBlobs.push_back(label);

                bool noteOnSent = isNoteOnSent(label);
                if(noteOnSent == false){
                    int age = tracker.getAge(label);
                    if(minAge <= age){
                        sendNoteOn(label);
                        
                        if(noteOnSentMap.count(label) == 0){
                            noteOnSentMap.insert(make_pair(label, NoteOnInfo(true)));
                        }else{
                            noteOnSentMap.at(label).bSent = true;
                            noteOnSentMap.at(label).bDead = false;
                            noteOnSentMap.at(label).framesAfterDeath = -1;
                        }
                        cout << "NoteOn  " << label << endl;
                    }
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
                ofSetColor(255, 160);
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
                    drawLabelAndAge(label, -rect.width/2-15, rect.height/2+15);
                    ofPopMatrix();
                }
                ofPopStyle();
            }
            
            // Selected
            auto itr = selectedBlobs.begin();
            int i = 0;
            for(; itr!=selectedBlobs.end(); ++itr){
                
                int label = *itr;
                bool bNoteOnSent = isNoteOnSent(label);

                int age = tracker.getAge(label);
                const cv::Rect& rect = tracker.getCurrent(label);
                glm::vec2 center(rect.x+rect.width/2, rect.y+rect.height/2);
                float area = (rect.width * rect.height) / (receiverW*receiverH);

                // this index might not be really reliable,
                // so only for drawing perpose
                int index = tracker.getIndexFromLabel(label);
                ofPolyline & poly = finder.getPolyline(index);
                
                ofPushStyle();
                ofPushMatrix();
                ofSetLineWidth(1);
                bNoteOnSent ? ofSetColor(255, 0, 0) : ofSetColor(255);
                ofNoFill();
                poly.draw();
                ofTranslate(center.x, center.y);
                ofSetRectMode(OF_RECTMODE_CENTER);
                bNoteOnSent ? ofSetColor(255, 0, 0, 200) : ofSetColor(255,200);
                ofDrawRectangle(0, 0, rect.width+5, rect.height+4);
                drawLabelAndAge(label, -rect.width/2-15, rect.height/2+15);
                ofPopMatrix();
                ofPopStyle();
                
                // osc
                if(bNoteOnSent){
                    glm::vec2 vel = ofxCv::toOf(tracker.getVelocityFromLabel(label));
                    glm::vec2 xyrate(center.x/receiverW, center.y/receiverH);
                    glm::vec2 inputSize(receiverW, receiverH);
                    sendVal(label, vel, area, age, center, inputSize);
                }
                
                // Heatmap
                addPointToHeatmap(center.x/receiverW, center.y/receiverH, area);
                
                if(i==0){
                    float speed = 0.90;
                    float speed2 = 1.0 - speed;
                    targetRect.set(rect.x, rect.y, rect.width, rect.height);
                    currentRect.x = currentRect.x*speed + targetRect.x * speed2;
                    currentRect.y = currentRect.y*speed + targetRect.y * speed2;
                    currentRect.width = currentRect.width*speed + targetRect.width * speed2;
                    currentRect.height = currentRect.height*speed + targetRect.height * speed2;
                    
                    ofNoFill();
                    ofSetColor(100,0, 200, 200);
                    ofDrawRectangle(currentRect);
                }
                
                i++;
            }
            
            ofPopMatrix();
            senderBlob.end();
        }
        
        void drawReference(int x, int y, int w, int h) override{
            foregroundImage.draw(x, y, w, h);
        }

        void drawNoteOnInfo(){
            auto itr = noteOnSentMap.begin();
            int i = 0;
            for(; itr!=noteOnSentMap.end(); ++itr){
                int label = itr->first;
                NoteOnInfo & info = itr->second;
                if(info.bSent){
                
                    stringstream ss;
                    ss << label;
                    if(info.bDead){
                        ss << " DEAD ";
                        ss << info.framesAfterDeath;
                        ofSetColor(255, 0, 0);
                    }else{
                        ofSetColor(0, 255, 0);
                    }
                    
                    ofDrawBitmapString(ss.str(), 0, 10+i*15);
                    i++;
                }
            }
        }
    
        ofPixels foregroundPix;
        ofxCvGrayscaleImage foregroundImage;
        
        // cv::BackgroundSubtractor
        cv::Ptr<cv::BackgroundSubtractor> pBackSub;
        cv::Mat currentMat, foregroundMat;
        
        ofParameter<int> bgAlgo{"Background Subtractor Algo", 1, 0, 1};
        ofParameter<float> blurAmt{ "Blur amount", 3, 0, 20 };
        ofParameterGroup bgGrp{"BG", bgAlgo, blurAmt};

        
        ofRectangle targetRect;
        ofRectangle currentRect;
    };
    
}
