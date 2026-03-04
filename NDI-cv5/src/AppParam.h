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
        void debugLoggingChanged(bool& enabled);

        void set();

		static const string version;
		ofParameter<bool> debugLogging{ "Debug Logs", false };
		ofParameter<bool> bVerticalSync{ "Vertical Sync", true };
		ofParameter<int> targetFps{ "Target FPS (VSync off)", 50, 1, 60 };
		ofParameter<int> fps{ "FPS", -1, 0, 500 };
		ofParameter<ofColor> bg{ "Background Color", ofColor(0), ofColor(0), ofColor(255) };
		ofParameter<bool> bAlphaBlending{ "Alpha Blending (advanced)", true };
		ofParameter<bool> bAntiAliasing{ "Anti Aliasing (advanced)", false };
		ofParameter<bool> bDepthTest{ "Depth Test (advanced)", false };
		ofParameterGroup advancedGrp{ "Advanced Render", bAlphaBlending, bAntiAliasing, bDepthTest };
		ofParameterGroup grp{ "App", debugLogging, bVerticalSync, targetFps, fps, bg, advancedGrp };

	};
}
