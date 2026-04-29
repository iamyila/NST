#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "NDIsource.h"
#include "AppParam.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
    void connectNDI();
	void keyPressed(int key);
    
    bool bHide = false;
    vector<std::shared_ptr<NDIsource>> ndis;

    ofxPanel gui;
    mtb::AppParam appPrm;

    ofParameter<void> connectNDIBtn{"Connect NDI"};
    ofParameter<int> soloMode{"Solo", 0, 0, 10};
    ofEventListeners listenerHolder;
};
