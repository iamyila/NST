//
//  NDISender.h
//

#pragma once

#include "ofMain.h"
#include "ofxNDISender.h"
#include "ofxNDISendStream.h"

class NDISender{

public:
    
    NDISender(){};
    ~NDISender(){};

	void setup(string name, int w, int h, bool bNDIOut) {
        // Fbo
		fbo.clear();
		fbo.allocate(w, h, GL_RGBA);
        fbo.begin();
        ofClear(255,255,255, 0);
        fbo.end();
        
        // NDI
		if (bNDIOut) {
			if (!sender.isSetup()) {
				std::string streamOutName = name;
				ofLogNotice() << "Setup NDI sender: " << streamOutName;
				if (sender.setup(streamOutName)) {
					senderVideo.setup(sender);
					senderVideo.setAsync(true);
				}
				else {
					ofLogError() << "Can not setup NDI HeatMap";
				}
			}
		}
    }
    
    
    void begin(){
        fbo.begin();
        ofClear(0,0,0,0);
         ofSetColor(255);
    }
    
    void end(){
        fbo.end();
    }

    void draw(int x, int y){
        fbo.draw(x, y, fbo.getWidth(), fbo.getHeight());
    }
    
    void draw(int x, int y, int w, int h){
        fbo.draw(x, y, w, h);
    }
    
    void send(){
        if(sender.isSetup()){
            fbo.readToPixels(pixels);
            senderVideo.send(pixels);
        }
    }
    
	void clear() {
		fbo.clear();
		pixels.clear();
		sender.disconnect();
	}

    
private:
    ofxNDISender sender;    
    ofxNDISendVideo senderVideo;
    ofPixels pixels;
    ofFbo fbo; // with alpha

};

