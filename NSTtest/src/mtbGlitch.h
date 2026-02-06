//
//  mtbGlitch.h
//
//

#pragma once

#include "ofMain.h"
#include "ofxEasyFboGlitch.h"
#include "NDISender.h"        // my own helper class


namespace mtb{

    class mtbGlitch{
        
    public:
        
        void setup(string name, int w, int h, bool ndiOut){
            glitch.allocate(w, h);
            
            targetFbo.allocate(w, h, GL_RGBA);
            targetFbo.begin();
            ofClear(255, 255, 255, 0);
            targetFbo.end();
            senderGlitch.setup(name, w, h, ndiOut);
        }
        
        void clear(){
            //glitch.clear();
            targetFbo.clear();
            senderGlitch.clear();
        }

        void beginTarget(){
            ofPushStyle();
            ofEnableAlphaBlending();
            targetFbo.begin();
            ofClear(0,0,0,0);
            ofSetColor(255);
        }
        
        void endTarget(){
            targetFbo.end();
            ofPopStyle();
        }
        
        void drawToFbo(int w, int h){
            senderGlitch.begin();
            glitch.draw(targetFbo, 0, h, w, -h);
            senderGlitch.end();
        }
        
        void drawTargetFbo(int x, int y, int w, int h){
            targetFbo.draw(x, y, w, h);
        }
        
        void drawFbo(int x, int y, int w, int h){
            senderGlitch.draw(x, y, w, h);
        }

        void sendNDI(){
            senderGlitch.send();
        }
        
        void doGlitch(int i){
            glitch.doGlitch(i);
        }
        
        ofFbo targetFbo;
        ofxEasyFboGlitch glitch;
        
        NDISender senderGlitch;

    };
    
}
