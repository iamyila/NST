//
//  AppParam.cpp
//


#include "AppParam.h"

namespace mtb{
    
    AppParam::AppParam(){
        targetFps.addListener(this, &AppParam::targetFpsChanged);
        logLevel.addListener(this, &AppParam::logLevelChanged);        
        fps.setSerializable(false);
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
