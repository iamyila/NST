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
#include "ofxHeatMap.h"
#include "NDISender.h"  // my own helper class
#include "ofxEasyFboGlitch.h"

using std::string;


class NDIsource{
    
public:
    NDIsource(){};
    
    void setup(int w, int h){
        
//        float sw = 300;
//        float sh = 300;
//        glm::vec2 r1 = toPolar(100, 0, sw, sh);
//        glm::vec2 r2 = toPolar(150, 200, sw, sh);
//        glm::vec2 r3 = toPolar(50, 100, sw, sh);
        
        inputWidth = w;
        inputHeight = h;
        currentImage.allocate(w,h);
        currentImageFixed.allocate(w,h);
        finalImage.allocate(w,h);

        // NDI sender
        setupNDI_OUT();
        
        setupOscSender();
        
        listenerHolder.push(ndiOut.newListener([&](bool & b){ setupNDI_OUT(); }));
        listenerHolder.push(bgAlgo.newListener([&](int & algo){ setupBS(); }));
        listenerHolder.push(oscIp.newListener([&](string & ip){ setupOscSender(); }));
        listenerHolder.push(oscPort.newListener([&](int & port){ setupOscSender(); }));
        listenerHolder.push(bDetectBlob.newListener([&](bool & b){ setupBS(); }));
        listenerHolder.push(bHeatmap.newListener([&](bool & b){ setupHeatmap(); }));
        listenerHolder.push(bGlitch.newListener([&](bool & b){ setupGlitch(); }));
        
        setupBS();
        setupHeatmap();
        setupGlitch();
    }
    
    
    void setupBS(){
        if(bDetectBlob){
            if (bgAlgo==0){
                pBackSub = cv::createBackgroundSubtractorMOG2();
            }else{
                pBackSub = cv::createBackgroundSubtractorKNN();
            }
        }
    }

    void setupHeatmap(){
        if(bHeatmap){
            heatmap.clear();
            heatmap.setup(inputWidth, inputHeight);
        }
    }
    
    void setupGlitch(){
        if(bGlitch){
            glitch.allocate(inputWidth, inputHeight);
            
            combinedFbo.allocate(inputWidth, inputHeight, GL_RGBA);
            combinedFbo.begin();
            ofClear(255,255,255, 0);
            combinedFbo.end();
        }
    }
    
    void setupNDI_OUT(){
        if(ndiOut){
            std::string nameBlob =  prm.getName() + "-Blob";
            std::string nameHeat =  prm.getName() + "-Heatmap";
            std::string nameGlitch =  prm.getName() + "-Glitch";

            senderBlob.setup(nameBlob, inputWidth, inputHeight);
            senderHeatmap.setup(nameHeat, inputWidth, inputHeight);
            senderGlitch.setup(nameGlitch, inputWidth, inputHeight);
        }
    }
    
