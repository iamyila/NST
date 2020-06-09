//
//  NDIcontrol.cpp
//  NDI-cv
//
//  Created by Sebastian Frisch on 25.05.20.
//

#include "NDIcontrol.h"



NDIcontrol::NDIcontrol() {
    // TODO Auto-generated constructor stub
    
}


void NDIcontrol::setup(string name){
    parameters.setName(name);
    parameters.add(showNDI.set("Show Stream",true));
    parameters.add(bgThreshold.set("Threshold", 80, 10, 300));
    parameters.add(bgTeachnique.set("BG", true));
    parameters.add(ndiOut.set("NDI_OUT", true));
    parameters.add(audienceFlip.set("audienceFlip", true));
    parameters.add(minBlobSize.set("minBlobSize", 20, 1, 3000));
    parameters.add(maxBlobSize.set("maxBlobSize", 10000, 10, 30000));
    parameters.add(frameCounterBGSet.set("Frames to new BG", 300, 0, 1000));
    
    
}

