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
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;

private:
    struct MotionBounds {
        float minX = 0.0f;
        float maxX = 0.0f;
        float minY = 0.0f;
        float maxY = 0.0f;
    };

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
        bool naturalOn = true;
        float stateRemainingSec = 1.0f;
        float lowSpeedAccumSec = 0.0f;
    };

    void initShapes();
    void updateShapes(float dt);
    void updateBlinkStates(float dt);
    MotionBounds getMotionBounds(float radius) const;
    void keepInsideFrame(MovingShape& shape);
    void keepInsideFrameAirHockey(MovingShape& shape);
    void applyCenterDeadZone(MovingShape& shape, float dt);
    void applyBlobRepulsion(float dt);
    void applyPushField(const glm::vec2& pt, float strength);
    void resetShapeForAirHockey(MovingShape& s);
    float randomHoldDuration(bool onState) const;
    ofRectangle getSliderRect(int sliderIndex) const;
    bool handleSliderAt(int x, int y);
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
    bool airHockeyMode = false;
    float simTime = 0.0f;
    bool autoBlobCount = true;
    int manualBlobCount = 3;
    int activeBlobLimit = 3;
    std::string manualBlobInput;
    bool edgeBounce = true;
    bool squareMotionBounds = false;
    bool deadZoneEnabled = false;
    float centerDeadZoneNorm = 0.0f; // 0..0.45, normalized to shortest frame side
    bool collisionPhysics = true;
    float collisionStrength = 1200.0f;
    float pushStrength = 1800.0f;
    bool naturalBlink = true;
    float onDutyControl = 0.72f;
    float blinkRateControl = 0.30f;

    void commitManualBlobInput();
};
