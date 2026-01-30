//
//  NDISender.h
//

#pragma once

#include "ofMain.h"
#ifdef TARGET_WIN32
#include "ofxNDI.h"
#else
#include "ofxNDISender.h"
#include "ofxNDISendStream.h"
#endif

class NDISender{

public:
    
    NDISender(){};
    ~NDISender(){};

    void setup(string name, int w, int h){
        // Fbo
        fbo.allocate(w, h, GL_RGBA);
        fbo.begin();
        ofClear(255,255,255, 0);
        fbo.end();
        
        // NDI
#ifdef TARGET_WIN32
		sender.SetReadback();
		sender.SetReadback(false);
		sender.SetAsync();
		sender.CreateSender(name.c_str(), w, h);
#else
        if(!sender.isSetup()){
            std::string streamOutName =  name;
            ofLogNotice() << "Setup NDI sender: " << streamOutName;
            if(sender.setup(streamOutName)) {
                senderVideo.setup(sender);
                senderVideo.setAsync(true);
            }else{
                ofLogError() << "Can not setup NDI HeatMap";
            }
        }
#endif
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
#ifdef TARGET_WIN32
		if(sender.SenderCreated()){
			sender.SendImage(fbo);
		}
#else
		if(sender.isSetup()){
            fbo.readToPixels(pixels);
            senderVideo.send(pixels);
        }
#endif
    }
    
//    void sendExternalFbo(const ofFbo & fbo){
//        fbo.readToPixels(pixels);
//        senderVideo.send(pixels);
//    }
    
private:
#ifdef TARGET_WIN32
	ofxNDIsender sender;
#else
	ofxNDISender sender;    
    ofxNDISendVideo senderVideo;
	ofPixels pixels;
#endif
    ofFbo fbo; // with alpha

};

