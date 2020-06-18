#include "ofApp.h"

using namespace ofxNDI::Recv;

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    NDIlib_initialize();

    NDIConnectButton.addListener(this, &ofApp::NDIConnectButtonPressed);
    
    gui.setup("settings", "settings.json");
    gui.add(appPrm.grp);
    gui.add(NDIConnectButton.setup("NDIConnect"));

    int camWidth = 640;
    int camHeight = 480;

    for(int i=0; i<10; i++){
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
    NDIconnect();
}


void ofApp::NDIconnect(){
    
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

//--------------------------------------------------------------
void ofApp::update(){
    
    appPrm.set();
    
    for (int i=0; i<ndis.size(); i++){
        ndis[i]->update();
    }
    
    for (int i=0; i<ndis.size(); i++){
        ndis[i]->findContour();
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    for (int i=0; i<ndis.size(); i++){
        ofPushMatrix();
        ofTranslate(0,i*250);
        ndis[i]->draw();
        ofPopMatrix();
    }
    
    for (int i=0; i<ndis.size(); i++){
        ndis[i]->sendNDI();
    }
    
    if(!bHide){
        ofDisableDepthTest();
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    switch (key){
            
        case 'h':
            bHide = !bHide;
            break;

        case 'f':
            ofToggleFullscreen();
            break;

        case ' ':
            for (int i=0; i<ndis.size(); i++){
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

