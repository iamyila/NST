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
                return it->second;
            }
            labelToSlot.erase(it);
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
                return slot;
            }
        }

        // Fallback if all slots are occupied.
        int slot = (label % maxBlobNum + maxBlobNum) % maxBlobNum + 1;
        labelToSlot[label] = slot;
        return slot;
    }

    void OscSender::releaseOscAddressSlot(int label){
        labelToSlot.erase(label);
    }
}
