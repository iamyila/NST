//
//  OscSender.cpp
//

#include "OscSender.h"

namespace mtb{
    
    int OscSender::getOscAddressSlot(int label, int maxBlobNum){
        // Keep slot assignment stable and compact for currently active labels.
        // This avoids sparse slot jumps (e.g. using slot 3 when only two blobs are active).
        if (maxBlobNum < 1) {
            return 1;
        }

        auto it = labelToSlot.find(label);
        if (it != labelToSlot.end()) {
            if (it->second >= 1 && it->second <= maxBlobNum) {
                labelLastSeenFrame[label] = frameCounter;
                return it->second;
            }
            labelToSlot.erase(it);
            labelLastSeenFrame.erase(label);
        }

        // Reclaim stale labels quickly so a single visible blob does not rotate slots
        // when tracker labels churn for a few frames.
        std::vector<int> staleLabels;
        for (const auto& kv : labelLastSeenFrame) {
            const int seenLabel = kv.first;
            const uint64_t lastSeen = kv.second;
            if (frameCounter > lastSeen + static_cast<uint64_t>(slotStaleFrames)) {
                staleLabels.push_back(seenLabel);
            }
        }
        for (int staleLabel : staleLabels) {
            labelLastSeenFrame.erase(staleLabel);
            labelToSlot.erase(staleLabel);
        }

        std::vector<bool> used(maxBlobNum + 1, false);
        for (const auto& kv : labelToSlot) {
            if (kv.second >= 1 && kv.second <= maxBlobNum) {
                used[kv.second] = true;
            }
        }

        for (int slot = 1; slot <= maxBlobNum; ++slot) {
            if (!used[slot]) {
                labelToSlot[label] = slot;
                labelLastSeenFrame[label] = frameCounter;
                return slot;
            }
        }

        // Fallback if all slots are occupied:
        // cycle slot selection in round-robin order so replacement voices
        // rotate 1..N instead of sticking to a modulo-biased slot.
        int slot = fallbackRoundRobinSlot;
        if (slot < 1 || slot > maxBlobNum) {
            slot = 1;
        }
        fallbackRoundRobinSlot = slot + 1;
        if (fallbackRoundRobinSlot > maxBlobNum) {
            fallbackRoundRobinSlot = 1;
        }
        labelToSlot[label] = slot;
        labelLastSeenFrame[label] = frameCounter;
        return slot;
    }

    void OscSender::releaseOscAddressSlot(int label){
        labelToSlot.erase(label);
        labelLastSeenFrame.erase(label);
    }
}
