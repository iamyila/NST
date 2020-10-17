#include "ofApp.h"

using namespace ofxNDI::Recv;

void ofApp::setup(){

    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetVerticalSync(false);
    
    NDIlib_initialize();

    gui.setup("settings", "settings.json");
    gui.add(appPrm.grp);
    gui.add(connectNDIBtn);
    gui.add(soloMode);
    listenerHolder.push(connectNDIBtn.newListener([&](void){ connectNDI();}));
    
    gui.setPosition(10, 30);
    
    for(int i=0; i<10; i++){
        std::shared_ptr<NDIsource> ndi = make_shared<NDIsource>();
        ndi->prm.setName("NDI source " + ofToString(i+1));
        gui.add(ndi->prm);
        ndis.emplace_back(ndi);
    }
    
    gui.loadFromFile("settings.json");
    gui.minimizeAll();

    int camWidth = 640;
    int camHeight = 360;
    for(int i=0; i<ndis.size(); i++){
        ndis[i]->setup(camWidth, camHeight);
    }
    connectNDI();
    
    oscReceiver.setup(9999);
}

void ofApp::connectNDI(){
    
    ofLogNotice() << "Listing existing NDI sources.." << endl;
    auto sources = ofxNDI::listSources();
    ofLogNotice() << "Found " << sources.size() << " sources"<< endl;
    for(auto & s : sources){
        ofLogNotice() << s.p_ndi_name;
    }
    
    for (int i=0; i <ndis.size(); i++){
        shared_ptr<NDIsource> ndi = ndis[i];
        if (!ndi->showNDI) continue;
        
        string name_or_url = ndi->NDI_name;
        if(name_or_url == "") continue;
        
        cout << "Looking for NDI source named : " << name_or_url;
        
        bool found = false;
        for(auto & s : sources){
            found = ofIsStringInString(s.p_ndi_name, name_or_url) || ofIsStringInString(s.p_url_address, name_or_url);
            cout << ".";
            
            if(found){
                ndi->receiver.setup(s);
                cout << " ok!" << endl;
                ndi->video.setup(ndi->receiver);
                break;
            }
        }
        
        if(!found) cout << " Not found" << endl;
        //ndi->receiver.setup();
    }
    
    cout << endl;
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
                ndis[i]->glitch.doGlitch(oscNumArgs);
            }
        }
    }
}

void ofApp::draw(){
    
    if(soloMode == 0){
        ofPushMatrix();
        ofTranslate(220, 30);
        ofSetColor(255);
        
        for (int i=0; i<ndis.size(); i++){
            ofPushMatrix();
            ofTranslate(i*360, 0);
            ndis[i]->draw();
            ofPopMatrix();
        }
        ofPopMatrix();
    
        if(!bHide){
            ofDisableDepthTest();
            gui.draw();
            
            ofPushMatrix();
            ofTranslate(20, 180*5 - 90);
            if(hasOscReceived-- > 0){
                ofFill();
                ofSetColor(200, 0, 100);
                ofDrawCircle(0, 0, 5, 5);
                ofDrawBitmapString("OSC received", 10, 5);
            }
            ofPopMatrix();
        }

    }else{
        int ndiCh = soloMode-1;
        if(0<=ndiCh && ndiCh<ndis.size()){
            auto ndi = ndis[ndiCh];
            ofPushMatrix();
            ndi->drawSolo();
            ofPopMatrix();
        }
    }
    
    for (int i=0; i<ndis.size(); i++){
        ndis[i]->sendNDI();
    }

}

void ofApp::keyPressed(int key){

    if(48<=key && key< 58){
        cout << key << endl;
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
            connectNDI();
            break;
        
        case 's':
            ndis[0]->heatmap.save();
            break;
            
        case 'g':
            ndis[0]->glitch.doGlitch(ofRandom(1, 10));
            break;
    }
}

