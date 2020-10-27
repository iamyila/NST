//
//  mtbBlobTracker.h
//

#pragma once

#include "ofMain.h"
#include "NDISender.h"        // my own helper class
#include "ofxOpenCv.h"
#include "ofxCv.h"

namespace mtb{
    
    class mtbBlobTracker{
        
    public:
        
        mtbBlobTracker(){
            listenerHolder.push(bgAlgo.newListener([&](int& algo) { setupBS(); }));
        }
        
        void setup(string name, int w, int h, bool ndiOut){
            currentImage.clear();
            currentImage.allocate(w,h);
            
            foregroundImage.clear();
            foregroundImage.allocate(w,h);
            if (bgAlgo == 0) {
                pBackSub = cv::createBackgroundSubtractorMOG2();
            }
            else {
                pBackSub = cv::createBackgroundSubtractorKNN();
            }
            
            senderBlob.setup(name, processWidth, processHeight, ndiOut);
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
            
        }
        
        void sendNoteOnOff(){
            
        }
        
        void clear(){
            senderBlob.clear();
        }
        
        ofPixels foregroundPix;
        ofxCvGrayscaleImage foregroundImage;
        ofxCvContourFinder contourFinder;

        
        ofxCv::RectTracker tracker;
        std::vector<cv::Rect> rects;
        std::map<int, bool> detectedBlobs; // label, noteOnSent
        
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
