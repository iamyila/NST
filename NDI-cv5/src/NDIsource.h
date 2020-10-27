//
//  NDIsource.h
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

using std::string;

class NDIsource{
    
public:
    NDIsource(){
		registerCallback();
	};
    
    void setup(){

        int w = processWidth;
        int h = processHeight;

        currentImage.clear();
        currentImage.allocate(w,h);
        setupAll();
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
		listenerHolder.push(oscIp.newListener([&](string& ip) { setupOscSender(); }));
		listenerHolder.push(oscPort.newListener([&](int& port) { setupOscSender(); }));
		listenerHolder.push(bDetectBlob.newListener([&](bool& b) { setupTracker(); }));
		listenerHolder.push(bGlitch.newListener([&](bool& b) { setupGlitch(); }));
        listenerHolder.push(bHeatmap.newListener([&](bool& b) { setupHeatmap(); }));
	}

	void setupAll() {
		setupTracker();
		setupHeatmap();
		setupGlitch();
		setupOscSender();
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
 
    void setupOscSender(){
		oscSender.setup(oscIp, oscPort);		
    }
    
    void update(){

		if (receiver.update()) {
			ofPixels& pix = receiver.getPixels();
			pix.setImageType(OF_IMAGE_COLOR);
			currentImage.setFromPixels(pix);
            if (bDetectBlob) {
                tracker.update(currentImage);
			}

			drawFbo();
		}
    }       
  

    
    void sendNoteOnOff(){
        /*
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
         */
    }
    
    void drawFbo(){
		if (!ndiIn) return;

        
        // FBO for Blob
        if(bDetectBlob){
            float rw = receiver.getWidth();
            float rh = receiver.getHeight();
            tracker.drawToFbo2(rw, rh, processWidth, processHeight);
            
            /*
             int nBlobs = contourFinder.blobs.size();
             int okBlobNum = 0;
             
             senderBlob.begin();
			ofPushMatrix();
            float inputWidth = receiver.getWidth();
            float inputHeight = receiver.getHeight();
            
            float sx = (float)processWidth / inputWidth;
            float sy = (float)processHeight / inputHeight;
			ofScale(sx, sy);

			for(int i=0; i<nBlobs; i++){
                int label = tracker.getCurrentLabels()[i];
                int age = tracker.getAge(label);
                ofxCvBlob & blob = contourFinder.blobs[i];
                ofRectangle & rect = blob.boundingRect;
                glm::vec2 center(rect.x + rect.width/2, rect.y + rect.height/2);
                
                if(minAge <= age){
                    
                    glm::vec2 velocity = ofxCv::toOf(tracker.getVelocity(i));
                    float area = blob.area / (inputWidth*inputHeight);
                    
                    ofSetLineWidth(1);
                    ofNoFill();
					{
						ofPushMatrix();
						ofNoFill();
						blob.draw();
						ofPopMatrix();
					}

                    // OSC
                    float xrate = center.x/inputWidth;
                    float yrate = center.y/inputHeight;
                    ofxOscMessage m;
                    m.setAddress(oscAddress.get() + "/" + ofToString(getOscAddressSlot(label)) +"/val");
                    m.addIntArg(label);
                    m.addFloatArg(xrate);
                    m.addFloatArg(yrate);
                    m.addFloatArg(glm::length(velocity));
                    m.addFloatArg(area);
                    m.addIntArg(age);
                    
                    // polar coordinate
                    glm::vec2 p = toPolar(center.x, center.y, inputWidth, inputHeight);
                    m.addFloatArg(p.x);
                    m.addFloatArg(p.y);

                    oscSender.sendMessage(m);
                    
                    okBlobNum++;
                    
                    if(bHeatmap){
                        heatmap.add(xrate, yrate, area);
                    }
                    
                    if(okBlobNum >= maxBlobNum) break;
                }else {
                    ofPushMatrix();
                    ofTranslate(center);
                    ofSetColor(255, 180);
                    ofNoFill();
                    ofSetRectMode(OF_RECTMODE_CENTER);
                    ofDrawRectangle(0, 0, rect.width, rect.height);
                    ofSetRectMode(OF_RECTMODE_CORNER);
                    ofPopMatrix();
                }
            }
            ofPopMatrix();
            senderBlob.end();
             */
        } // end of FBO for Blob


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
        return label % tracker.maxBlobNum + 1;
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
			tracker.drawFbo(ofGetWidth()/2, ofGetHeight()/2, v.width, v.height);
            heatmap.drawFbo(ofGetWidth()/2, ofGetHeight()/2, v.width, v.height);
            ofSetRectMode(OF_RECTMODE_CORNER);
			ofPopStyle();
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
                tracker.drawForeground(0, ty, w, h);

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
            ofDrawBitmapString("label   age", 0, -5);
            tracker.drawInfo();
            ofPopMatrix();
            
            ofPushMatrix();
            ofTranslate(w+110, 28);
            ofSetColor(255);
            ofDrawBitmapString("label   age", 0, -5);
            tracker.drawInfo2();
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
            //tracker.send();
            heatmap.send();
            glitch.send();
        }
    }
    
	int getNumMonitor() {
		int nMonitor = 1;
		if (bDetectBlob)	nMonitor++;
		if (bHeatmap)		nMonitor++;
		if (bGlitch)		nMonitor+=2;
		return nMonitor;
	}


	string longName = "";

    // NDI receive
    NDIReceiver receiver;

    ofxCvColorImage currentImage;
    
    ofxOscSender oscSender;

    mtb::mtbGlitch glitch;
    mtb::mtbHeatmap heatmap;
    mtb::mtbTracker tracker;

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

    // OSC sender settings
    ofParameter<string> oscIp{"IP", "localhost"};
    ofParameter<int> oscPort{"port", 12345, 0, 12345};
    ofParameter<string> oscAddress{"oscAddress", "NDITracker"};
    ofParameterGroup oscGrp{"OSC send", oscIp, oscPort, oscAddress};
    
    ofParameterGroup prm{"NDI source", generalGrp, layerGrp, oscGrp, tracker.grp, heatmap.grp};
    
    ofEventListeners listenerHolder;
};
