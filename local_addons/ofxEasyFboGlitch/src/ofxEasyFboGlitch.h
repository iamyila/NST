#pragma once

#ifndef __ofxEasyFboGlitch__
#define __ofxEasyFboGlitch__

#include <iostream>

#include "ofMain.h"
#include "ofxFastFboReader.h"
class ofxEasyFboGlitch : public ofBaseApp{
public:
    ofxEasyFboGlitch();

    //void setup();
    void allocate(float _w,float _h);
    void draw(ofFbo _fbo,float _x,float _y,float _w,float _h);
    void setGlichResetProbability (float _probability);
    void doGlitch(int duration);
    
    ofImage glitchImg;
    ofImageQualityType imgQuality;
    float fboW,fboH;
    bool glitchReset;
    ofFbo fbo;
    ofFloatPixels pix;
    ofxFastFboReader reader;
    float glitchResetProbability;
    int duration;   // frames
};
#endif
