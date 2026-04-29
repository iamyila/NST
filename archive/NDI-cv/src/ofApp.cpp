#include "ofApp.h"

using namespace ofxNDI::Recv;

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Cameras used
    camsUsed = 10;
    
    // NDI image resolution
    camWidth = 640;
    camHeight = 480;
    
    NDIConnectButton.addListener(this, &ofApp::NDIConnectButtonPressed);

    moveImage = 0;
    
    gui.setup(); // most of the time you don't need a name
    gui.add(fps.setup("FPS", 25, 1, 60));
    gui.add(NDIConnectButton.setup("NDIConnect"));
    
    gui.add(showNDI[0].setup(NDI_streams[0], true));
    gui.add(bgTeachnique[0].setup("BG0", true));
    gui.add(showNDI[1].setup(NDI_streams[1], true));
    gui.add(bgTeachnique[1].setup("BG1", true));
    gui.add(showNDI[2].setup(NDI_streams[2], true));
    gui.add(bgTeachnique[2].setup("BG2", true));
    gui.add(showNDI[3].setup(NDI_streams[3], true));
    gui.add(bgTeachnique[3].setup("BG3", true));
    gui.add(showNDI[4].setup(NDI_streams[4], true));
    gui.add(bgTeachnique[4].setup("BG4", true));
    gui.add(showNDI[5].setup(NDI_streams[5], true));
    gui.add(bgTeachnique[5].setup("BG5", true));
    gui.add(showNDI[6].setup(NDI_streams[6], true));
    gui.add(bgTeachnique[6].setup("BG6", true));
    gui.add(showNDI[7].setup(NDI_streams[7], true));
    gui.add(bgTeachnique[7].setup("BG7", true));
    gui.add(showNDI[8].setup(NDI_streams[8], true));
    gui.add(bgTeachnique[8].setup("BG8", true));
    gui.add(showNDI[9].setup(NDI_streams[9], true));
    gui.add(bgTeachnique[9].setup("BG9", true));
    
    
    gui.add(threshold.setup("Threshold", 80, 10, 300));

    gui.add(minBlobSize.setup("minBlobSize", 20, 1, 3000));
    gui.add(maxBlobSize.setup("maxBlobSize", 10000, 10, 30000));
    
    
    gui.add(frameCounterBGSet.setup("Frames to new BG", 300, 10, 1000));
    
    
    //FRAMERATE
    ofSetFrameRate(fps);
    
    // open an outgoing connection to HOST:PORT
    oscSender.setup(HOST, PORT);
    
    NDIlib_initialize();
 
    
    for (int i = 0; i < camsUsed; i++){
        grayImage[i].allocate(camWidth,camHeight);
        grayBg[i].allocate(camWidth,camHeight);
        grayDiff[i].allocate(camWidth,camHeight);
        exitSender[i] = false;
        showNDI[i] = false;
        bgTeachnique[i] =false;
    }
    
    scaleX = 320/camWidth;
    scaleY = 240/camHeight;
    
    
    bHide = false;
    gui.loadFromFile("settings.xml");
    
    showInRows = -1;
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
    
    for (int i = 0; i < camsUsed; i++){

        if (showNDI[i] == true){
            string name_or_url = NDI_streams[i];    // Specify name or address of expected NDI source. In case of blank or not found, receiver will grab default(which is found first) source.
            auto result = findSource(name_or_url);
            if(result.second ? receiver_[i].setup(result.first) : receiver_[i].setup()) {
                video_[i].setup(receiver_[i]);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    //FRAMERATE
    ofSetFrameRate(fps);
    
    for (int i = 0; i < camsUsed; i++){

        if (showNDI[i] == 1) {
            
        if(receiver_[i].isConnected()) {
           video_[i].update();
            if(video_[i].isFrameNew()) {
                
                frameCounter++;
                video_[i].decodeTo(pixels_[i]);
                pixels_[i].setImageType(OF_IMAGE_GRAYSCALE);
                grayImageFixed[i].setFromPixels(pixels_[i]);
                grayImage[i].scaleIntoMe(grayImageFixed[i]);
                
            }
            
            grayDiff[i].absDiff(grayBg[i], grayImage[i]);
            grayDiff[i].threshold(threshold);
            
            
        }
                
                
            }
            
            if (bgTeachnique[i] == false) {
                //Use dynamic BG substraction
     
                 grayBg[i] = grayImage[i];
            }
            
                
        if (frameCounter > frameCounterBGSet) {
                grayBg[i] = grayImage[i];
            frameCounter =0;
        }
                // if not Use static BG substraction


           
            // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
            // also, find holes is set to true so we will get interior contours as well....
            contourFinder[i].findContours(grayDiff[i], minBlobSize, maxBlobSize, 1, false);
            
            //OSC STUFF
            if (contourFinder[i].nBlobs > 0) {
                
                //x = currentPosition
                //y = currentPosition
                
                ofPoint velocity(blobCenter[i].x - oldX, blobCenter[i].y - oldY);
                
                oldX = blobCenter[i].x;
                oldY = blobCenter[i].y;
                
                float dist = sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
                
                ofxOscMessage m;
                string adress = "NDITracker";
                adress.push_back(i + '0');
                m.setAddress(adress);
                m.addIntArg(contourFinder[i].nBlobs);
                m.addFloatArg(blobCenter[i].x/camWidth);
                m.addFloatArg(blobCenter[i].y/camHeight);
                m.addFloatArg(dist);
                m.addFloatArg(area[i]);
                oscSender.sendMessage(m, false);
                exitSender[i] = true;
                
            }
            else {
                //send the inactive message, just once
                if (exitSender[i] == true){
                    ofxOscMessage m;
                    string adress = "NDITracker";
                    adress.push_back(i + '0');
                    m.setAddress(adress);
                    m.addFloatArg(0);
                    oscSender.sendMessage(m, false);
                    exitSender[i] = false;
                }
            }
        }
    }


//--------------------------------------------------------------
void ofApp::draw(){
 ofEnableAlphaBlending();
    ofBackground(0);
    ofSetHexColor(0xffffff);
    
  for (int i = 0; i < camsUsed; i++){
      
      if (showNDI[i] == 1) {
          
          showInRows++;
          
          if(receiver_[i].isConnected()) {
            
              grayImage[i].draw(0,moveImage*50+10+260*showInRows,320,240);
              grayBg[i].draw(320,moveImage*50+10+260*showInRows,320,240);
              grayDiff[i].draw(640,moveImage*50+10+260*showInRows,320,240);
              
              // then draw the contours:
              ofFill();
              ofSetHexColor(0x333333);
              ofDrawRectangle(960,moveImage*50+10+260*showInRows,320,240);
              ofSetHexColor(0xffffff);
              
              // we could draw the whole contour finder
              //contourFinder.draw(360,540);
              // or, instead we can draw each blob individually from the blobs vector,
              // this is how to get access to them:
              ofPushMatrix();
              ofTranslate(960,moveImage*50+10+260*showInRows);
              ofScale(scaleX,scaleY);
              ofColor c(255, 255, 255);

                for (int k = 0; k < contourFinder[i].nBlobs; k++){
                    contourFinder[i].blobs[k].draw(0,0);
                    blobCenter[i].x = contourFinder[i].blobs.at(k).centroid.x;
                    blobCenter[i].y = contourFinder[i].blobs.at(k).centroid.y;
                    area[i] = contourFinder[i].blobs.at(k).area/ (camWidth*camHeight);
                    c.setHsb(k * 64, 255, 255);
                    ofSetColor(c);
                    ofDrawCircle(blobCenter[i], 5);
                    ofSetHexColor(0xffffff);
                }
              
              ofPopMatrix();
              ofSetHexColor(0x00ffff);
              stringstream reportStr;
              reportStr << NDI_streams[i];
              ofDrawBitmapString(reportStr.str(), 0,moveImage*50+10+260*showInRows);
              ofSetHexColor(0xffffff);
              
        }
      }
  }
    showInRows = -1;
    
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
            for (int i = 0; i < camsUsed; i++){
                bLearnBakground[i] = true;
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

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
