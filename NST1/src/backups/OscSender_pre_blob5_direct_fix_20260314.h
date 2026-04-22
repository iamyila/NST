//
//  OscSender.h
//

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include <map>
#include <vector>
#include <cstdint>

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

        // Call once per tracker frame so slot ownership can expire stale labels.
        void beginFrame(){
            frameCounter++;
        }
        
        int sendNoteOn(int label, int maxBlobNum){
            int slot = getOscAddressSlot(label, maxBlobNum);
            // Legacy AMXD pipeline derives note on/off internally from value stream.
            // Keep API return value for tracker bookkeeping, but don't emit separate OSC events.
            return slot;
        }
        
        int sendNoteOff(int label, int maxBlobNum){
            int slot = getOscAddressSlot(label, maxBlobNum);
            sendDeathEvent(label, slot);
            // See sendNoteOn(): avoid injecting extra message shapes into legacy route chain.
            releaseOscAddressSlot(label);
            return slot;
        }
        
        int sendVal(int label, int maxBlobNum, glm::vec2 vel, float area, int age, glm::vec2 center, glm::vec2 inputSize){
            ofxOscMessage m;
            int slot = getOscAddressSlot(label, maxBlobNum);
            // Debug slot churn: only log when a slot changes owner, and only when log level allows.
            auto itPrev = lastLabelBySlot.find(slot);
            if (itPrev == lastLabelBySlot.end() || itPrev->second != label) {
                const int prev = (itPrev == lastLabelBySlot.end()) ? -1 : itPrev->second;
                ofLogNotice("OscSender") << "slot " << slot << " label " << prev << " -> " << label
                                         << " y=" << (center.y / inputSize.y)
                                         << " age=" << age
                                         << " frame=" << frameCounter;
                lastLabelBySlot[slot] = label;
            }
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

        // When only one blob is visible, pin it to slot 1 to avoid note/slot drift
        // from tracker label churn.
        void forceSingleLabelToSlot1(int label){
            labelToSlot.clear();
            labelLastSeenFrame.clear();
            lastLabelBySlot.clear();
            labelToSlot[label] = 1;
            labelLastSeenFrame[label] = frameCounter;
            lastLabelBySlot[1] = label;
            fallbackRoundRobinSlot = 1;
        }

        void forceVisibleLabelsToLowestSlots(const std::vector<int>& labels){
            if (labels.empty()) {
                return;
            }

            lastLabelBySlot.clear();
            for (std::size_t i = 0; i < labels.size(); ++i) {
                const int label = labels[i];
                const int slot = static_cast<int>(i) + 1;
                labelToSlot[label] = slot;
                labelLastSeenFrame[label] = frameCounter;
                lastLabelBySlot[slot] = label;
            }

            fallbackRoundRobinSlot = static_cast<int>(labels.size()) + 1;
            if (fallbackRoundRobinSlot < 1) {
                fallbackRoundRobinSlot = 1;
            }
        }

        void sendMergeEvent(int prevCount, int currentCount, int label){
            ofxOscMessage m;
            m.setAddress(oscMergeAddress);
            m.addIntArg(prevCount);
            m.addIntArg(currentCount);
            m.addIntArg(label);
            sender.sendMessage(m, false);
        }

        void sendDeathEvent(int label, int slot){
            ofxOscMessage m;
            m.setAddress(oscDeathAddress);
            m.addIntArg(label);
            m.addIntArg(slot);
            sender.sendMessage(m, false);
        }
        
        int getOscAddressSlot(int label, int maxBlobNum);
        void releaseOscAddressSlot(int label);
        
    private:
        glm::vec2 toPolar(float x, float y, float w, float h){
            // Match the proven Blob 1/2/3/4 Max maths so Blob 5+ can read source-side
            // azimuth/distance directly without doing a second conversion in Max.
            const float xNorm = ofClamp(x / w, 0.0f, 1.0f);
            const float yNorm = ofClamp(y / h, 0.0f, 1.0f);

            const float cx = xNorm - 0.5f;
            const float cy = (1.0f - yNorm) - 0.5f;

            float angleNorm = 0.5f;
            if (!(cx == 0.0f && cy == 0.0f)) {
                angleNorm = 0.5f - std::atan2(-cx, cy) / 6.283185307179586f;
                angleNorm -= std::floor(angleNorm);
            }

            float distNorm = std::sqrt(cx * cx + cy * cy) / 0.70710678f;
            distNorm = std::pow(distNorm, 1.1f);
            distNorm = ofClamp(distNorm, 0.0f, 1.0f);

            return glm::vec2(angleNorm, distNorm);
        }
        
        ofxOscSender sender;
        std::map<int, int> labelToSlot;
        std::map<int, uint64_t> labelLastSeenFrame;
        std::map<int, int> lastLabelBySlot;
        uint64_t frameCounter = 0;
        // More tolerant stale window reduces slot churn under brief detection dropouts.
        int slotStaleFrames = 8;
        int fallbackRoundRobinSlot = 1;

    public:
        // OSC sender settings
        ofParameter<string> oscIp{"IP", "localhost"};
        ofParameter<int> oscPort{"port", 12345, 0, 12345};
        // Legacy Max route object in AMXD matches symbols without a leading slash.
        const std::string oscAddressBase = "NDITracker";
        const std::string oscMergeAddress = "NDITrackerMerge";
        const std::string oscDeathAddress = "NDITrackerDeath";
        ofParameterGroup grp{"OSC send", oscIp, oscPort};
        
        ofEventListeners listenerHolder;
    };
    
}