    void setupOscSender(){
        oscSender.setup(oscIp, oscPort);
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
                        if(bDetectBlob){
                            pBackSub->apply(currentMat, foregroundMat);
                            
                            ofPixels pix;
                            ofxCv::toOf(foregroundMat, pix);
                            pix.setImageType(OF_IMAGE_GRAYSCALE);
                            finalImage.setFromPixels(pix);
                            
                            findContour();
                            
                            sendNoteOnOff();
                        }
                        
                        if(bHeatmap){
                            //heatmap.update(OFX_HEATMAP_CS_SPECTRAL_SOFT);
                            heatmap.update(OFX_HEATMAP_CS_RED_GRAY_MIXED);
                        }
                        
                        drawFbo();
                    }
                }
            }
        }
        
        // ofxHeatmap increase memory use, so we reset every 3 min.
        
        if( ofGetFrameNum() % (30*60*3) == 0){
            heatmap.clear();
            heatmap.setup(inputWidth, inputHeight);
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

        // FBO 1
        if(bHeatmap){
            senderHeatmap.begin();
            ofSetColor(255, 100);
            heatmap.draw(0, 0);
            senderHeatmap.end();
        }
        
        // FBO 2
        if(bDetectBlob){
            senderBlob.begin();
            
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
                    
                    // Effects
                    float heatRadius = MIN(blob.area*0.05, 30);
                    heatmap.setRadius(heatRadius);
                    heatmap.addPoint(center.x, center.y);
                    
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
            senderBlob.end();
        } // end of FBO 2

        if(bGlitch){
            ofPushStyle();
            ofEnableAlphaBlending();
            combinedFbo.begin();
            ofClear(0,0,0,0);
            ofSetColor(255);
            currentImage.draw(0,0,camWidth,camHeight);
            if(bDetectBlob) senderBlob.draw(0,0,camWidth, camHeight);
            if(bHeatmap) senderHeatmap.draw(0,0,camWidth, camHeight);
            combinedFbo.end();
            ofPopStyle();
            
            // Glitch
            senderGlitch.begin();
            glitch.draw(combinedFbo, 0, 0, camWidth, camHeight);
            senderGlitch.end();
        }
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
            int w = inputWidth;
            int h = inputHeight;
            ofRectangle v = ofRectangle(0,0,w,h);
            v.scaleTo(ofGetCurrentViewport());
            ofDisableAlphaBlending();
            ofSetColor(255);
            ofSetRectMode(OF_RECTMODE_CENTER);
            senderBlob.draw(ofGetWidth()/2, ofGetHeight()/2, v.width, v.height);
            senderHeatmap.draw(ofGetWidth()/2, ofGetHeight()/2, v.width, v.height);
            ofSetRectMode(OF_RECTMODE_CORNER);
        }
    }
    
    void draw(){
        
        if(!showNDI) return;
        
        if(receiver.isConnected()){
            
            int h = ofGetHeight() / 8;
            int w = h * 1920/1080;
            
            int ty = 0;
            ofPushStyle();
            ofSetColor(255);
            
            // 1
            currentImage.draw(0,0,w,h);

            if(bDetectBlob){
                // 2
                ty += h+10;
                ofxCv::drawMat(foregroundMat,0, ty,w,h);  //////??????

                ofEnableAlphaBlending();
                
                // 3
                ty += h+10;
                senderBlob.draw(0, ty, w, h);
            }
    
            if(bHeatmap){
                // 4
                ty += h+10;
                senderHeatmap.draw(0, ty, w, h);
            }
            
            if(bGlitch){
                // 5
                ty += h+10;
                combinedFbo.draw(0, ty, w, h);
                
                // 6
                ty += h+10;
                senderGlitch.draw(0, ty, w, h);
            }
            
            // 7 info text
            ty += h+10+10;
            ofPushMatrix();
            ofTranslate(0, ty);
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
    
    bool getIsNDIConected(){
        return receiver.isConnected();
    }
    
    void sendNDI(){
        if(ndiOut){
            senderBlob.send();
            senderHeatmap.send();
            senderGlitch.send();
        }
    }
    
    //
    int inputWidth, inputHeight;
    
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
    
    // NID send
    NDISender senderBlob;
    NDISender senderHeatmap;
    NDISender senderGlitch;
        
    int frameCounter = 0;
    
    ofxOscSender oscSender;
    
    //
    ofFbo combinedFbo;
    
    // Effects
    ofxHeatMap heatmap;
    
    ofxEasyFboGlitch glitch;
    
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
    
    // OSC sender settings
    ofParameter<string> oscIp{"IP", "localhost"};
    ofParameter<int> oscPort{"port", 12345, 0, 12345};
    ofParameter<string> oscAddress{"oscAddress", "NDITracker"};
    ofParameterGroup oscGrp{"OSC send", oscIp, oscPort, oscAddress};

    // layers
    ofParameter<bool> bDetectBlob{"Detect Blob", true};
    ofParameter<bool> bHeatmap{"Heat Map", true};
    ofParameter<bool> bGlitch{"Glitch", true};
    ofParameterGroup layerGrp{"Layer", bDetectBlob, bHeatmap, bGlitch};
    
    ofParameterGroup prm{"NDI source", NDI_name, showNDI, ndiOut, bgGrp, trackerGrp, oscGrp, layerGrp};
    
    ofEventListeners listenerHolder;
};
