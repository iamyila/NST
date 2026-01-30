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
        grayFinal.allocate(w,h);
        grayDiff.allocate(w,h);

        // NDI sender
        setupNDI_OUT();
        sender_Fbo.allocate(w, h, GL_RGBA);
        sender_Fbo.begin();
        ofClear(255,255,255, 0);
        sender_Fbo.end();

        // OSC Sender
        oscSender.setup(HOST, PORT);
        
        listenerHolder.push(bUseBG.newListener([&](bool & b){
            if(bUseBG){
                grayBg = grayImage;
                grayFinal.clear();
            }else{
                grayBg.clear();
                grayFinal.clear();
            }
        }));
        
        listenerHolder.push(ndiOut.newListener([&](bool & b){
            if(ndiOut && !sender.isSetup()){
                setupNDI_OUT();
            }
        }));

    }
    
    void setupNDI_OUT(){
        if(ndiOut){
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
                        pixels.setImageType(OF_IMAGE_GRAYSCALE);
                        grayImageFixed.setFromPixels(pixels);
                        grayImage.scaleIntoMe(grayImageFixed);
                    }

                    if(bUseBG){

                        grayDiff.absDiff(grayBg, grayImage);
                        
                        grayDiff.threshold(bgThreshold);
                        
                        switch(bgMode){
                            case 0:
                                // single frame difference
                                grayFinal = grayDiff;
                                break;
                            case 1:
                                // additive background
                                grayFinal += grayDiff;
                                break;
                            case 2:
                            {
                                cv::Mat diffMat = ofxCv::toCv(grayDiff);
                                cv::Mat finalMat = ofxCv::toCv(grayFinal);
                                diffMat.convertTo(finalMat, CV_32F);
                                cv::accumulateWeighted(diffMat, finalMat, acmWeight);
                                break;
                            }
                            case 3:
                                //cv::background
                                break;
                        }
                        
                        if(bgMode >= 2){
                            if (frameCounter >= bgUpdateFrame) {
                                grayBg = grayImage;
                                frameCounter =0;
                                grayFinal = grayDiff;
                            }
                        }
                    }else{
                        grayBg.clear();
                        grayFinal = grayImage;
                    }
                    
                    frameCounter++;
                    
                    findContour();
                }
            }
        }
    }

    void findContour(){
        // contour finder
        if(grayFinal.bAllocated){
            contourFinder.findContours(grayFinal, minArea, maxArea, maxBlobNum, bFindHoles, bSimplify);
            
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
    
    void draw(){
        if(!showNDI) return;
        
        if(receiver.isConnected()){
        
            int h = 200;
            int w = h * 1920/1080;

            ofSetColor(255);
            grayImage.draw(0,0,w, h);
            if(bUseBG){
                grayBg.draw(w,0,w,h);
                grayFinal.draw(w*2,0,w,h);
            }else{
                ofNoFill();
                ofSetColor(255);
                ofDrawRectangle(w, 0, w, h);
                ofDrawLine(w, 0, w*2, h);
                ofDrawLine(w, h, w*2, 0);
                grayImage.draw(w*2, 0, w, h);
            }
            
           if(1){
                // send /on, /off osc message
                ofxOscBundle bundle;
                const vector<unsigned int>& newLabels = tracker.getNewLabels();
                const vector<unsigned int>& deadLabels = tracker.getDeadLabels();
                for(int i = 0; i < newLabels.size(); i++) {
                    int label = newLabels[i];
                    ofxOscMessage m;
                    m.setAddress(oscAddress.get()+ "/" + ofToString(label%maxBlobNum+1) +"/on");
                    m.addIntArg(label);
                    bundle.addMessage(m);
                }
                for(int i = 0; i < deadLabels.size(); i++) {
                    int label = deadLabels[i];
                    ofxOscMessage m;
                    m.setAddress(oscAddress.get() + "/"+ ofToString(label%maxBlobNum+1) +"/off");
                    m.addIntArg(label);
                    bundle.addMessage(m);
                }
                
                if(bundle.getMessageCount()>0){
                    oscSender.sendBundle(bundle);
                }
            }
            
            float camWidth = grayFinal.getWidth();
            float camHeight = grayFinal.getHeight();
            
            ofPushMatrix();
            ofTranslate(w*2, 0);
            
            ofxOscBundle bundle;

            int nBlobs = contourFinder.blobs.size();

            ofLogNotice() << nBlobs;

            int okBlobNum = 0;
            for(int i=0; i<nBlobs; i++){
                int age = tracker.getAge(i);
                int label = tracker.getCurrentLabels()[i];
                ofxCvBlob & blob = contourFinder.blobs[i];
                ofRectangle & rect = blob.boundingRect;
                glm::vec2 center(rect.x + rect.width/2, rect.y + rect.height/2);
                
                if(1){
                    glm::vec2 velocity = ofxCv::toOf(tracker.getVelocity(i));
                    float area = blob.area / (camWidth*camHeight);
                    
                    ofSetLineWidth(1);
                    ofNoFill();
                    
                    ofPushMatrix();
                    ofScale(w/camWidth, h/camHeight);

                    ofColor c;
                    c.setHsb(label*10%255, 255, 255);
                    ofSetColor(c);

                    // Polylines
                    blob.draw();

                    // text
                    string msg = ofToString(label) + ":" + ofToString(tracker.getAge(label));
                    ofDrawBitmapString(msg, 0, camHeight-i*25);
                    ofPopMatrix();
                    
                    // OSC
                    ofxOscMessage m;
                    m.setAddress(oscAddress.get() + "/" + ofToString(label%maxBlobNum+1) +"/val");
                    m.addIntArg(label);
                    m.addFloatArg(center.x/camWidth);
                    m.addFloatArg(center.y/camHeight);
                    m.addFloatArg(glm::length(velocity));
                    m.addFloatArg(area);
                    m.addIntArg(age);
                    bundle.addMessage(m);
                
                    okBlobNum++;
                    if(okBlobNum >= maxBlobNum) break;
                    
                }else {
                    ofPushMatrix();
                    ofScale(w/camWidth, h/camHeight);
                    ofTranslate(center);
                    ofSetColor(255);
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
        if(ndiOut && sender.isSetup()){
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
    ofxCvGrayscaleImage grayFinal;
    ofxCvContourFinder contourFinder;
    
    ofxCv::RectTracker tracker;
    vector<cv::Rect> rects;
    
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
    
    // Background
    ofParameter<bool> bUseBG{"Use BG", false};
    ofParameter<int>  bgThreshold{"Threshold", 80, 10, 300};
    ofParameter<int> bgUpdateFrame{"Update Frame", 10, 0, 300};
    ofParameter<int> bgMode{"Background Mode", 0, 0, 3}; // 0: instant diff, 1: add, 2: accumlate, 3: cv::background
    ofParameter<float> acmWeight{"Accumulate Weight", 0.5, 0, 1.0};
    ofParameterGroup bgGrp{"Background", bUseBG, bgThreshold, bgUpdateFrame, bgMode, acmWeight};
    
    // CV::Contor, CV::Tracker
    ofParameter<float> minArea{ "minArea", 5, 0, 100*100 };
    ofParameter<float> maxArea{ "maxArea", 10, 0, 300*300 };
    ofParameter<bool> bFindHoles{ "find holes", false };
    ofParameter<bool> bSimplify{ "simplify", false };
    ofParameter<int> persistence{ "persistence (frames)", 15, 1, 60 };
    ofParameter<float> maxDistance{ "max distance (pix)", 100, 0, 300 };
    ofParameter<float> smoothingRate{ "smoothingRate", 0.5, 0, 1.0 };
    ofParameter<int> maxBlobNum{ "Max blob num", 3, 1, 30 };
    ofParameterGroup trackerGrp{ "Tracker", minArea, maxArea, bFindHoles, bSimplify, persistence, maxDistance, smoothingRate,  maxBlobNum };
    
    ofParameter<string> oscAddress{"oscAddress", "NDITracker"};
    ofParameterGroup prm{"NDI source", NDI_name, showNDI, ndiOut, bgGrp, trackerGrp, oscAddress};
    
    ofEventListeners listenerHolder;
};
