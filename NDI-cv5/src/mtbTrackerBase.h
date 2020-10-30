//
//  mtbTrackerBase.h
//

#pragma once

#include "ofMain.h"
#include "NDISender.h"        // my own helper class
#include "ofxOpenCv.h"
#include "ofxCv.h"

class NDISource;

namespace mtb{
    
    class mtbTrackerBase{
        
    public:
        
        virtual void registerUser(NDISource * s) = 0;
        virtual void setup(string name, int w, int h, bool ndiOut) = 0;
        virtual void update(ofxCvColorImage & currentImage) = 0;
        virtual void findContour() = 0;
        virtual void drawToFbo(float receiverW, float receiverH, float processW, float processH) = 0;
        virtual void drawReference(int x, int y, int w, int h) = 0;

        void drawFbo(int x, int y, int w, int h){
            senderBlob.draw(x, y, w, h);
        }

        void clear(){
            senderBlob.clear();
        }
        
        void send(){
            senderBlob.send();
        }
        
        void drawLabelAndAge(int label, int x=0, int y=0){
            int age = tracker.getAge(label);
            char c[255];
            sprintf(c, "%3i:%3i", label, age);
            ofDrawBitmapString(c, x, y);
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
                drawLabelAndAge(label, 0, i*15);
                i++;
            }
        }
        
        ofxCv::RectTracker tracker;
        std::vector<cv::Rect> rects;
        std::map<int, bool> selectedBlobs; // label, noteOnSent
        
        NDISource * user;
        NDISender senderBlob;
        ofEventListeners listenerHolder;
        
    };
}
