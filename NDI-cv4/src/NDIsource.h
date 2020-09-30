//
//  NDIsource.h
//

#pragma once

#include "ofMain.h"
#include "ofxNDIVideoGrabber.h"
#include "ofxNDIReceiver.h"
#include "ofxNDIRecvStream.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "ofxNDISender.h"
#include "ofxNDISendStream.h"

using std::string;

// OSC send
#define HOST "localhost"
#define PORT 12345

class NDIsource{
    
public:
    NDIsource(){};
    
    void setup(int w, int h){
        
//        float sw = 300;
//        float sh = 300;
//        glm::vec2 r1 = toPolar(100, 0, sw, sh);
//        glm::vec2 r2 = toPolar(150, 200, sw, sh);
//        glm::vec2 r3 = toPolar(50, 100, sw, sh);
                
        currentImage.allocate(w,h);
        currentImageFixed.allocate(w,h);
        finalImage.allocate(w,h);

        // NDI sender
        setupNDI_OUT();
        sender_Fbo.allocate(w, h, GL_RGBA);
        sender_Fbo.begin();
        ofClear(255,255,255, 0);
        sender_Fbo.end();

        // OSC Sender
        oscSender.setup(HOST, PORT);
        
        listenerHolder.push(ndiOut.newListener([&](bool & b){ setupNDI_OUT(); }));
        listenerHolder.push(bgAlgo.newListener([&](int & algo){ setupBS(); }));
        
        setupBS();
    }
    
    void setupNDI_OUT(){
        if(ndiOut && !sender.isSetup()){
            std::string streamOutName =  prm.getName() + "-Out";
            ofLogNotice() << "Setup NDI sender " << streamOutName;
            if(sender.setup(streamOutName)) {
                senderVideo.setup(sender);
                senderVideo.setAsync(true);
            }else{
                ofLogError() << "Can not setup NDI sender";
            }
        }
    }
    
    void setupBS(){
        if (bgAlgo==0){
            pBackSub = cv::createBackgroundSubtractorMOG2();
        }else{
            pBackSub = cv::createBackgroundSubtractorKNN();
        }
    }
    
    void update(){
        
        if(showNDI){
            if(receiver.isConnected()){
                video.update();
        
                if(video.isFrameNew()) {
                    auto & frame = video.getFrame();
                    int xres = frame.xres;
                    int yres = frame.yres;
                    
                    if(xres != 0 && yres != 0 ){
                        video.decodeTo(pixels);
                        pixels.setImageType(OF_IMAGE_COLOR);
                        currentImageFixed.setFromPixels(pixels);

                        currentImage.scaleIntoMe(currentImageFixed);
                        currentMat = ofxCv::toCv(currentImage);
                        pBackSub->apply(currentMat, foregroundMat);
                        
                        ofPixels pix;
                        ofxCv::toOf(foregroundMat, pix);
                        pix.setImageType(OF_IMAGE_GRAYSCALE);
                        finalImage.setFromPixels(pix);
                        
                        findContour();
                        
                        sendNoteOnOff();
                        drawFbo();
                    }
                }
            }
        }
    }

    void findContour(){
        // contour finder
        if(finalImage.bAllocated){
            contourFinder.findContours(finalImage, minArea*minArea, maxArea*maxArea, maxBlobNum, bFindHoles, bSimplify);
            
            rects.clear();
            for(auto & b : contourFinder.blobs){
                rects.push_back(ofxCv::toCv(b.boundingRect));
            }
            tracker.setSmoothingRate(smoothingRate);
            tracker.setMaximumDistance(maxDistance);
            tracker.setPersistence(persistence);
            tracker.track(rects);
        }
    }
    
