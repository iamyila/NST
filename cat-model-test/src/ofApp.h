#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;

private:
    bool loadCatObj();
    void drawFallbackCat() const;
    void writeDebugFile(const std::string& path) const;

    ofEasyCam cam;
    ofMesh catMesh;

    bool catLoaded = false;
    bool snapshotSaved = false;
    std::string loadedPath;
    glm::vec3 catMin{0.0f};
    glm::vec3 catMax{0.0f};
    float catHeight = 1.0f;
    float turntableDeg = 0.0f;
};
