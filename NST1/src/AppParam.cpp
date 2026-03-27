//
//  AppParam.cpp
//


#include "AppParam.h"

namespace mtb{
    
    AppParam::AppParam(){
        targetFps.addListener(this, &AppParam::targetFpsChanged);
        debugLogging.addListener(this, &AppParam::debugLoggingChanged);
        fps.setSerializable(false);
        ofSetLogLevel(debugLogging ? OF_LOG_NOTICE : OF_LOG_SILENT);
    }
    
    
    AppParam::~AppParam() {
        targetFps.removeListener(this, &AppParam::targetFpsChanged);
        debugLogging.removeListener(this, &AppParam::debugLoggingChanged);
    };
    
    void AppParam::targetFpsChanged(int& fps) {
        if (!bVerticalSync) {
            ofSetFrameRate(fps);
        }
    }
    
    void AppParam::debugLoggingChanged(bool& enabled) {
        ofSetLogLevel(enabled ? OF_LOG_NOTICE : OF_LOG_SILENT);
    }
    
    void AppParam::set() {
        fps = ofGetFrameRate();
        
        // this makes app slower
        //bSmoothing ? ofEnableSmoothing() : ofDisableSmoothing();
        
        bAlphaBlending ? ofEnableAlphaBlending() : ofDisableAlphaBlending();
        bAntiAliasing ? ofEnableAntiAliasing() : ofDisableAntiAliasing();
        bDepthTest ? ofEnableDepthTest() : ofDisableDepthTest();
        ofSetVerticalSync(bVerticalSync);
        if (!bVerticalSync) {
            // Keep frame limiter deterministic when VSync is disabled.
            ofSetFrameRate(targetFps);
        } else {
            // Avoid old FPS cap values affecting behavior while VSync is enabled.
            ofSetFrameRate(240);
        }
        ofBackground(bg);
    }
}
