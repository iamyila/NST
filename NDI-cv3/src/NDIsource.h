//
//  NDIsource.h
//

#pragma once

#include "ofMain.h"
#include "ofxNDIVideoGrabber.h"
#include "ofxNDIReceiver.h"
#include "ofxNDIRecvStream.h"
#include "ofxOpenCv.h"
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
        
        listenerHolder.push(bUseFD.newListener([&](bool & b){
            if(bUseFD){
                grayBg = grayImage;
                grayFinal.clear();
            }else{
                grayBg.clear();
                grayFinal.clear();
            }
        }));
        
        prevCenter.assign(100, glm::vec2(0));
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
            
                // diff
                if(bUseFD){
                    grayFinal.absDiff(grayBg, grayImage);
                    grayFinal.threshold(fdThreshold);
                }
            }
        }
        
        
        if(bUseFD){
            if (bLearnBakground) {
                grayBg = grayImage;
                bLearnBakground = false;
            }
            if (frameCounter >= fdUpdateFrame) {
                grayBg = grayImage;
                frameCounter = 0;
            }
        }else{
            grayBg.clear();
            grayFinal = grayImage;
        }
    }

    void findContour(){
        if(1){
            // contour finder
            contourFinder.findContours(grayFinal, minArea, maxArea, maxBlobNum, bFindHoles, bSimplify);
        }
    }
    
    void processBlob(int i){
        
        float camWidth = grayFinal.getWidth();
        float camHeight = grayFinal.getHeight();

        ofxCvBlob & b = contourFinder.blobs[i];
        ofRectangle & rect = b.boundingRect;
        glm::vec2 center(rect.x+rect.width/2, rect.y+rect.height/2);
        
        // This velocity is not really accurate since we can not distinguish each blobs
        glm::vec2 velocity = center - prevCenter[i];
        float area = b.area / (camWidth*camHeight);
            
        ofSetLineWidth(1);
        ofNoFill();
        
        ofPushMatrix();
        ofScale(320/camWidth, 240/camHeight);
        
        ofSetColor(0, 255, 255);
        
        // Poly
        b.draw();
            
        ofTranslate(center);
        
        // text
        //string msg = ofToString(label) + ":" + ofToString(age);
        //ofDrawBitmapString(msg, 0, 0);
            
        // velocity line
        ofDrawLine(0, 0, velocity.x/3, velocity.y/3);
        ofPopMatrix();
            
        // OSC
        ofxOscMessage m;
        m.setAddress(oscAddress.get() + "/val");
        m.addFloatArg(center.x/camWidth);
        m.addFloatArg(center.y/camHeight);
        m.addFloatArg(glm::length(velocity));
        m.addFloatArg(area);
        oscSender.sendMessage(m);
    
        prevCenter[i] = center;
    }
    
    void draw(){
        if(!showNDI) return;
        
        if(receiver.isConnected()){
        
            ofSetColor(255);
            grayImage.draw(0,0,320,240);
            if(bUseFD){
                grayBg.draw(320,0,320,240);
                grayFinal.draw(640,0,320,240);
            }else{
                ofNoFill();
                ofSetColor(255);
                ofDrawRectangle(320, 0, 320, 240);
                ofDrawLine(320, 0, 640, 240);
                ofDrawLine(320, 240, 640, 0);
                grayImage.draw(640, 0, 320, 240);
            }
            
            if(0){
                // send /on, /off osc message
//                ofxOscBundle bundle;
//                const vector<unsigned int>& newLabels = tracker.getNewLabels();
//                const vector<unsigned int>& deadLabels = tracker.getDeadLabels();
//                for(int i = 0; i < newLabels.size(); i++) {
//                    int label = newLabels[i];
//                    ofxOscMessage m;
//                    m.setAddress(oscAddress.get()+ "/" + ofToString(label%maxBlobNum+1) +"/on");
//                    m.addIntArg(label);
//                    bundle.addMessage(m);
//                }
//                for(int i = 0; i < deadLabels.size(); i++) {
//                    int label = deadLabels[i];
//                    ofxOscMessage m;
//                    m.setAddress(oscAddress.get() + "/"+ ofToString(label%maxBlobNum+1) +"/off");
//                    m.addIntArg(label);
//                    bundle.addMessage(m);
//                }
//                if(bundle.getMessageCount()>0){
//                    oscSender.sendBundle(bundle);
//                }
            }
            
            ofPushMatrix();
            ofTranslate(960, 0);

            // gray canvas for contour
            ofFill();
            ofSetHexColor(0x333333);
            ofDrawRectangle(0, 0, 320, 240);
            ofSetHexColor(0xffffff);

            int n= contourFinder.blobs.size();
            for(int i=0; i<n; i++){
                processBlob(i);
            }
         
            ofPopMatrix();

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
    ofxCvGrayscaleImage grayFinal;
    ofxCvContourFinder contourFinder;
    
    // send
    ofxNDISender sender;
    ofxNDISendVideo senderVideo;
    ofPixels senderPixels;
    ofFbo sender_Fbo; // with alpha
    
    bool bLearnBakground;
    int frameCounter = 0;
    vector<glm::vec2> prevCenter;
    
    ofxOscSender oscSender;
    
    ofParameter<string> NDI_name{"Name", "sender1"};
    ofParameter<bool> showNDI{"Show Stream",true};
    ofParameter<bool> ndiOut{"NDI OUT", true};
    
    ofParameter<bool> bUseFD{"Use FD", false};
    ofParameter<int>  fdThreshold{"FD Threshold", 80, 10, 300};
    ofParameter<int> fdUpdateFrame{"FD fdUpdateFrame", 300, 0, 1000};
    ofParameter<float> minArea{ "minArea", 20, 0, 10000 };
    ofParameter<float> maxArea{ "maxArea", 10000, 0, 300000 };
    ofParameter<bool> bFindHoles{ "find holes", false };
    ofParameter<bool> bSimplify{ "simplify", false };
    ofParameter<int> maxBlobNum{ "Max blob num", 3, 1, 30 };
    ofParameterGroup fdGrp{"Frame Difference", bUseFD, fdThreshold, fdUpdateFrame, minArea, maxArea, bFindHoles, bSimplify, maxBlobNum };
    
    ofParameter<string> oscAddress{"oscAddress", "NDITracker"};
    ofParameterGroup prm{"NDI source", NDI_name, showNDI, ndiOut, fdGrp, oscAddress};
    
    ofEventListeners listenerHolder;
};
