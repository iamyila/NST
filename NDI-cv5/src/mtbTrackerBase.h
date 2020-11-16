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
        
        void registerUser(NDISource * s);
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
        
        void sendNDI(){
            senderBlob.send();
        }
        
        void drawLabelAndAge(int label, int x=0, int y=0){
            auto & tracker = finder.getTracker();
            int age = tracker.getAge(label);
            char c[255];
            sprintf(c, "%3i:%3i", label, age);
            ofDrawBitmapString(c, x, y);
        }
        
        void drawInfo(){
            auto & tracker = finder.getTracker();
            char c[255];
            int i = 0;
            auto itr = selectedBlobs.begin();
            for(; itr!=selectedBlobs.end(); itr++){
                int label = *itr;
                bool bNoteOnSent = isNoteOnSent(label);
                int age = tracker.getAge(label);
                bNoteOnSent ? ofSetHexColor(0xff0099) : ofSetColor(220);
                drawLabelAndAge(label, 0, 10+i*15);
                i++;
            }
        }
        
        void addPointToHeatmap(float x, float y, float area);
        
        bool isSelected(int label){
            auto itr = std::find(selectedBlobs.begin(), selectedBlobs.end(), label);
            return itr!=selectedBlobs.end();
        }
        
        bool isNoteOnSent(int label){
            if(noteOnSentMap.count(label) != 0){
                return noteOnSentMap[label].bSent;
            }else{
                return false;
            }
        }
        
        bool needNoteOff(int label){
            
            int targetSlot = getOscAddressSlot(label);
            auto itr = noteOnSentMap.begin();
            for(; itr!=noteOnSentMap.end(); ++itr){
                int sentLabel = itr->first;
                NoteOnInfo & info = itr->second;
                bool bSent = info.bSent;
                if(sentLabel == label) continue;
                if(!bSent) continue;
                int slot = getOscAddressSlot(sentLabel);
                if(targetSlot == slot){
                    // we dont need to send noteOff
                    // since there are still sounding note
                    return false;
                }
            }
            return true;
        }
        
        // osc wrapper
        int getOscAddressSlot(int label);
        int sendNoteOn(int label);
        int sendNoteOff(int label);
        int sendVal(int label, glm::vec2 vel, float area, int age, glm::vec2 center, glm::vec2 inputSize);
        
        //ofxCvContourFinder contourFinder;
        ofxCv::ContourFinder finder;
        //ofxCv::RectTracker tracker;

        struct NoteOnInfo{
        public:
            bool bSent;
            bool bDead;
            int framesAfterDeath; // -1 if not dead
            
            NoteOnInfo(int _bSent=false)
            :bSent(_bSent),
            bDead(false),
            framesAfterDeath(-1){
            }
        };

        std::vector<cv::Rect> rects;
        std::vector<int> selectedBlobs; // label
        std::map<int, NoteOnInfo> noteOnSentMap; // lable, noteOnSent
        
        
        NDISource * user;
        NDISender senderBlob;
        ofEventListeners listenerHolder;

        // CV::Contor, CV::Tracker
        ofParameter<float> minArea{ "minArea", 5, 0, 500 };
        ofParameter<float> maxArea{ "maxArea", 10, 0, 500 };
        ofParameter<bool> bFindHoles{ "find holes", false };
        ofParameter<bool> bSimplify{ "simplify", false };
        ofParameter<int> persistence{ "persistence (frames)", 15, 0, 60 };
        ofParameter<float> maxDistance{ "max distance (pix)", 100, 0, 500 };
        //ofParameter<float> smoothingRate{ "smoothingRate", 0.5, 0, 1.0 };
        ofParameter<int> maxBlobCandidate{ "Max blob candidate", 10, 1, 100 };
        ofParameter<bool> bDrawCandidates{ "Draw Candidates", true};
        ofParameter<int> maxBlobNum{ "Max blob num", 3, 1, 10 };
        ofParameter<int> minAge{ "Min age", 10, 0, 60 };
        ofParameterGroup grp{ "Tracker", minArea, maxArea, bFindHoles, bSimplify, persistence, maxDistance, /*smoothingRate,*/ bDrawCandidates, maxBlobCandidate, maxBlobNum, minAge, /*blobScale */};
    };
}
