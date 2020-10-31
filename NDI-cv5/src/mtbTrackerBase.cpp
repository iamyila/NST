//
//  mtbTrackerBase.cpp
//

#include "mtbTrackerBase.h"
#include "NDISource.h"

namespace mtb{
    
    void mtbTrackerBase::registerUser(NDISource * s){
        user = s;
    }
    
    int mtbTrackerBase::getOscAddressSlot(int label){
        return user->oscSender.getOscAddressSlot(label, maxBlobNum);
    }
    
    void mtbTrackerBase::addPointToHeatmap(float x, float y, float area){
        user->addPointToHeatmap(x, y, area);
    }
    
    int mtbTrackerBase::sendNoteOn(int label){
        return user->oscSender.sendNoteOn(label, maxBlobNum);        
    }

    int mtbTrackerBase::sendNoteOff(int label){
        return user->oscSender.sendNoteOff(label, maxBlobNum);
    }
    
    int mtbTrackerBase::sendVal(int label, glm::vec2 vel, float area, int age, glm::vec2 center, glm::vec2 inputSize){
        return user->oscSender.sendVal(label, maxBlobNum, vel, area, age, center, inputSize);
    }
    
}
