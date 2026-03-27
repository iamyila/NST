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
#include <opencv2/dnn.hpp>
#include <set>
#include <sstream>

class NDISource;

namespace mtb{

    class mtbTracker : public mtbTrackerBase{
        
    public:
        
        mtbTracker(){
            listenerHolder.push(bgAlgo.newListener([&](int& algo) { changeBG(); }));
            listenerHolder.push(yoloModelPath.newListener([&](string&) { yoloLoaded = false; yoloModelWarned = false; }));
            
            grp.add(bgGrp);
            grp.add(yoloGrp);
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
            updateYOLO(currentMat);
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
            tracker.setMaximumDistance(getTrackMatchDistancePx());
            tracker.setPersistence(getTrackHoldFrames());

            //finder.findContours(foregroundImage);
            finder.findContours(foregroundMat);
            processTrackedResults(foregroundMat.cols, foregroundMat.rows);
        }

        void drawToFbo(float receiverW, float receiverH, float processW, float processH) override{
            
            ofxCv::RectTracker & tracker = finder.getTracker();
            
            senderBlob.begin();
            
            float sx = (float)processW / receiverW;
            float sy = (float)processH / receiverH;
            ofPushMatrix();
            ofScale(sx, sy);
            
            // Candidates
            if(bDrawCandidates && trackingTechnique == 0){
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

            if(bDrawCandidates && trackingTechnique == 1){
                ofPushStyle();
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofNoFill();
                for (const auto& kv : yoloCurrentRects) {
                    const int label = kv.first;
                    const cv::Rect& rect = kv.second;
                    const float score = yoloCurrentScores.count(label) ? yoloCurrentScores.at(label) : 0.0f;
                    const int classId = yoloCurrentClassIds.count(label) ? yoloCurrentClassIds.at(label) : -1;
                    const std::string className = yoloClassName(classId);
                    glm::vec2 center(rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f);
                    ofSetColor(120, 220, 255, 180);
                    ofPushMatrix();
                    ofTranslate(center.x, center.y);
                    ofDrawRectangle(0, 0, rect.width, rect.height);
                    drawLabelAndAge(label, -rect.width/2-15, rect.height/2+15);
                    if (yoloDrawClassNames) {
                        std::stringstream ss;
                        ss << className << " " << ofToString(score, 2);
                        ofDrawBitmapString(ss.str(), -rect.width/2, -rect.height/2 - 6);
                    }
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

                    ofPushStyle();
                    ofPushMatrix();
                    ofSetLineWidth(1);
                    ofSetColor(255, 0, 0);
                    ofNoFill();
                    if (trackingTechnique == 0) {
                        ofPolyline & poly = finder.getPolyline(index);
                        poly.draw();
                    }
                    ofTranslate(center.x, center.y);
                    ofSetRectMode(OF_RECTMODE_CENTER);
                    ofSetColor(255, 0, 0);
                    ofDrawRectangle(0, 0, rect.width+5, rect.height+4);
                    drawLabelAndAge(label, -rect.width/2-15, rect.height/2+15);
                    if (trackingTechnique == 1 && yoloDrawClassNames) {
                        const int classId = yoloCurrentClassIds.count(label) ? yoloCurrentClassIds.at(label) : -1;
                        const float score = yoloCurrentScores.count(label) ? yoloCurrentScores.at(label) : 0.0f;
                        ofDrawBitmapString(yoloClassName(classId) + " " + ofToString(score, 2), -rect.width/2, -rect.height/2 - 6);
                    }
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
            if(trackingTechnique == 1 && yoloPreviewImage.isAllocated()){
                yoloPreviewImage.draw(x, y, w, h);
            } else if(bDrawReferenceImage){
                foregroundImageOf.draw(x, y, w, h);
            }
        }

        void updateYOLO(cv::Mat & currentMat) {
            if (!ensureYoloLoaded()) {
                update(currentMat);
                return;
            }

            yoloPreviewImage.setFromPixels(currentMat.data, currentMat.cols, currentMat.rows, OF_IMAGE_COLOR);
            yoloPreviewImage.update();

            ofxCv::RectTracker & tracker = finder.getTracker();
            tracker.setMaximumDistance(getTrackMatchDistancePx());
            tracker.setPersistence(getTrackHoldFrames());

            std::vector<cv::Rect> detections;
            std::vector<int> classIds;
            std::vector<float> scores;
            runYolo(currentMat, detections, classIds, scores);

            const std::vector<unsigned int>& labels = tracker.track(detections);
            yoloCurrentRects.clear();
            yoloCurrentClassIds.clear();
            yoloCurrentScores.clear();
            for (std::size_t i = 0; i < labels.size() && i < detections.size(); ++i) {
                const int label = static_cast<int>(labels[i]);
                yoloCurrentRects[label] = detections[i];
                if (i < classIds.size()) yoloCurrentClassIds[label] = classIds[i];
                if (i < scores.size()) yoloCurrentScores[label] = scores[i];
            }

            processTrackedResults(currentMat.cols, currentMat.rows);
        }

        bool ensureYoloLoaded() {
            const std::string modelPath = yoloModelPath.get();
            if (yoloLoaded && modelPath == yoloLoadedPath) {
                return true;
            }
            yoloLoaded = false;
            yoloLoadedPath.clear();
            try {
                if (!ofFile::doesFileExist(modelPath)) {
                    if (!yoloModelWarned) {
                        ofLogWarning("Tracker") << "YOLO model not found: " << modelPath << ". Falling back to Blob tracking.";
                        yoloModelWarned = true;
                    }
                    return false;
                }
                yoloNet = cv::dnn::readNet(modelPath);
                yoloLoaded = !yoloNet.empty();
                yoloLoadedPath = modelPath;
                yoloModelWarned = false;
                ofLogNotice("Tracker") << "Loaded YOLO model: " << modelPath;
                return yoloLoaded;
            } catch (const std::exception& e) {
                ofLogError("Tracker") << "Failed to load YOLO model: " << e.what();
                yoloModelWarned = true;
                return false;
            }
        }

        std::set<std::string> parsedYoloClassFilter() const {
            std::set<std::string> out;
            std::stringstream ss(yoloClassFilter.get());
            std::string item;
            while (std::getline(ss, item, ',')) {
                ofStringReplace(item, "\t", " ");
                item = ofTrim(item);
                if (!item.empty()) {
                    out.insert(ofToLower(item));
                }
            }
            return out;
        }

        std::string yoloClassName(int classId) const {
            static const std::vector<std::string> names = {
                "person","bicycle","car","motorcycle","airplane","bus","train","truck","boat","traffic light",
                "fire hydrant","stop sign","parking meter","bench","bird","cat","dog","horse","sheep","cow",
                "elephant","bear","zebra","giraffe","backpack","umbrella","handbag","tie","suitcase","frisbee",
                "skis","snowboard","sports ball","kite","baseball bat","baseball glove","skateboard","surfboard","tennis racket","bottle",
                "wine glass","cup","fork","knife","spoon","bowl","banana","apple","sandwich","orange",
                "broccoli","carrot","hot dog","pizza","donut","cake","chair","couch","potted plant","bed",
                "dining table","toilet","tv","laptop","mouse","remote","keyboard","cell phone","microwave","oven",
                "toaster","sink","refrigerator","book","clock","vase","scissors","teddy bear","hair drier","toothbrush"
            };
            if (classId < 0 || classId >= static_cast<int>(names.size())) return "obj";
            return names[classId];
        }

        void runYolo(const cv::Mat& currentMat, std::vector<cv::Rect>& boxes, std::vector<int>& classIds, std::vector<float>& confidences) {
            boxes.clear();
            classIds.clear();
            confidences.clear();

            const int inputSize = yoloInputSize.get();
            cv::Mat blob = cv::dnn::blobFromImage(currentMat, 1.0 / 255.0, cv::Size(inputSize, inputSize), cv::Scalar(), true, false);
            yoloNet.setInput(blob);
            std::vector<cv::Mat> outputs;
            yoloNet.forward(outputs, yoloNet.getUnconnectedOutLayersNames());
            if (outputs.empty()) return;

            cv::Mat out = outputs[0];
            if (out.dims == 3 && out.size[1] < out.size[2]) {
                out = out.reshape(1, out.size[1]);
                cv::transpose(out, out);
            } else if (out.dims == 3) {
                out = out.reshape(1, out.size[1]);
            }

            const float xFactor = static_cast<float>(currentMat.cols) / static_cast<float>(inputSize);
            const float yFactor = static_cast<float>(currentMat.rows) / static_cast<float>(inputSize);
            const auto classFilter = parsedYoloClassFilter();

            std::vector<int> nmsClassIds;
            std::vector<float> nmsScores;
            std::vector<cv::Rect> nmsBoxes;

            for (int i = 0; i < out.rows; ++i) {
                const float* data = out.ptr<float>(i);
                if (!data) continue;

                cv::Mat scores(1, out.cols - 4, CV_32F, const_cast<float*>(data + 4));
                cv::Point classIdPoint;
                double maxClassScore = 0.0;
                cv::minMaxLoc(scores, nullptr, &maxClassScore, nullptr, &classIdPoint);
                if (maxClassScore < yoloConfidenceThreshold) continue;

                const int classId = classIdPoint.x;
                const std::string className = yoloClassName(classId);
                if (!classFilter.empty() && classFilter.count(ofToLower(className)) == 0) continue;

                const float cx = data[0];
                const float cy = data[1];
                const float w = data[2];
                const float h = data[3];

                const int left = std::max(0, static_cast<int>((cx - 0.5f * w) * xFactor));
                const int top = std::max(0, static_cast<int>((cy - 0.5f * h) * yFactor));
                const int width = std::min(currentMat.cols - left, static_cast<int>(w * xFactor));
                const int height = std::min(currentMat.rows - top, static_cast<int>(h * yFactor));
                if (width <= 1 || height <= 1) continue;

                nmsClassIds.push_back(classId);
                nmsScores.push_back(static_cast<float>(maxClassScore));
                nmsBoxes.emplace_back(left, top, width, height);
            }

            std::vector<int> indices;
            cv::dnn::NMSBoxes(nmsBoxes, nmsScores, yoloConfidenceThreshold, yoloNmsThreshold, indices);
            for (int idx : indices) {
                boxes.push_back(nmsBoxes[idx]);
                classIds.push_back(nmsClassIds[idx]);
                confidences.push_back(nmsScores[idx]);
            }
        }

        void processTrackedResults(int frameWidth, int frameHeight){
            beginOscFrame();

            ofxCv::RectTracker & tracker = finder.getTracker();

            vector<int> prevSelectedBlobs(selectedBlobs);
            selectedBlobs.clear();

            auto currs = tracker.getCurrentLabels();

            if(currs.size()>1){
                std::sort(currs.begin(), currs.end(), [&](const int & a, const int & b){
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

            vector<int> noteOnSendInThisLoop;
            int soundingCount = 0;
            for (const auto& kv : noteOnSentMap) {
                if (kv.second.bSent && !kv.second.bDead) soundingCount++;
            }

            for(auto itrC = currs.begin(); itrC!=currs.end(); ++itrC){
                int label = *itrC;
                selectedBlobs.push_back(label);

                bool noteOnSent = isNoteOnSent(label);
                if(noteOnSent == false){
                    int age = tracker.getAge(label);
                    int requiredAge = minAge;
                    if (soundingCount >= 2) requiredAge = std::max(requiredAge, static_cast<int>(extraVoiceMinAge));
                    if(requiredAge <= age){
                        sendNoteOn(label);

                        if(noteOnSentMap.count(label) == 0){
                            noteOnSentMap.insert(make_pair(label, NoteOnInfo(true)));
                        }else{
                            noteOnSentMap.at(label).bSent = true;
                            noteOnSentMap.at(label).bDead = false;
                            noteOnSentMap.at(label).framesAfterDeath = -1;
                        }
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
                float area = (rect.width * rect.height) / static_cast<float>(frameWidth * frameHeight);
                currentSelectedCenters[label] = center;
                currentSelectedAreas[label] = area;
                currentSelectedRects[label] = rect;
            }

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
                            prevRectAIt == prevSelectedRects.end()) continue;

                        for (std::size_t j = i + 1; j < prevSelectedBlobs.size() && !mergeSent; ++j) {
                            const int prevLabelB = prevSelectedBlobs[j];
                            auto prevCenterBIt = prevSelectedCenters.find(prevLabelB);
                            auto prevAreaBIt = prevSelectedAreas.find(prevLabelB);
                            auto prevRectBIt = prevSelectedRects.find(prevLabelB);
                            if (prevCenterBIt == prevSelectedCenters.end() ||
                                prevAreaBIt == prevSelectedAreas.end() ||
                                prevRectBIt == prevSelectedRects.end()) continue;

                            const float pairDistance = glm::distance(prevCenterAIt->second, prevCenterBIt->second);
                            if (pairDistance > proximityPx) continue;

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
                            if (!overlapsA || !overlapsB) continue;

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

            auto & deads = tracker.getDeadLabels();
            for(auto itrD = deads.begin(); itrD<deads.end(); ++itrD){
                int label = *itrD;
                if(noteOnSentMap.count(label) != 0){
                    if(!noteOnSentMap[label].bDead){
                        sendDeathNow(label);
                    }
                    noteOnSentMap[label].bDead = true;
                    noteOnSentMap[label].framesAfterDeath = 0;
                }
                yoloCurrentRects.erase(label);
                yoloCurrentClassIds.erase(label);
                yoloCurrentScores.erase(label);
            }

            vector<int> dels;
            for(auto itrM = noteOnSentMap.begin(); itrM!=noteOnSentMap.end(); ++itrM){
                int label = itrM->first;
                int slot = getOscAddressSlot(label);
                for(int i=0; i<noteOnSendInThisLoop.size(); i++){
                    int sentSlot = getOscAddressSlot(noteOnSendInThisLoop[i]);
                    if(sentSlot == slot){
                        continue;
                    }
                }

                NoteOnInfo & info = itrM->second;
                if(info.bSent && info.bDead){
                    int afterDeath = info.framesAfterDeath;
                    if( getTrackHoldFrames() <= afterDeath ){
                        if(needNoteOff(label)){
                            sendNoteOff(label);
                        }
                        dels.push_back(label);
                    }else{
                        info.framesAfterDeath++;
                    }
                }
            }

            for_each(dels.begin(),dels.end(), [&](const int & label){ noteOnSentMap.erase(label);});
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

        cv::dnn::Net yoloNet;
        bool yoloLoaded = false;
        bool yoloModelWarned = false;
        std::string yoloLoadedPath;
        ofImage yoloPreviewImage;
        std::map<int, cv::Rect> yoloCurrentRects;
        std::map<int, int> yoloCurrentClassIds;
        std::map<int, float> yoloCurrentScores;
    };
    
}
