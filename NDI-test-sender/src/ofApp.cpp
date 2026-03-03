#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(16);

    fbo.allocate(frameW, frameH, GL_RGBA);
    fbo.begin();
    ofClear(0, 0, 0, 255);
    fbo.end();

    if (!ndiSender.setup(streamName)) {
        ofLogError("ofApp") << "Failed to set up NDI sender: " << streamName;
    } else {
        ndiVideo.setup(ndiSender);
        ndiVideo.setAsync(true);
        ofLogNotice("ofApp") << "NDI sender ready: " << streamName;
    }
}

void ofApp::renderFrame(float t) {
    fbo.begin();
    ofClear(10, 10, 14, 255);

    ofPushStyle();

    for (int x = 0; x <= frameW; x += 80) {
        ofSetColor(28, 28, 34);
        ofDrawLine(x, 0, x, frameH);
    }
    for (int y = 0; y <= frameH; y += 80) {
        ofSetColor(28, 28, 34);
        ofDrawLine(0, y, frameW, y);
    }

    for (int i = 0; i < 4; ++i) {
        float phase = t * (0.7f + 0.2f * i) + i * 1.2f;
        float x = ofMap(sinf(phase), -1.0f, 1.0f, 80.0f, frameW - 80.0f);
        float y = ofMap(cosf(phase * 1.37f), -1.0f, 1.0f, 80.0f, frameH - 80.0f);
        float r = 22.0f + 10.0f * i;

        ofSetColor(40 + i * 45, 200 - i * 25, 255 - i * 35);
        ofDrawCircle(x, y, r);

        ofNoFill();
        ofSetColor(255, 255, 255, 70);
        ofDrawCircle(x, y, r + 14.0f);
        ofFill();
    }

    float boxX = ofMap(sinf(t * 0.8f), -1.0f, 1.0f, 120.0f, frameW - 320.0f);
    float boxY = ofMap(cosf(t * 1.1f), -1.0f, 1.0f, 120.0f, frameH - 220.0f);
    ofSetColor(245, 90, 40);
    ofDrawRectangle(boxX, boxY, 200, 120);

    ofSetColor(255);
    ofDrawBitmapStringHighlight("NST NDI Motion Test", 20, 24);
    ofDrawBitmapStringHighlight("Stream: " + streamName, 20, 44);
    ofDrawBitmapStringHighlight("Time: " + ofToString(t, 2), 20, 64);
    ofDrawBitmapStringHighlight("Keys: +/- speed, space pause", 20, 84);

    ofPopStyle();
    fbo.end();
}

void ofApp::update() {
    float t = (paused ? 0.0f : ofGetElapsedTimef() * speed);
    renderFrame(t);

    if (ndiSender.isSetup()) {
        fbo.readToPixels(pixels);
        ndiVideo.send(pixels);
    }
}

void ofApp::draw() {
    ofSetColor(255);
    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());

    ofDrawBitmapStringHighlight(
        "Sending moving NDI stream: " + streamName +
        " | " + (paused ? "PAUSED" : "LIVE") +
        " | speed=" + ofToString(speed, 2),
        20, ofGetHeight() - 20
    );
}

void ofApp::keyPressed(int key) {
    if (key == ' ') {
        paused = !paused;
        return;
    }

    if (key == '+' || key == '=') {
        speed = std::min(4.0f, speed + 0.1f);
    } else if (key == '-' || key == '_') {
        speed = std::max(0.1f, speed - 0.1f);
    }
}
