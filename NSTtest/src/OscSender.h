//
//  OscSender.h
//

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

namespace mtb{
    
    class OscSender{
        
    public:
        
        OscSender(){
            listenerHolder.push(oscIp.newListener([&](string& ip) { setup(); }));
            listenerHolder.push(oscPort.newListener([&](int& port) { setup(); }));
        }
        
        void setup(){
            sender.setup(oscIp, oscPort);
        }
        
        int sendNoteOn(int label, int maxBlobNum){
            ofxOscMessage m;
            int slot = getOscAddressSlot(label, maxBlobNum);
            m.setAddress(oscAddress.get()+ "/" + ofToString(slot) +"/on");
            m.addIntArg(label);
            sender.sendMessage(m, false);
            return slot;
        }
        
        int sendNoteOff(int label, int maxBlobNum){
            ofxOscMessage m;
            int slot = getOscAddressSlot(label, maxBlobNum);
            m.setAddress(oscAddress.get() + "/"+ ofToString(slot) +"/off");
            m.addIntArg(label);
            sender.sendMessage(m, false);
            return slot;
        }
        
        int sendVal(int label, int maxBlobNum, glm::vec2 vel, float area, int age, glm::vec2 center, glm::vec2 inputSize){
            ofxOscMessage m;
            int slot = getOscAddressSlot(label, maxBlobNum);
            m.setAddress(oscAddress.get() + "/" + ofToString(slot) +"/val");
            m.addIntArg(label);
            m.addFloatArg(center.x/inputSize.x);
            m.addFloatArg(center.y/inputSize.y);
            m.addFloatArg(glm::length(vel));
            m.addFloatArg(area);
            m.addIntArg(age);
            
            // polar coordinate
            glm::vec2 p = toPolar(center.x, center.y, inputSize.x, inputSize.y);
            m.addFloatArg(p.x);
            m.addFloatArg(p.y);
            // Keep packet format consistent with on/off and avoid per-message bundle wrapping overhead.
            sender.sendMessage(m, false);
            
            return slot;
        }
        
        static int getOscAddressSlot(int label, int maxBlobNum);
        
    private:
        glm::vec2 toPolar(float x, float y, float w, float h){
            float tx = x/w*2.0 - 1.0;
            float ty = (h-y)/h*2.0 - 1.0;
            
            float angle = 0;
            if(!(tx==0 && ty==0)){
                angle = atan2(tx, ty);
                angle = ofRadToDeg(angle);
            }
            float len = sqrt(tx*tx + ty*ty);
            len = ofMap(len, 0, 1.41421356, 0.01, 2.0, true);
            return glm::vec2(angle, len);
        }
        
        ofxOscSender sender;

    public:
        // OSC sender settings
        ofParameter<string> oscIp{"IP", "localhost"};
        ofParameter<int> oscPort{"port", 12345, 0, 12345};
        ofParameter<string> oscAddress{"oscAddress", "/NDITracker0"};
        ofParameterGroup grp{"OSC send", oscIp, oscPort, oscAddress};
        
        ofEventListeners listenerHolder;
    };
    
}