    void sendNoteOnOff(){
        // send /on, /off osc message
        ofxOscBundle bundle;
        const vector<unsigned int>& newLabels = tracker.getNewLabels();
        const vector<unsigned int>& deadLabels = tracker.getDeadLabels();
        for(int i = 0; i < newLabels.size(); i++) {
            int label = newLabels[i];
            detectedBlobs.emplace(label, false);    // age = 1

            ofLogVerbose() << "New blob : " << label;
        }
        
        for(int i = 0; i<deadLabels.size(); i++) {
            int label = deadLabels[i];
            ofxOscMessage m;
            m.setAddress(oscAddress.get() + "/"+ ofToString(label%maxBlobNum+1) +"/off");
            m.addIntArg(label);
            bundle.addMessage(m);
            detectedBlobs.erase(label);
            ofLogVerbose() << "Dead blob : " << label;
        }

        
        // check detectedBlobs if it satisfies minAge to send NoteOn osc
        std::map<int, bool>::iterator itr = detectedBlobs.begin();
        for(; itr!=detectedBlobs.end(); itr++) {
            bool noteOnSent = (*itr).second;
            if(!noteOnSent){
                int label = (*itr).first;
                int age = tracker.getAge(label);
                if(minAge <= age){
                    ofxOscMessage m;
                    m.setAddress(oscAddress.get()+ "/" + ofToString(getOscAddressSlot(label)) +"/on");
                    m.addIntArg(label);
                    bundle.addMessage(m);
                    (*itr).second = true;
                }
            }
        }
        
        if(bundle.getMessageCount()>0){
            oscSender.sendBundle(bundle);
        }
    }
    
    void drawFbo(){
        
        float camWidth = finalImage.getWidth();
        float camHeight = finalImage.getHeight();
        int nBlobs = contourFinder.blobs.size();
        int okBlobNum = 0;
        
        sender_Fbo.begin();
        ofClear(0,0,0,0);
        
        for(int i=0; i<nBlobs; i++){
            int label = tracker.getCurrentLabels()[i];
            int age = tracker.getAge(label);
            ofxCvBlob & blob = contourFinder.blobs[i];
            ofRectangle & rect = blob.boundingRect;
            glm::vec2 center(rect.x + rect.width/2, rect.y + rect.height/2);
            
            if(minAge <= age){
                
                glm::vec2 velocity = ofxCv::toOf(tracker.getVelocity(i));
                float area = blob.area / (camWidth*camHeight);
                
                ofSetLineWidth(1);
                ofNoFill();
                ofPushMatrix();
                
                // Polyline & rect
                ofNoFill();
                blob.draw();
                
                if(0){
                    ofTranslate(center.x+20, center.y);
                    ofColor c;
                    c.setHsb(label*10%255, 255, 255);
                    ofSetColor(c);
                    string msg = ofToString(label) + ":" + ofToString(age);
                    ofDrawBitmapString(msg, 0, 0);
                }
                
                ofPopMatrix();
                
                // OSC
                ofxOscMessage m;
                m.setAddress(oscAddress.get() + "/" + ofToString(getOscAddressSlot(label)) +"/val");
                m.addIntArg(label);
                m.addFloatArg(center.x/camWidth);
                m.addFloatArg(center.y/camHeight);
                m.addFloatArg(glm::length(velocity));
                m.addFloatArg(area);
                m.addIntArg(age);
                
                // polar coordinate
                glm::vec2 p = toPolar(center.x, center.y, camWidth, camHeight);
                m.addFloatArg(p.x);
                m.addFloatArg(p.y);

                oscSender.sendMessage(m);
                
                okBlobNum++;
                if(okBlobNum >= maxBlobNum) break;
            }else {
                ofPushMatrix();
                ofTranslate(center);
                ofSetColor(255, 180);
                ofNoFill();
                ofSetRectMode(OF_RECTMODE_CENTER);
                ofDrawRectangle(0, 0, rect.width, rect.height);
                ofSetRectMode(OF_RECTMODE_CORNER);
                 if(0){
                    string msg = ofToString(label) + ":" + ofToString(age);
                    ofDrawBitmapString(msg, 0, 0);
                 }
                ofPopMatrix();
            }
        }
        ofPopMatrix();

        
        sender_Fbo.end();

    }
    
    glm::vec2 toPolar(float x, float y, float w, float h){
        float tx = x/w*2.0 - 1.0;
        float ty = (h-y)/h*2.0 - 1.0;
        
        float angle = 0;
        if(!(tx==0 && ty==0)){
            angle = atan2(tx, ty);
            angle = ofRadToDeg(angle);
        }
        float len = sqrt(tx*tx + ty*ty);
        len = ofMap(len, 0, 1.41421356, 0.01, 2.0, true);
        return glm::vec2(angle, len);
    }
    
    int getOscAddressSlot(int label){
        return label % maxBlobNum + 1;
    }
    
    void drawSolo(){
        if(!showNDI) return;
        
        if(receiver.isConnected()){
            int w = sender_Fbo.getWidth();
            int h = sender_Fbo.getHeight();
            ofRectangle v = ofRectangle(0,0,w,h);
            v.scaleTo(ofGetCurrentViewport());
            ofDisableAlphaBlending();
            ofSetColor(255);
            ofSetRectMode(OF_RECTMODE_CENTER);
            sender_Fbo.draw(ofGetWidth()/2, ofGetHeight()/2, v.width, v.height);
            ofSetRectMode(OF_RECTMODE_CORNER);
        }
    }
    
