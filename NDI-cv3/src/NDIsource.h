//
//  NDIsource.h
//

#pragma once

#include "ofMain.h"
#include "ofxNDIVideoGrabber.h"
#include "ofxNDIReceiver.h"
#include "ofxNDIRecvStream.h"
#include "ofxOpenCv.h"
//#include "ofxOsc.h"
#include "ofxGui.h"
#include "ofxNDISender.h"
#include "ofxNDISendStream.h"

using std::string;

class NDIsource{
    
public:
    NDIsource(){};
    
    void setup(int w, int h){
        grayImage.allocate(w,h);
        grayBg.allocate(w,h);
        grayDiff.allocate(w,h);
        //pixels_.allocate(w, h, 1);
        exitSender = false;
        showNDI = false;
        bgTeachnique =false;
        
        std::string streamsOutName = NDI_name.get() + "Out";
        if(sender.setup(streamsOutName)) {
            senderVideo.setup(sender);
            senderVideo.setAsync(true);
        }
        
        sender_Fbo.allocate(640, 360, GL_RGBA);
        sender_Fbo.begin();
        ofClear(255,255,255, 0);
        sender_Fbo.end();
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
            ofLogNotice() << "decode: " <<  xres << "," << yres << ", " << "format " << format;
            
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
            }
        }
        
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(bgThreshold);
    }
    
    void draw(){
        if(!showNDI || !receiver.isConnected()) return;

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
        
        // name of NDI
       ofSetHexColor(0x00ffff);
        ofDrawBitmapString(NDI_name, 0, 10);
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
    ofParameter<string> NDI_name{"Name", "sender1"};
    ofParameter<bool> showNDI{"Show Stream",true};
    ofParameter<bool> bgTeachnique{"BG Teachnique", true};
    ofParameter<int>  bgThreshold{"BG Threshold", 80, 10, 300};
    ofParameter<bool> ndiOut{"NDI OUT", true};
    ofParameter<bool> audienceFlip{"Audience Flip", true};
    ofParameter<int> minBlobSize{"Min Blob Size", 20, 1, 3000};
    ofParameter<int> maxBlobSize{"Max Blob Size", 10000, 10, 30000};
    ofParameter<int> frameCounterBGSet{"Frame Counter BG Set", 300, 0, 1000};
    ofParameterGroup prm{"NDI source", NDI_name, showNDI,bgTeachnique, bgThreshold, ndiOut, audienceFlip, minBlobSize, maxBlobSize, frameCounterBGSet};
    
};
