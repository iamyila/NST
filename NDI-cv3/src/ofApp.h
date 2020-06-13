#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "NDIsource.h"

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
    void NDIconnect();
	void keyPressed(int key);
    void exit();
    void NDIConnectButtonPressed();
    
    vector<std::shared_ptr<NDIsource>> ndis;
    
    ofxIntSlider fps;
    ofxButton NDIConnectButton;
    ofxPanel gui;
    
    bool bHide = false;
    
    ofSoundPlayer ring;
};
