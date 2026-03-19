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
            pBackSub->apply(currentMat, foregroundMat, bgLearningRate);
            if(0<blurAmt) ofxCv::blur(foregroundMat, foregroundMat, blurAmt);

            if(bDrawReferenceImage){
                foregroundImageOf.update();
            }

            findContour();
        }

        void updateByTrackingTechnique(cv::Mat & currentMat) {
            if (trackingTechnique == 0) {
                update(currentMat);
                return;
            }

            // YOLO scaffold: keep runtime behavior stable until detector/tracker is integrated.
            static bool loggedOnce = false;
            if (!loggedOnce) {
                ofLogWarning("Tracker") << "YOLO mode selected, but YOLO is not integrated yet. Falling back to Blob tracking.";
                loggedOnce = true;
            }
            update(currentMat);
        }
        
        void findContour() override{
            if(!foregroundImageOf.isAllocated()) return;
            beginOscFrame();
            
            finder.setMinArea(minArea*minArea);
            finder.setMaxArea(maxArea*maxArea);
            finder.setSimplify(bSimplify);
            finder.setFindHoles(bFindHoles);
            finder.setSortBySize(false);

            ofxCv::RectTracker & tracker = finder.getTracker();
            //tracker.setSmoothingRate(smoothingRate);
            tracker.setMaximumDistance(getTrackMatchDistancePx());
            tracker.setPersistence(getTrackHoldFrames());

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

            if (currs.size() == 1) {
                const int currentLabel = currs[0];
                const cv::Rect& currentRect = tracker.getCurrent(currentLabel);
                const glm::vec2 currentCenter(currentRect.x + currentRect.width / 2.0f,
                                              currentRect.y + currentRect.height / 2.0f);

                int targetSlot = -1;
                float bestDistance = std::numeric_limits<float>::max();
                for (const int prevLabel : prevSelectedBlobs) {
                    auto itPrevCenter = prevSelectedCenters.find(prevLabel);
                    if (itPrevCenter == prevSelectedCenters.end()) continue;
                    const float d = glm::distance(currentCenter, itPrevCenter->second);
                    if (d < bestDistance) {
                        bestDistance = d;
                        targetSlot = getOscAddressSlot(prevLabel);
                    }
                }

                if (targetSlot > 0) {
                    forceLabelToSlot(currentLabel, targetSlot);
                } else {
                    int liveSlotCount = 0;
                    for (const auto& kv : noteOnSentMap) {
                        const NoteOnInfo& info = kv.second;
                        if (!info.bSent || info.bDead) continue;
                        targetSlot = getOscAddressSlot(kv.first);
                        liveSlotCount++;
                    }
                    if (liveSlotCount == 1 && targetSlot > 0) {
                        forceLabelToSlot(currentLabel, targetSlot);
                    } else if (liveSlotCount == 0) {
                        forceSingleBlobSlot1(currentLabel);
                    }
                }
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
            int soundingCount = 0;
            for (const auto& kv : noteOnSentMap) {
                if (kv.second.bSent && !kv.second.bDead) {
                    soundingCount++;
                }
            }
            
            for(; itrC!=currs.end(); ++itrC){
                int label = *itrC;
                selectedBlobs.push_back(label);

                bool noteOnSent = isNoteOnSent(label);
                if(noteOnSent == false){
                    int age = tracker.getAge(label);
                    int requiredAge = minAge;
                    if (soundingCount >= 2) {
                        requiredAge = std::max(requiredAge, static_cast<int>(extraVoiceMinAge));
                    }
                    if(requiredAge <= age){
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
                        soundingCount++;
                    }
                }

                if(selectedBlobs.size() >= maxBlobNum) break;
            }

            std::map<int, glm::vec2> currentSelectedCenters;
            std::map<int, float> currentSelectedAreas;
            std::map<int, cv::Rect> currentSelectedRects;
            for (const int label : selectedBlobs) {
                const cv::Rect& rect = tracker.getCurrent(label);
                glm::vec2 center(rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f);
                float area = (rect.width * rect.height) / static_cast<float>(foregroundMat.cols * foregroundMat.rows);
                currentSelectedCenters[label] = center;
                currentSelectedAreas[label] = area;
                currentSelectedRects[label] = rect;
            }

            // Merge event: previous frame had N blobs, current frame has N-1 blobs,
            // and one current blob plausibly covers a close pair from the previous frame.
            const int currentSelectedCount = static_cast<int>(selectedBlobs.size());
            if (prevSelectedBlobCount >= 2 && currentSelectedCount == prevSelectedBlobCount - 1) {
                const float proximityPx = std::max(40.0f, getTrackMatchDistancePx() * 0.75f);
                const int rectMargin = 18;
                bool mergeSent = false;

                for (const int currentLabel : selectedBlobs) {
                    const auto currCenterIt = currentSelectedCenters.find(currentLabel);
                    const auto currAreaIt = currentSelectedAreas.find(currentLabel);
                    const auto currRectIt = currentSelectedRects.find(currentLabel);
                    if (currCenterIt == currentSelectedCenters.end() ||
                        currAreaIt == currentSelectedAreas.end() ||
                        currRectIt == currentSelectedRects.end()) {
                        continue;
                    }

                    cv::Rect expandedCurrent = currRectIt->second;
                    expandedCurrent.x -= rectMargin;
                    expandedCurrent.y -= rectMargin;
                    expandedCurrent.width += rectMargin * 2;
                    expandedCurrent.height += rectMargin * 2;

                    for (std::size_t i = 0; i < prevSelectedBlobs.size() && !mergeSent; ++i) {
                        const int prevLabelA = prevSelectedBlobs[i];
                        auto prevCenterAIt = prevSelectedCenters.find(prevLabelA);
                        auto prevAreaAIt = prevSelectedAreas.find(prevLabelA);
                        auto prevRectAIt = prevSelectedRects.find(prevLabelA);
                        if (prevCenterAIt == prevSelectedCenters.end() ||
                            prevAreaAIt == prevSelectedAreas.end() ||
                            prevRectAIt == prevSelectedRects.end()) {
                            continue;
                        }

                        for (std::size_t j = i + 1; j < prevSelectedBlobs.size() && !mergeSent; ++j) {
                            const int prevLabelB = prevSelectedBlobs[j];
                            auto prevCenterBIt = prevSelectedCenters.find(prevLabelB);
                            auto prevAreaBIt = prevSelectedAreas.find(prevLabelB);
                            auto prevRectBIt = prevSelectedRects.find(prevLabelB);
                            if (prevCenterBIt == prevSelectedCenters.end() ||
                                prevAreaBIt == prevSelectedAreas.end() ||
                                prevRectBIt == prevSelectedRects.end()) {
                                continue;
                            }

                            const float pairDistance = glm::distance(prevCenterAIt->second, prevCenterBIt->second);
                            if (pairDistance > proximityPx) {
                                continue;
                            }

                            cv::Rect expandedPrevA = prevRectAIt->second;
                            expandedPrevA.x -= rectMargin;
                            expandedPrevA.y -= rectMargin;
                            expandedPrevA.width += rectMargin * 2;
                            expandedPrevA.height += rectMargin * 2;

                            cv::Rect expandedPrevB = prevRectBIt->second;
                            expandedPrevB.x -= rectMargin;
                            expandedPrevB.y -= rectMargin;
                            expandedPrevB.width += rectMargin * 2;
                            expandedPrevB.height += rectMargin * 2;

                            const bool overlapsA = (expandedCurrent & expandedPrevA).area() > 0;
                            const bool overlapsB = (expandedCurrent & expandedPrevB).area() > 0;
                            if (!overlapsA || !overlapsB) {
                                continue;
                            }

                            const glm::vec2 pairCentroid = (prevCenterAIt->second + prevCenterBIt->second) * 0.5f;
                            const float centroidDistance = glm::distance(currCenterIt->second, pairCentroid);
                            const float pairMaxArea = std::max(prevAreaAIt->second, prevAreaBIt->second);
                            const bool areaComparable = currAreaIt->second >= (pairMaxArea * 0.85f);
                            const bool nearPairCentroid = centroidDistance <= proximityPx;

                            if (areaComparable && nearPairCentroid) {
                                sendMergeEvent(prevSelectedBlobCount, currentSelectedCount, currentLabel);
                                mergeSent = true;
                            }
                        }
                    }
                }
            }

            prevSelectedBlobCount = static_cast<int>(selectedBlobs.size());
            prevSelectedCenters = currentSelectedCenters;
            prevSelectedAreas = currentSelectedAreas;
            prevSelectedRects = currentSelectedRects;
            
            // Process Dead blobs, just mark bDead
            auto & deads = tracker.getDeadLabels();
            auto itrD = deads.begin();
            for(; itrD<deads.end(); ++itrD){
                int label = *itrD;
                if(noteOnSentMap.count(label) != 0){
                    if(!noteOnSentMap[label].bDead){
                        sendDeathNow(label);
                    }
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
                int slot = getOscAddressSlot(label);
                for(int i=0; i<noteOnSendInThisLoop.size(); i++){
                    int sentSlot = getOscAddressSlot(noteOnSendInThisLoop[i]);
                    if(sentSlot == slot){
                        continue;
                    }
                }
                
                NoteOnInfo & info = itrM->second;
                bool bSent = info.bSent;
                bool bDead = info.bDead;
                
                if(bSent && bDead){
                    int afterDeath = info.framesAfterDeath;
                    if( getTrackHoldFrames() <= afterDeath ){
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

        std::map<int, glm::vec2> prevSelectedCenters;
        std::map<int, float> prevSelectedAreas;
        std::map<int, cv::Rect> prevSelectedRects;
        std::vector<cv::Rect> prevContourRects;
        bool mergeContactLatched = false;
    
        //ofPixels foregroundPix;
        ofImage foregroundImageOf;
        
        // cv::BackgroundSubtractor
        cv::Ptr<cv::BackgroundSubtractor> pBackSub;
        //cv::Mat currentMat;
        cv::Mat foregroundMat;
        
        ofParameter<int> bgAlgo{"Background Subtractor Algo", 0, 0, 1};
        ofParameter<float> blurAmt{ "Blur amount", 3, 0, 20 };
        ofParameter<float> bgLearningRate{ "BG Learning Rate", 0.001f, 0.0f, 0.05f };
        ofParameter<bool> bDrawReferenceImage{ "Draw Reference Image", false };
        ofParameterGroup bgGrp{"BG", bgAlgo, blurAmt, bgLearningRate, bDrawReferenceImage};
    };
    
}
