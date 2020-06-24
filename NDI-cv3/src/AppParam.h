//
//  AppParam.h
//

#pragma once
#include "ofMain.h"

namespace mtb {

	class AppParam {

	public:

        AppParam();
        ~AppParam();
        void targetFpsChanged(int& fps);
        void windowTitleChanged(std::string& title);
        void logLevelChanged(std::string& level);

        void set();

		std::map<std::string, ofLogLevel> logLevelMap;

		ofParameter<std::string> appVersion{ "App Version"};
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
