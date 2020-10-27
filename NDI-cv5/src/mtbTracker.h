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
            sendNoteOnOff();
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
                if(selectedLabels.count(label) != 0){
                    // this one need NoteOff
                }
            }

            // Sort and select
            vector<unsigned int> currentLabels = tracker.getCurrentLabels();
            std::sort(currentLabels.begin(), currentLabels.end(), byLable());
            
            auto & itr = currentLabels.rbegin();
            
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
                //
                if(selectedBlobs[label] == false){
                    //int age = ...
                    // if(minAge < age){
                    // send OSC
                }
                
                i++;
                if(i>=maxBlobNum) break;
            } //cout << endl;
        }
        
        void sendNoteOnOff(){
            
        }
        
        void draw(){
            
            auto & itr = selectedBlobs.begin();
            for(; itr!=selectedBlobs.end(); ++itr){
             
                // draw
                
            }
        }
        
        void clear(){
            senderBlob.clear();
        }
        
        void send(){
            
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
