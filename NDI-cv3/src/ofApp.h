#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "NDIsource.h"

// send host (aka ip address)
#define HOST "localhost"

/// send port
#define PORT 12345

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
    void NDIconnect();
	void keyPressed(int key);
    void exit();
    void NDIConnectButtonPressed();
    
    //char NDI_streams[10][32] = {"sender1", "sender2", "sender3", "sender4", "sender5", "sender6","sender7", "ALASTAIR-MCNEILL-BROWNS-IPHONE", "OBS", "OBS Preview" };
    
    vector<std::shared_ptr<NDIsource>> ndis;
    
    ofxOscSender oscSender;

    //ofxIntSlider fps;
    ofxButton NDIConnectButton;
    ofxPanel gui;
    
    float oldX, oldY;
    
    int moveImage = 0;
    bool bHide = false;
    int showInRows = -1;
    float frameCounter;
    
    ofSoundPlayer ring;
};
