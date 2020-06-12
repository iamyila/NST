#include "ofxNDIRouter.h"

bool ofxNDIRouter::setup(const std::string &name, const std::string &group)
{
	NDIlib_routing_create_t info = {
		name.c_str(),
		group.c_str()
	};
	instance_ = NDIlib_routing_create(&info);
	return instance_ != nullptr;
}
bool ofxNDIRouter::setRoute(const ofxNDI::Source &source) const
{
	NDIlib_source_t src = source;
	return NDIlib_routing_change(instance_, &src);
}
bool ofxNDIRouter::clear() const
{
	return NDIlib_routing_clear(instance_);
}

ofxNDIRouter::~Router()
{
	NDIlib_routing_destroy(instance_);
	NDIlib_destroy();
}