    void draw(){
        
        if(!showNDI) return;
        
        if(receiver.isConnected()){
            
            int w = 320;
            int h = 240;
            
            ofPushStyle();
            ofSetColor(255);
            currentImage.draw(0,0,w,h);
            ofxCv::drawMat(foregroundMat, w+10,0,w,h);
            ofEnableAlphaBlending();
            sender_Fbo.draw(w+10, 0, w, h);
            ofDisableAlphaBlending();
            sender_Fbo.draw(w*2+20, 0, w, h);
            
            ofPushMatrix();
            ofTranslate(w*3+30, 0);
            ofSetColor(255);
            ofDrawBitmapString("label   age   OscAdrsSlot", 0, -5);
            char c[255];
            
            int i = 0;
            map<int, bool>::iterator itr = detectedBlobs.begin();
            for(; itr!=detectedBlobs.end(); itr++){
                int label = (*itr).first;
                bool bNoteOnSent = (*itr).second;
                int age = tracker.getAge(label);
                bNoteOnSent ? ofSetHexColor(0xff0099) : ofSetColor(220);
                sprintf(c, "%5i %5i  %2i", label, age, getOscAddressSlot(label));
                ofDrawBitmapString(c, 0, (i+1)*15);
                i++;
            }
            ofPopMatrix();
            ofPopStyle();
        }
        
        // name of NDI
        receiver.isConnected() ? ofSetHexColor(0x00ffff) : ofSetHexColor(0xff0000);
        ofDrawBitmapString(NDI_name, 0, 10);
    }
    
    
    void sendNDI(){
        if(ndiOut && sender.isSetup()){
            sender_Fbo.readToPixels(senderPixels);
            senderVideo.send(senderPixels);
        }
    }
    
    // receive
    ofxNDIReceiver receiver;
    ofxNDIRecvVideoFrameSync video;
    ofPixels pixels;
    ofxCvColorImage currentImage;
    ofxCvColorImage currentImageFixed;
    ofxCvGrayscaleImage finalImage;
    ofxCvContourFinder contourFinder;
    
    ofxCv::RectTracker tracker;
    std::vector<cv::Rect> rects;
    std::map<int, bool> detectedBlobs; // label, noteOnSent
    
    // send
    ofxNDISender sender;
    ofxNDISendVideo senderVideo;
    ofPixels senderPixels;
    ofFbo sender_Fbo; // with alpha
    
    int frameCounter = 0;
    
    ofxOscSender oscSender;
    
    ofParameter<string> NDI_name{"Name", "sender1"};
    ofParameter<bool> showNDI{"Show Stream",true};
    ofParameter<bool> ndiOut{"NDI OUT", true};
    
    // cv::BackgroundSubtractor
    cv::Ptr<cv::BackgroundSubtractor> pBackSub;
    cv::Mat currentMat, foregroundMat;
    
    ofParameter<int> bgAlgo{"BG Algo", 1, 0, 1};
    ofParameterGroup bgGrp{"Background Subtractor", bgAlgo};
    
    // CV::Contor, CV::Tracker
    ofParameter<float> minArea{ "minArea", 5, 0, 100 };
    ofParameter<float> maxArea{ "maxArea", 10, 0, 300 };
    ofParameter<bool> bFindHoles{ "find holes", false };
    ofParameter<bool> bSimplify{ "simplify", false };
    ofParameter<int> persistence{ "persistence (frames)", 15, 1, 60 };
    ofParameter<float> maxDistance{ "max distance (pix)", 100, 0, 300 };
    ofParameter<float> smoothingRate{ "smoothingRate", 0.5, 0, 1.0 };
    ofParameter<int> maxBlobNum{ "Max blob num", 3, 1, 10 };
    ofParameter<int> minAge{ "Min age", 10, 0, 60 };
    ofParameterGroup trackerGrp{ "Tracker", minArea, maxArea, bFindHoles, bSimplify, persistence, maxDistance, smoothingRate, maxBlobNum, minAge };
    
    ofParameter<string> oscAddress{"oscAddress", "NDITracker"};
    ofParameterGroup prm{"NDI source", NDI_name, showNDI, ndiOut, bgGrp, trackerGrp, oscAddress};
    
    ofEventListeners listenerHolder;
};
