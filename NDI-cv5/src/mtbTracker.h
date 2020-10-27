//
//  mtbBlobTracker.h
//

#pragma once

#include "ofMain.h"
#include "NDISender.h"        // my own helper class
#include "ofxOpenCv.h"
#include "ofxCv.h"

namespace mtb{

    struct byLable {
        bool operator()(const unsigned int &a, const unsigned int &b) {
            return a < b;
        }
    };

    
    class mtbTracker{
        
    public:
        
        mtbTracker(){
            listenerHolder.push(bgAlgo.newListener([&](int& algo) { changeBG(); }));
        }
        
        void setup(string name, int w, int h, bool ndiOut){
            
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
        
        void update(ofxCvColorImage & currentImage){
            currentMat = ofxCv::toCv(currentImage);
            pBackSub->apply(currentMat, foregroundMat);
            ofxCv::toOf(foregroundMat, foregroundPix);
            foregroundImage.setFromPixels(foregroundPix);
            if(0<blurAmt) foregroundImage.blur(blurAmt);
            findContour();
        }
        
        void findContour(){
            if(!foregroundImage.bAllocated) return;
            
            int numCandidates = 30;
            
            contourFinder.findContours(foregroundImage, minArea*minArea, maxArea*maxArea, numCandidates, bFindHoles, bSimplify);
            
            rects.clear();
            for(auto & b : contourFinder.blobs){
                rects.push_back(ofxCv::toCv(b.boundingRect));
            }
            tracker.setSmoothingRate(smoothingRate);
            tracker.setMaximumDistance(maxDistance);
            tracker.setPersistence(persistence);
            tracker.track(rects);
            
            // Erase Dead blob
            const vector<unsigned int> deadLabels = tracker.getDeadLabels();
            for(int i=0; i<deadLabels.size(); i++){
                int label = deadLabels[i];
                if(selectedBlobs.count(label) != 0){
                    // this one need NoteOff
                    selectedBlobs.erase(label);
                }
            }

            // Sort and select
            vector<unsigned int> currentLabels = tracker.getCurrentLabels();
            std::sort(currentLabels.begin(), currentLabels.end(), byLable());
            

            int selected = 0;
            
            auto itr = currentLabels.begin();
            // 1. try to find already selected blob
            for(; itr!=currentLabels.end(); ++itr){
                int label = *itr;
                if(selectedBlobs.count(label) == 1){
                    selected++;
                }
            }

            // 2. need to add extra
            if(selected < maxBlobNum){
                int needToAdd = maxBlobNum - selected;
                for(int i=0; i<needToAdd; i++){
                    if(currentLabels.size()>i){
                        int label = currentLabels[i];
                        int age = tracker.getAge(label);
                        selectedBlobs.emplace(make_pair(label,false));
                    }
                }
            }
            
            // 3. check if we need NoteOn
            {
                auto itr = selectedBlobs.begin();
                for(; itr!=selectedBlobs.end(); ++itr){
                    int label = itr->first;
                    bool bOn = itr->second;
                    
                    if(bOn == false){
                        int age = tracker.getAge(label);
                        if(minAge <= age){
                            itr->second = true;
                        }
                    }
                }
            }
            
            
            // delete overflow
//            auto itr = selectedBlobs.rbegin();
//            itr += maxBlobNum;
//            selectedBlobs.erase(itr, selectedBlobs.rend());
//            selectedBlobs.
        }
    
        void drawToFbo2(float receiverW, float receiverH, float processW, float processH){
            
            senderBlob.begin();
            
            float sx = (float)processW / receiverW;
            float sy = (float)processH / receiverH;
            ofPushMatrix();
            ofScale(sx, sy);
            
            int nBlobs = contourFinder.blobs.size();
            for(int i=0; i<nBlobs; i++){
                
                int label = tracker.getCurrentLabels()[i];
                int age = tracker.getAge(label);
                ofxCvBlob & blob = contourFinder.blobs[i];
                ofRectangle & rect = blob.boundingRect;
                glm::vec2 center(rect.x + rect.width/2, rect.y + rect.height/2);
                
                ofPushStyle();
                ofPushMatrix();
                ofTranslate(center);
                ofSetColor(255);
                ofNoFill();
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofDrawRectangle(0, 0, rect.width, rect.height);
                ofDrawBitmapString(ofToString(label), 0, 0);
                ofPopMatrix();
                ofPopStyle();
            }
        
            ofPopMatrix();
            senderBlob.end();
        }

        void drawToFbo(float receiverW, float receiverH, float processW, float processH){
            
            senderBlob.begin();

            float sx = (float)processW / receiverW;
            float sy = (float)processH / receiverH;
            ofPushMatrix();
            ofScale(sx, sy);
            
            auto itr = selectedBlobs.begin();
            for(; itr!=selectedBlobs.end(); ++itr){
                
                int label = itr->first;
                bool bNoteOnSent = itr->second;
                int age = tracker.getAge(label);
                int index = tracker.getIndexFromLabel(label);
                ofxCvBlob & blob = contourFinder.blobs[index];
                ofRectangle & rect = blob.boundingRect;
                glm::vec2 center(rect.x + rect.width/2, rect.y + rect.height/2);
                glm::vec2 velocity = ofxCv::toOf(tracker.getVelocity(index));
                float area = blob.area / (receiverW*receiverH);

                ofPushStyle();
                ofPushMatrix();
                if(bNoteOnSent){
                    ofSetLineWidth(1);
                    ofNoFill();
                    blob.draw();
                    ofDrawBitmapString(ofToString(label), center.x, center.y);
                }else{
                    ofTranslate(center);
                    ofSetColor(255, 200);
                    ofNoFill();
                    ofSetRectMode(OF_RECTMODE_CENTER);
                    ofDrawRectangle(0, 0, rect.width, rect.height);
                    ofDrawBitmapString(ofToString(label), 0, 0);
                }
                ofPopMatrix();
                ofPopStyle();
            }
            ofPopMatrix();
            senderBlob.end();
        }
        
        void drawInfo(){
            char c[255];
            int i = 0;
            auto itr = selectedBlobs.begin();
            for(; itr!=selectedBlobs.end(); itr++){
                int label = (*itr).first;
                bool bNoteOnSent = (*itr).second;
                int age = tracker.getAge(label);
                bNoteOnSent ? ofSetHexColor(0xff0099) : ofSetColor(220);
                sprintf(c, "%5i %5i", label, age); //, getOscAddressSlot(label));
                ofDrawBitmapString(c, 0, (i+1)*15);
                i++;
                //if(maxBlobNum<=i){
                //    break;
                //}
            }
        }
        
        void drawInfo2(){
            const vector<unsigned int> & currentLabels = tracker.getCurrentLabels();
            auto itr = currentLabels.begin();
            char c[255];
            int i = 0;
            for(; itr!=currentLabels.end(); itr++){
                int label = *itr;
                int age = tracker.getAge(label);
                sprintf(c, "%5i %5i", label, age);
                ofDrawBitmapString(c, 0, (i+1)*15);
                i++;
            }
        }
        
        void drawForeground(int x, int y, int w, int h){
            foregroundImage.draw(x, y, w, h);
        }
        
        void drawFbo(int x, int y, int w, int h){
            senderBlob.draw(x, y, w, h);
        }
        
        void clear(){
            senderBlob.clear();
        }
        
        void send(){
            senderBlob.send();
        }
        
        ofPixels foregroundPix;
        ofxCvGrayscaleImage foregroundImage;
        ofxCvContourFinder contourFinder;

        
        ofxCv::RectTracker tracker;
        std::vector<cv::Rect> rects;
        std::map<int, bool> selectedBlobs; // label, noteOnSent
        
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
        ofParameter<int> maxBlobNum{ "Max blob num", 3, 1, 10 };
        ofParameter<int> minAge{ "Min age", 10, 0, 60 };
        //ofParameter<float> blobScale{ "scale", 1, 0.1, 4.0 };
        ofParameterGroup grp{ "Tracker", bgAlgo, blurAmt, minArea, maxArea, bFindHoles, bSimplify, persistence, maxDistance, smoothingRate, maxBlobNum, minAge, /*blobScale */};

        
        NDISender senderBlob;
        ofEventListeners listenerHolder;

    };
    
}
