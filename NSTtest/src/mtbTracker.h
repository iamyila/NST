//
//  mtbBlobTracker.h
//

#pragma once

#include "ofMain.h"
#include "mtbTrackerBase.h"
#include "NDISender.h"        // my own helper class
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "OscSender.h"

class NDISource;

namespace mtb{

    class mtbTracker : public mtbTrackerBase{
        
    public:
        
        mtbTracker(){
            listenerHolder.push(bgAlgo.newListener([&](int& algo) { changeBG(); }));
            
            grp.add(bgGrp);
        }                

        void setup(string name, int w, int h, bool ndiOut) override{
            
            foregroundImageOf.clear();
            foregroundImageOf.allocate(w,h, OF_IMAGE_GRAYSCALE);
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
        }
        
        void update(cv::Mat & currentMat) {
            //currentMat = ofxCv::toCv(currentImage);
            foregroundMat = ofxCv::toCv(foregroundImageOf);
            pBackSub->apply(currentMat, foregroundMat);
            if(0<blurAmt) ofxCv::blur(foregroundMat, foregroundMat, blurAmt);

            if(bDrawReferenceImage){
                foregroundImageOf.update();
            }

            findContour();
        }
        
        void findContour() override{
            if(!foregroundImageOf.isAllocated()) return;
            
            finder.setMinArea(minArea*minArea);
            finder.setMaxArea(maxArea*maxArea);
            finder.setSimplify(bSimplify);
            finder.setFindHoles(bFindHoles);
            finder.setSortBySize(false);

            ofxCv::RectTracker & tracker = finder.getTracker();
            //tracker.setSmoothingRate(smoothingRate);
            tracker.setMaximumDistance(maxDistance);
            tracker.setPersistence(persistence);

            //finder.findContours(foregroundImage);
            finder.findContours(foregroundMat);
            

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

            vector<int> noteOnSendInThisLoop;
            
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
                        
                        noteOnSendInThisLoop.push_back(label);
                    }
                }

                if(selectedBlobs.size() >= maxBlobNum) break;
            }
            
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

                // Do not send noteOff, if we send noteOn already
                int slot = OscSender::getOscAddressSlot(label, maxBlobNum);
                bool slotReusedThisLoop = false;
                for(int i=0; i<noteOnSendInThisLoop.size(); i++){
                    int sentSlot = OscSender::getOscAddressSlot(noteOnSendInThisLoop[i], maxBlobNum);
                    if(sentSlot == slot){
                        slotReusedThisLoop = true;
                        break;
                    }
                }
                if(slotReusedThisLoop){
                    // A new blob already took this OSC slot in the same frame.
                    // Drop stale mapping without emitting noteOff to prevent slot crosstalk.
                    dels.push_back(label);
                    continue;
                }
                
                NoteOnInfo & info = itrM->second;
                bool bSent = info.bSent;
                bool bDead = info.bDead;
                
                if(bSent && bDead){
                    int afterDeath = info.framesAfterDeath;
                    if( persistence <= afterDeath ){
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

                if(bNoteOnSent){

                    // this index might not be really reliable,
                    // so only for drawing perpose
                    //int index = tracker.getIndexFromLabel(label);
                    int index = -1;
                    auto & curs = tracker.getCurrentLabels();
                    for(int j=0; j<curs.size(); j++){
                        if(label == curs[j]){
                            index = j;
                            break;
                        }
                    }
                    
                    if(index == -1){
                        continue;
                    }
                
                    int age = tracker.getAge(label);
                    const cv::Rect& rect = tracker.getCurrent(label);
                    glm::vec2 center(rect.x+rect.width/2, rect.y+rect.height/2);
                    float area = (rect.width * rect.height) / (receiverW*receiverH);

                    ofPolyline & poly = finder.getPolyline(index);
                    
                    ofPushStyle();
                    ofPushMatrix();
                    ofSetLineWidth(1);
                    ofSetColor(255, 0, 0);
                    ofNoFill();
                    poly.draw();
                    ofTranslate(center.x, center.y);
                    ofSetRectMode(OF_RECTMODE_CENTER);
                    ofSetColor(255, 0, 0);
                    ofDrawRectangle(0, 0, rect.width+5, rect.height+4);
                    drawLabelAndAge(label, -rect.width/2-15, rect.height/2+15);
                    ofPopMatrix();
                    ofPopStyle();
                
                    // osc
                    glm::vec2 vel = ofxCv::toOf(tracker.getVelocityFromLabel(label));
                    glm::vec2 xyrate(center.x/receiverW, center.y/receiverH);
                    glm::vec2 inputSize(receiverW, receiverH);
                    sendVal(label, vel, area, age, center, inputSize);

                    // Heatmap
                    addPointToHeatmap(center.x/receiverW, center.y/receiverH, area);
                }
                
                i++;
            }
            
            ofPopMatrix();
            senderBlob.end();
        }
        
        void drawReference(int x, int y, int w, int h) override{
            //foregroundImage.draw(x, y, w, h);
            //foregroundMat.draw(x, y, w, h);
            if(bDrawReferenceImage){
                foregroundImageOf.draw(x, y, w, h);
            }
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
    
        //ofPixels foregroundPix;
        ofImage foregroundImageOf;
        
        // cv::BackgroundSubtractor
        cv::Ptr<cv::BackgroundSubtractor> pBackSub;
        //cv::Mat currentMat;
        cv::Mat foregroundMat;
        
        ofParameter<int> bgAlgo{"Background Subtractor Algo", 1, 0, 1};
        ofParameter<float> blurAmt{ "Blur amount", 3, 0, 20 };
        ofParameter<bool> bDrawReferenceImage{ "Draw Reference Image", false };
        ofParameterGroup bgGrp{"BG", bgAlgo, blurAmt, bDrawReferenceImage};
    };
    
}
