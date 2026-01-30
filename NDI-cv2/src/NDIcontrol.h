/*
 * NDIcontrol.h
 *
 *  Created on: 11/07/2012
 *      Author: Sebastian Frisch
 */

#ifndef NDIcontrol_H_
#define NDIcontrol_H_

#include "ofParameterGroup.h"
#include "ofParameter.h"
#include "ofMain.h"

class NDIcontrol;

template<typename ParameterType>
class ofNDIcontrolParam: public ofReadOnlyParameter<ParameterType,NDIcontrol>{
    friend class NDIcontrol;
};

class NDIcontrol {
public:
    NDIcontrol();
    
    void setup(string name);
    void draw();
    
    ofParameterGroup parameters;
    
    ofParameter<bool> showNDI;
    ofParameter<bool> bgTeachnique;
    ofParameter<int>  bgThreshold;
    ofParameter<bool> ndiOut;
    ofParameter<bool> audienceFlip;
    ofParameter<int> minBlobSize;
    ofParameter<int> maxBlobSize;
    ofParameter<int> frameCounterBGSet;
    
};

#endif /* NDIcontrol_H_ */


