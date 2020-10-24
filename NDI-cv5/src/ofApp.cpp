#include "ofApp.h"

using namespace ofxNDI::Recv;

void ofApp::setup(){

	ofSetWindowShape(700, 1000);
	ofSetWindowPosition(0, 25);
    NDIlib_initialize();

    gui.setup("settings", "settings.json");
    gui.add(appPrm.grp);
    gui.add(connectNDIBtn);
    gui.add(soloMode);
    listenerHolder.push(connectNDIBtn.newListener([&](void){ connectNDI();}));
    
    gui.setPosition(10, 20);
    
    for(int i=0; i<1; i++){
        std::shared_ptr<NDIsource> ndi = make_shared<NDIsource>();
        ndi->prm.setName("NDI source " + ofToString(i+1));
        gui.add(ndi->prm);
        ndis.emplace_back(ndi);
    }
    
    gui.loadFromFile("settings.json");
    gui.minimizeAll();

    connectNDI();
    
    oscReceiver.setup(9999);
}

void ofApp::connectNDI(){

	for (int i = 0; i < ndis.size(); i++) {
		ndis[i]->setup();
		ndis[i]->connect();
    }    
}

void ofApp::update(){
    
    appPrm.set();
    
    for (int i=0; i<ndis.size(); i++){
        ndis[i]->update();
    }
    
    ofSetWindowTitle(ofToString((int)ofGetFrameRate()));
    
    receiveOsc();
}

void ofApp::receiveOsc(){
    
    oscNumArgs = 0;
    
    while(oscReceiver.hasWaitingMessages()){
        
        // get the next message
        ofxOscMessage m;
        oscReceiver.getNextMessage(m);
        
        // check for mouse moved message
        if(m.getAddress() == "/grainpotision"){
            // No idea to use this info so far
        }
        else if(m.getAddress() == "/grainsize"){
            int nArgs = m.getNumArgs();
            oscNumArgs += nArgs;
        }
    }
    
    if(oscNumArgs > 0){
        
        hasOscReceived = 4;

        for(int i=0; i<ndis.size(); i++){
            if(ndis[i]->getIsNDIConected()){
                if(ndis[i]->bGlitch){
                    ndis[i]->glitch.doGlitch(oscNumArgs);
                }
            }
        }
    }
}

void ofApp::draw(){
    
    if(!soloMode){
        ofPushMatrix();
        ofTranslate(220, 20);
        ofSetColor(255);
        
		int xpos = 0;
        for (int i=0; i<ndis.size(); i++){
    			
			ofPushMatrix();
            ofTranslate(xpos, 0);
            ndis[i]->draw();
            ofPopMatrix();

			int nMon = ndis[i]->getNumMonitor();
			int h = (ofGetHeight() - 200) / nMon - 10;
			int w = h * 1920 / 1080;
			xpos += (w + 10);
        }
        ofPopMatrix();
    
        if(!bHide){
            ofDisableDepthTest();
            gui.draw();            
        }

    }else{
        auto ndi = ndis[0];
        ofPushMatrix();
        ndi->drawSolo();
        ofPopMatrix();
    }
    
    for (int i=0; i<ndis.size(); i++){
        ndis[i]->sendNDI();
    }

}

void ofApp::keyPressed(int key){

    if(48<=key && key< 58){
        soloMode = key-48;
    }
    
    switch (key){
            
        case 'h':
            bHide = !bHide;
            break;

        case 'f':
            ofToggleFullscreen();
            break;

        case 'c':
		case ' ':
			connectNDI();
            break;
        
        case 's':
			soloMode = !soloMode;
            break;
            
        case 'g':
            ndis[0]->glitch.doGlitch(ofRandom(1, 10));
            break;
    }
}

