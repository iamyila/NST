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
        if (showNDI) {
            
            if(receiver.isConnected()) {
                video.update();
                
                if(video.isFrameNew()) {
                    auto & frame = video.getFrame();
                    int xres = frame.xres;
                    int yres = frame.yres;
                    int format = frame.getOfPixelFormat();
                    ofLogNotice() << "decode: " <<  xres << "," << yres << ", " << "format " << format;
                    
                    if(xres != 0 && yres != 0 ){
                        video.decodeTo(pixels);
                        pixels.setImageType(OF_IMAGE_GRAYSCALE);
                        grayImage.setFromPixels(pixels);
                        grayImage.scaleIntoMe(grayImageFixed);
                    }
                }
            }
        }
    }
    
    void draw(){


        if (showNDI) {
            if(receiver.isConnected()) {
                ofSetColor(255);
                ofImage(pixels).draw(0, 0, 320,240);
                grayImage.draw(320,0,320,240);
                grayBg.draw(640,0,320,240);
                grayDiff.draw(960,0,320,240);
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
