//
//  AppParam.h
//

#pragma once
#include "ofMain.h"

namespace mtb {

	class AppParam {

	public:

		AppParam() {
			targetFps.addListener(this, &AppParam::targetFpsChanged);
			windowTitle.addListener(this, &AppParam::windowTitleChanged);
			logLevel.addListener(this, &AppParam::logLevelChanged);

			//bStart.setSerializable(false);
			fps.setSerializable(false);


			//TODO: Maybe there is a better way of doing this?
			logLevelMap.insert(std::make_pair("OF_LOG_VERBOSE", OF_LOG_VERBOSE));
			logLevelMap.insert(std::make_pair("OF_LOG_NOTICE", OF_LOG_NOTICE));
			logLevelMap.insert(std::make_pair("OF_LOG_WARNING", OF_LOG_WARNING));
			logLevelMap.insert(std::make_pair("OF_LOG_ERROR", OF_LOG_ERROR));
			logLevelMap.insert(std::make_pair("OF_LOG_FATAL_ERROR", OF_LOG_FATAL_ERROR));
			logLevelMap.insert(std::make_pair("OF_LOG_SILENT", OF_LOG_SILENT));
			ofSetLogLevel(logLevelMap.at(logLevel));
		}

		~AppParam() {
			targetFps.removeListener(this, &AppParam::targetFpsChanged);
		};

		void targetFpsChanged(int& fps) {
			ofSetFrameRate(fps);
		}

		void windowTitleChanged(std::string& title) {
			ofSetWindowTitle(title);
		}

		void logLevelChanged(std::string& level) {
			ofSetLogLevel(logLevelMap.at(level));
		}

		void set() {
			fps = ofGetFrameRate();

			// this makes app slower
			//bSmoothing ? ofEnableSmoothing() : ofDisableSmoothing();

			bAlphaBlending ? ofEnableAlphaBlending() : ofDisableAlphaBlending();
			bAntiAliasing ? ofEnableAntiAliasing() : ofDisableAntiAliasing();
			bDepthTest ? ofEnableDepthTest() : ofDisableDepthTest();
			ofSetVerticalSync(bVerticalSync);
			ofBackground(bg);
		}

		std::map<std::string, ofLogLevel> logLevelMap;

		ofParameter<std::string> appVersion{ "App Version", __DATE__ };
		ofParameter<std::string> windowTitle{ "Window Title", "" };
		ofParameter<std::string> logLevel{ "Log Level", "OF_LOG_SILENT" };
        //ofParameter<bool> bStart{ "Start", false };
		//ofParameter<bool> bDebug{ "Debug", true };
		ofParameter<int> targetFps{ "Target FPS", 50, 0, 60 };
		ofParameter<int> fps{ "FPS", -1, 0, 500 };
		ofParameter<bool> bAntiAliasing{ "Anti Aliasing", true };
		ofParameter<bool> bDepthTest{ "Depth Test", false };
		ofParameter<bool> bAlphaBlending{ "Alpha Blending", true };
		ofParameter<bool> bVerticalSync{ "Vertical Sync", true };
		ofParameter<ofColor> bg{ "Background Color", ofColor(0), ofColor(0), ofColor(255) };
		ofParameterGroup grp{ "App", appVersion, windowTitle, logLevel, /*bStart,*/ /*bDebug,*/ targetFps, fps, bAntiAliasing, bDepthTest, bAlphaBlending, /*bSmoothing,*/ bVerticalSync, bg };

	};
}
