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
        
        void sendNoteOn(int label, int maxBlobNum){
            ofxOscMessage m;
            m.setAddress(oscAddress.get()+ "/" + ofToString(getOscAddressSlot(label, maxBlobNum)) +"/on");
            m.addIntArg(label);
            sender.sendMessage(m);
        }
        
        void sendNoteOff(int label, int maxBlobNum){
            ofxOscMessage m;
            m.setAddress(oscAddress.get() + "/"+ ofToString(getOscAddressSlot(label, maxBlobNum)) +"/off");
            m.addIntArg(label);
            sender.sendMessage(m);
        }
        
        void sendVal(int label, glm::vec2 xyrate, float vel, float area, int age, glm::vec2 center, glm::vec2 inputSize, int maxBlobNum){
            ofxOscMessage m;
            m.setAddress(oscAddress.get() + "/" + ofToString(getOscAddressSlot(label, maxBlobNum)) +"/val");
            m.addIntArg(label);
            m.addFloatArg(xyrate.x);
            m.addFloatArg(xyrate.y);
            m.addFloatArg(glm::length(vel));
            m.addFloatArg(area);
            m.addIntArg(age);
            
            // polar coordinate
            glm::vec2 p = toPolar(center.x, center.y, inputSize.x, inputSize.y);
            m.addFloatArg(p.x);
            m.addFloatArg(p.y);
            sender.sendMessage(m);
        }
        
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
        
        int getOscAddressSlot(int label, int maxBlobNum){
            return label % maxBlobNum + 1;
        }
        
        ofxOscSender sender;

    public:
        // OSC sender settings
        ofParameter<string> oscIp{"IP", "localhost"};
        ofParameter<int> oscPort{"port", 12345, 0, 12345};
        ofParameter<string> oscAddress{"oscAddress", "NDITracker"};
        ofParameterGroup grp{"OSC send", oscIp, oscPort, oscAddress};
        
        ofEventListeners listenerHolder;
    };
    
}
