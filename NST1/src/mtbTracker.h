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
#include "YoloDetector.h"
#include <algorithm>
#include <array>
#include <set>
#include <sstream>

class NDISource;

namespace mtb{

    class mtbTracker : public mtbTrackerBase{
        
    public:
        static constexpr int kYoloClassCount = 80;
        struct YoloTrack;
        
        mtbTracker(){
            listenerHolder.push(bgAlgo.newListener([&](int& algo) { changeBG(); }));
            listenerHolder.push(yoloModelPath.newListener([&](string&) { resetYoloBackend(); }));
            listenerHolder.push(yoloCoreMLModelPath.newListener([&](string&) { resetYoloBackend(); }));
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
                    {
                        std::stringstream ss;
                        ss << label << ":" << yoloTrackAgeForLabel(label);
                        ofDrawBitmapString(ss.str(), -rect.width/2-15, rect.height/2+15);
                    }
                    if (yoloDrawClassNames) {
                        std::stringstream ss;
                        ss << className << " " << ofToString(score, 2);
                        ofDrawBitmapString(ss.str(), -rect.width/2, -rect.height/2 - 6);
                    }
                    ofPopMatrix();
                }
                ofPopStyle();
            }

            if (trackingTechnique == 1 && yoloRawMode) {
                ofPushStyle();
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofNoFill();
                ofSetLineWidth(2);
                for (const auto& kv : yoloCurrentRects) {
                    const int label = kv.first;
                    const cv::Rect& rect = kv.second;
                    const float score = yoloCurrentScores.count(label) ? yoloCurrentScores.at(label) : 0.0f;
                    const int classId = yoloCurrentClassIds.count(label) ? yoloCurrentClassIds.at(label) : -1;
                    const std::string className = yoloClassName(classId);
                    const glm::vec2 center(rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f);
                    ofSetColor(255, 80, 80, 220);
                    ofPushMatrix();
                    ofTranslate(center.x, center.y);
                    ofDrawRectangle(0, 0, rect.width + 4, rect.height + 4);
                    if (yoloDrawClassNames) {
                        std::stringstream ss;
                        ss << className << " " << ofToString(score, 2);
                        ofDrawBitmapString(ss.str(), -rect.width/2, -rect.height/2 - 6);
                    }
                    ofPopMatrix();
                }
                ofPopStyle();
                ofPopMatrix();
                senderBlob.end();
                return;
            }
            
            // Selected
            auto itr = selectedBlobs.begin();
            int i = 0;
            for(; itr!=selectedBlobs.end(); ++itr){
                
                int label = *itr;
                bool bNoteOnSent = isNoteOnSent(label);
                const bool shouldRender = (trackingTechnique == 1) || bNoteOnSent;
                if(!shouldRender){
                    i++;
                    continue;
                }

                int index = -1;
                auto & curs = tracker.getCurrentLabels();
                for(int j=0; j<curs.size(); j++){
                    if(label == curs[j]){
                        index = j;
                        break;
                    }
                }
                
                bool usingRetained = false;
                int age = 0;
                cv::Rect rect;
                cv::Rect2f drawRectF;
                glm::vec2 center(0.0f, 0.0f);
                float area = 0.0f;
                glm::vec2 vel(0.0f, 0.0f);
                int classId = -1;
                float score = 0.0f;
                bool hasGeometry = false;

                if (trackingTechnique == 1) {
                    auto retainedIt = retainedOutputTracks.find(label);
                    if (retainedIt != retainedOutputTracks.end()) {
                        const RetainedOutputTrack& retained = retainedIt->second;
                        usingRetained = retained.missingFrames > 0;
                        drawRectF = retained.rect;
                        rect = cv::Rect(
                            static_cast<int>(std::round(retained.rect.x)),
                            static_cast<int>(std::round(retained.rect.y)),
                            static_cast<int>(std::round(retained.rect.width)),
                            static_cast<int>(std::round(retained.rect.height))
                        );
                        center = glm::vec2(retained.rect.x + retained.rect.width * 0.5f,
                                           retained.rect.y + retained.rect.height * 0.5f);
                        area = retained.area;
                        age = retained.age;
                        vel = retained.velocity;
                        classId = retained.classId;
                        score = retained.score;
                        hasGeometry = true;
                    } else {
                        auto rectIt = yoloCurrentRects.find(label);
                        if (rectIt != yoloCurrentRects.end()) {
                            rect = rectIt->second;
                            drawRectF = cv::Rect2f(rect.x, rect.y, rect.width, rect.height);
                            center = glm::vec2(drawRectF.x + drawRectF.width * 0.5f,
                                               drawRectF.y + drawRectF.height * 0.5f);
                            area = (drawRectF.width * drawRectF.height) / (receiverW * receiverH);
                            age = yoloTrackAgeForLabel(label);
                            auto classIt = yoloCurrentClassIds.find(label);
                            if (classIt != yoloCurrentClassIds.end()) classId = classIt->second;
                            auto scoreIt = yoloCurrentScores.find(label);
                            if (scoreIt != yoloCurrentScores.end()) score = scoreIt->second;
                            hasGeometry = true;
                        }
                    }
                } else if(index != -1){
                    age = tracker.getAge(label);
                    rect = tracker.getCurrent(label);
                    drawRectF = cv::Rect2f(rect.x, rect.y, rect.width, rect.height);
                    center = glm::vec2(rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f);
                    area = (rect.width * rect.height) / (receiverW*receiverH);
                    vel = ofxCv::toOf(tracker.getVelocityFromLabel(label));
                    hasGeometry = true;
                } else {
                    auto retainedIt = retainedOutputTracks.find(label);
                    if (retainedIt != retainedOutputTracks.end()) {
                        usingRetained = true;
                        const RetainedOutputTrack& retained = retainedIt->second;
                        rect = cv::Rect(
                            static_cast<int>(std::round(retained.rect.x)),
                            static_cast<int>(std::round(retained.rect.y)),
                            static_cast<int>(std::round(retained.rect.width)),
                            static_cast<int>(std::round(retained.rect.height))
                        );
                        drawRectF = retained.rect;
                        center = glm::vec2(retained.rect.x + retained.rect.width * 0.5f,
                                           retained.rect.y + retained.rect.height * 0.5f);
                        area = retained.area;
                        age = retained.age;
                        vel = retained.velocity;
                        classId = retained.classId;
                        score = retained.score;
                        hasGeometry = true;
                    }
                }

                if (!hasGeometry) {
                    i++;
                    continue;
                }

                if (drawRectF.width <= 0.0f || drawRectF.height <= 0.0f) {
                    drawRectF = cv::Rect2f(rect.x, rect.y, rect.width, rect.height);
                }

                ofPushStyle();
                ofPushMatrix();
                ofSetLineWidth(1);
                ofSetColor(usingRetained ? ofColor(255, 170, 0) : ofColor(255, 0, 0));
                ofNoFill();
                if (trackingTechnique == 0 && index != -1) {
                    ofPolyline & poly = finder.getPolyline(index);
                    poly.draw();
                }
                ofTranslate(center.x, center.y);
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofSetColor(usingRetained ? ofColor(255, 170, 0) : ofColor(255, 0, 0));
                ofDrawRectangle(0, 0, drawRectF.width + 5.0f, drawRectF.height + 4.0f);
                {
                    std::stringstream ss;
                    ss << label << ":" << age;
                    ofDrawBitmapString(ss.str(), -(drawRectF.width * 0.5f) - 15.0f, (drawRectF.height * 0.5f) + 15.0f);
                }
                if (trackingTechnique == 1 && yoloDrawClassNames) {
                    ofDrawBitmapString(yoloClassName(classId) + " " + ofToString(score, 2),
                                       -(drawRectF.width * 0.5f),
                                       -(drawRectF.height * 0.5f) - 6.0f);
                }
                ofPopMatrix();
                ofPopStyle();
            
                // Heatmap
                addPointToHeatmap(center.x/receiverW, center.y/receiverH, area);
                
                i++;
            }
            
