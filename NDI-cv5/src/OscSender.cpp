//
//  OscSender.cpp
//

#include "OscSender.h"

namespace mtb{
    
    int OscSender::getOscAddressSlot(int label, int maxBlobNum){
        return label % maxBlobNum + 1;
    }
}
