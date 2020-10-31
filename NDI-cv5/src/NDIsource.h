//
//  NDISource.h
//

#pragma once

#include "ofMain.h"
#include "ofxNDIVideoGrabber.h"
#include "ofxNDIReceiver.h"
#include "ofxNDIRecvStream.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "NDIReceiver.h"	// my own helper class
#include "mtbHeatmap.h"
#include "mtbGlitch.h"
#include "mtbTracker.h"
#include "OscSender.h"

using std::string;

class NDISource{
    
public:
    NDISource(){
		registerCallback();
	};
    
    void setup(){

        int w = processWidth;
        int h = processHeight;

        currentImage.clear();
        currentImage.allocate(w,h);
        setupAll();
                
        tracker.registerUser(this);
    }
         
	void connect() {
		longName = receiver.connect(NDI_name /*, ndiInHighestBandwidth*/);
	}

	void disconnect() {
		receiver.disconnect();
		longName = "";
	}

	void registerCallback() {
		listenerHolder.push(processWidth.newListener([&](int& i) { setup(); }));
		listenerHolder.push(processHeight.newListener([&](int& i) { setup(); }));
		listenerHolder.push(ndiOut.newListener([&](bool& b) { setupAll(); }));
		listenerHolder.push(bDetectBlob.newListener([&](bool& b) { setupTracker(); }));
		listenerHolder.push(bGlitch.newListener([&](bool& b) { setupGlitch(); }));
        listenerHolder.push(bHeatmap.newListener([&](bool& b) { setupHeatmap(); }));
	}

	void setupAll() {
		setupTracker();
		setupHeatmap();
		setupGlitch();
        oscSender.setup();
	}

    void setupTracker(){
		if (bDetectBlob) {
			std::string nameBlob = prm.getName() + "-Blob";
			tracker.setup(nameBlob, processWidth, processHeight, ndiOut);
		}
		else {
			tracker.clear();
		}
    }

    void setupHeatmap(){
		if (bHeatmap) {
			std::string nameHeat = prm.getName() + "-Heatmap";
			heatmap.setup(nameHeat, processWidth, processHeight, ndiOut);
		}
		else {
			heatmap.clear();
		}
	}
    
    void setupGlitch(){
		if (bGlitch) {
			std::string nameGlitch = prm.getName() + "-Glitch";
			glitch.setup(nameGlitch, processWidth, processHeight, ndiOut);
		}
		else {
			glitch.clear();
		}
    }
    
    void update(){

		if (receiver.update()) {
			ofPixels& pix = receiver.getPixels();
			pix.setImageType(OF_IMAGE_COLOR);
			currentImage.setFromPixels(pix);
        }

        if (bDetectBlob) {
            tracker.update(currentImage);
        }
        
        drawFbo();
    }       
  
    void drawFbo(){
		if (!ndiIn) return;
        
        // FBO for Blob
        if(bDetectBlob){
            float rw = receiver.getWidth();
            float rh = receiver.getHeight();
            tracker.drawToFbo(rw, rh, processWidth, processHeight);
        }


		// FBO for Heatmap
		if (bHeatmap) {
            heatmap.drawToFbo();
		}

        if(bGlitch){
            glitch.beginTarget();
            int w = glitch.targetFbo.getWidth();
            int h = glitch.targetFbo.getHeight();
            currentImage.draw(0,0,w,h);
            if(bDetectBlob) tracker.drawFbo(0,0,w,h);
            if(bHeatmap) heatmap.drawFbo(0,0,w,h);
            glitch.endTarget();
            glitch.drawToFbo(w, h);
        }
    }
    
    void drawSolo(){
        if(!ndiIn) return;
        
        if(receiver.isConnected()){
            int w = processWidth;
            int h = processHeight;
            ofRectangle v = ofRectangle(0,0,w,h);
            v.scaleTo(ofGetCurrentViewport());
			ofPushStyle();
			ofEnableAlphaBlending();
            ofSetColor(255);
            ofSetRectMode(OF_RECTMODE_CENTER);
			currentImage.draw(ofGetWidth() / 2, ofGetHeight() / 2, v.width, v.height);
			if(bDetectBlob) tracker.drawFbo(ofGetWidth()/2, ofGetHeight()/2, v.width, v.height);
            if(bHeatmap) heatmap.drawFbo(ofGetWidth()/2, ofGetHeight()/2, v.width, v.height);
			ofPopStyle();
            
            {
                ofPushMatrix();
                ofTranslate(30, 30);
                ofSetColor(255);
                ofDrawBitmapString("Selected label : age", 0, -5);
                tracker.drawInfo();
                
                ofTranslate(300, 0);
                ofSetColor(255);
                ofDrawBitmapString("NoteOn sent (label)", 0, -5);
                ofSetColor(0,255, 0);
                tracker.drawNoteOnSlots();
                ofPopMatrix();
            }
        }
    }
    