            ofPopMatrix();
            senderBlob.end();
        }

        int getDisplayAgeForLabel(int label) override {
            if (trackingTechnique == 1) {
                return yoloTrackAgeForLabel(label);
            }
            return finder.getTracker().getAge(label);
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

            syncYoloRawModeState();

            if (yoloRawMode) {
                std::vector<cv::Rect> detections;
                std::vector<int> classIds;
                std::vector<float> scores;
                yoloFrameCounter++;
                yoloLastFrameSize = currentMat.size();
                runYolo(currentMat, detections, classIds, scores);
                updateYoloPreviewImage(currentMat);

                yoloCurrentRects.clear();
                yoloCurrentClassIds.clear();
                yoloCurrentScores.clear();
                selectedBlobs.clear();
                for (std::size_t i = 0; i < detections.size(); ++i) {
                    const int label = 1000 + static_cast<int>(i);
                    yoloCurrentRects[label] = detections[i];
                    if (i < classIds.size()) yoloCurrentClassIds[label] = classIds[i];
                    if (i < scores.size()) yoloCurrentScores[label] = scores[i];
                    if (selectedBlobs.size() < static_cast<std::size_t>(maxBlobNum)) {
                        selectedBlobs.push_back(label);
                    }
                }
                return;
            }

            std::vector<cv::Rect> detections;
            std::vector<int> classIds;
            std::vector<float> scores;
            yoloFrameCounter++;
            yoloLastFrameSize = currentMat.size();
            updateYoloPreviewImage(currentMat);

            const bool shouldRunInference =
                yoloTracks.empty() ||
                yoloInferenceInterval <= 1 ||
                ((yoloFrameCounter - 1) % yoloInferenceInterval) == 0;

            if (shouldRunInference) {
                runYoloForTracking(currentMat, detections, classIds, scores);
                updateYoloTrackIds(detections, classIds, scores);
            } else {
                advanceYoloTracksWithoutInference();
            }

            processYoloTrackedResults(currentMat);
        }

        bool ensureYoloLoaded() {
            const YoloDetectorConfig config = makeYoloConfig();
            const std::string modelKey = config.coreMlModelPath + "|" + config.onnxModelPath;
            if (yoloLoaded && modelKey == yoloLoadedPath && yoloDetector) {
                return true;
            }
            resetYoloBackend();
            yoloLoadedPath = modelKey;

            std::vector<std::string> loadErrors;

#ifdef __APPLE__
            if (ofFile::doesFileExist(config.coreMlModelPath)) {
                auto detector = createCoreMLYoloDetector();
                std::string error;
                if (detector && detector->load(config, error)) {
                    yoloDetector = std::move(detector);
                } else if (!error.empty()) {
                    loadErrors.push_back("Core ML: " + error);
                }
            }
#endif

            if (!yoloDetector && ofFile::doesFileExist(config.onnxModelPath)) {
                auto detector = createOpenCvYoloDetector();
                std::string error;
                if (detector && detector->load(config, error)) {
                    yoloDetector = std::move(detector);
                } else if (!error.empty()) {
                    loadErrors.push_back("OpenCV: " + error);
                }
            }

            if (yoloDetector) {
                yoloLoaded = true;
                yoloLoadedBackendName = yoloDetector->backendName();
                yoloModelWarned = false;
                ofLogNotice("Tracker") << "Loaded YOLO backend: " << yoloLoadedBackendName;
                std::cout << "Loaded YOLO backend: " << yoloLoadedBackendName << std::endl;
                return true;
            }

            if (!yoloModelWarned) {
                std::ostringstream oss;
                oss << "No usable YOLO backend found.";
                if (!config.coreMlModelPath.empty()) {
                    oss << " Core ML: " << config.coreMlModelPath;
                }
                if (!config.onnxModelPath.empty()) {
                    oss << " ONNX: " << config.onnxModelPath;
                }
                if (!loadErrors.empty()) {
                    oss << " Errors: ";
                    for (std::size_t i = 0; i < loadErrors.size(); ++i) {
                        if (i > 0) oss << " | ";
                        oss << loadErrors[i];
                    }
                }
                oss << " Falling back to Blob tracking.";
                ofLogWarning("Tracker") << oss.str();
                std::cout << oss.str() << std::endl;
                yoloModelWarned = true;
            }
            return false;
        }

        void resetYoloBackend() {
            yoloDetector.reset();
            yoloLoaded = false;
            yoloModelWarned = false;
            yoloLoadedPath.clear();
            yoloLoadedBackendName.clear();
            yoloFrameCounter = 0;
            yoloTracks.clear();
            yoloNextTrackId = 1;
            yoloStableDetections.clear();
            yoloSlotMemoryTracks.clear();
            yoloSlotVisualTrackers.clear();
            retainedOutputTracks.clear();
            yoloCurrentRects.clear();
            yoloCurrentClassIds.clear();
            yoloCurrentScores.clear();
        }

        void syncYoloRawModeState() {
            if (yoloRawMode == yoloRawModeActive) return;

            if (!noteOnSentMap.empty()) {
                std::vector<int> labelsToClear;
                labelsToClear.reserve(noteOnSentMap.size());
                for (const auto& kv : noteOnSentMap) {
                    labelsToClear.push_back(kv.first);
                }
                for (const int label : labelsToClear) {
                    if (needNoteOff(label)) {
                        sendDeathNow(label);
                        sendNoteOff(label);
                    }
                }
            }

            selectedBlobs.clear();
            noteOnSentMap.clear();
            yoloSlotMemoryTracks.clear();
            yoloSlotVisualTrackers.clear();
            retainedOutputTracks.clear();
            yoloTracks.clear();
            yoloStableDetections.clear();
            yoloCurrentRects.clear();
            yoloCurrentClassIds.clear();
            yoloCurrentScores.clear();
            prevSelectedBlobCount = 0;
            prevSelectedCenters.clear();
            prevSelectedAreas.clear();
            prevSelectedRects.clear();
            yoloNextTrackId = 1;
            yoloRawModeActive = yoloRawMode;
        }

        YoloDetectorConfig makeYoloConfig() const {
            YoloDetectorConfig config;
            config.onnxModelPath = yoloModelPath.get();
            config.coreMlModelPath = yoloCoreMLModelPath.get();
            config.inputSize = yoloInputSize.get();
            config.confidenceThreshold = yoloConfidenceThreshold.get();
            config.nmsThreshold = yoloNmsThreshold.get();
            config.classFilter = parsedYoloClassFilter();
            return config;
        }

        YoloDetectorConfig makeYoloTrackingConfig() const {
            YoloDetectorConfig config = makeYoloConfig();
            // Let tracking see all detector classes, then map the live tracks to the
            // constrained display labels afterwards. Filtering inside the detector was
            // causing the third object to disappear whenever YOLO briefly guessed a
            // non-target class like "kite" or "sports ball".
            config.classFilter.clear();
            return config;
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

        bool useThreeClassSceneLabeling() const {
            const auto filter = parsedYoloClassFilter();
            return filter.size() == 3 &&
                   filter.count("person") > 0 &&
                   filter.count("car") > 0 &&
                   filter.count("cat") > 0;
        }

        int sceneGeometryClassId(const cv::Rect2f& rect) const {
            if (yoloLastFrameSize.width > 0 && yoloLastFrameSize.height > 0) {
                const float frameArea = static_cast<float>(yoloLastFrameSize.width * yoloLastFrameSize.height);
                const float areaFraction = rectArea(rect) / std::max(frameArea, 1.0f);
                const bool touchesHorizontalEdge =
                    rect.x <= 8.0f ||
                    (rect.x + rect.width) >= (static_cast<float>(yoloLastFrameSize.width) - 8.0f);
                if (areaFraction >= 0.05f || (touchesHorizontalEdge && areaFraction >= 0.03f)) {
                    return 2; // car
                }
            }
            const float aspect = rectAspect(rect);
            if (aspect >= 1.25f) return 2;  // car
            if (aspect <= 0.72f) return 0;  // person
            return 15;                      // cat
        }

        bool detectionLooksImplausiblyLargeForThreeScene(const cv::Rect2f& rect) const {
            if (!useThreeClassSceneLabeling()) return false;
            if (yoloLastFrameSize.width <= 0 || yoloLastFrameSize.height <= 0) return false;

            const float frameWidth = static_cast<float>(yoloLastFrameSize.width);
            const float frameHeight = static_cast<float>(yoloLastFrameSize.height);
            const float frameArea = std::max(frameWidth * frameHeight, 1.0f);
            const float areaFraction = rectArea(rect) / frameArea;
            const float widthFraction = rect.width / frameWidth;
            const float heightFraction = rect.height / frameHeight;

            return areaFraction >= 0.18f ||
                   widthFraction >= 0.62f ||
                   heightFraction >= 0.72f;
        }

        int preferredDisplayClassId(const YoloTrack& track, const cv::Rect2f& rect) const {
            if (!useThreeClassSceneLabeling()) return track.classId;

            // In the constrained sender scene we only care about person / car / cat.
            // The pretrained detector keeps churning through unrelated COCO labels,
            // but the track geometry is far more stable than the raw class guesses.
            // Use the persistent track shape as the display label source.
            return sceneGeometryClassId(rect);
        }

        std::map<int, int> assignThreeSceneSlotLabels(const std::map<int, cv::Rect>& slotRects) const {
            std::map<int, int> result;
            if (!useThreeClassSceneLabeling() || slotRects.empty() ||
                yoloLastFrameSize.width <= 0 || yoloLastFrameSize.height <= 0) {
                return result;
            }

            struct SlotScores {
                int slot = -1;
                float car = 0.0f;
                float person = 0.0f;
                float cat = 0.0f;
            };

            std::vector<SlotScores> scores;
            scores.reserve(slotRects.size());
            const float frameWidth = static_cast<float>(yoloLastFrameSize.width);
            const float frameHeight = static_cast<float>(yoloLastFrameSize.height);
            const float frameArea = std::max(frameWidth * frameHeight, 1.0f);

            for (const auto& kv : slotRects) {
                const cv::Rect& rect = kv.second;
                const float width = std::max(rect.width, 1);
                const float height = std::max(rect.height, 1);
                const float aspect = width / height;
                const float widthFrac = width / frameWidth;
                const float heightFrac = height / frameHeight;
                const float areaFrac = (width * height) / frameArea;
                const bool touchesHorizontalEdge =
                    rect.x <= 8 || (rect.x + rect.width) >= (yoloLastFrameSize.width - 8);

                SlotScores s;
                s.slot = kv.first;
                s.car = (areaFrac * 10.0f) + (aspect * 2.5f) + (touchesHorizontalEdge ? 0.8f : 0.0f);
                s.person = (heightFrac * 3.0f) + ((1.0f / std::max(aspect, 0.25f)) * 1.8f) - (areaFrac * 2.0f);
                s.cat = (1.5f - std::abs(aspect - 0.95f) * 2.0f) + ((0.035f - std::abs(areaFrac - 0.035f)) * 14.0f) - (heightFrac * 0.5f);
                scores.push_back(s);
            }

            auto remaining = scores;
            auto takeBest = [&](auto scoreFn, int classId) {
                if (remaining.empty()) return;
                auto bestIt = std::max_element(remaining.begin(), remaining.end(), [&](const SlotScores& a, const SlotScores& b) {
                    return scoreFn(a) < scoreFn(b);
                });
                result[bestIt->slot] = classId;
                remaining.erase(bestIt);
            };

            if (remaining.size() >= 3) {
                takeBest([](const SlotScores& s) { return s.car; }, 2);
                takeBest([](const SlotScores& s) { return s.person; }, 0);
                if (!remaining.empty()) {
                    result[remaining.front().slot] = 15;
                    remaining.clear();
                }
            } else if (remaining.size() == 2) {
                takeBest([](const SlotScores& s) { return s.car; }, 2);
                if (!remaining.empty()) {
                    const SlotScores& last = remaining.front();
                    result[last.slot] = (last.person >= last.cat) ? 0 : 15;
                }
                remaining.clear();
            } else if (remaining.size() == 1) {
                const SlotScores& only = remaining.front();
                if (only.car >= only.person && only.car >= only.cat) {
                    result[only.slot] = 2;
                } else if (only.person >= only.cat) {
                    result[only.slot] = 0;
                } else {
                    result[only.slot] = 15;
                }
                remaining.clear();
            }

            return result;
        }

        void resetTrackClassVotes(struct YoloTrack& track) {
            track.classVotes.fill(0.0f);
        }

        void seedTrackClassVote(struct YoloTrack& track, int classId, float weight) {
            resetTrackClassVotes(track);
            if (classId < 0 || classId >= kYoloClassCount) {
                track.classId = classId;
                return;
            }
            track.classVotes[static_cast<std::size_t>(classId)] = std::max(weight, 1.0f);
            track.classId = classId;
        }

        void reinforceTrackClass(struct YoloTrack& track, int classId, float score) {
            if (classId < 0 || classId >= kYoloClassCount) return;

            for (float& vote : track.classVotes) {
                vote *= yoloTrackClassVoteDecay;
            }

            track.classVotes[static_cast<std::size_t>(classId)] += std::max(score, yoloTrackClassVoteMinWeight);

            int bestClassId = track.classId;
            float bestVote = -1.0f;
            for (int i = 0; i < kYoloClassCount; ++i) {
                const float vote = track.classVotes[static_cast<std::size_t>(i)];
                if (vote > bestVote) {
                    bestVote = vote;
                    bestClassId = i;
                }
            }
            track.classId = bestClassId;
        }

        void pruneDuplicateYoloTracks() {
            std::vector<int> ids;
            ids.reserve(yoloTracks.size());
            for (const auto& kv : yoloTracks) {
                ids.push_back(kv.first);
            }

            std::set<int> drop;
            for (std::size_t i = 0; i < ids.size(); ++i) {
                const int aId = ids[i];
                if (drop.count(aId) > 0) continue;
                auto aIt = yoloTracks.find(aId);
                if (aIt == yoloTracks.end()) continue;

                for (std::size_t j = i + 1; j < ids.size(); ++j) {
                    const int bId = ids[j];
                    if (drop.count(bId) > 0) continue;
                    auto bIt = yoloTracks.find(bId);
                    if (bIt == yoloTracks.end()) continue;

                    const YoloTrack& a = aIt->second;
                    const YoloTrack& b = bIt->second;
                    if (!rectLooksLikeDuplicateTrack(a.rect, b.rect)) continue;

                    const int aOwnedSlot = slotForYoloSourceTrack(aId);
                    const int bOwnedSlot = slotForYoloSourceTrack(bId);
                    if (aOwnedSlot > 0 && bOwnedSlot > 0 && aOwnedSlot != bOwnedSlot) {
                        continue;
                    }
                    if (aOwnedSlot > 0 && bOwnedSlot <= 0) {
                        drop.insert(bId);
                        continue;
                    }
                    if (bOwnedSlot > 0 && aOwnedSlot <= 0) {
                        drop.insert(aId);
                        break;
                    }

                    const float aRank = (a.visibleThisFrame ? 10.0f : 0.0f) + (a.hits * 0.25f) + a.score;
                    const float bRank = (b.visibleThisFrame ? 10.0f : 0.0f) + (b.hits * 0.25f) + b.score;
                    drop.insert(aRank >= bRank ? bId : aId);
                    if (drop.count(aId) > 0) break;
                }
            }

            for (const int id : drop) {
                yoloTracks.erase(id);
            }
        }

        glm::vec2 rectCenter(const cv::Rect2f& rect) const {
            return glm::vec2(rect.x + rect.width * 0.5f, rect.y + rect.height * 0.5f);
        }

        float rectArea(const cv::Rect2f& rect) const {
            return std::max(rect.width, 0.0f) * std::max(rect.height, 0.0f);
        }

        float rectAspect(const cv::Rect2f& rect) const {
            const float h = std::max(rect.height, 1.0f);
            return std::max(rect.width, 1.0f) / h;
        }

        bool rectGeometryCompatible(const cv::Rect2f& a,
                                    const cv::Rect2f& b,
                                    float maxAreaRatio,
                                    float maxAspectRatioChange) const {
            const float areaA = rectArea(a);
            const float areaB = rectArea(b);
            const float areaRatio = std::max(areaA, areaB) / std::max(std::min(areaA, areaB), 1.0f);
            const float aspectA = rectAspect(a);
            const float aspectB = rectAspect(b);
            const float aspectRatioChange = std::max(aspectA, aspectB) / std::max(std::min(aspectA, aspectB), 0.05f);
            return areaRatio <= maxAreaRatio && aspectRatioChange <= maxAspectRatioChange;
        }

        bool rectStepSizeCompatible(const cv::Rect2f& a,
                                    const cv::Rect2f& b,
                                    float maxWidthRatio,
                                    float maxHeightRatio) const {
            const float widthRatio = std::max(a.width, b.width) / std::max(std::min(a.width, b.width), 1.0f);
            const float heightRatio = std::max(a.height, b.height) / std::max(std::min(a.height, b.height), 1.0f);
            return widthRatio <= maxWidthRatio && heightRatio <= maxHeightRatio;
        }

        bool rectLikelySameObject(const cv::Rect2f& a,
                                  const cv::Rect2f& b,
                                  float minIou,
                                  float centerDistanceFactor,
                                  float minCenterDistancePx,
                                  float maxAreaRatio,
                                  float maxAspectRatioChange) const {
            if (!rectGeometryCompatible(a, b, maxAreaRatio, maxAspectRatioChange)) {
                return false;
            }

            const float iou = rectIou(a, b);
            if (iou >= minIou) {
                return true;
            }

            const float diag = std::max(glm::length(glm::vec2(a.width, a.height)),
                                        glm::length(glm::vec2(b.width, b.height)));
            const float allowedDistance = std::max(diag * centerDistanceFactor, minCenterDistancePx);
            const float centerDistance = glm::distance(rectCenter(a), rectCenter(b));
            return centerDistance <= allowedDistance;
        }

        bool rectDefinitelyReacquired(const cv::Rect2f& a, const cv::Rect2f& b) const {
            if (!rectGeometryCompatible(a, b, 1.6f, 1.35f)) {
                return false;
            }

            const float iou = rectIou(a, b);
            if (iou >= 0.65f) {
                return true;
            }

            const float diag = std::max(glm::length(glm::vec2(a.width, a.height)),
                                        glm::length(glm::vec2(b.width, b.height)));
            const float centerDistance = glm::distance(rectCenter(a), rectCenter(b));
            const float allowedDistance = std::max(diag * 0.18f, 16.0f);
            return iou >= 0.35f && centerDistance <= allowedDistance;
        }

        bool rectLooksLikeDuplicateTrack(const cv::Rect2f& a, const cv::Rect2f& b) const {
            if (!rectGeometryCompatible(a, b, 1.7f, 1.45f)) {
                return false;
            }

            const float iou = rectIou(a, b);
            const float centerDistance = glm::distance(rectCenter(a), rectCenter(b));
            const float diag = std::max(glm::length(glm::vec2(a.width, a.height)),
                                        glm::length(glm::vec2(b.width, b.height)));
            return rectDefinitelyReacquired(a, b) ||
                   iou >= 0.72f ||
                   (iou >= 0.52f && centerDistance <= std::max(diag * 0.14f, 14.0f));
        }

        float rectIou(const cv::Rect2f& a, const cv::Rect2f& b) const {
            const float x1 = std::max(a.x, b.x);
            const float y1 = std::max(a.y, b.y);
            const float x2 = std::min(a.x + a.width, b.x + b.width);
            const float y2 = std::min(a.y + a.height, b.y + b.height);
            const float intersection = std::max(0.0f, x2 - x1) * std::max(0.0f, y2 - y1);
            const float unionArea = a.width * a.height + b.width * b.height - intersection;
            if (unionArea <= 0.0f) return 0.0f;
            return intersection / unionArea;
        }

        cv::Rect2f lerpRect(const cv::Rect2f& from, const cv::Rect2f& to, float alpha) const {
            return cv::Rect2f(
                ofLerp(from.x, to.x, alpha),
                ofLerp(from.y, to.y, alpha),
                ofLerp(from.width, to.width, alpha),
                ofLerp(from.height, to.height, alpha)
            );
        }

        cv::Rect2f blendTrackedRect(const cv::Rect2f& from, const cv::Rect2f& to) const {
            const float posAlpha = yoloTrackRectSmoothing;
            const float sizeAlpha = useThreeClassSceneLabeling() ? 0.32f : yoloTrackRectSmoothing;
            return cv::Rect2f(
                ofLerp(from.x, to.x, posAlpha),
                ofLerp(from.y, to.y, posAlpha),
                ofLerp(from.width, to.width, sizeAlpha),
                ofLerp(from.height, to.height, sizeAlpha)
            );
        }

        cv::Rect2f smoothOutputRect(const cv::Rect2f& from, const cv::Rect2f& to, float alpha) const {
            cv::Rect2f smoothed = lerpRect(from, to, ofClamp(alpha, 0.0f, 1.0f));
            const glm::vec2 fromCenter = rectCenter(from);
            const glm::vec2 toCenter = rectCenter(smoothed);
            const glm::vec2 delta = toCenter - fromCenter;
            const float distance = glm::length(delta);
            const float diag = std::max(glm::length(glm::vec2(from.width, from.height)),
                                        glm::length(glm::vec2(to.width, to.height)));
            const float maxStep = std::max(diag * 0.42f, 42.0f);
            if (distance > maxStep && distance > 0.0001f) {
                const glm::vec2 limitedCenter = fromCenter + (delta / distance) * maxStep;
                smoothed.x = limitedCenter.x - smoothed.width * 0.5f;
                smoothed.y = limitedCenter.y - smoothed.height * 0.5f;
            }
            return clampRectToFrame(smoothed, yoloLastFrameSize);
        }

        cv::Rect2f offsetRect(const cv::Rect2f& rect, const glm::vec2& offset) const {
            return cv::Rect2f(rect.x + offset.x, rect.y + offset.y, rect.width, rect.height);
        }

        cv::Rect2f clampRectToFrame(const cv::Rect2f& rect, const cv::Size& frameSize) const {
            if (frameSize.width <= 0 || frameSize.height <= 0) return rect;
            const float width = std::min(rect.width, static_cast<float>(frameSize.width));
            const float height = std::min(rect.height, static_cast<float>(frameSize.height));
            return cv::Rect2f(
                ofClamp(rect.x, 0.0f, std::max(0.0f, static_cast<float>(frameSize.width) - width)),
                ofClamp(rect.y, 0.0f, std::max(0.0f, static_cast<float>(frameSize.height) - height)),
                width,
                height
            );
        }

        void updateYoloPreviewImage(const cv::Mat& currentMat) {
            const bool sizeChanged = !yoloPreviewImage.isAllocated() ||
                                     yoloPreviewImage.getWidth() != currentMat.cols ||
                                     yoloPreviewImage.getHeight() != currentMat.rows;
            if (!sizeChanged && (yoloFrameCounter % yoloPreviewUpdateInterval) != 0) {
                return;
            }
            yoloPreviewImage.setFromPixels(currentMat.data, currentMat.cols, currentMat.rows, OF_IMAGE_COLOR);
            yoloPreviewImage.update();
        }

        int yoloTrackAgeForLabel(int label) const {
            auto trackIt = yoloTracks.find(label);
            if (trackIt != yoloTracks.end()) {
                return trackIt->second.age;
            }
            auto memoryIt = yoloSlotMemoryTracks.find(label);
            if (memoryIt != yoloSlotMemoryTracks.end()) {
                return memoryIt->second.age;
            }
            auto retainedIt = retainedOutputTracks.find(label);
            if (retainedIt != retainedOutputTracks.end()) {
                return retainedIt->second.age;
            }
            return 0;
        }

        int yoloSlotMemoryRetentionFrames() const {
            // Keep hidden slot identity alive longer than visible box hold so a
            // temporarily lost object can reclaim its slot after a messy crossover
            // without leaving a ghost box on screen.
            return std::max(yoloTrackMaxMissedFrames * 8, getTrackHoldFrames());
        }

        int yoloVisualRetentionFramesForSlot(int slot) const {
            // Keep musical/note hold independent from spatial hold.
            // Long visual retention was letting slots ghost in empty space for seconds,
            // which made both the picture and OSC coordinates feel wrong.
            (void)slot;
            return static_cast<int>(ofMap(trackHoldStrictness, 0.0f, 100.0f, 8.0f, 2.0f, true));
        }

        int yoloSourcePredictionMissesForSlot(int slot) const {
            (void)slot;
            // A slot's own source track should be allowed to coast through
            // crossovers/temporary YOLO misses. The visual ghost guard remains
            // separate, so unowned empty-space retention is still short.
            return std::max(12, yoloTrackMaxMissedFrames - 4);
        }

        int slotForYoloSourceTrack(int trackId) const {
            for (const auto& kv : yoloSlotMemoryTracks) {
                if (kv.second.sourceTrackId == trackId) {
                    return kv.first;
                }
            }
            return -1;
        }

        int yoloVisualTrackerRetentionFrames() const {
            return 240;
        }

        cv::Rect safeTrackerInitRect(const cv::Rect2f& rect, const cv::Size& frameSize) const {
            cv::Rect2f clamped = clampRectToFrame(rect, frameSize);
            clamped.width = std::max(clamped.width, 8.0f);
            clamped.height = std::max(clamped.height, 8.0f);
            clamped.x = ofClamp(clamped.x, 0.0f, std::max(0.0f, static_cast<float>(frameSize.width) - clamped.width));
            clamped.y = ofClamp(clamped.y, 0.0f, std::max(0.0f, static_cast<float>(frameSize.height) - clamped.height));
            cv::Rect out(
                static_cast<int>(std::round(clamped.x)),
                static_cast<int>(std::round(clamped.y)),
                static_cast<int>(std::round(clamped.width)),
                static_cast<int>(std::round(clamped.height))
            );
            return out & cv::Rect(0, 0, frameSize.width, frameSize.height);
        }

        bool initSlotVisualTracker(int slot, const cv::Mat& frame, const cv::Rect2f& rect) {
            if (slot < 1 || slot > maxBlobNum || frame.empty()) return false;
            if (rect.width < 8.0f || rect.height < 8.0f) return false;
            if (detectionLooksImplausiblyLargeForThreeScene(rect)) return false;

            cv::Rect initRect = safeTrackerInitRect(rect, frame.size());
            if (initRect.width < 8 || initRect.height < 8) return false;

            SlotVisualTracker visualTracker;
            cv::Mat gray;
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            initRect = initRect & cv::Rect(0, 0, gray.cols, gray.rows);
            if (initRect.width < 8 || initRect.height < 8) return false;
            try {
                visualTracker.templateGray = gray(initRect).clone();
            } catch (...) {
                return false;
            }
            if (visualTracker.templateGray.empty()) return false;

            visualTracker.initialized = true;
            visualTracker.lastRect = cv::Rect2f(initRect.x, initRect.y, initRect.width, initRect.height);
            visualTracker.framesSinceYolo = 0;
            yoloSlotVisualTrackers[slot] = visualTracker;
            return true;
        }

        bool updateSlotVisualTracker(int slot, const cv::Mat& frame, cv::Rect2f& outRect, glm::vec2& outVelocity) {
            auto trackerIt = yoloSlotVisualTrackers.find(slot);
            if (trackerIt == yoloSlotVisualTrackers.end() || !trackerIt->second.initialized || frame.empty()) {
                return false;
            }

            SlotVisualTracker& visualTracker = trackerIt->second;
            if (visualTracker.templateGray.empty()) {
                visualTracker.initialized = false;
                return false;
            }

            cv::Mat gray;
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

            const float basePadding =
                std::max(visualTracker.lastRect.width, visualTracker.lastRect.height) *
                (1.35f + std::min(visualTracker.framesSinceYolo, 90) * 0.018f);
            cv::Rect2f searchRectF(
                visualTracker.lastRect.x - basePadding,
                visualTracker.lastRect.y - basePadding,
                visualTracker.lastRect.width + basePadding * 2.0f,
                visualTracker.lastRect.height + basePadding * 2.0f
            );
            searchRectF = clampRectToFrame(searchRectF, frame.size());
            cv::Rect searchRect(
                static_cast<int>(std::round(searchRectF.x)),
                static_cast<int>(std::round(searchRectF.y)),
                static_cast<int>(std::round(searchRectF.width)),
                static_cast<int>(std::round(searchRectF.height))
            );
            searchRect = searchRect & cv::Rect(0, 0, gray.cols, gray.rows);
            if (searchRect.width < 12 || searchRect.height < 12) {
                visualTracker.initialized = false;
                return false;
            }

            cv::Mat searchImage;
            try {
                searchImage = gray(searchRect);
            } catch (...) {
                visualTracker.initialized = false;
                return false;
            }
            double bestScore = -1.0;
            cv::Rect bestRect;
            const std::array<float, 5> scales{{0.80f, 0.92f, 1.0f, 1.10f, 1.22f}};
            for (const float scale : scales) {
                cv::Mat templateImage;
                if (std::abs(scale - 1.0f) < 0.001f) {
                    templateImage = visualTracker.templateGray;
                } else {
                    cv::resize(visualTracker.templateGray, templateImage, cv::Size(), scale, scale, cv::INTER_LINEAR);
                }
                if (templateImage.cols < 8 || templateImage.rows < 8) continue;
                if (templateImage.cols > searchImage.cols || templateImage.rows > searchImage.rows) continue;

                cv::Mat matchResult;
                cv::matchTemplate(searchImage, templateImage, matchResult, cv::TM_CCOEFF_NORMED);
                double minVal = 0.0;
                double maxVal = 0.0;
                cv::Point minLoc;
                cv::Point maxLoc;
                cv::minMaxLoc(matchResult, &minVal, &maxVal, &minLoc, &maxLoc);
                if (maxVal > bestScore) {
                    bestScore = maxVal;
                    bestRect = cv::Rect(
                        searchRect.x + maxLoc.x,
                        searchRect.y + maxLoc.y,
                        templateImage.cols,
                        templateImage.rows
                    );
                }
            }

            const double minScore = useThreeClassSceneLabeling() ? 0.24 : 0.28;
            if (bestScore < minScore || bestRect.width <= 0 || bestRect.height <= 0) {
                visualTracker.initialized = false;
                return false;
            }

            cv::Rect2f trackedRectF(bestRect.x, bestRect.y, bestRect.width, bestRect.height);
            trackedRectF = clampRectToFrame(trackedRectF, frame.size());
            if (trackedRectF.width < 8.0f || trackedRectF.height < 8.0f) {
                visualTracker.initialized = false;
                return false;
            }
            if (detectionLooksImplausiblyLargeForThreeScene(trackedRectF)) {
                visualTracker.initialized = false;
                return false;
            }

            auto memoryIt = yoloSlotMemoryTracks.find(slot);
            if (memoryIt != yoloSlotMemoryTracks.end()) {
                const RetainedOutputTrack& memoryTrack = memoryIt->second;
                const float maxAreaRatio = useThreeClassSceneLabeling() ? 4.0f : 5.0f;
                const float maxAspectRatio = useThreeClassSceneLabeling() ? 3.2f : 4.0f;
                if (!rectGeometryCompatible(memoryTrack.rect, trackedRectF, maxAreaRatio, maxAspectRatio)) {
                    visualTracker.initialized = false;
                    return false;
                }
            }

            outVelocity = rectCenter(trackedRectF) - rectCenter(visualTracker.lastRect);
            outRect = trackedRectF;
            visualTracker.lastRect = trackedRectF;
            visualTracker.framesSinceYolo++;

            cv::Rect updateRect = safeTrackerInitRect(trackedRectF, frame.size());
            updateRect = updateRect & cv::Rect(0, 0, gray.cols, gray.rows);
            if (updateRect.width == visualTracker.templateGray.cols &&
                updateRect.height == visualTracker.templateGray.rows &&
                updateRect.x >= 0 && updateRect.y >= 0 &&
                (updateRect.x + updateRect.width) <= gray.cols &&
                (updateRect.y + updateRect.height) <= gray.rows) {
                try {
                    cv::Mat freshTemplate = gray(updateRect);
                    cv::addWeighted(visualTracker.templateGray, 0.96, freshTemplate, 0.04, 0.0, visualTracker.templateGray);
                } catch (...) {
                    visualTracker.initialized = false;
                }
            }
            return true;
        }

        const cv::Rect2f* lastKnownRectForLabel(int label) const {
            auto memoryIt = yoloSlotMemoryTracks.find(label);
            if (memoryIt != yoloSlotMemoryTracks.end()) {
                return &memoryIt->second.rect;
            }

            auto prevRectIt = prevSelectedRects.find(label);
            if (prevRectIt != prevSelectedRects.end()) {
                static thread_local cv::Rect2f prevRect;
                prevRect = cv::Rect2f(prevRectIt->second.x,
                                      prevRectIt->second.y,
                                      prevRectIt->second.width,
                                      prevRectIt->second.height);
                return &prevRect;
            }

            auto retainedIt = retainedOutputTracks.find(label);
            if (retainedIt != retainedOutputTracks.end()) {
                return &retainedIt->second.rect;
            }
            return nullptr;
        }

        std::vector<int> rebindPreferredYoloTrackIds(const std::vector<int>& activeTrackIds,
                                                     const std::vector<int>& prevSelectedLabels) {
            struct RebindCandidate {
                float score = 0.0f;
                int previousLabel = -1;
                int trackId = -1;
            };

            std::set<int> remainingTracks(activeTrackIds.begin(), activeTrackIds.end());
            std::vector<int> preferredTrackIds;
            preferredTrackIds.reserve(prevSelectedLabels.size());

            for (const int previousLabel : prevSelectedLabels) {
                if (remainingTracks.erase(previousLabel) > 0) {
                    preferredTrackIds.push_back(previousLabel);
                }
            }

            std::vector<RebindCandidate> candidates;
            for (const int previousLabel : prevSelectedLabels) {
                if (std::find(preferredTrackIds.begin(), preferredTrackIds.end(), previousLabel) != preferredTrackIds.end()) {
                    continue;
                }

                const cv::Rect2f* previousRectPtr = lastKnownRectForLabel(previousLabel);
                if (!previousRectPtr) continue;
                const cv::Rect2f previousRect = *previousRectPtr;

                for (const int trackId : activeTrackIds) {
                    if (remainingTracks.count(trackId) == 0) continue;
                    auto rectIt = yoloCurrentRects.find(trackId);
                    if (rectIt == yoloCurrentRects.end()) continue;

                    const cv::Rect2f currentRect(rectIt->second.x,
                                                 rectIt->second.y,
                                                 rectIt->second.width,
                                                 rectIt->second.height);

                    if (!rectLikelySameObject(previousRect,
                                              currentRect,
                                              0.10f,
                                              0.60f,
                                              54.0f,
                                              2.6f,
                                              2.1f)) {
                        continue;
                    }

                    const float iou = rectIou(previousRect, currentRect);
                    const float diag = std::max(glm::length(glm::vec2(previousRect.width, previousRect.height)),
                                                glm::length(glm::vec2(currentRect.width, currentRect.height)));
                    const float allowedDistance = std::max(diag * 0.60f, 54.0f);
                    const float centerDistance = glm::distance(rectCenter(previousRect), rectCenter(currentRect));
                    const float closeness = 1.0f - std::min(centerDistance / std::max(allowedDistance, 1.0f), 1.0f);
                    candidates.push_back({(iou * 3.0f) + closeness, previousLabel, trackId});
                }
            }

            std::sort(candidates.begin(), candidates.end(), [](const RebindCandidate& a, const RebindCandidate& b) {
                return a.score > b.score;
            });

            std::set<int> reboundPrevLabels;
            for (const RebindCandidate& candidate : candidates) {
                if (remainingTracks.count(candidate.trackId) == 0) continue;
                if (reboundPrevLabels.count(candidate.previousLabel) > 0) continue;

                if (candidate.previousLabel != candidate.trackId) {
                    adoptLabelState(candidate.previousLabel, candidate.trackId);
                }
                preferredTrackIds.push_back(candidate.trackId);
                reboundPrevLabels.insert(candidate.previousLabel);
                remainingTracks.erase(candidate.trackId);
            }

            return preferredTrackIds;
        }

        bool tryAppendRetainedOutputTrack(int label,
                                          std::vector<int>& outputLabels,
                                          std::set<int>& activeLabels,
                                          std::map<int, glm::vec2>& outputCenters,
                                          std::map<int, float>& outputAreas,
                                          std::map<int, cv::Rect>& outputRects,
                                          int frameWidth,
                                          int frameHeight,
                                          bool preserveEvenIfNearby = false) {
            if (activeLabels.count(label) > 0) return false;
            auto retainedIt = retainedOutputTracks.find(label);
            if (retainedIt == retainedOutputTracks.end()) return false;

            RetainedOutputTrack& retained = retainedIt->second;
            if (!preserveEvenIfNearby) {
                for (const auto& currentRectKv : outputRects) {
                    if (currentRectKv.first == label) continue;
                    const cv::Rect2f currentRect(currentRectKv.second.x,
                                                 currentRectKv.second.y,
                                                 currentRectKv.second.width,
                                                 currentRectKv.second.height);
                    if (rectDefinitelyReacquired(retained.rect, currentRect)) {
                        return false;
                    }
                }
            }

            retained.missingFrames++;
            retained.age++;
            retained.rect = clampRectToFrame(offsetRect(retained.rect, retained.velocity * yoloOutputPredictionFactor), yoloLastFrameSize);
            retained.velocity *= yoloOutputVelocityDecay;
            if (retained.missingFrames > yoloOutputRetentionFrames) {
                retainedOutputTracks.erase(retainedIt);
                return false;
            }

            if (outputLabels.size() >= static_cast<std::size_t>(maxBlobNum)) {
                return false;
            }

            outputLabels.push_back(label);
            activeLabels.insert(label);

            cv::Rect rect(
                static_cast<int>(std::round(retained.rect.x)),
                static_cast<int>(std::round(retained.rect.y)),
                static_cast<int>(std::round(retained.rect.width)),
                static_cast<int>(std::round(retained.rect.height))
            );
            rect.x = ofClamp(rect.x, 0, std::max(0, frameWidth - rect.width));
            rect.y = ofClamp(rect.y, 0, std::max(0, frameHeight - rect.height));

            outputCenters[label] = glm::vec2(rect.x + rect.width * 0.5f,
                                             rect.y + rect.height * 0.5f);
            outputAreas[label] = retained.area;
            outputRects[label] = rect;
            return true;
        }

        void updateYoloTrackIds(const std::vector<cv::Rect>& boxes,
                                const std::vector<int>& classIds,
                                const std::vector<float>& confidences) {
            struct MatchCandidate {
                float score = 0.0f;
                int trackId = -1;
                int detectionIndex = -1;
            };

            const float primaryThreshold = std::max(yoloConfidenceThreshold.get(), yoloTrackPrimaryConfidenceFloor);
            std::vector<int> highConfidenceDetections;
            std::vector<int> lowConfidenceDetections;
            for (std::size_t i = 0; i < confidences.size(); ++i) {
                if (confidences[i] >= primaryThreshold) {
                    highConfidenceDetections.push_back(static_cast<int>(i));
                } else {
                    lowConfidenceDetections.push_back(static_cast<int>(i));
                }
            }

            std::map<int, cv::Rect2f> predictedRects;
            for (const auto& kv : yoloTracks) {
                const YoloTrack& track = kv.second;
                const float predictionFactor =
                    (track.missedFrames <= 2) ? yoloTrackPredictionFactor : 0.0f;
                predictedRects[kv.first] = clampRectToFrame(
                    offsetRect(track.rect, track.velocity * predictionFactor),
                    yoloLastFrameSize
                );
            }

            std::set<int> matchedTracks;
            std::set<int> matchedDetections;

            auto tryMatchDetections = [&](const std::vector<int>& detectionIndices, bool allowLowConfidenceRefresh) {
                std::vector<MatchCandidate> candidates;
                for (const int detectionIndex : detectionIndices) {
                    const cv::Rect2f incomingRect(boxes[detectionIndex].x,
                                                  boxes[detectionIndex].y,
                                                  boxes[detectionIndex].width,
                                                  boxes[detectionIndex].height);
                    if (detectionLooksImplausiblyLargeForThreeScene(incomingRect)) continue;
                    const int incomingClassId = detectionIndex < classIds.size() ? classIds[detectionIndex] : -1;
                    for (const auto& kv : yoloTracks) {
                        const int trackId = kv.first;
                        if (matchedTracks.count(trackId) > 0) continue;
                        const YoloTrack& track = kv.second;
                        const cv::Rect2f& predictedRect = predictedRects[trackId];
                        const float iou = rectIou(predictedRect, incomingRect);
                        const glm::vec2 predictedCenter = rectCenter(predictedRect);
                        const glm::vec2 incomingCenter = rectCenter(incomingRect);
                        const float centerDistance = glm::distance(predictedCenter, incomingCenter);
                        const float diag = std::max(glm::length(glm::vec2(predictedRect.width, predictedRect.height)),
                                                    glm::length(glm::vec2(incomingRect.width, incomingRect.height)));
                        const float allowedDistance = std::max(
                            diag * (yoloTrackCenterDistanceFactor + (track.missedFrames * 0.12f)),
                            yoloTrackMinCenterDistancePx + (track.missedFrames * 6.0f)
                        );
                        const bool geometryCompatible = rectGeometryCompatible(
                            predictedRect,
                            incomingRect,
                            yoloTrackMaxAreaRatio,
                            yoloTrackMaxAspectRatioChange
                        );
                        const bool stepCompatible = rectStepSizeCompatible(
                            predictedRect,
                            incomingRect,
                            useThreeClassSceneLabeling() ? 1.55f : 1.8f,
                            useThreeClassSceneLabeling() ? 1.55f : 1.8f
                        );
                        const bool spatialMatch =
                            (iou >= yoloTrackMinIou) ||
                            (centerDistance <= allowedDistance && geometryCompatible);
                        if (!spatialMatch || !stepCompatible) continue;

                        float score = (iou * 2.8f) +
                                      (1.0f - std::min(centerDistance / std::max(allowedDistance, 1.0f), 1.0f));
                        const float predictedArea = rectArea(predictedRect);
                        const float incomingArea = rectArea(incomingRect);
                        const float areaRatio = std::max(predictedArea, incomingArea) / std::max(std::min(predictedArea, incomingArea), 1.0f);
                        const float predictedAspect = rectAspect(predictedRect);
                        const float incomingAspect = rectAspect(incomingRect);
                        const float aspectRatioChange = std::max(predictedAspect, incomingAspect) / std::max(std::min(predictedAspect, incomingAspect), 0.05f);
                        score -= std::min((areaRatio - 1.0f) * 0.20f, 0.80f);
                        score -= std::min((aspectRatioChange - 1.0f) * 0.18f, 0.60f);
                        if (useThreeClassSceneLabeling()) {
                            const int predictedSceneClass = sceneGeometryClassId(predictedRect);
                            const int incomingSceneClass = sceneGeometryClassId(incomingRect);
                            if (predictedSceneClass == incomingSceneClass) {
                                score += 1.5f;
                            } else {
                                // In the constrained person/car/cat scene, a shape-class
                                // mismatch is usually a bad crossover steal, not a real
                                // identity change. Only tolerate it when the overlap is
                                // already very strong.
                                if (iou < 0.22f && centerDistance > std::max(allowedDistance * 0.28f, 22.0f)) {
                                    continue;
                                }
                                score -= 1.25f;
                            }
                        }
                        if (track.classId == incomingClassId) {
                            score += yoloTrackSameClassBonus;
                        }
                        if (!allowLowConfidenceRefresh && confidences[detectionIndex] < primaryThreshold) {
                            continue;
                        }
                        candidates.push_back({score, trackId, detectionIndex});
                    }
                }

                std::sort(candidates.begin(), candidates.end(), [](const MatchCandidate& a, const MatchCandidate& b) {
                    return a.score > b.score;
                });

                for (const MatchCandidate& candidate : candidates) {
                    if (matchedTracks.count(candidate.trackId) > 0) continue;
                    if (matchedDetections.count(candidate.detectionIndex) > 0) continue;

                    auto trackIt = yoloTracks.find(candidate.trackId);
                    if (trackIt == yoloTracks.end()) continue;

                    YoloTrack& track = trackIt->second;
                    const cv::Rect2f incomingRect(boxes[candidate.detectionIndex].x,
                                                  boxes[candidate.detectionIndex].y,
                                                  boxes[candidate.detectionIndex].width,
                                                  boxes[candidate.detectionIndex].height);
                    const int incomingClassId = candidate.detectionIndex < classIds.size() ? classIds[candidate.detectionIndex] : -1;
                    const float incomingScore = candidate.detectionIndex < confidences.size() ? confidences[candidate.detectionIndex] : 0.0f;
                    const glm::vec2 previousCenter = rectCenter(track.rect);
                    const glm::vec2 incomingCenter = rectCenter(incomingRect);
                    const glm::vec2 measuredVelocity = incomingCenter - previousCenter;

                    track.rect = blendTrackedRect(track.rect, incomingRect);
                    track.velocity = glm::mix(track.velocity, measuredVelocity, yoloTrackVelocitySmoothing);
                    track.score = std::max(incomingScore, ofLerp(track.score, incomingScore, yoloTrackScoreSmoothing));
                    track.age++;
                    track.hits++;
                    track.missedFrames = 0;
                    track.visibleThisFrame = true;

                    reinforceTrackClass(track, incomingClassId, incomingScore);
                    track.candidateClassId = -1;
                    track.candidateClassMatches = 0;

                    matchedTracks.insert(candidate.trackId);
                    matchedDetections.insert(candidate.detectionIndex);
                }
            };

            tryMatchDetections(highConfidenceDetections, false);
            tryMatchDetections(lowConfidenceDetections, true);

            for (auto& kv : yoloTracks) {
                if (matchedTracks.count(kv.first) > 0) continue;
                YoloTrack& track = kv.second;
                track.age++;
                track.missedFrames++;
                track.visibleThisFrame = false;
                track.rect = predictedRects[kv.first];
                track.velocity *= yoloTrackVelocityDecay;
                track.score *= yoloTrackScoreDecay;
                track.candidateClassId = -1;
                track.candidateClassMatches = 0;
            }

            for (std::size_t i = 0; i < boxes.size(); ++i) {
                if (matchedDetections.count(static_cast<int>(i)) > 0) continue;
                if (confidences[i] < primaryThreshold) continue;
                const cv::Rect2f incomingRect(boxes[i].x, boxes[i].y, boxes[i].width, boxes[i].height);
                if (detectionLooksImplausiblyLargeForThreeScene(incomingRect)) continue;
                bool overlapsExistingTrack = false;
                for (const auto& kv : yoloTracks) {
                    const cv::Rect2f predictedRect = predictedRects.count(kv.first) ? predictedRects.at(kv.first) : kv.second.rect;
                    if (rectLooksLikeDuplicateTrack(predictedRect, incomingRect)) {
                        overlapsExistingTrack = true;
                        break;
                    }
                }
                if (overlapsExistingTrack) continue;
                YoloTrack track;
                track.id = yoloNextTrackId++;
                track.rect = incomingRect;
                track.classId = i < classIds.size() ? classIds[i] : -1;
                track.score = i < confidences.size() ? confidences[i] : 0.0f;
                track.age = 1;
                track.hits = 1;
                track.missedFrames = 0;
                track.visibleThisFrame = true;
                seedTrackClassVote(track, track.classId, track.score);
                yoloTracks[track.id] = track;
            }

            std::vector<int> expiredTracks;
            for (const auto& kv : yoloTracks) {
                const YoloTrack& track = kv.second;
                const bool staleWeakTrack =
                    !track.visibleThisFrame &&
                    track.missedFrames > 18 &&
                    track.score < yoloTrackKeepScoreFactor;
                if (track.missedFrames > yoloTrackMaxMissedFrames || staleWeakTrack) {
                    expiredTracks.push_back(kv.first);
                }
            }
            for (const int trackId : expiredTracks) {
                yoloTracks.erase(trackId);
                yoloCurrentRects.erase(trackId);
                yoloCurrentClassIds.erase(trackId);
                yoloCurrentScores.erase(trackId);
            }

            pruneDuplicateYoloTracks();

            yoloCurrentRects.clear();
            yoloCurrentClassIds.clear();
            yoloCurrentScores.clear();
            for (const auto& kv : yoloTracks) {
                const YoloTrack& track = kv.second;
                if (track.hits < yoloTrackMinHits) continue;
                if (track.missedFrames > yoloOutputRetentionFrames) continue;
                if (!track.visibleThisFrame && track.score < yoloTrackKeepScoreFactor) continue;

                yoloCurrentRects[kv.first] = cv::Rect(
                    static_cast<int>(std::round(track.rect.x)),
                    static_cast<int>(std::round(track.rect.y)),
                    static_cast<int>(std::round(track.rect.width)),
                    static_cast<int>(std::round(track.rect.height))
                );
                yoloCurrentClassIds[kv.first] = preferredDisplayClassId(track, track.rect);
                yoloCurrentScores[kv.first] = track.score;
            }
        }

        void advanceYoloTracksWithoutInference() {
            std::vector<int> expiredTracks;

            for (auto& kv : yoloTracks) {
                YoloTrack& track = kv.second;
                track.age++;
                track.visibleThisFrame = false;
                track.rect = clampRectToFrame(
                    offsetRect(track.rect, track.velocity * yoloTrackPredictionFactor),
                    yoloLastFrameSize
                );
                track.velocity *= yoloTrackVelocityDecay;
                track.candidateClassId = -1;
                track.candidateClassMatches = 0;

                const bool staleWeakTrack =
                    track.missedFrames > 18 &&
                    track.score < yoloTrackKeepScoreFactor;
                if (track.missedFrames > yoloTrackMaxMissedFrames || staleWeakTrack) {
                    expiredTracks.push_back(kv.first);
                }
            }

            for (const int trackId : expiredTracks) {
                yoloTracks.erase(trackId);
            }

            yoloCurrentRects.clear();
            yoloCurrentClassIds.clear();
            yoloCurrentScores.clear();
            for (const auto& kv : yoloTracks) {
                const YoloTrack& track = kv.second;
                if (track.hits < yoloTrackMinHits) continue;
                if (track.missedFrames > yoloOutputRetentionFrames) continue;
                if (track.score < yoloTrackKeepScoreFactor) continue;

                yoloCurrentRects[kv.first] = cv::Rect(
                    static_cast<int>(std::round(track.rect.x)),
                    static_cast<int>(std::round(track.rect.y)),
                    static_cast<int>(std::round(track.rect.width)),
                    static_cast<int>(std::round(track.rect.height))
                );
                yoloCurrentClassIds[kv.first] = preferredDisplayClassId(track, track.rect);
                yoloCurrentScores[kv.first] = track.score;
            }
        }

        void processYoloTrackedResults(const cv::Mat& currentMat) {
            const int frameWidth = currentMat.cols;
            const int frameHeight = currentMat.rows;
            beginOscFrame();

            const auto trackRects = yoloCurrentRects;
            const auto trackClassIds = yoloCurrentClassIds;
            const auto trackScores = yoloCurrentScores;

            std::vector<int> prevSelectedSlots(selectedBlobs);
            selectedBlobs.clear();

            for (auto it = yoloSlotMemoryTracks.begin(); it != yoloSlotMemoryTracks.end();) {
                if (it->first < 1 || it->first > maxBlobNum) {
                    it = yoloSlotMemoryTracks.erase(it);
                } else {
                    ++it;
                }
            }
            for (auto it = yoloSlotVisualTrackers.begin(); it != yoloSlotVisualTrackers.end();) {
                if (it->first < 1 || it->first > maxBlobNum) {
                    it = yoloSlotVisualTrackers.erase(it);
                } else {
                    ++it;
                }
            }
            for (auto it = retainedOutputTracks.begin(); it != retainedOutputTracks.end();) {
                if (it->first < 1 || it->first > maxBlobNum) {
                    it = retainedOutputTracks.erase(it);
                } else {
                    ++it;
                }
            }
            for (auto it = noteOnSentMap.begin(); it != noteOnSentMap.end();) {
                if (it->first < 1 || it->first > maxBlobNum) {
                    it = noteOnSentMap.erase(it);
                } else {
                    ++it;
                }
            }

            std::vector<int> trackIdsForExistingSlots;
            std::vector<int> visibleTrackIds;
            trackIdsForExistingSlots.reserve(yoloTracks.size());
            visibleTrackIds.reserve(yoloTracks.size());
            for (const auto& kv : yoloTracks) {
                const YoloTrack& track = kv.second;
                if (track.hits < yoloTrackMinHits) continue;
                if (track.missedFrames > yoloOutputRetentionFrames) continue;
                if (!track.visibleThisFrame && track.score < yoloTrackKeepScoreFactor) continue;
                if (!track.visibleThisFrame && track.missedFrames > 12) continue;
                trackIdsForExistingSlots.push_back(kv.first);
                if (track.visibleThisFrame) {
                    visibleTrackIds.push_back(kv.first);
                }
            }

            auto sortTrackIds = [&](std::vector<int>& ids) {
                std::sort(ids.begin(), ids.end(), [&](int a, int b) {
                    const YoloTrack& ta = yoloTracks.at(a);
                    const YoloTrack& tb = yoloTracks.at(b);
                    if (ta.visibleThisFrame != tb.visibleThisFrame) return ta.visibleThisFrame > tb.visibleThisFrame;
                    if (ta.missedFrames != tb.missedFrames) return ta.missedFrames < tb.missedFrames;
                    if (ta.hits != tb.hits) return ta.hits > tb.hits;
                    if (ta.score != tb.score) return ta.score > tb.score;
                    return ta.id < tb.id;
                });
            };
            sortTrackIds(trackIdsForExistingSlots);
            sortTrackIds(visibleTrackIds);

            int soundingCount = 0;
            for (const auto& kv : noteOnSentMap) {
                if (kv.second.bSent && !kv.second.bDead) soundingCount++;
            }

            std::set<int> matchedTracks;
            std::set<int> occupiedSlots;
            std::set<int> advancedRetainedSlots;
            std::map<int, glm::vec2> currentSelectedCenters;
            std::map<int, float> currentSelectedAreas;
            std::map<int, cv::Rect> currentSelectedRects;

            auto updateSlotFromTrack = [&](int slot, int trackId) {
                if (slot < 1 || slot > maxBlobNum) return;
                auto rectIt = trackRects.find(trackId);
                if (rectIt == trackRects.end()) return;

                const YoloTrack& track = yoloTracks.at(trackId);
                const cv::Rect2f currentRectF(rectIt->second.x, rectIt->second.y, rectIt->second.width, rectIt->second.height);
                cv::Rect rect = rectIt->second;

                auto memoryIt = yoloSlotMemoryTracks.find(slot);
                const bool hadMemory = memoryIt != yoloSlotMemoryTracks.end();
                if (hadMemory) {
                    const RetainedOutputTrack& existingSlot = memoryIt->second;
                    const bool sameSourceTrack = existingSlot.sourceTrackId == trackId;
                    const float maxAreaRatio = sameSourceTrack ? 3.4f : (useThreeClassSceneLabeling() ? 1.9f : 2.4f);
                    const float maxAspectRatio = sameSourceTrack ? 2.9f : (useThreeClassSceneLabeling() ? 1.8f : 2.1f);
                    const float maxWidthStep = sameSourceTrack ? 2.5f : (useThreeClassSceneLabeling() ? 1.55f : 1.75f);
                    const float maxHeightStep = sameSourceTrack ? 2.5f : (useThreeClassSceneLabeling() ? 1.55f : 1.75f);
                    if (!rectGeometryCompatible(existingSlot.rect, currentRectF, maxAreaRatio, maxAspectRatio) ||
                        !rectStepSizeCompatible(existingSlot.rect, currentRectF, maxWidthStep, maxHeightStep) ||
                        detectionLooksImplausiblyLargeForThreeScene(currentRectF)) {
                        return;
                    }
                }

                for (const auto& currentRectKv : currentSelectedRects) {
                    if (slotForYoloSourceTrack(trackId) == slot) {
                        continue;
                    }
                    const cv::Rect& occupiedRectI = currentRectKv.second;
                    const cv::Rect2f occupiedRect(occupiedRectI.x, occupiedRectI.y,
                                                  occupiedRectI.width, occupiedRectI.height);
                    if (rectLooksLikeDuplicateTrack(occupiedRect, currentRectF)) {
                        return;
                    }
                }

                RetainedOutputTrack& memoryTrack = yoloSlotMemoryTracks[slot];
                cv::Rect2f outputRectF = currentRectF;
                if (hadMemory) {
                    const float alpha = memoryTrack.missingFrames > 0 ? 0.26f : 0.38f;
                    outputRectF = smoothOutputRect(memoryTrack.rect, currentRectF, alpha);
                    rect = cv::Rect(
                        static_cast<int>(std::round(outputRectF.x)),
                        static_cast<int>(std::round(outputRectF.y)),
                        static_cast<int>(std::round(outputRectF.width)),
                        static_cast<int>(std::round(outputRectF.height))
                    );
                }

                const glm::vec2 center(rect.x + rect.width * 0.5f, rect.y + rect.height * 0.5f);
                const float area = (rect.width * rect.height) / static_cast<float>(frameWidth * frameHeight);
                const int displayClassId = preferredDisplayClassId(track, currentRectF);
                const int lockedClassId = hadMemory ? memoryTrack.classId : -1;
                const int previousAge = hadMemory ? memoryTrack.age : 0;
                memoryTrack.rect = outputRectF;
                memoryTrack.velocity = track.velocity;
                memoryTrack.area = area;
                memoryTrack.age = std::max(previousAge + 1, 1);
                memoryTrack.missingFrames = 0;
                memoryTrack.score = track.score;
                memoryTrack.sourceTrackId = trackId;
                if (track.visibleThisFrame) {
                    initSlotVisualTracker(slot, currentMat, memoryTrack.rect);
                }
                if (useThreeClassSceneLabeling()) {
                    // Once a slot has been initialized to person/car/cat, keep that
                    // object identity stable through crossovers instead of letting a
                    // single odd box shape rewrite the slot's class every frame.
                    memoryTrack.classId = lockedClassId >= 0 ? lockedClassId : displayClassId;
                } else {
                    memoryTrack.classId = displayClassId >= 0 ? displayClassId : memoryTrack.classId;
                }

                RetainedOutputTrack& slotTrack = retainedOutputTracks[slot];
                slotTrack = memoryTrack;

                selectedBlobs.push_back(slot);
                occupiedSlots.insert(slot);
                matchedTracks.insert(trackId);
                currentSelectedCenters[slot] = center;
                currentSelectedAreas[slot] = area;
                currentSelectedRects[slot] = rect;

                bool noteOnSent = isNoteOnSent(slot);
                if (!noteOnSent) {
                    int requiredAge = minAge;
                    if (soundingCount >= 2) requiredAge = std::max(requiredAge, static_cast<int>(extraVoiceMinAge));
                    if (slotTrack.age >= requiredAge) {
                        sendNoteOn(slot);
                        noteOnSentMap[slot].bSent = true;
                        noteOnSentMap[slot].bDead = false;
                        noteOnSentMap[slot].framesAfterDeath = -1;
                        soundingCount++;
                    }
                } else {
                    noteOnSentMap[slot].bDead = false;
                    noteOnSentMap[slot].framesAfterDeath = -1;
                }
            };

            auto scoreTrackForSlot = [&](int slot, int trackId, float& outScore) -> bool {
                const cv::Rect2f* previousRectPtr = lastKnownRectForLabel(slot);
                if (!previousRectPtr) return false;
                cv::Rect2f previousRect = *previousRectPtr;
                auto memoryIt = yoloSlotMemoryTracks.find(slot);
                const int memoryMissedFrames = memoryIt != yoloSlotMemoryTracks.end() ? memoryIt->second.missingFrames : 0;
                const bool sameSourceTrack =
                    memoryIt != yoloSlotMemoryTracks.end() &&
                    memoryIt->second.sourceTrackId == trackId;
                if (memoryIt != yoloSlotMemoryTracks.end() && memoryIt->second.missingFrames <= 8) {
                    previousRect = clampRectToFrame(
                        offsetRect(previousRect, memoryIt->second.velocity * yoloTrackPredictionFactor),
                        yoloLastFrameSize
                    );
                }

                auto rectIt = trackRects.find(trackId);
                if (rectIt == trackRects.end()) return false;

                const cv::Rect2f currentRect(rectIt->second.x,
                                             rectIt->second.y,
                                             rectIt->second.width,
                                             rectIt->second.height);
                float minIou = ofMap(static_cast<float>(memoryMissedFrames), 0.0f, 36.0f, 0.08f, 0.04f, true);
                float centerDistanceFactor = ofMap(static_cast<float>(memoryMissedFrames), 0.0f, 36.0f, 0.65f, 0.90f, true);
                float minCenterDistancePx = ofMap(static_cast<float>(memoryMissedFrames), 0.0f, 36.0f, 60.0f, 90.0f, true);
                float maxAreaRatio = ofMap(static_cast<float>(memoryMissedFrames), 0.0f, 36.0f, 2.8f, 3.2f, true);
                float maxAspectRatio = ofMap(static_cast<float>(memoryMissedFrames), 0.0f, 36.0f, 2.2f, 2.6f, true);
                if (sameSourceTrack) {
                    // Let a slot reclaim its own source track a little more easily
                    // during tight crossovers without loosening the general matcher.
                    minIou *= 0.65f;
                    centerDistanceFactor *= 1.10f;
                    minCenterDistancePx += 14.0f;
                    maxAreaRatio += 0.25f;
                    maxAspectRatio += 0.18f;
                }
                if (!rectLikelySameObject(previousRect,
                                          currentRect,
                                          minIou,
                                          centerDistanceFactor,
                                          minCenterDistancePx,
                                          maxAreaRatio,
                                          maxAspectRatio)) {
                    return false;
                }

                const float iou = rectIou(previousRect, currentRect);
                const float diag = std::max(glm::length(glm::vec2(previousRect.width, previousRect.height)),
                                            glm::length(glm::vec2(currentRect.width, currentRect.height)));
                const float allowedDistance = std::max(diag * centerDistanceFactor, minCenterDistancePx);
                const float centerDistance = glm::distance(rectCenter(previousRect), rectCenter(currentRect));
                const float closeness = 1.0f - std::min(centerDistance / std::max(allowedDistance, 1.0f), 1.0f);
                outScore = (iou * 3.0f) + closeness;
                if (sameSourceTrack) {
                    outScore += 0.85f;
                }
                return true;
            };

            const int maxOutputSlots = maxBlobNum.get();

            std::vector<int> outputSlots;
            outputSlots.reserve(maxOutputSlots);
            for (int slot = 1; slot <= maxOutputSlots; ++slot) {
                outputSlots.push_back(slot);
            }

            auto trackRankScore = [&](int trackId) {
                const YoloTrack& track = yoloTracks.at(trackId);
                float score = track.score + (track.hits * 0.12f);
                if (track.visibleThisFrame) score += 3.0f;
                score -= track.missedFrames * 0.35f;
                return score;
            };

            std::vector<int> candidateTrackIds = trackIdsForExistingSlots;
            for (int slot = 1; slot <= maxOutputSlots; ++slot) {
                auto memoryIt = yoloSlotMemoryTracks.find(slot);
                if (memoryIt == yoloSlotMemoryTracks.end()) continue;
                const int trackId = memoryIt->second.sourceTrackId;
                if (trackId < 0) continue;
                if (yoloTracks.count(trackId) == 0) continue;
                if (std::find(candidateTrackIds.begin(), candidateTrackIds.end(), trackId) == candidateTrackIds.end()) {
                    candidateTrackIds.push_back(trackId);
                }
            }

            std::sort(candidateTrackIds.begin(), candidateTrackIds.end(), [&](int a, int b) {
                const float scoreA = trackRankScore(a);
                const float scoreB = trackRankScore(b);
                if (scoreA != scoreB) return scoreA > scoreB;
                return a < b;
            });

            const std::size_t preferredCandidateCount =
                static_cast<std::size_t>(std::max(maxOutputSlots + 3, maxOutputSlots));
            if (candidateTrackIds.size() > preferredCandidateCount) {
                std::vector<int> trimmed(candidateTrackIds.begin(), candidateTrackIds.begin() + preferredCandidateCount);
                for (int slot = 1; slot <= maxOutputSlots; ++slot) {
                    auto memoryIt = yoloSlotMemoryTracks.find(slot);
                    if (memoryIt == yoloSlotMemoryTracks.end()) continue;
                    const int trackId = memoryIt->second.sourceTrackId;
                    if (trackId < 0 || yoloTracks.count(trackId) == 0) continue;
                    if (std::find(trimmed.begin(), trimmed.end(), trackId) == trimmed.end()) {
                        trimmed.push_back(trackId);
                    }
                }
                candidateTrackIds = trimmed;
            }

            auto scoreTrackForOutputSlot = [&](int slot, int trackId, float& outScore) -> bool {
                auto trackIt = yoloTracks.find(trackId);
                if (trackIt == yoloTracks.end()) return false;
                const YoloTrack& track = trackIt->second;
                const cv::Rect2f currentRectF = track.rect;
                if (detectionLooksImplausiblyLargeForThreeScene(currentRectF)) return false;

                auto memoryIt = yoloSlotMemoryTracks.find(slot);
                const bool slotHasState =
                    memoryIt != yoloSlotMemoryTracks.end() ||
                    retainedOutputTracks.count(slot) > 0 ||
                    noteOnSentMap.count(slot) > 0 ||
                    prevSelectedRects.count(slot) > 0;

                float continuityScore = -1.0f;
                const bool continuityValid = scoreTrackForSlot(slot, trackId, continuityScore);

                float score = trackRankScore(trackId);
                if (track.visibleThisFrame) {
                    score += 0.45f;
                } else {
                    score -= 0.20f + (0.08f * track.missedFrames);
                }

                if (slotHasState) {
                    const bool sourceTrackRecovery =
                        memoryIt != yoloSlotMemoryTracks.end() &&
                        memoryIt->second.sourceTrackId == trackId &&
                        track.missedFrames <= yoloSourcePredictionMissesForSlot(slot);
                    const bool sceneClassRecovery =
                        useThreeClassSceneLabeling() &&
                        track.visibleThisFrame &&
                        memoryIt != yoloSlotMemoryTracks.end() &&
                        memoryIt->second.classId >= 0 &&
                        sceneGeometryClassId(currentRectF) == memoryIt->second.classId;

                    if (!continuityValid && !sourceTrackRecovery && !sceneClassRecovery) {
                        return false;
                    }

                    if (continuityValid) {
                        score += continuityScore * 1.75f;
                    }

                    if (memoryIt != yoloSlotMemoryTracks.end() && memoryIt->second.sourceTrackId == trackId) {
                        score += 8.5f;
                    }

                    if (useThreeClassSceneLabeling() &&
                        memoryIt != yoloSlotMemoryTracks.end() &&
                        memoryIt->second.classId >= 0) {
                        const int candidateClassId = sceneGeometryClassId(currentRectF);
                        if (candidateClassId == memoryIt->second.classId) {
                            score += 3.0f;
                        } else {
                            if (!continuityValid && !sourceTrackRecovery) {
                                return false;
                            }
                            score -= 2.5f;
                        }
                    }

                    if (!continuityValid && sceneClassRecovery) {
                        score += 2.0f;
                    }
                }

                outScore = score;
                return true;
            };

            std::map<int, std::map<int, float>> slotTrackScores;
            for (const int slot : outputSlots) {
                for (const int trackId : candidateTrackIds) {
                    float score = -1.0f;
                    if (!scoreTrackForOutputSlot(slot, trackId, score)) continue;
                    slotTrackScores[slot][trackId] = score;
                }
            }

            struct AssignedTrack {
                int slot = -1;
                int trackId = -1;
                float score = -1.0f;
            };

            std::vector<AssignedTrack> bestAssignments;
            std::vector<AssignedTrack> currentAssignments;
            std::set<int> usedTrackIds;
            float bestAssignmentScore = -1000000.0f;

            auto assignmentsConflict = [&](int slotA, int trackA, int slotB, int trackB) {
                if (slotA == slotB || trackA == trackB) return true;
                return false;
            };

            std::function<void(std::size_t, float)> searchAssignments =
                [&](std::size_t slotIndex, float currentScore) {
                    if (slotIndex >= outputSlots.size()) {
                        if (currentScore > bestAssignmentScore) {
                            bestAssignmentScore = currentScore;
                            bestAssignments = currentAssignments;
                        }
                        return;
                    }

                    const int slot = outputSlots[slotIndex];
                    const bool slotHasState =
                        yoloSlotMemoryTracks.count(slot) > 0 ||
                        retainedOutputTracks.count(slot) > 0 ||
                        noteOnSentMap.count(slot) > 0 ||
                        prevSelectedRects.count(slot) > 0;

                    const float emptyPenalty = slotHasState ? -1.0f : 0.0f;
                    searchAssignments(slotIndex + 1, currentScore + emptyPenalty);

                    auto slotScoreIt = slotTrackScores.find(slot);
                    if (slotScoreIt == slotTrackScores.end()) return;
                    for (const auto& trackScoreKv : slotScoreIt->second) {
                        const int trackId = trackScoreKv.first;
                        if (usedTrackIds.count(trackId) > 0) continue;
                        bool conflictsExistingAssignment = false;
                        for (const AssignedTrack& currentAssignment : currentAssignments) {
                            if (assignmentsConflict(slot, trackId, currentAssignment.slot, currentAssignment.trackId)) {
                                conflictsExistingAssignment = true;
                                break;
                            }
                        }
                        if (conflictsExistingAssignment) continue;
                        usedTrackIds.insert(trackId);
                        currentAssignments.push_back({slot, trackId, trackScoreKv.second});
                        searchAssignments(slotIndex + 1, currentScore + trackScoreKv.second);
                        currentAssignments.pop_back();
                        usedTrackIds.erase(trackId);
                    }
                };

            searchAssignments(0, 0.0f);

            std::sort(bestAssignments.begin(), bestAssignments.end(), [&](const AssignedTrack& a, const AssignedTrack& b) {
                auto sourceTrackIdForSlot = [&](int slot) {
                    auto it = yoloSlotMemoryTracks.find(slot);
                    return it != yoloSlotMemoryTracks.end() ? it->second.sourceTrackId : -1;
                };
                const bool aSameSource = sourceTrackIdForSlot(a.slot) == a.trackId;
                const bool bSameSource = sourceTrackIdForSlot(b.slot) == b.trackId;
                if (aSameSource != bSameSource) return aSameSource > bSameSource;
                if (a.score != b.score) return a.score > b.score;
                return a.slot < b.slot;
            });

            for (const AssignedTrack& assignment : bestAssignments) {
                updateSlotFromTrack(assignment.slot, assignment.trackId);
            }

            std::vector<int> expiredSlotMemory;
            for (auto& kv : yoloSlotMemoryTracks) {
                const int slot = kv.first;
                if (slot < 1 || slot > maxBlobNum) {
                    expiredSlotMemory.push_back(slot);
                    continue;
                }
                if (occupiedSlots.count(slot) > 0) {
                    continue;
                }

                RetainedOutputTrack& memoryTrack = kv.second;
                memoryTrack.missingFrames++;
                memoryTrack.age++;
                memoryTrack.velocity *= 0.35f;
                if (memoryTrack.missingFrames > yoloSlotMemoryRetentionFrames()) {
                    expiredSlotMemory.push_back(slot);
                    continue;
                }

                const int sourceTrackId = memoryTrack.sourceTrackId;
                auto sourceTrackIt = yoloTracks.find(sourceTrackId);
                auto sourceRectIt = trackRects.find(sourceTrackId);
                const bool sourceTrackAvailable =
                    sourceTrackId >= 0 &&
                    sourceTrackIt != yoloTracks.end() &&
                    sourceRectIt != trackRects.end() &&
                    matchedTracks.count(sourceTrackId) == 0;
                if (sourceTrackAvailable) {
                    const YoloTrack& sourceTrack = sourceTrackIt->second;
                    const cv::Rect& sourceRectI = sourceRectIt->second;
                    const cv::Rect2f sourceRectF(sourceRectI.x,
                                                sourceRectI.y,
                                                sourceRectI.width,
                                                sourceRectI.height);
                    bool looksLikeDuplicate = false;
                    if (slotForYoloSourceTrack(sourceTrackId) != slot) {
                        for (const auto& currentRectKv : currentSelectedRects) {
                            const cv::Rect& occupiedRectI = currentRectKv.second;
                            const cv::Rect2f occupiedRect(occupiedRectI.x,
                                                          occupiedRectI.y,
                                                          occupiedRectI.width,
                                                          occupiedRectI.height);
                            if (rectLooksLikeDuplicateTrack(occupiedRect, sourceRectF)) {
                                looksLikeDuplicate = true;
                                break;
                            }
                        }
                    }

                    if (!looksLikeDuplicate &&
                        (sourceTrack.visibleThisFrame || sourceTrack.missedFrames <= yoloSourcePredictionMissesForSlot(slot)) &&
                        !detectionLooksImplausiblyLargeForThreeScene(sourceRectF)) {
                        RetainedOutputTrack visibleTrack = memoryTrack;
                        const float sourceAlpha = sourceTrack.visibleThisFrame ? 0.34f : 0.22f;
                        visibleTrack.rect = smoothOutputRect(memoryTrack.rect, sourceRectF, sourceAlpha);
                        visibleTrack.velocity = sourceTrack.velocity;
                        visibleTrack.area =
                            rectArea(visibleTrack.rect) / static_cast<float>(frameWidth * frameHeight);
                        visibleTrack.age = std::max(visibleTrack.age, sourceTrack.age);
                        visibleTrack.score = sourceTrack.score;
                        visibleTrack.classId =
                            visibleTrack.classId >= 0 ? visibleTrack.classId : preferredDisplayClassId(sourceTrack, sourceRectF);
                        visibleTrack.missingFrames = std::min(memoryTrack.missingFrames, yoloVisualRetentionFramesForSlot(slot));
                        memoryTrack.rect = visibleTrack.rect;
                        memoryTrack.velocity = visibleTrack.velocity;
                        memoryTrack.area = visibleTrack.area;
                        memoryTrack.score = visibleTrack.score;
                        if (sourceTrack.visibleThisFrame) {
                            initSlotVisualTracker(slot, currentMat, sourceRectF);
                        }

                        retainedOutputTracks[slot] = visibleTrack;

                        const cv::Rect rect(
                            static_cast<int>(std::round(visibleTrack.rect.x)),
                            static_cast<int>(std::round(visibleTrack.rect.y)),
                            static_cast<int>(std::round(visibleTrack.rect.width)),
                            static_cast<int>(std::round(visibleTrack.rect.height))
                        );
                        const glm::vec2 center(rect.x + rect.width * 0.5f,
                                               rect.y + rect.height * 0.5f);
                        selectedBlobs.push_back(slot);
                        occupiedSlots.insert(slot);
                        advancedRetainedSlots.insert(slot);
                        currentSelectedCenters[slot] = center;
                        currentSelectedAreas[slot] = visibleTrack.area;
                        currentSelectedRects[slot] = rect;
                        continue;
                    }
                }

                if (memoryTrack.missingFrames <= yoloVisualTrackerRetentionFrames()) {
                    cv::Rect2f trackedRectF;
                    glm::vec2 trackedVelocity(0.0f, 0.0f);
                    if (updateSlotVisualTracker(slot, currentMat, trackedRectF, trackedVelocity)) {
                        trackedRectF = clampRectToFrame(trackedRectF, currentMat.size());
                        trackedRectF = smoothOutputRect(memoryTrack.rect, trackedRectF, 0.24f);
                        trackedVelocity = rectCenter(trackedRectF) - rectCenter(memoryTrack.rect);
                        const float trackedArea =
                            rectArea(trackedRectF) / static_cast<float>(frameWidth * frameHeight);

                        memoryTrack.velocity = glm::mix(memoryTrack.velocity, trackedVelocity, 0.60f);
                        memoryTrack.rect = trackedRectF;
                        memoryTrack.area = trackedArea;
                        memoryTrack.score *= yoloTrackScoreDecay;

                        RetainedOutputTrack visibleTrack = memoryTrack;
                        visibleTrack.missingFrames = std::min(memoryTrack.missingFrames, yoloVisualRetentionFramesForSlot(slot));
                        retainedOutputTracks[slot] = visibleTrack;

                        const cv::Rect rect(
                            static_cast<int>(std::round(trackedRectF.x)),
                            static_cast<int>(std::round(trackedRectF.y)),
                            static_cast<int>(std::round(trackedRectF.width)),
                            static_cast<int>(std::round(trackedRectF.height))
                        );
                        const glm::vec2 center(rect.x + rect.width * 0.5f, rect.y + rect.height * 0.5f);
                        selectedBlobs.push_back(slot);
                        occupiedSlots.insert(slot);
                        advancedRetainedSlots.insert(slot);
                        currentSelectedCenters[slot] = center;
                        currentSelectedAreas[slot] = trackedArea;
                        currentSelectedRects[slot] = rect;
                        continue;
                    }
                }

                const bool wasVisibleLastFrame =
                    std::find(prevSelectedSlots.begin(), prevSelectedSlots.end(), slot) != prevSelectedSlots.end();
                if (!wasVisibleLastFrame) {
                    retainedOutputTracks.erase(slot);
                    continue;
                }

                RetainedOutputTrack visibleTrack = memoryTrack;
                auto retainedIt = retainedOutputTracks.find(slot);
                if (retainedIt != retainedOutputTracks.end()) {
                    visibleTrack.rect = retainedIt->second.rect;
                    visibleTrack.missingFrames = retainedIt->second.missingFrames + 1;
                } else {
                    visibleTrack.missingFrames = 1;
                }
                if (visibleTrack.missingFrames > yoloVisualRetentionFramesForSlot(slot)) {
                    retainedOutputTracks.erase(slot);
                    continue;
                }

                retainedOutputTracks[slot] = visibleTrack;

                const cv::Rect rect(
                    static_cast<int>(std::round(visibleTrack.rect.x)),
                    static_cast<int>(std::round(visibleTrack.rect.y)),
                    static_cast<int>(std::round(visibleTrack.rect.width)),
                    static_cast<int>(std::round(visibleTrack.rect.height))
                );
                const glm::vec2 center(rect.x + rect.width * 0.5f, rect.y + rect.height * 0.5f);
                selectedBlobs.push_back(slot);
                occupiedSlots.insert(slot);
                advancedRetainedSlots.insert(slot);
                currentSelectedCenters[slot] = center;
                currentSelectedAreas[slot] = visibleTrack.area;
                currentSelectedRects[slot] = rect;
            }

            for (const int slot : expiredSlotMemory) {
                yoloSlotMemoryTracks.erase(slot);
                yoloSlotVisualTrackers.erase(slot);
                retainedOutputTracks.erase(slot);
            }

            for (auto it = retainedOutputTracks.begin(); it != retainedOutputTracks.end();) {
                if (it->first < 1 || it->first > maxBlobNum) {
                    it = retainedOutputTracks.erase(it);
                    continue;
                }
                if (occupiedSlots.count(it->first) == 0 && advancedRetainedSlots.count(it->first) == 0) {
                    it = retainedOutputTracks.erase(it);
                    continue;
                }
                ++it;
            }

            // YOLO output labels are already fixed slot ids. Force OSC ownership
            // before emitting values so NDITrackerN always carries label/slot N,
            // even immediately after a detection dropout or app restart.
            for (const int slot : selectedBlobs) {
                forceLabelToSlot(slot, slot);
            }

            const auto sceneSlotClassOverrides = assignThreeSceneSlotLabels(currentSelectedRects);
            bool refreshThreeSceneClassLocks = false;
            if (useThreeClassSceneLabeling() && !sceneSlotClassOverrides.empty()) {
                std::set<int> lockedClasses;
                for (const int slot : selectedBlobs) {
                    auto memoryIt = yoloSlotMemoryTracks.find(slot);
                    const int lockedClassId = memoryIt != yoloSlotMemoryTracks.end() ? memoryIt->second.classId : -1;
                    if (lockedClassId < 0) {
                        refreshThreeSceneClassLocks = true;
                        break;
                    }
                    lockedClasses.insert(lockedClassId);
                }
                if (!refreshThreeSceneClassLocks &&
                    selectedBlobs.size() >= 3 &&
                    lockedClasses.size() < selectedBlobs.size()) {
                    refreshThreeSceneClassLocks = true;
                }
            }

            for (const auto& kv : sceneSlotClassOverrides) {
                auto memoryIt = yoloSlotMemoryTracks.find(kv.first);
                if (memoryIt != yoloSlotMemoryTracks.end() &&
                    (refreshThreeSceneClassLocks || memoryIt->second.classId < 0)) {
                    memoryIt->second.classId = kv.second;
                }
                auto retainedIt = retainedOutputTracks.find(kv.first);
                if (retainedIt != retainedOutputTracks.end() &&
                    (refreshThreeSceneClassLocks || retainedIt->second.classId < 0)) {
                    retainedIt->second.classId = kv.second;
                }
            }

            prevSelectedBlobCount = static_cast<int>(selectedBlobs.size());
            prevSelectedCenters = currentSelectedCenters;
            prevSelectedAreas = currentSelectedAreas;
            prevSelectedRects = currentSelectedRects;

            emitOscForSelectedLabels(currentSelectedCenters, currentSelectedAreas, frameWidth, frameHeight);

            yoloCurrentRects.clear();
            yoloCurrentClassIds.clear();
            yoloCurrentScores.clear();
            for (const int slot : selectedBlobs) {
                auto rectIt = currentSelectedRects.find(slot);
                if (rectIt == currentSelectedRects.end()) continue;
                yoloCurrentRects[slot] = rectIt->second;

                auto retainedIt = retainedOutputTracks.find(slot);
                if (retainedIt != retainedOutputTracks.end()) {
                    auto overrideIt = sceneSlotClassOverrides.find(slot);
                    yoloCurrentClassIds[slot] =
                        overrideIt != sceneSlotClassOverrides.end() ? overrideIt->second : retainedIt->second.classId;
                    yoloCurrentScores[slot] = retainedIt->second.score;
                    continue;
                }

                auto classIt = trackClassIds.find(slot);
                auto overrideIt = sceneSlotClassOverrides.find(slot);
                if (overrideIt != sceneSlotClassOverrides.end()) {
                    yoloCurrentClassIds[slot] = overrideIt->second;
                } else if (classIt != trackClassIds.end()) {
                    yoloCurrentClassIds[slot] = classIt->second;
                }
                auto scoreIt = trackScores.find(slot);
                if (scoreIt != trackScores.end()) yoloCurrentScores[slot] = scoreIt->second;
            }

            std::vector<int> dels;
            for (auto itr = noteOnSentMap.begin(); itr != noteOnSentMap.end(); ++itr) {
                const int label = itr->first;
                NoteOnInfo& info = itr->second;
                const bool stillSelected = std::find(selectedBlobs.begin(), selectedBlobs.end(), label) != selectedBlobs.end();
                const bool hasContinuityMemory = yoloSlotMemoryTracks.count(label) > 0;

                if (info.bSent && !stillSelected) {
                    if (hasContinuityMemory) {
                        info.bDead = false;
                        info.framesAfterDeath = -1;
                    } else if (!info.bDead) {
                        info.bDead = true;
                        info.framesAfterDeath = 0;
                    }
                }

                if (info.bSent && info.bDead) {
                    if (getTrackHoldFrames() <= info.framesAfterDeath) {
                        if (needNoteOff(label)) {
                            sendDeathNow(label);
                            sendNoteOff(label);
                        }
                        dels.push_back(label);
                    } else {
                        info.framesAfterDeath++;
                    }
                }
            }

            for (const int label : dels) {
                noteOnSentMap.erase(label);
                yoloSlotMemoryTracks.erase(label);
                yoloSlotVisualTrackers.erase(label);
                retainedOutputTracks.erase(label);
            }
        }

        void emitOscForSelectedLabels(const std::map<int, glm::vec2>& centers,
                                      const std::map<int, float>& areas,
                                      int frameWidth,
                                      int frameHeight) {
            const glm::vec2 inputSize(frameWidth, frameHeight);

            if (trackingTechnique == 1) {
                for (const int label : selectedBlobs) {
                    const auto centerIt = centers.find(label);
                    const auto areaIt = areas.find(label);
                    if (centerIt == centers.end() || areaIt == areas.end()) continue;

                    glm::vec2 vel(0.0f, 0.0f);
                    int age = yoloTrackAgeForLabel(label);
                    auto retainedIt = retainedOutputTracks.find(label);
                    if (retainedIt != retainedOutputTracks.end()) {
                        vel = retainedIt->second.velocity;
                        age = retainedIt->second.age;
                    }

                    sendVal(label, vel, areaIt->second, age, centerIt->second, inputSize);
                }
                return;
            }

            auto& tracker = finder.getTracker();
            for (const int label : selectedBlobs) {
                const auto centerIt = centers.find(label);
                const auto areaIt = areas.find(label);
                if (centerIt == centers.end() || areaIt == areas.end()) continue;
                const glm::vec2 vel = ofxCv::toOf(tracker.getVelocityFromLabel(label));
                const int age = tracker.getAge(label);
                sendVal(label, vel, areaIt->second, age, centerIt->second, inputSize);
            }
        }

        void updateStableYoloDetections(const std::vector<cv::Rect>& boxes,
                                        const std::vector<int>& classIds,
                                        const std::vector<float>& confidences) {
            std::vector<bool> stableMatched(yoloStableDetections.size(), false);

            for (std::size_t i = 0; i < boxes.size(); ++i) {
                const cv::Rect2f incomingRect(boxes[i].x, boxes[i].y, boxes[i].width, boxes[i].height);
                const int incomingClassId = i < classIds.size() ? classIds[i] : -1;
                const float incomingScore = i < confidences.size() ? confidences[i] : 0.0f;

                int bestMatch = -1;
                float bestMatchScore = -1.0f;
                for (std::size_t j = 0; j < yoloStableDetections.size(); ++j) {
                    if (stableMatched[j]) continue;
                    const YoloStableDetection& stable = yoloStableDetections[j];

                    cv::Rect2f predictedRect = stable.rect;
                    if (glm::length(stable.velocity) > 0.0f) {
                        predictedRect = clampRectToFrame(offsetRect(stable.rect, stable.velocity * yoloStablePredictionFactor), yoloLastFrameSize);
                    }

                    const float iou = rectIou(predictedRect, incomingRect);
                    const glm::vec2 stableCenter = rectCenter(predictedRect);
                    const glm::vec2 incomingCenter = rectCenter(incomingRect);
                    const float centerDistance = glm::distance(stableCenter, incomingCenter);
                    const float stableDiag = glm::length(glm::vec2(predictedRect.width, predictedRect.height));
                    const float incomingDiag = glm::length(glm::vec2(incomingRect.width, incomingRect.height));
                    const float maxDiag = std::max(std::max(stableDiag, incomingDiag), 1.0f);
                    const float allowedCenterDistance = std::max(maxDiag * yoloStableCenterDistanceFactor, yoloStableMinCenterDistancePx);
                    const bool sameClass = stable.classId == incomingClassId;
                    if (iou < yoloStableMinIou && centerDistance > allowedCenterDistance) continue;

                    float matchScore = iou * 2.0f + (1.0f - std::min(centerDistance / std::max(allowedCenterDistance, 1.0f), 1.0f));
                    if (sameClass) {
                        matchScore += yoloStableSameClassBonus;
                    }
                    if (matchScore > bestMatchScore) {
                        bestMatchScore = matchScore;
                        bestMatch = static_cast<int>(j);
                    }
                }

                if (bestMatch >= 0) {
                    YoloStableDetection& stable = yoloStableDetections[bestMatch];
                    const float previousStableScore = stable.score;
                    const glm::vec2 previousCenter = rectCenter(stable.rect);
                    const glm::vec2 incomingCenter = rectCenter(incomingRect);
                    const glm::vec2 measuredVelocity = incomingCenter - previousCenter;
                    stable.rect = lerpRect(stable.rect, incomingRect, yoloStableRectSmoothing);
                    stable.score = ofLerp(stable.score, incomingScore, yoloStableScoreSmoothing);
                    stable.velocity = glm::mix(stable.velocity, measuredVelocity, yoloStableVelocitySmoothing);
                    if (incomingClassId == stable.classId) {
                        stable.candidateClassId = -1;
                        stable.candidateClassMatches = 0;
                    } else {
                        if (stable.candidateClassId == incomingClassId) {
                            stable.candidateClassMatches++;
                        } else {
                            stable.candidateClassId = incomingClassId;
                            stable.candidateClassMatches = 1;
                        }
                        if (stable.candidateClassMatches >= yoloStableClassSwitchMatches &&
                            incomingScore >= (previousStableScore + yoloStableClassSwitchScoreGain)) {
                            stable.classId = incomingClassId;
                            stable.candidateClassId = -1;
                            stable.candidateClassMatches = 0;
                        }
                    }
                    stable.missedInferencePasses = 0;
                    stable.consecutiveMatches++;
                    stableMatched[bestMatch] = true;
                } else {
                    YoloStableDetection stable;
                    stable.rect = incomingRect;
                    stable.classId = incomingClassId;
                    stable.score = incomingScore;
                    stable.missedInferencePasses = 0;
                    stable.velocity = glm::vec2(0.0f, 0.0f);
                    stable.consecutiveMatches = 1;
                    stable.candidateClassId = -1;
                    stable.candidateClassMatches = 0;
                    yoloStableDetections.push_back(stable);
                    stableMatched.push_back(true);
                }
            }

            std::vector<YoloStableDetection> filtered;
            filtered.reserve(yoloStableDetections.size());
            for (std::size_t i = 0; i < yoloStableDetections.size(); ++i) {
                YoloStableDetection stable = yoloStableDetections[i];
                if (!stableMatched[i]) {
                    stable.missedInferencePasses++;
                    stable.consecutiveMatches = 0;
                    stable.candidateClassId = -1;
                    stable.candidateClassMatches = 0;
                    stable.rect = clampRectToFrame(offsetRect(stable.rect, stable.velocity * yoloStablePredictionFactor), yoloLastFrameSize);
                    stable.velocity *= yoloStableVelocityDecay;
                    stable.score *= yoloStableScoreDecay;
                }

                const float minKeepScore = yoloConfidenceThreshold * yoloStableKeepScoreFactor;
                if (stable.missedInferencePasses <= yoloStableMaxMissedInferencePasses && stable.score >= minKeepScore) {
                    filtered.push_back(stable);
                }
            }
            yoloStableDetections = std::move(filtered);
        }

        void preserveCurrentLabelSlots(const std::vector<unsigned int>& currentLabels,
                                       ofxCv::RectTracker& tracker,
                                       const std::vector<int>& previousLabels) {
            struct SlotCandidate {
                float distance = 0.0f;
                int currentLabel = -1;
                int previousLabel = -1;
                int slot = -1;
            };

            std::vector<SlotCandidate> candidates;
            const float maxDistance = std::max(getTrackMatchDistancePx(), yoloStableTrackMatchPx);
            for (const int currentLabel : currentLabels) {
                const cv::Rect& currentRect = tracker.getCurrent(currentLabel);
                const glm::vec2 currentCenter(currentRect.x + currentRect.width * 0.5f,
                                              currentRect.y + currentRect.height * 0.5f);

                for (const int previousLabel : previousLabels) {
                    if (!isNoteOnSent(previousLabel)) continue;
                    auto prevCenterIt = prevSelectedCenters.find(previousLabel);
                    if (prevCenterIt == prevSelectedCenters.end()) continue;
                    const float distance = glm::distance(currentCenter, prevCenterIt->second);
                    if (distance > maxDistance) continue;
                    candidates.push_back({distance, currentLabel, previousLabel, getOscAddressSlot(previousLabel)});
                }
            }

            std::sort(candidates.begin(), candidates.end(), [](const SlotCandidate& a, const SlotCandidate& b) {
                return a.distance < b.distance;
            });

            std::set<int> assignedCurrent;
            std::set<int> assignedSlots;
            for (const SlotCandidate& candidate : candidates) {
                if (candidate.slot < 1) continue;
                if (assignedCurrent.count(candidate.currentLabel) > 0) continue;
                if (assignedSlots.count(candidate.slot) > 0) continue;
                forceLabelToSlot(candidate.currentLabel, candidate.slot);
                adoptLabelState(candidate.previousLabel, candidate.currentLabel);
                assignedCurrent.insert(candidate.currentLabel);
                assignedSlots.insert(candidate.slot);
            }

            if (currentLabels.size() == 1 && assignedCurrent.empty()) {
                const int currentLabel = currentLabels.front();
                int targetSlot = -1;
                int targetPreviousLabel = -1;
                int liveSlotCount = 0;
                for (const auto& kv : noteOnSentMap) {
                    const NoteOnInfo& info = kv.second;
                    if (!info.bSent || info.bDead) continue;
                    targetSlot = getOscAddressSlot(kv.first);
                    targetPreviousLabel = kv.first;
                    liveSlotCount++;
                }
                if (liveSlotCount == 1 && targetSlot > 0) {
                    forceLabelToSlot(currentLabel, targetSlot);
                    adoptLabelState(targetPreviousLabel, currentLabel);
                } else if (liveSlotCount == 0) {
                    forceSingleBlobSlot1(currentLabel);
                }
            }
        }

        void adoptLabelState(int previousLabel, int currentLabel) {
            if (previousLabel < 0 || currentLabel < 0 || previousLabel == currentLabel) return;

            auto noteIt = noteOnSentMap.find(previousLabel);
            if (noteIt != noteOnSentMap.end()) {
                NoteOnInfo adopted = noteIt->second;
                adopted.bSent = true;
                adopted.bDead = false;
                adopted.framesAfterDeath = -1;
                noteOnSentMap[currentLabel] = adopted;
                noteOnSentMap.erase(noteIt);
            }

            auto retainedIt = retainedOutputTracks.find(previousLabel);
            if (retainedIt != retainedOutputTracks.end()) {
                retainedOutputTracks[currentLabel] = retainedIt->second;
                retainedOutputTracks[currentLabel].missingFrames = 0;
                auto trackIt = yoloTracks.find(currentLabel);
                if (trackIt != yoloTracks.end() && trackIt->second.classId >= 0) {
                    retainedOutputTracks[currentLabel].classId = trackIt->second.classId;
                    yoloCurrentClassIds[currentLabel] = trackIt->second.classId;
                }
                retainedOutputTracks.erase(retainedIt);
            }
        }

        void updateRetainedOutputTrack(int label,
                                       const cv::Rect& rect,
                                       const glm::vec2& velocity,
                                       float area,
                                       int age) {
            RetainedOutputTrack& retained = retainedOutputTracks[label];
            retained.rect = cv::Rect2f(rect.x, rect.y, rect.width, rect.height);
            retained.velocity = velocity;
            retained.area = area;
            retained.age = age;
            retained.missingFrames = 0;

            auto classIt = yoloCurrentClassIds.find(label);
            if (classIt != yoloCurrentClassIds.end()) {
                retained.classId = classIt->second;
            }

            auto scoreIt = yoloCurrentScores.find(label);
            if (scoreIt != yoloCurrentScores.end()) {
                retained.score = scoreIt->second;
            }
        }

        void appendRetainedOutputTracks(std::vector<int>& outputLabels,
                                        std::map<int, glm::vec2>& outputCenters,
                                        std::map<int, float>& outputAreas,
                                        std::map<int, cv::Rect>& outputRects,
                                        int frameWidth,
                                        int frameHeight,
                                        bool requireLiveNote = true) {
            std::set<int> activeLabels(outputLabels.begin(), outputLabels.end());
            std::vector<int> expiredLabels;

            for (auto& kv : retainedOutputTracks) {
                const int label = kv.first;
                RetainedOutputTrack& retained = kv.second;

                if (activeLabels.count(label) > 0) continue;

                auto noteIt = noteOnSentMap.find(label);
                if (requireLiveNote && (noteIt == noteOnSentMap.end() || !noteIt->second.bSent || noteIt->second.bDead)) {
                    expiredLabels.push_back(label);
                    continue;
                }

                bool reacquiredByAnotherTrack = false;
                for (const auto& currentRectKv : outputRects) {
                    if (currentRectKv.first == label) continue;
                    const cv::Rect2f currentRect(currentRectKv.second.x, currentRectKv.second.y,
                                                 currentRectKv.second.width, currentRectKv.second.height);
                    if (rectDefinitelyReacquired(retained.rect, currentRect)) {
                        reacquiredByAnotherTrack = true;
                        break;
                    }
                }

                if (reacquiredByAnotherTrack) {
                    if (requireLiveNote && noteIt != noteOnSentMap.end() && !noteIt->second.bDead) {
                        noteIt->second.bDead = true;
                        noteIt->second.framesAfterDeath = 0;
                    }
                    expiredLabels.push_back(label);
                    continue;
                }

                retained.missingFrames++;
                retained.age++;
                retained.rect = clampRectToFrame(offsetRect(retained.rect, retained.velocity * yoloOutputPredictionFactor), yoloLastFrameSize);
                retained.velocity *= yoloOutputVelocityDecay;

                if (retained.missingFrames > yoloOutputRetentionFrames) {
                    if (requireLiveNote && noteIt != noteOnSentMap.end() && !noteIt->second.bDead) {
                        noteIt->second.bDead = true;
                        noteIt->second.framesAfterDeath = 0;
                    }
                    expiredLabels.push_back(label);
                    continue;
                }

                if (outputLabels.size() >= static_cast<std::size_t>(maxBlobNum)) {
                    continue;
                }

                outputLabels.push_back(label);
                activeLabels.insert(label);

                cv::Rect rect(
                    static_cast<int>(std::round(retained.rect.x)),
                    static_cast<int>(std::round(retained.rect.y)),
                    static_cast<int>(std::round(retained.rect.width)),
                    static_cast<int>(std::round(retained.rect.height))
                );
                rect.x = ofClamp(rect.x, 0, std::max(0, frameWidth - rect.width));
                rect.y = ofClamp(rect.y, 0, std::max(0, frameHeight - rect.height));

                const glm::vec2 center(rect.x + rect.width * 0.5f, rect.y + rect.height * 0.5f);
                outputCenters[label] = center;
                outputAreas[label] = retained.area;
                outputRects[label] = rect;
            }

            for (const int label : expiredLabels) {
                retainedOutputTracks.erase(label);
            }
        }

        void gatherStableYoloDetections(std::vector<cv::Rect>& boxes,
                                        std::vector<int>& classIds,
                                        std::vector<float>& confidences) const {
            boxes.clear();
            classIds.clear();
            confidences.clear();

            for (const YoloStableDetection& stable : yoloStableDetections) {
                boxes.emplace_back(
                    static_cast<int>(std::round(stable.rect.x)),
                    static_cast<int>(std::round(stable.rect.y)),
                    static_cast<int>(std::round(stable.rect.width)),
                    static_cast<int>(std::round(stable.rect.height))
                );
                classIds.push_back(stable.classId);
                confidences.push_back(stable.score);
            }
        }

        void runYolo(const cv::Mat& currentMat, std::vector<cv::Rect>& boxes, std::vector<int>& classIds, std::vector<float>& confidences) {
            runYoloWithConfig(currentMat, makeYoloConfig(), boxes, classIds, confidences);
        }

        void runYoloForTracking(const cv::Mat& currentMat, std::vector<cv::Rect>& boxes, std::vector<int>& classIds, std::vector<float>& confidences) {
            runYoloWithConfig(currentMat, makeYoloTrackingConfig(), boxes, classIds, confidences);
        }

        void runYoloWithConfig(const cv::Mat& currentMat,
                               const YoloDetectorConfig& config,
                               std::vector<cv::Rect>& boxes,
                               std::vector<int>& classIds,
                               std::vector<float>& confidences) {
            boxes.clear();
            classIds.clear();
            confidences.clear();

            if (!yoloDetector) {
                return;
            }

            std::vector<YoloDetection> detections;
            std::string error;
            if (!yoloDetector->infer(currentMat, config, detections, error)) {
                ofLogError("Tracker") << "YOLO infer failed (" << yoloLoadedBackendName << "): " << error;
                return;
            }

            boxes.reserve(detections.size());
            classIds.reserve(detections.size());
            confidences.reserve(detections.size());
            for (const auto& detection : detections) {
                boxes.push_back(detection.box);
                classIds.push_back(detection.classId);
                confidences.push_back(detection.score);
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
            preserveCurrentLabelSlots(currs, tracker, prevSelectedBlobs);

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

                if (isNoteOnSent(label)) {
                    const cv::Rect& rect = tracker.getCurrent(label);
                    const glm::vec2 center(rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f);
                    const float area = (rect.width * rect.height) / static_cast<float>(frameWidth * frameHeight);
                    const glm::vec2 vel = ofxCv::toOf(tracker.getVelocityFromLabel(label));
                    updateRetainedOutputTrack(label, rect, vel, area, tracker.getAge(label));
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

            appendRetainedOutputTracks(selectedBlobs, currentSelectedCenters, currentSelectedAreas, currentSelectedRects, frameWidth, frameHeight);

            prevSelectedBlobCount = currentSelectedCount;
            prevSelectedCenters = currentSelectedCenters;
            prevSelectedAreas = currentSelectedAreas;
            prevSelectedRects = currentSelectedRects;

            emitOscForSelectedLabels(currentSelectedCenters, currentSelectedAreas, frameWidth, frameHeight);

            auto & deads = tracker.getDeadLabels();
            for(auto itrD = deads.begin(); itrD<deads.end(); ++itrD){
                int label = *itrD;
                if (retainedOutputTracks.count(label) != 0) {
                    yoloCurrentRects.erase(label);
                    yoloCurrentClassIds.erase(label);
                    yoloCurrentScores.erase(label);
                    continue;
                }
                if(noteOnSentMap.count(label) != 0){
                    if(!noteOnSentMap[label].bDead){
                        noteOnSentMap[label].framesAfterDeath = 0;
                    }
                    noteOnSentMap[label].bDead = true;
                    noteOnSentMap[label].framesAfterDeath = std::max(0, noteOnSentMap[label].framesAfterDeath);
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
                            sendDeathNow(label);
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

        std::unique_ptr<YoloDetectorBackend> yoloDetector;
        bool yoloLoaded = false;
        bool yoloModelWarned = false;
        std::string yoloLoadedPath;
        std::string yoloLoadedBackendName;
        ofImage yoloPreviewImage;
        std::map<int, cv::Rect> yoloCurrentRects;
        std::map<int, int> yoloCurrentClassIds;
        std::map<int, float> yoloCurrentScores;
        struct YoloStableDetection {
            cv::Rect2f rect;
            glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
            int classId = -1;
            float score = 0.0f;
            int missedInferencePasses = 0;
            int consecutiveMatches = 0;
            int candidateClassId = -1;
            int candidateClassMatches = 0;
        };
        struct RetainedOutputTrack {
            cv::Rect2f rect;
            glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
            float area = 0.0f;
            int age = 0;
            int missingFrames = 0;
            int classId = -1;
            float score = 0.0f;
            int sourceTrackId = -1;
        };
        struct YoloTrack {
            int id = -1;
            cv::Rect2f rect;
            glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
            int classId = -1;
            std::array<float, kYoloClassCount> classVotes{};
            int candidateClassId = -1;
            int candidateClassMatches = 0;
            float score = 0.0f;
            int age = 0;
            int hits = 0;
            int missedFrames = 0;
            bool visibleThisFrame = false;
        };
        struct SlotVisualTracker {
            cv::Mat templateGray;
            cv::Rect2f lastRect;
            int framesSinceYolo = 0;
            bool initialized = false;
        };
        std::map<int, YoloTrack> yoloTracks;
        int yoloNextTrackId = 1;
        std::vector<YoloStableDetection> yoloStableDetections;
        std::map<int, RetainedOutputTrack> yoloSlotMemoryTracks;
        std::map<int, SlotVisualTracker> yoloSlotVisualTrackers;
        std::map<int, RetainedOutputTrack> retainedOutputTracks;
        int yoloFrameCounter = 0;
        int yoloInferenceInterval = 3;
        // Keep the tracker reference view in sync with the live frame instead of
        // publishing a heavily throttled preview image.
        int yoloPreviewUpdateInterval = 1;
        bool yoloRawModeActive = false;
        cv::Size yoloLastFrameSize;
        float yoloTrackMinIou = 0.03f;
        float yoloTrackCenterDistanceFactor = 1.25f;
        float yoloTrackMinCenterDistancePx = 70.0f;
        float yoloTrackLowConfidenceThreshold = 0.02f;
        float yoloTrackPrimaryConfidenceFloor = 0.05f;
        float yoloTrackRectSmoothing = 0.82f;
        float yoloTrackScoreSmoothing = 0.55f;
        float yoloTrackScoreDecay = 0.99f;
        float yoloTrackVelocitySmoothing = 0.35f;
        float yoloTrackVelocityDecay = 0.94f;
        float yoloTrackPredictionFactor = 0.18f;
        int yoloTrackMaxMissedFrames = 120;
        float yoloTrackKeepScoreFactor = 0.08f;
        float yoloTrackMaxAreaRatio = 3.0f;
        float yoloTrackMaxAspectRatioChange = 2.5f;
        float yoloTrackSameClassBonus = 0.25f;
        int yoloTrackClassSwitchMatches = 3;
        float yoloTrackClassSwitchScoreGain = 0.08f;
        int yoloTrackMinHits = 1;
        float yoloTrackClassVoteDecay = 0.92f;
        float yoloTrackClassVoteMinWeight = 0.35f;
        float yoloStableMinIou = 0.08f;
        float yoloStableCenterDistanceFactor = 1.35f;
        float yoloStableMinCenterDistancePx = 56.0f;
        float yoloStableRectSmoothing = 0.35f;
        float yoloStableScoreSmoothing = 0.40f;
        float yoloStableScoreDecay = 0.985f;
        float yoloStableVelocitySmoothing = 0.45f;
        float yoloStableVelocityDecay = 0.82f;
        float yoloStablePredictionFactor = 1.15f;
        int yoloStableMaxMissedInferencePasses = 24;
        float yoloStableKeepScoreFactor = 0.25f;
        float yoloStableSameClassBonus = 0.20f;
        int yoloStableClassSwitchMatches = 8;
        float yoloStableClassSwitchScoreGain = 0.18f;
        float yoloStableTrackMatchPx = 220.0f;
        int yoloStableTrackPersistenceFrames = 96;
        int yoloOutputRetentionFrames = 120;
        float yoloOutputVelocityDecay = 0.94f;
        float yoloOutputPredictionFactor = 0.08f;
    };
    
}
