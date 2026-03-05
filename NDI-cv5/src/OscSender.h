//
//  OscSender.h
//

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include <map>
#include <vector>

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
            int slot = getOscAddressSlot(label, maxBlobNum);
            // Legacy AMXD pipeline derives note on/off internally from value stream.
            // Keep API return value for tracker bookkeeping, but don't emit separate OSC events.
            return slot;
        }
        
        int sendNoteOff(int label, int maxBlobNum){
            int slot = getOscAddressSlot(label, maxBlobNum);
            // See sendNoteOn(): avoid injecting extra message shapes into legacy route chain.
            releaseOscAddressSlot(label);
            return slot;
        }
        
        int sendVal(int label, int maxBlobNum, glm::vec2 vel, float area, int age, glm::vec2 center, glm::vec2 inputSize){
            ofxOscMessage m;
            int slot = getOscAddressSlot(label, maxBlobNum);
            // One address per slot keeps compatibility with "route NDITracker1 ... NDITracker10".
            m.setAddress(oscAddressBase + ofToString(slot));
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
            // Max route chains in this project expect plain OSC messages, not bundled packets.
            sender.sendMessage(m, false);
            
            return slot;
        }
        
        int getOscAddressSlot(int label, int maxBlobNum);
        void releaseOscAddressSlot(int label);
        
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
        std::map<int, int> labelToSlot;
        int fallbackRoundRobinSlot = 1;

    public:
        // OSC sender settings
        ofParameter<string> oscIp{"IP", "localhost"};
        ofParameter<int> oscPort{"port", 12345, 0, 12345};
        // Legacy Max route object in AMXD matches symbols without a leading slash.
        const std::string oscAddressBase = "NDITracker";
        ofParameterGroup grp{"OSC send", oscIp, oscPort};
        
        ofEventListeners listenerHolder;
    };
    
}
