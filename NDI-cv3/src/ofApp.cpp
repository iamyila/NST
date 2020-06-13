#include "ofApp.h"

using namespace ofxNDI::Recv;

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    NDIlib_initialize();

    NDIConnectButton.addListener(this, &ofApp::NDIConnectButtonPressed);
    
    gui.setup("settings", "settings.json");
    //gui.add(fps.setup("FPS", 25, 1, 60));
    gui.add(NDIConnectButton.setup("NDIConnect"));

    int camWidth = 640;
    int camHeight = 480;

    for(int i=0; i<3; i++){
        std::shared_ptr<NDIsource> ndi = make_shared<NDIsource>();
        ndi->prm.setName("NDI source " + ofToString(i+1));
        gui.add(ndi->prm);
        ndis.emplace_back(ndi);
    }
    
    gui.loadFromFile("settings.json");
    gui.minimizeAll();

    for(int i=0; i<ndis.size(); i++){
        ndis[i]->setup(camWidth, camHeight);
    }
}


void ofApp::NDIconnect(){
    
    auto findSource = [](const string &name_or_url) {
        auto sources = ofxNDI::listSources();
        if(name_or_url == "") {
            return make_pair(ofxNDI::Source(), false);
        }
        auto found = find_if(begin(sources), end(sources), [name_or_url](const ofxNDI::Source &s) {
            ofLogNotice() << s.p_ndi_name << ", " << name_or_url;
            //return s.p_ndi_name == name_or_url;
            return ofIsStringInString(s.p_ndi_name, name_or_url) || ofIsStringInString(s.p_url_address, name_or_url);
        });
        if(found == end(sources)) {
            ofLogWarning("ofxNDI") << "no NDI source found by string:" << name_or_url;
            return make_pair(ofxNDI::Source(), false);
        }
        return make_pair(*found, true);
    };
    
    for (int i=0; i <ndis.size(); i++){
        shared_ptr<NDIsource> ndi = ndis[i];
        if (ndi->showNDI == true){
            string name_or_url = ndi->NDI_name;    // Specify name or address of expected NDI source. In case of blank or not found, receiver will grab default(which is found first) source.
            auto result = findSource(name_or_url);
            if(result.second ? ndi->receiver.setup(result.first) : ndi->receiver.setup()) {
                ofLogNotice() << "Found NDI source " << name_or_url;
                ndi->video.setup(ndi->receiver);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i=0; i<ndis.size(); i++){
        ndis[i]->update();
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableAlphaBlending();
    ofBackground(0);
    
    for (int i=0; i<ndis.size(); i++){
        ofPushMatrix();
        ofTranslate(0,i*250);
        ndis[i]->draw();
        ofPopMatrix();
    }
    
    for (int i=0; i<ndis.size(); i++){
        ndis[i]->sendNDI();
    }

    for (int i=0; i<ndis.size(); i++){
        ndis[i]->sendOSC();
    }
    
    if(!bHide){
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key){
            
        case 'h':
            bHide = !bHide;
            break;
            
        case ' ':
            for (int i=0; i <ndis.size(); i++){
                ndis[i]->bLearnBakground = true;
            }
            break;
        case 's':
            gui.saveToFile("settings.json");
            break;
            
        case 'l':
            gui.loadFromFile("settings.json");
            break;
        case 'c':
            NDIconnect();
            break;
    }
}
void ofApp::NDIConnectButtonPressed(){
    NDIconnect();
}

void ofApp::exit(){
    NDIConnectButton.removeListener(this, &ofApp::NDIConnectButtonPressed);
}

