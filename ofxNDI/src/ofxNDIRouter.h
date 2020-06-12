#pragma once

#include "ofxNDI.h"
#include <string>
#include <Processing.NDI.Lib.h>

namespace ofxNDI {
class Router
{
public:
	using Instance = NDIlib_routing_instance_t;
	~Router();

	bool setup(const std::string &name, const std::string &group="");
	bool setRoute(const ofxNDI::Source &source) const;
	bool clear() const;
private:
	Instance instance_=nullptr;
};
}

using ofxNDIRouter = ofxNDI::Router;
