#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxNDISender.h"
#include "ofxNDISendStream.h"
#include <array>
#include <mutex>
#include <string>
#include <tuple>
#include <vector>

#ifdef __APPLE__
#include <CoreMIDI/CoreMIDI.h>
#endif

class ofApp : public ofBaseApp {
public:
    ~ofApp() override;
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

public:
    enum class ObjectKind {
        Person,
        Hand,
        Cat,
        Dog,
        PlainObject,
        Car
    };

    enum class ObjectPreset {
        Mixed,
        People,
        Hands,
        Cats,
        Dogs,
        PlainObjects,
        Cars
    };

private:

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
        bool rainDormant = false;
        float depth = 0.5f;
        float depthVel = 0.0f;
        float yawDeg = 0.0f;
        ObjectKind objectKind = ObjectKind::PlainObject;
    };

    struct SenderPreset {
        bool valid = false;
        float speed = 1.0f;
        bool bUseBrownianDrunkMotion = true;
        bool airHockeyMode = false;
        bool rainMode = false;
        bool autoBlobCount = true;
        int manualBlobCount = 3;
        bool edgeBounce = true;
        bool squareMotionBounds = false;
        bool deadZoneEnabled = false;
        float centerDeadZoneNorm = 0.0f;
        bool collisionPhysics = true;
        float collisionStrength = 1200.0f;
        bool naturalBlink = true;
        bool alwaysOnMode = true;
        float onDutyControl = 0.72f;
        float blinkRateControl = 0.30f;
        bool magnetMode = false;
        float magnetStrength = 720.0f;
        bool floodEnabled = false;
        float floodDurationSec = 2.6f;
        float floodCooldownSec = 1.4f;
        float rainAngleDeg = 90.0f;
        float viewYawDeg = 0.0f;
        float viewPitchDeg = 18.0f;
        float observerOffsetX = 0.0f;
        float observerDistanceY = 130.0f;
        bool midiTakeoverEnabled = false;
        bool midiTakeoverPickUp = true;
        int objectPreset = 0;
    };

    void initShapes();
    void updateShapes(float dt);
    void updateBlinkStates(float dt);
    MotionBounds getMotionBounds(float radius) const;
    void keepInsideFrame(MovingShape& shape);
    void keepInsideFrameAirHockey(MovingShape& shape);
    void applyCenterDeadZone(MovingShape& shape, float dt);
    void applyMagnetForce(MovingShape& shape, float dt, const glm::vec2& target);
    void applyBlobRepulsion(float dt);
    void applyPushField(const glm::vec2& pt, float strength);
    void resetShapeForAirHockey(MovingShape& s);
    void resetShapeForRain(MovingShape& s, bool firstInit, int rainIndex = -1);
    float randomHoldDuration(bool onState) const;
    void updateDepthState(MovingShape& s, float dt, int idx);
    glm::vec3 shapeWorldPoint(const MovingShape& s) const;
    float shapeWorldCollisionRadius(const MovingShape& shape) const;
    glm::vec2 velocityScreenToWorld(const glm::vec2& screenVel) const;
    glm::vec2 velocityWorldToScreen(const glm::vec2& worldVel) const;
    glm::vec3 cameraTargetWorld() const;
    glm::vec3 cameraEyeWorld() const;
    bool projectWorldPoint(const glm::vec3& worldPoint, glm::vec2& screenPoint, float* cameraDepth = nullptr) const;
    float projectScaleAtWorld(const glm::vec3& worldPoint) const;
    float projectRadius(const MovingShape& s) const;
    void drawShape3D(const MovingShape& s, int idx);
    bool drawCatModel3D(const MovingShape& s);
    bool drawPersonModel3D(const MovingShape& s);
    bool drawCarModel3D(const MovingShape& s);
    void drawPersonGlyph(const glm::vec2& p, float size) const;
    void drawHandGlyph(const glm::vec2& p, float size) const;
    void drawCatGlyph(const glm::vec2& p, float size, float yawDeg) const;
    void drawDogGlyph(const glm::vec2& p, float size, float yawDeg) const;
    void drawPlainObjectGlyph(const glm::vec2& p, float size, float yawDeg) const;
    void drawListenerHead() const;
    void drawGroundPlane() const;
    void drawHemisphereOverlay() const;
    void drawTopDownOverview() const;
    void loadCatModel();
    void loadPersonModel();
    void loadCarModel();
    void assignObjectPreset();
    std::string objectPresetName() const;
    ofRectangle getSliderRect(int sliderIndex) const;
    ofRectangle getFloodArmRect() const;
    bool handleSliderAt(int x, int y);
    bool handlePresetGridAt(int x, int y);
    ofRectangle getPresetCellRect(int row, int col) const;
    bool isShapeOn(const MovingShape& shape) const;
    void renderFrame();
    void applyPeriodicBlinkControls();
    void savePresetSlot(int slotIndex);
    void loadPresetSlot(int slotIndex);
    void applyPreset(const SenderPreset& p);
    SenderPreset captureCurrentPreset() const;
    void savePresetFile() const;
    void loadPresetFile();
    float edgeMetric01(const MovingShape& s) const;
    void setupMidiInput();
    void teardownMidiInput();
    void processMidiInputQueue();
    void applyMidiTakeover(float dt);
    glm::vec2 rainDirectionUnit() const;
    glm::vec2 rainTangentUnit() const;
    void getRainProjectionExtents(float& alongDirHalfExtent, float& alongTangentHalfExtent) const;
    int midiAxisForCc(int cc) const;
    std::string midiSourceName(MIDIEndpointRef source) const;
    static void midiReadProc(const MIDIPacketList* packetList, void* readProcRefCon, void* srcConnRefCon);
    void handleMidiPacketList(const MIDIPacketList* packetList);

    ofxNDISender ndiSender;
    ofxNDISendVideo ndiVideo;
    ofxAssimpModelLoader catModel;
    ofVboMesh catObjMesh;
    ofImage catObjTexture;
    ofVboMesh personObjMesh;
    ofImage personObjTexture;
    ofVboMesh carObjMesh;
    ofImage carObjTexture;

    ofFbo fbo;
    ofPixels pixels;
    std::vector<MovingShape> shapes;
    bool catObjLoaded = false;
    bool catObjTextureLoaded = false;
    bool personObjLoaded = false;
    bool personObjTextureLoaded = false;
    bool carObjLoaded = false;
    bool carObjTextureLoaded = false;
    bool catModelLoaded = false;
    std::vector<ofMesh> catModelMeshes;
    glm::vec3 catModelMin{0.0f};
    glm::vec3 catModelMax{0.0f};
    float catModelHeight = 1.0f;
    float catModelDepth = 1.0f;
    glm::vec3 personModelMin{0.0f};
    glm::vec3 personModelMax{0.0f};
    float personModelHeight = 1.0f;
    float personModelDepth = 1.0f;
    glm::vec3 carModelMin{0.0f};
    glm::vec3 carModelMax{0.0f};
    float carModelHeight = 1.0f;
    float carModelDepth = 1.0f;

    std::string streamName = "NST Motion Test 3D";
    float ndiSendTargetFps = 30.0f;
    double lastNdiSendTimeSec = -1.0;
    int frameW = 1280;
    int frameH = 720;
    float speed = 1.0f;
    bool paused = false;
    bool bUseBrownianDrunkMotion = true;
    bool airHockeyMode = false;
    bool rainMode = false;
    float simTime = 0.0f;
    bool autoBlobCount = false;
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
    bool alwaysOnMode = true;
    float onDutyControl = 0.72f;
    float blinkRateControl = 0.30f;
    bool magnetMode = false;
    float magnetStrength = 720.0f;
    bool floodEnabled = false;
    bool floodActive = false;
    float floodRemainingSec = 0.0f;
    float floodCooldownRemainingSec = 0.0f;
    bool floodEdgeLatch = false;
    float floodDurationSec = 2.6f;
    float floodCooldownSec = 1.4f;
    float rainAngleDeg = 90.0f; // 0=right, 90=down, 180=left, 270=up
    ObjectPreset objectPreset = ObjectPreset::Mixed;
    float viewYawDeg = 0.0f;
    float viewPitchDeg = 18.0f;
    float observerOffsetX = 0.0f;
    float observerDistanceY = 130.0f;
    bool midiTakeoverEnabled = false;
    bool midiTakeoverPickUp = true;
    bool midiTakeoverAllowRain = false;
    bool showHelpOverlay = false;
    int midiTakeoverChannel = 16;
    std::array<int, 8> midiTakeoverCcMap{{0, 1, 6, 7, 8, 9, 10, 11}};
    std::array<float, 8> midiTakeoverNorm{{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}};
    std::array<bool, 8> midiTakeoverSeen{{false, false, false, false, false, false, false, false}};
    std::array<bool, 8> midiTakeoverUpdated{{false, false, false, false, false, false, false, false}};
    std::array<bool, 8> midiTakeoverLatched{{false, false, false, false, false, false, false, false}};
    std::string midiTakeoverStatus = "MIDI takeover ready";
    int midiConnectedSourceCount = 0;
#ifdef __APPLE__
    MIDIClientRef midiClientRef = 0;
    MIDIPortRef midiInputPortRef = 0;
#endif
    std::mutex midiQueueMutex;
    std::vector<std::tuple<int, int, int>> midiCcQueue;
    std::array<SenderPreset, 4> presetSlots;
    int currentPresetSlot = -1;
    std::string presetStatus;
    float presetStatusUntil = 0.0f;
    bool startupSnapshotSaved = false;

    void commitManualBlobInput();
};
