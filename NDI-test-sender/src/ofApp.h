#pragma once

#include "ofMain.h"
#include "ofxNDISender.h"
#include "ofxNDISendStream.h"
#include <string>

class ofApp : public ofBaseApp {
public:
    void setup() override;
    void update() override;
    void draw() override;
    void keyPressed(int key) override;

private:
    enum class MotionType {
        Brownian,
        Drunkard
    };

    struct MovingShape {
        glm::vec2 pos{0.0f, 0.0f};
        glm::vec2 vel{0.0f, 0.0f};
        glm::vec2 walkDir{0.0f, 0.0f};
        float radius = 20.0f;
        ofColor color = ofColor::white;
        MotionType motion = MotionType::Brownian;
        bool bRect = false;
        float blinkPeriodSec = 2.0f;
        float blinkDuty = 0.6f;
        float blinkPhaseSec = 0.0f;
    };

    void initShapes();
    void updateShapes(float dt);
    void keepInsideFrame(MovingShape& shape);
    bool isShapeOn(const MovingShape& shape) const;
    void renderFrame();

    ofxNDISender ndiSender;
    ofxNDISendVideo ndiVideo;

    ofFbo fbo;
    ofPixels pixels;
    std::vector<MovingShape> shapes;

    std::string streamName = "NST Motion Test";
    int frameW = 1280;
    int frameH = 720;
    float speed = 1.0f;
    bool paused = false;
    bool bUseBrownianDrunkMotion = true;
    float simTime = 0.0f;
    bool autoBlobCount = true;
    int manualBlobCount = 3;
    int activeBlobLimit = 3;
    std::string manualBlobInput;

    void commitManualBlobInput();
};
