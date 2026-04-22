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
        
        inImg.allocate(w, h, OF_IMAGE_COLOR);
        
        //currentImage.clear();
        //currentImage.allocate(w,h);
        setupAll();
                
        tracker.registerUser(this);
    }
         
	void connect() {
		// Reconnect should prefer the last exact resolved source name to avoid
		// ambiguity when new NDI sources appear on the network.
		const std::string preferred = longName.empty() ? NDI_name.get() : longName;
		std::string resolved = receiver.connect(preferred /*, ndiInHighestBandwidth*/);
		if (resolved.empty() && preferred != NDI_name.get()) {
			// Fallback to current manual field if previous source is gone.
			resolved = receiver.connect(NDI_name.get() /*, ndiInHighestBandwidth*/);
		}
		if (!resolved.empty()) {
			longName = resolved;
			NDI_name = resolved;
		}
	}

    void connectToSource(const ofxNDI::Source& source) {
        longName = receiver.connect(source);
        if (longName != "") {
            NDI_name = longName;
        }
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
        if (ndiIn && !receiver.isConnected()) {
            reconnectFrameCounter++;
            if (reconnectFrameCounter == 1 || (reconnectFrameCounter % 120) == 0) {
                connect();
            }
        } else if (receiver.isConnected()) {
            reconnectFrameCounter = 0;
        }

		if (receiver.update()) {
			ofPixels& pix = receiver.getPixels();
            inImg.setFromPixels(pix);
            matRGBA = ofxCv::toCv(inImg);
            if (matRGBA.channels() == 4) {
                cv::cvtColor(matRGBA, matRGB, cv::COLOR_RGBA2RGB);
            } else if (matRGBA.channels() == 3) {
                matRGB = matRGBA;
            } else if (matRGBA.channels() == 1) {
                cv::cvtColor(matRGBA, matRGB, cv::COLOR_GRAY2RGB);
            } else {
                ofLogWarning("NDISource") << "Unsupported pixel channel count: " << matRGBA.channels();
                return;
            }

            if (bDetectBlob) {
                tracker.updateByTrackingTechnique(matRGB);
            }
            
            drawFbo();
        }
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
            //currentImage.draw(0,0,w,h);
            inImg.draw(0,0,w,h);
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
            const float drawX = (ofGetWidth() - v.width) * 0.5f;
            const float drawY = (ofGetHeight() - v.height) * 0.5f;
			ofPushStyle();
            ofSetColor(255);
			inImg.draw(drawX, drawY, v.width, v.height);
            if(bHeatmap) heatmap.drawFbo(drawX, drawY, v.width, v.height);
            if(bDetectBlob) tracker.drawFbo(drawX, drawY, v.width, v.height);
            if(bGlitch) glitch.drawFbo(drawX, drawY, v.width, v.height);
			ofPopStyle();
            
            {
                ofPushMatrix();
                ofTranslate(30, 50);
                ofSetColor(255);
                ofDrawBitmapStringHighlight("fps: " + ofToString(ofGetFrameRate(), 1), 0, -5);
                
                ofTranslate(0, 30);
                ofSetColor(255);
                ofDrawBitmapString("Selected label : age", 0, -5);
                tracker.drawInfo();
                
                ofTranslate(300, 0);
                ofSetColor(255);
                ofDrawBitmapString("NoteOn sent (label)", 0, -5);
                ofSetColor(0,255, 0);
                tracker.drawNoteOnInfo();
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
            inImg.draw(0,ty,w,h);

            if(bDetectBlob){
                // 2
                ty += h+10;
                tracker.drawReference(0, ty, w, h);

                // 2+
                ofPushStyle();
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
            tracker.drawNoteOnInfo();
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

    ofImage inImg;

    mtb::mtbTracker tracker;
    mtb::mtbHeatmap heatmap;
    mtb::mtbGlitch glitch;
    mtb::OscSender oscSender;

    string longName = "";
    
    // NDI receive
    NDIReceiver receiver;
    //ofxCvColorImage currentImage;
    cv::Mat matRGBA;
    cv::Mat matRGB;
    int reconnectFrameCounter = 0;
    
    // General
    ofParameter<string> NDI_name{"NDI Source Match (Manual)", "NST Motion Test 3D"};
    ofParameter<bool> ndiIn{"NDI IN",true};
    ofParameter<bool> ndiOut{"NDI OUT", false};
	ofParameter<int> processWidth{ "Process Width", 1280, 240, 1920};
	ofParameter<int> processHeight{ "Process Height", 720, 135, 1080};
	ofParameterGroup generalGrp{ "NDI in/out", NDI_name, ndiIn, ndiOut /*ndiInHighestBandwidth,*/ };

    // Tracking
    ofParameter<bool> bDetectBlob{"Detect Blob", true};
    ofParameterGroup trackingAdvancedGrp{"Tracking Advanced", processWidth, processHeight};
    ofParameterGroup trackingGrp{"Tracking", bDetectBlob, trackingAdvancedGrp};

    // Optional visual FX (kept disabled by default so OSC tracking workflow stays clean).
    ofParameter<bool> bHeatmap{"Heat Map (optional)", false};
    ofParameter<bool> bGlitch{"Glitch (optional)", false};
    ofParameterGroup fxGrp{"Visual FX (optional)", bHeatmap, bGlitch, heatmap.grp};

    ofParameter<int> lockMsec{"Lock msec", 0, 0, 10000};
    
    ofParameterGroup prm{"Processing", trackingGrp, oscSender.grp, tracker.grp, fxGrp};
    
    ofEventListeners listenerHolder;
};
