#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "NDISource.h"
#include "AppParam.h"
#include "ofxOscReceiver.h"

class ofApp : public ofBaseApp{
	
public:
    void setup();
	void update();
	void draw();
    void connectNDI();
    void refreshNDISources();
    void applySelectedNDISource();
	void keyPressed(int key);
    void windowResized(int w, int h);
    void receiveOsc();
    void updateLayout();
    void setupGui();
    void applyGuiScale(float scale);
    
    bool bHide = false;
    vector<std::shared_ptr<NDISource>> ndis;

    ofxPanel gui;
    mtb::AppParam appPrm;

    ofParameter<void> refreshSourcesBtn{"Refresh NDI Sources"};
    ofParameter<void> prevSourceBtn{"Prev NDI Source"};
    ofParameter<void> nextSourceBtn{"Next NDI Source"};
    ofParameter<int> ndiSourceIndex{"NDI Source Index (internal)", 0, 0, 0};
    // TODO: Replace prev/next stepping with a clickable dropdown/list of source names.
    // The current text + prev/next flow works but is less discoverable when multiple streams exist.
    ofParameter<string> ndiSourceName{"Selected NDI Source", ""};
    ofParameter<void> applySelectedSourceBtn{"Apply Selected Source"};
    ofParameter<void> connectNDIBtn{"Connect NDI"};
    ofParameter<bool> soloMode{"Solo", false};
    ofParameter<bool> guiScaleEnabled{"Scale GUI", true};
    ofEventListeners listenerHolder;
    std::vector<ofxNDI::Source> availableNDISources;

    // this is for receiving Re-consttuctor OSC
    ofxOscReceiver oscReceiver;
    
    int hasOscReceived = 0;
    int oscNumArgs = 0;

    float sidebarWidth = 220.0f;
    float guiScale = 1.0f;
};
