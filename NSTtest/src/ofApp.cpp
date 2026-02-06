#include "ofApp.h"

using namespace ofxNDI::Recv;

void ofApp::setup(){

	ofSetWindowShape(700, 1000);
	ofSetWindowPosition(0, 25);
    NDIlib_initialize();

    for(int i=0; i<1; i++){
        std::shared_ptr<NDISource> ndi = make_shared<NDISource>();
        ndi->prm.setName("NDI Source " + ofToString(i+1));
        ndis.emplace_back(ndi);
    }

    applyGuiScale(guiScaleEnabled ? ofClamp(ofGetWidth() / 700.0f, 0.8f, 1.6f) : 1.0f);
    setupGui();
    updateLayout();
    gui.loadFromFile("settings.json");

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
        ofTranslate(sidebarWidth, 20);
        ofSetColor(255);
        
		int xpos = 0;
        for (int i=0; i<ndis.size(); i++){
    			
			ofPushMatrix();
            ofTranslate(xpos, 0);
            ndis[i]->draw();
            ofPopMatrix();

			int nMon = ndis[i]->getNumMonitor();
			int h = (ofGetHeight() - 150) / nMon - 10;
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

void ofApp::windowResized(int w, int h){
    if(guiScaleEnabled){
        float newScale = ofClamp(ofGetWidth() / 700.0f, 0.8f, 1.6f);
        if (fabs(newScale - guiScale) > 0.02f) {
            applyGuiScale(newScale);
            setupGui();
        }
    }
    updateLayout();
}

void ofApp::updateLayout(){
    const float minWidth = 220.0f;
    const float maxWidth = 520.0f;
    sidebarWidth = ofClamp(ofGetWidth() * 0.28f, minWidth, maxWidth);
    gui.setPosition(10, 20);
    gui.setWidthElements(sidebarWidth - 20.0f);
}

void ofApp::setupGui(){
    gui.clear();
    gui.setup("settings", "settings.json");
    gui.add(appPrm.grp);
    gui.add(connectNDIBtn);
    gui.add(soloMode);
    gui.add(guiScaleEnabled);
    for (auto &ndi : ndis) {
        gui.add(ndi->prm);
    }

    listenerHolder.unsubscribeAll();
    listenerHolder.push(connectNDIBtn.newListener([&](void){ connectNDI();}));
    listenerHolder.push(guiScaleEnabled.newListener([&](bool& b){
        applyGuiScale(b ? ofClamp(ofGetWidth() / 700.0f, 0.8f, 1.6f) : 1.0f);
        setupGui();
        updateLayout();
    }));
}

void ofApp::applyGuiScale(float scale){
    guiScale = scale;
    ofxGuiSetDefaultWidth(200.0f * guiScale);
    ofxGuiSetDefaultHeight(18.0f * guiScale);
    const int fontSize = static_cast<int>(ofClamp(14.0f * guiScale, 10.0f, 28.0f));
    const std::string fontPath = "/System/Library/Fonts/Supplemental/Arial.ttf";
    if (ofFile::doesFileExist(fontPath)) {
        ofxGuiSetFont(fontPath, fontSize, true, true);
    } else {
        ofxGuiSetBitmapFont();
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

		case ' ':
			connectNDI();
            break;
            
        case 's':
			soloMode = !soloMode;
            break;
            
        case 'g':
            ndis[0]->glitch.doGlitch(ofRandom(1, 10));
            break;
            
        case 'c':
            ndis[0]->tracker.bDrawCandidates = !ndis[0]->tracker.bDrawCandidates;
            break;

    }
}