    void draw(){
        
        if(!ndiIn) return;
      
        if(receiver.isConnected()){
            
			int nMon = getNumMonitor();
			int h = (ofGetHeight() - 150) / nMon - 10;
            int w = h * 1920/1080;
            
            int ty = 28;
            ofPushStyle();
            ofSetColor(255);
            
            // 1
            currentImage.draw(0,ty,w,h);

            if(bDetectBlob){
                // 2
                ty += h+10;
                tracker.drawReference(0, ty, w, h);

                // 2+
                ofPushStyle();
                ofEnableAlphaBlending();
                tracker.drawFbo(0, ty, w, h);
                ofPopStyle();
            }
    
            if(bHeatmap){
                // 3
                ty += h+10;
                heatmap.drawFbo(0, ty, w, h);
            }
            
            if(bGlitch){
                // 4
                ty += h+10;
                glitch.drawTargetFbo(0, ty, w, h);
                
                // 5
                ty += h+10;
                glitch.drawFbo(0, ty, w, h);
            }
            
            // 7 info text
            ofPushMatrix();
            ofTranslate(w+10, 28);
            ofSetColor(255);
            ofDrawBitmapString("Selected label : age", 0, -5);
            tracker.drawInfo();

            ofTranslate(0, h+10);
            ofSetColor(255);
            ofDrawBitmapString("NoteOn sent (label)", 0, -5);
            ofSetColor(0,255, 0);
            tracker.drawNoteOnSlots();
            ofPopMatrix();
            
            ofPopStyle();
        }
        
        // name of NDI
        receiver.isConnected() ? ofSetHexColor(0x0000ff) : ofSetHexColor(0xff0000);

		stringstream ss;
		ss << longName << "\n";
		ss << receiver.getWidth() << "x" << receiver.getHeight();		
		ofDrawBitmapString(ss.str(), 0, 10);
    }
    
    bool getIsNDIConected(){
        return receiver.isConnected();
    }
    
    void sendNDI(){
        if(ndiOut){
            if (bDetectBlob) tracker.sendNDI();
            if (bHeatmap) heatmap.sendNDI();
            if (bGlitch) glitch.sendNDI();
        }
    }
    
	int getNumMonitor() {
		int nMonitor = 1;
		if (bDetectBlob)	nMonitor++;
		if (bHeatmap)		nMonitor++;
		if (bGlitch)		nMonitor+=2;
		return nMonitor;
	}
    
    void addPointToHeatmap(float x, float y, float area){
        if(bHeatmap) heatmap.add(x, y, area);
    }
    
public:
    mtb::mtbTracker tracker;
    mtb::mtbHeatmap heatmap;
    mtb::mtbGlitch glitch;
    mtb::OscSender oscSender;

    string longName = "";
    
    // NDI receive
    NDIReceiver receiver;
    ofxCvColorImage currentImage;

    // General
    ofParameter<string> NDI_name{"Name", "sender1"};
    ofParameter<bool> ndiIn{"NDI IN",false};
    ofParameter<bool> ndiOut{"NDI OUT", false};
	ofParameter<int> processWidth{ "Process Width", 1280, 240, 1920};
	ofParameter<int> processHeight{ "Process Height", 720, 135, 1080};
	ofParameterGroup generalGrp{ "NDI in/out", NDI_name, ndiIn, ndiOut, /*ndiInHighestBandwidth,*/ processWidth, processHeight };

    // Layers
    ofParameter<bool> bDetectBlob{"Detect Blob", true};
    ofParameter<bool> bHeatmap{"Heat Map", true};
    ofParameter<bool> bGlitch{"Glitch", true};
    ofParameterGroup layerGrp{"Layer", bDetectBlob, bHeatmap, bGlitch};

    ofParameter<int> lockMsec{"Lock msec", 0, 0, 10000};
    
    ofParameterGroup prm{"NDI source", generalGrp, layerGrp, oscSender.grp, tracker.grp, heatmap.grp};
    
    ofEventListeners listenerHolder;    
};
