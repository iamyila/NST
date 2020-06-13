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
        grayDiff.allocate(w,h);

        // NDI sender
        if(1){
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
            exitSender = false;

            // OSC Sender
            oscSender.setup(HOST, PORT);
        }
    }
    
    void update(){
        if(!showNDI || !receiver.isConnected()) return;
        
        video.update();
        
        if(video.isFrameNew()) {
            frameCounter++;
            auto & frame = video.getFrame();
            int xres = frame.xres;
            int yres = frame.yres;
            int format = frame.getOfPixelFormat();
            
            if(xres != 0 && yres != 0 ){
                video.decodeTo(pixels);
                pixels.setImageType(OF_IMAGE_GRAYSCALE);
                grayImageFixed.setFromPixels(pixels);
                grayImage.scaleIntoMe(grayImageFixed);
                
                if (bgTeachnique == false) {
                    //Use dynamic BG substraction
                    grayBg = grayImage;
                }
                
                if(frameCounterBGSet > 0) {
                    if (frameCounter > frameCounterBGSet) {
                        grayBg = grayImage;
                        frameCounter =0;
                    }
                }
                // if not Use static BG substraction
                // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
                // also, find holes is set to true so we will get interior contours as well....
                contourFinder.findContours(grayDiff, minBlobSize, maxBlobSize, 1, false);
            }else{
                ofLogWarning() << "decode: " <<  xres << "," << yres << ", " << "format " << format;
            }
        }
        
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(bgThreshold);
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
            float camWidth = grayDiff.getWidth();
            float camHeight = grayDiff.getHeight();
            ofFill();
            ofSetHexColor(0x333333);
            ofDrawRectangle(960,0,320,240);
            ofPushMatrix();
            ofTranslate(960, 0);
            ofScale(320/camWidth, 240/camHeight);
            ofSetColor(255);
            for (int k = 0; k < contourFinder.nBlobs; k++){
                contourFinder.blobs[k].draw(0,0);
                blobCenter.x = contourFinder.blobs.at(k).centroid.x;
                blobCenter.y = contourFinder.blobs.at(k).centroid.y;
                area = contourFinder.blobs.at(k).area/ (camWidth*camHeight);
                ofColor c;
                c.setHsb(k * 64, 255, 255);
                ofSetColor(c);
                ofDrawCircle(blobCenter, 5);
                ofSetHexColor(0xffffff);
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
            contourFinder.draw(0,0,640,360);
            sender_Fbo.end();
            sender_Fbo.readToPixels(senderPixels);
            senderVideo.send(senderPixels);
        }
    }
    
    void sendOSC(){
        if (contourFinder.nBlobs > 0) {

            float camWidth = grayDiff.getWidth();
            float camHeight = grayDiff.getHeight();
            glm::vec2 velocity = blobCenter - blobCenterPrev;
            blobCenterPrev = blobCenter;
            float dist = glm::length(velocity);
            
            ofxOscMessage m;
            m.setAddress(oscAddress);
            m.addIntArg(contourFinder.nBlobs);
            m.addFloatArg(blobCenter.x/camWidth);
            m.addFloatArg(blobCenter.y/camHeight);
            m.addFloatArg(dist);
            m.addFloatArg(area);
            oscSender.sendMessage(m, false);
            exitSender = true;
        }
        else {
            //send the inactive message, just once
            if (exitSender == true){
                ofxOscMessage m;
                m.setAddress(oscAddress);
                m.addFloatArg(0);
                oscSender.sendMessage(m, false);
                exitSender = false;
            }
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
    ofxCvContourFinder contourFinder;
    
    // send
    ofxNDISender sender;
    ofxNDISendVideo senderVideo;
    ofPixels senderPixels;
    ofFbo sender_Fbo; // with alpha
    
    bool bLearnBakground;
    bool exitSender;
    float area;
    int frameCounter = 0;
    glm::vec2 blobCenter;
    glm::vec2 blobCenterPrev;
    
    ofxOscSender oscSender;
    
    ofParameter<string> NDI_name{"Name", "sender1"};
    ofParameter<bool> showNDI{"Show Stream",true};
    ofParameter<bool> bgTeachnique{"BG Teachnique", true};
    ofParameter<int>  bgThreshold{"BG Threshold", 80, 10, 300};
    ofParameter<bool> ndiOut{"NDI OUT", true};
    ofParameter<bool> audienceFlip{"Audience Flip", true};
    ofParameter<int> minBlobSize{"Min Blob Size", 20, 1, 3000};
    ofParameter<int> maxBlobSize{"Max Blob Size", 10000, 10, 30000};
    ofParameter<int> frameCounterBGSet{"Frame Counter BG Set", 300, 0, 1000};
    ofParameter<string> oscAddress{"oscAddress", "NDITracker"};
    ofParameterGroup prm{"NDI source", NDI_name, showNDI,bgTeachnique, bgThreshold, ndiOut, audienceFlip, minBlobSize, maxBlobSize, frameCounterBGSet, oscAddress};
};
