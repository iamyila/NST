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

        // NDI sender
        setupNDI_OUT();
        sender_Fbo.allocate(640, 360, GL_RGBA);
        sender_Fbo.begin();
        ofClear(255,255,255, 0);
        sender_Fbo.end();

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
        
        listenerHolder.push(ndiOut.newListener([&](bool & b){
            if(ndiOut && !sender.isSetup()){
                setupNDI_OUT();
            }
        }));

    }
    
    void setupNDI_OUT(){
        std::string streamOutName =  prm.getName() + "-Out";
        ofLogNotice() << "Setup NDI sender " << streamOutName;
        if(sender.setup(streamOutName)) {
            senderVideo.setup(sender);
            senderVideo.setAsync(true);
        }else{
            ofLogError() << "Can not setup NDI sender";
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

                    if(bUseFD){
                        grayFinal.absDiff(grayBg, grayImage);
                        grayFinal.threshold(fdThreshold);

                        if (bLearnBakground) {
                            grayBg = grayImage;
                            bLearnBakground = false;
                        }
                        if (frameCounter >= fdUpdateFrame) {
                            grayBg = grayImage;
                            frameCounter =0;
                        }
                    }else{
                        grayBg.clear();
                        grayFinal = grayImage;
                    }
                    
                    frameCounter++;
                }
            }
        }
    }

    void findContour(){
        if(showNDI){
            // contour finder
            contourFinder.findContours(grayFinal, minAreaRadius, maxAreaRadius, maxBlobNum, bFindHoles, bSimplify);
            
            rects.clear();
            for(auto & b : contourFinder.blobs){
                rects.push_back(ofxCv::toCv(b.boundingRect));
            }
            tracker.track(rects);
        }
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
            ofTranslate(640, 0);
            
            ofxOscBundle bundle;

            int nBlobs = contourFinder.blobs.size();
            std::vector<pair<int, int>> ages;
            ages.reserve(nBlobs);
            
            for (int i=0; i<nBlobs; i++){
                int label = tracker.getCurrentLabels()[i];
                int age = tracker.getAge(label);
                ages.emplace_back(make_pair(i, age));
            }
            
            std::sort(ages.begin(), ages.end(),
                      [](pair<int,int> & a,
                         pair<int,int> & b){
                          return a.second > b.second;
                      });

            // debug
            // for(auto & a: ages){ cout << std::get<1>(a) << ","; } cout << endl;
            
            int n = MIN(maxBlobNum.get(), ages.size());
            for(int j=0; j<n; j++){
                int i = ages[j].first;
                int age = ages[j].second;
                int label = tracker.getCurrentLabels()[i];
                ofxCvBlob & blob = contourFinder.blobs[i];
                ofRectangle & rect = blob.boundingRect;
                glm::vec2 center(rect.x + rect.width/2, rect.y + rect.height/2);
                
                if(age > minAge){

                    glm::vec2 velocity = ofxCv::toOf(tracker.getVelocity(i));
                    float area = blob.area / (camWidth*camHeight);
                    
                    ofSetLineWidth(1);
                    ofNoFill();
                    
                    ofPushMatrix();
                    ofScale(320/camWidth, 240/camHeight);

                    ofColor c;
                    c.setHsb(label*10%255, 255, 255);
                    ofSetColor(c);

                    // Polylines
                    blob.draw();

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
                    m.setAddress(oscAddress.get() + "/" + ofToString(label%maxBlobNum+1) +"/val");
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
    ofxCvGrayscaleImage grayFinal;
    ofxCvContourFinder contourFinder;
    
    ofxCv::RectTracker tracker;
    vector<cv::Rect> rects;
    
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
    
    ofParameter<bool> bUseFD{"Use FD", false};
    ofParameter<int>  fdThreshold{"FD Threshold", 80, 10, 300};
    ofParameter<int> fdUpdateFrame{"FD fdUpdateFrame", 300, 0, 1000};
    ofParameterGroup fdGrp{"Frame Difference", bUseFD, fdThreshold, fdUpdateFrame};
    
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
    ofParameter<int> minAge{ "min age", 15, 0, 60 };
    ofParameter<int> maxBlobNum{ "Max blob num", 3, 1, 30 };
    ofParameterGroup trackerGrp{ "Tracker", minAreaRadius, maxAreaRadius, bAutoThreshold, threshold, bFindHoles, bSimplify, persistence, maxDistance, smoothingRate, minAge, maxBlobNum };
    
    ofParameter<string> oscAddress{"oscAddress", "NDITracker"};
    ofParameterGroup prm{"NDI source", NDI_name, showNDI, ndiOut, fdGrp, trackerGrp, oscAddress};
    
    ofEventListeners listenerHolder;
};
