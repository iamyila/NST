//
//  AppParam.cpp
//


#include "AppParam.h"

namespace mtb{

    const string AppParam::version = ofToString(__DATE__) + ", " + ofToString(__TIME__);
    
    AppParam::AppParam(){
        targetFps.addListener(this, &AppParam::targetFpsChanged);
        windowTitle.addListener(this, &AppParam::windowTitleChanged);
        logLevel.addListener(this, &AppParam::logLevelChanged);
        
        //bStart.setSerializable(false);
        fps.setSerializable(false);
        
        appVersion = version;
        
        //TODO: Maybe there is a better way of doing this?
        logLevelMap.insert(std::make_pair("OF_LOG_VERBOSE", OF_LOG_VERBOSE));
        logLevelMap.insert(std::make_pair("OF_LOG_NOTICE", OF_LOG_NOTICE));
        logLevelMap.insert(std::make_pair("OF_LOG_WARNING", OF_LOG_WARNING));
        logLevelMap.insert(std::make_pair("OF_LOG_ERROR", OF_LOG_ERROR));
        logLevelMap.insert(std::make_pair("OF_LOG_FATAL_ERROR", OF_LOG_FATAL_ERROR));
        logLevelMap.insert(std::make_pair("OF_LOG_SILENT", OF_LOG_SILENT));
        ofSetLogLevel(logLevelMap.at(logLevel));
    }
    
    
    AppParam::~AppParam() {
        targetFps.removeListener(this, &AppParam::targetFpsChanged);
    };
    
    void AppParam::targetFpsChanged(int& fps) {
        ofSetFrameRate(fps);
    }
    
    void AppParam::windowTitleChanged(std::string& title) {
        ofSetWindowTitle(title);
    }
    
    void AppParam::logLevelChanged(std::string& level) {
        ofSetLogLevel(logLevelMap.at(level));
    }
    
    void AppParam::set() {
        fps = ofGetFrameRate();
        
        // this makes app slower
        //bSmoothing ? ofEnableSmoothing() : ofDisableSmoothing();
        
        bAlphaBlending ? ofEnableAlphaBlending() : ofDisableAlphaBlending();
        bAntiAliasing ? ofEnableAntiAliasing() : ofDisableAntiAliasing();
        bDepthTest ? ofEnableDepthTest() : ofDisableDepthTest();
        ofSetVerticalSync(bVerticalSync);
        ofBackground(bg);
    }
}
