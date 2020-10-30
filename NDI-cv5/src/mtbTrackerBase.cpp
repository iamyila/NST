//
//  mtbTrackerBase.cpp
//

#include "mtbTrackerBase.h"
#include "NDISource.h"

namespace mtb{
    
    void mtbTrackerBase::registerUser(NDISource * s){
        user = s;
    }
    
    void mtbTrackerBase::addPointToHeatmap(float x, float y, float area){
        user->addPointToHeatmap(x, y, area);
    }
    
    void mtbTrackerBase::sendNoteOn(int label, int maxBlobNum){
        user->oscSender.sendNoteOn(label, maxBlobNum);
    }

    void mtbTrackerBase::sendNoteOff(int label, int maxBlobNum){
        user->oscSender.sendNoteOff(label, maxBlobNum);
    }
    
    void mtbTrackerBase::sendVal(int label, int maxBlobNum, glm::vec2 vel, float area, int age, glm::vec2 center, glm::vec2 inputSize){
        user->oscSender.sendVal(label, maxBlobNum, vel, area, age, center, inputSize);
    }
    
}
