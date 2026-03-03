#pragma once

#include "ofMain.h"
#include "ofxNDISender.h"
#include "ofxNDISendStream.h"

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;

private:
    void renderFrame(float t);

    ofxNDISender ndiSender;
    ofxNDISendVideo ndiVideo;

    ofFbo fbo;
    ofPixels pixels;

    std::string streamName = "NST Motion Test";
    int frameW = 1280;
    int frameH = 720;
    float speed = 1.0f;
    bool paused = false;
};
