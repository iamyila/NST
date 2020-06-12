#include "ofApp.h"

using namespace ofxNDI::Recv;

//--------------------------------------------------------------
void ofApp::setup(){

    NDIlib_initialize();

    ofSetFrameRate(60);

    // NDI image resolution
    NDIConnectButton.addListener(this, &ofApp::NDIConnectButtonPressed);
    
    gui.setup("settings", "settings.json");
    //gui.add(fps.setup("FPS", 25, 1, 60));
    gui.add(NDIConnectButton.setup("NDIConnect"));

    int camWidth = 640;
    int camHeight = 480;

    for(int i=0; i<10; i++){
        std::shared_ptr<NDIsource> ndi = make_shared<NDIsource>();
        ndi->setup(camWidth, camHeight);
        gui.add(ndi->prm);
        ndis.emplace_back(ndi);
    }
    
    gui.loadFromFile("settings.json");
    gui.minimizeAll();
    
    oscSender.setup(HOST, PORT);
}


void ofApp::NDIconnect(){
    
    auto findSource = [](const string &name_or_url) {
        auto sources = ofxNDI::listSources();
        if(name_or_url == "") {
            return make_pair(ofxNDI::Source(), false);
        }
        auto found = find_if(begin(sources), end(sources), [name_or_url](const ofxNDI::Source &s) {
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
    ofSetHexColor(0xffffff);
    
    for (int i=0; i<ndis.size(); i++){
        ofPushMatrix();
        ofTranslate(0,i*250);
        ndis[i]->draw();
        ofPopMatrix();
    }
    
//    for (int i=0; i<ndis.size(); i++){
//
//      if (stream[i].showNDI == 1) {
//
//          showInRows++;
//
//          if(receiver_[i].isConnected()) {
//
//              ofSetColor(255);
//              ofImage(pixels_[i]).draw(100,100, 320,240);
//              int x = pixels_[i].getWidth();
//              int y = pixels_[i].getHeight();
//              int ch = pixels_[i].getNumChannels();
//              ofLogNotice() << "x " << x << ", y " << y << ", ch "<<  ch;
              
              //grayImage[i].draw(0,moveImage*50+10+260*showInRows,320,240);
              //grayBg[i].draw(320,moveImage*50+10+260*showInRows,320,240);
              //grayDiff[i].draw(640,moveImage*50+10+260*showInRows,320,240);
              
              // then draw the contours:
//              ofFill();
//              ofSetHexColor(0x333333);
//              ofDrawRectangle(960,moveImage*50+10+260*showInRows,320,240);
//              ofSetHexColor(0xffffff);
//

              
            
              // we could draw the whole contour finder
              //contourFinder.draw(360,540);
              // or, instead we can draw each blob individually from the blobs vector,
              // this is how to get access to them:
//              ofPushMatrix();
//              ofTranslate(960,moveImage*50+10+260*showInRows);
//              ofScale(scaleX,scaleY);
//              ofColor c(255, 255, 255);
//
//                for (int k = 0; k < contourFinder[i].nBlobs; k++){
//                    contourFinder[i].blobs[k].draw(0,0);
//                    blobCenter[i].x = contourFinder[i].blobs.at(k).centroid.x;
//                    blobCenter[i].y = contourFinder[i].blobs.at(k).centroid.y;
//                    area[i] = contourFinder[i].blobs.at(k).area/ (camWidth*camHeight);
//                    c.setHsb(k * 64, 255, 255);
//                    ofSetColor(c);
//                    ofDrawCircle(blobCenter[i], 5);
//                    ofSetHexColor(0xffffff);
//                }
//
//              ofPopMatrix();
//              ofSetHexColor(0x00ffff);
//              stringstream reportStr;
//              reportStr << NDI_streams[i];
//              ofDrawBitmapString(reportStr.str(), 0,moveImage*50+10+260*showInRows);
//              ofSetHexColor(0xffffff);
//        }
//      }
//  }
    
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
                gui.saveToFile("settings.xml");
            break;
            
        case 'l':
                gui.loadFromFile("settings.xml");
            break;
        case 'c':
            NDIconnect();
            break;
            
        case OF_KEY_DOWN:
            moveImage++;
            break;
            
        case OF_KEY_UP:
            moveImage--;
            break;
    }
}
void ofApp::NDIConnectButtonPressed(){
    NDIconnect();
}

void ofApp::exit(){
    NDIConnectButton.removeListener(this, &ofApp::NDIConnectButtonPressed);
}

