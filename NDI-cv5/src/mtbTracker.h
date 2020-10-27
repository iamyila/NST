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
            
            auto itr = currentLabels.rbegin();
            
            //cout << currentLabels.size() << " : ";
            int i=0;
            for(; itr!=currentLabels.rend(); ++itr){
                int label = *itr;
                //cout << label << ", ";
                if(selectedBlobs.count(label) == 0){
                    // this blob is not selected, lets add
                    selectedBlobs.emplace(make_pair(label, false));
                }else{
                    // this blob is already selected, do nothing
                }
                
                // check if this blob need NoteOn message
                if(selectedBlobs[label] == false){
                    int age = tracker.getAge(label);
                    if(minAge <= age){
                        selectedBlobs[label] = true;
                        // send OSC
                    }
                }
                
                i++;
                if(selectedBlobs.size()>=maxBlobNum) break;
            } //cout << endl;

            // delete overflow
//            auto itr = selectedBlobs.rbegin();
//            itr += maxBlobNum;
//            selectedBlobs.erase(itr, selectedBlobs.rend());
//            selectedBlobs.
        }
    
        
        void drawToFbo(float receiverW, float receiverH, float processW, float processH){
            
            senderBlob.begin();

            float sx = (float)processW / receiverW;
            float sy = (float)processH / receiverH;
            ofPushMatrix();
            ofScale(sx, sy);
            
            int nB = 0;
            auto itr = selectedBlobs.begin();
            for(; itr!=selectedBlobs.end(); ++itr){
                
                int label = itr->first;
                int age = tracker.getAge(label);
                int index = tracker.getIndexFromLabel(label);
                ofxCvBlob & blob = contourFinder.blobs[index];
                ofRectangle & rect = blob.boundingRect;
                glm::vec2 center(rect.x + rect.width/2, rect.y + rect.height/2);
                glm::vec2 velocity = ofxCv::toOf(tracker.getVelocity(index));
                float area = blob.area / (receiverW*receiverH);
                
                ofSetLineWidth(1);
                ofNoFill();
                {
                    ofPushMatrix();
                    ofNoFill();
                    blob.draw();
                    ofPopMatrix();
                }
                
                nB++;
                if(maxBlobNum<=nB){
                    break;
                }
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
                if(maxBlobNum<=i){
                    break;
                }
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
        
        // CV::Contor, CV::Tracker
        ofParameter<float> minArea{ "minArea", 5, 0, 100 };
        ofParameter<float> maxArea{ "maxArea", 10, 0, 300 };
        ofParameter<bool> bFindHoles{ "find holes", false };
        ofParameter<bool> bSimplify{ "simplify", false };
        ofParameter<int> persistence{ "persistence (frames)", 15, 1, 60 };
        ofParameter<float> maxDistance{ "max distance (pix)", 100, 0, 300 };
        ofParameter<float> smoothingRate{ "smoothingRate", 0.5, 0, 1.0 };
        ofParameter<int> maxBlobNum{ "Max blob num", 3, 1, 10 };
        ofParameter<int> minAge{ "Min age", 10, 0, 60 };
        //ofParameter<float> blobScale{ "scale", 1, 0.1, 4.0 };
        ofParameterGroup grp{ "Tracker", bgAlgo, minArea, maxArea, bFindHoles, bSimplify, persistence, maxDistance, smoothingRate, maxBlobNum, minAge, /*blobScale */};

        
        NDISender senderBlob;
        ofEventListeners listenerHolder;

    };
    
}
