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
        
        grayImage.allocate(w,h);
        grayBg.allocate(w,h);
        grayDiff.allocate(w,h);

        // NDI sender
        if(ndiOut){
            std::string streamOutName =  prm.getName() + "-Out";
            ofLogNotice() << "Setup NDI sender " << streamOutName;
            if(sender.setup(streamOutName)) {
                senderVideo.setup(sender);
                senderVideo.setAsync(true);
            }else{
                ofLogError() << "Can not setup NDI sender";
            }
            
            sender_Fbo.allocate(640, 360, GL_RGBA);
            sender_Fbo.begin();
            ofClear(255,255,255, 0);
            sender_Fbo.end();
        }
        
        // OSC Sender
        oscSender.setup(HOST, PORT);
    }
    
    void update(){
        if(showNDI){
            if(receiver.isConnected()){
                video.update();
        
                if(video.isFrameNew()) {
                    frameCounter++;
                    auto & frame = video.getFrame();
                    int xres = frame.xres;
                    int yres = frame.yres;
                    
                    if(xres != 0 && yres != 0 ){
                        video.decodeTo(pixels);
                        pixels.setImageType(OF_IMAGE_GRAYSCALE);
                        grayImageFixed.setFromPixels(pixels);
                        grayImage.scaleIntoMe(grayImageFixed);
                    }
                }

                grayDiff.absDiff(grayBg, grayImage);
                grayDiff.threshold(bgThreshold);
            }
            
            
            if (bgTeachnique == false || bLearnBakground) {
                grayBg = grayImage;
                bLearnBakground = false;
            }else{
                if(frameCounterBGSet > 0) {
                    if (frameCounter > frameCounterBGSet) {
                        grayBg = grayImage;
                        frameCounter =0;
                    }
                }
            }
        }
    }

    void findContour(){
        if(showNDI){
            // contour finder
            contourFinder.setMinAreaRadius(minAreaRadius);
            contourFinder.setMaxAreaRadius(maxAreaRadius);
            contourFinder.setThreshold(threshold);
            contourFinder.setFindHoles(bFindHoles);
            contourFinder.setSimplify(bSimplify);
            contourFinder.setAutoThreshold(bAutoThreshold);
            contourFinder.findContours(grayDiff);
        }
    }
    
    void draw(){
        if(!showNDI) return;
        
        if(receiver.isConnected()){
        
            ofSetColor(255);
            //ofImage(pixels).draw(0, 0, 320,240);
            grayImage.draw(0,0,320,240);
            grayBg.draw(320,0,320,240);
            grayDiff.draw(640,0,320,240);
            
            // contour
            ofxCv::RectTracker& tracker = contourFinder.getTracker();

            if(1){
                // send /on, /off osc message
                ofxOscBundle bundle;
                const vector<unsigned int>& newLabels = tracker.getNewLabels();
                const vector<unsigned int>& deadLabels = tracker.getDeadLabels();
                for(int i = 0; i < newLabels.size(); i++) {
                    int label = newLabels[i];
                    ofxOscMessage m;
                    m.setAddress(oscAddress.get()+"/on");
                    m.addIntArg(label);
                    bundle.addMessage(m);
                }
                for(int i = 0; i < deadLabels.size(); i++) {
                    int label = deadLabels[i];
                    ofxOscMessage m;
                    m.setAddress(oscAddress.get()+"/off");
                    m.addIntArg(label);
                    bundle.addMessage(m);
                }
                
                if(bundle.getMessageCount()>0){
                    oscSender.sendBundle(bundle);
                }
            }
            
            float camWidth = grayDiff.getWidth();
            float camHeight = grayDiff.getHeight();
            if(0){
                ofFill();
                ofSetHexColor(0x333333);
                ofDrawRectangle(960,0,320,240);
            }
            ofPushMatrix();
            ofTranslate(640, 0);
            //ofScale(320/camWidth, 240/camHeight);
            ofSetColor(255);
            
            ofxOscBundle bundle;

            for (int i=0; i<contourFinder.size(); i++){

                int label = contourFinder.getLabel(i);
                int age = tracker.getAge(label);
                glm::vec2 center = ofxCv::toOf(contourFinder.getCenter(i));
                const ofRectangle & rect = ofxCv::toOf(contourFinder.getBoundingRect(i));
                
                if(age > minAge){

                    glm::vec2 velocity = ofxCv::toOf(contourFinder.getVelocity(i));
                    float area = contourFinder.getContourArea(i) / (camWidth*camHeight);
                    const vector<ofPolyline> & polys = contourFinder.getPolylines();
                    
                    ofSetLineWidth(1);
                    ofNoFill();
                    
                    ofPushMatrix();
                    ofScale(320/camWidth, 240/camHeight);

                    ofColor c;
                    c.setHsb(label*10%255, 255, 255);
                    ofSetColor(c);

                    // Polylines
                    for(auto & p: polys){
                        p.draw();
                    }

                    ofTranslate(center);
                    
                    // Bounding Box
                    ofSetRectMode(OF_RECTMODE_CENTER);
                    ofDrawRectangle(0, 0, rect.width, rect.height);
                    ofSetRectMode(OF_RECTMODE_CORNER);
                    
                    // text
                    string msg = ofToString(label) + ":" + ofToString(tracker.getAge(label));
                    ofDrawBitmapString(msg, 0, 0);
                    
                    // velocity line
                    ofDrawLine(0, 0, velocity.x*4, velocity.y*4);
                    ofPopMatrix();
                    
                    // OSC
                    ofxOscMessage m;
                    m.setAddress(oscAddress);
                    m.addIntArg(label);
                    m.addFloatArg(center.x/camWidth);
                    m.addFloatArg(center.y/camHeight);
                    m.addFloatArg(glm::length(velocity));
                    m.addFloatArg(area);
                    m.addIntArg(age);
                    bundle.addMessage(m);
                
                }else {
                    ofPushMatrix();
                    ofScale(320/camWidth, 240/camHeight);
                    ofTranslate(center);
                    ofSetColor(255, 50);
                    ofSetRectMode(OF_RECTMODE_CENTER);
                    ofDrawRectangle(0, 0, rect.width, rect.height);
                    ofSetRectMode(OF_RECTMODE_CORNER);
                    ofPopMatrix();
                }
            }
            ofPopMatrix();
    
            if(bundle.getMessageCount()>0){
                oscSender.sendBundle(bundle);
            }
        }
        
        
        // name of NDI
        receiver.isConnected() ? ofSetHexColor(0x00ffff) : ofSetHexColor(0xff0000);
        ofDrawBitmapString(NDI_name, 0, 10);
    }
    
    
    void sendNDI(){
        if(ndiOut){
            sender_Fbo.begin();
            ofClear(0);
            contourFinder.draw();
            sender_Fbo.end();
            sender_Fbo.readToPixels(senderPixels);
            senderVideo.send(senderPixels);
        }
    }
    
    // receive
    ofxNDIReceiver receiver;
    ofxNDIRecvVideoFrameSync video;
    ofPixels pixels;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayImageFixed;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    //ofxCvContourFinder contourFinder;
    ofxCv::ContourFinder contourFinder;
    
    // send
    ofxNDISender sender;
    ofxNDISendVideo senderVideo;
    ofPixels senderPixels;
    ofFbo sender_Fbo; // with alpha
    
    bool bLearnBakground;
    int frameCounter = 0;
    
    ofxOscSender oscSender;
    
    ofParameter<string> NDI_name{"Name", "sender1"};
    ofParameter<bool> showNDI{"Show Stream",true};
    ofParameter<bool> ndiOut{"NDI OUT", true};
    ofParameter<bool> bgTeachnique{"BG Teachnique", true};
    ofParameter<int>  bgThreshold{"BG Threshold", 80, 10, 300};
    ofParameter<int> frameCounterBGSet{"Frame Counter BG Set", 300, 0, 1000};
    ofParameter<bool> audienceFlip{"Audience Flip", true};

    // CV::Contor, CV::Tracker
    ofParameter<bool> bAutoThreshold{ "Auto Threshold", false };
    ofParameter<float> threshold{ "threshold", 128, 0, 255 };
    ofParameter<float> minAreaRadius{ "minAreaRadius", 5, 0, 100 };
    ofParameter<float> maxAreaRadius{ "maxAreaRadius", 10, 0, 100 };
    ofParameter<bool> bFindHoles{ "find holes", false };
    ofParameter<bool> bSimplify{ "simplify", false };
    ofParameter<int> persistence{ "persistence (frames)", 15, 1, 60 };
    ofParameter<float> maxDistance{ "max distance (pix)", 100, 0, 300 };
    ofParameter<float> smoothingRate{ "smoothingRate", 0.5, 0, 1.0 };
    ofParameter<int> minAge{ "min age", 15, 1, 60 };
    ofParameterGroup trackerGrp{ "Tracker", minAreaRadius, maxAreaRadius, bAutoThreshold, threshold, bFindHoles, bSimplify, persistence, maxDistance, smoothingRate, minAge };
    
    ofParameter<string> oscAddress{"oscAddress", "NDITracker"};
    ofParameterGroup prm{"NDI source", NDI_name, showNDI, ndiOut,bgTeachnique, bgThreshold, frameCounterBGSet, audienceFlip, trackerGrp, oscAddress};
};
