#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "NDIsource.h"
#include "AppParam.h"
#include "ofxOscReceiver.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
    void connectNDI();
	void keyPressed(int key);
    void receiveOsc();
    
    bool bHide = false;
    vector<std::shared_ptr<NDIsource>> ndis;

    ofxPanel gui;
    mtb::AppParam appPrm;

    ofParameter<void> connectNDIBtn{"Connect NDI"};
    ofParameter<bool> soloMode{"Solo", false};
    ofEventListeners listenerHolder;

    // this is for receiving Re-consttuctor OSC
    ofxOscReceiver oscReceiver;
    
    int hasOscReceived = 0;
    int oscNumArgs = 0;
};
