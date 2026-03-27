#include "ofApp.h"
#include <cmath>
#include <sstream>

namespace {
constexpr float kWorldSide = 100.0f;
constexpr float kWorldNearY = 100.0f;
constexpr float kWorldFarY = -100.0f;
constexpr float kHemisphereRadius = 100.0f;

int midiDataBytesForStatus(unsigned char status) {
    if (status >= 0xF0) return 0;
    const unsigned char type = static_cast<unsigned char>(status & 0xF0);
    if (type == 0xC0 || type == 0xD0) return 1;
    return 2;
}

float wrapDegrees(float deg) {
    while (deg < 0.0f) deg += 360.0f;
    while (deg >= 360.0f) deg -= 360.0f;
    return deg;
}

float wrapSignedDegrees(float deg) {
    while (deg < -180.0f) deg += 360.0f;
    while (deg > 180.0f) deg -= 360.0f;
    return deg;
}

const char* objectPresetLabel(ofApp::ObjectPreset preset) {
    switch (preset) {
        case ofApp::ObjectPreset::Mixed: return "Mixed";
        case ofApp::ObjectPreset::People: return "People";
        case ofApp::ObjectPreset::Hands: return "Hands";
        case ofApp::ObjectPreset::Dogs: return "Dogs";
        case ofApp::ObjectPreset::PlainObjects: return "Objects";
        case ofApp::ObjectPreset::Squares: return "Squares";
        case ofApp::ObjectPreset::Stars: return "Stars";
    }
    return "Mixed";
}

ofApp::ObjectKind objectKindForPreset(ofApp::ObjectPreset preset, int index) {
    switch (preset) {
        case ofApp::ObjectPreset::People: return ofApp::ObjectKind::Person;
        case ofApp::ObjectPreset::Hands: return ofApp::ObjectKind::Hand;
        case ofApp::ObjectPreset::Dogs: return ofApp::ObjectKind::Dog;
        case ofApp::ObjectPreset::PlainObjects: return ofApp::ObjectKind::PlainObject;
        case ofApp::ObjectPreset::Squares: return ofApp::ObjectKind::Square;
        case ofApp::ObjectPreset::Stars: return ofApp::ObjectKind::Star;
        case ofApp::ObjectPreset::Mixed:
        default: {
            const ofApp::ObjectKind kinds[] = {
                ofApp::ObjectKind::Person,
                ofApp::ObjectKind::Hand,
                ofApp::ObjectKind::Dog,
                ofApp::ObjectKind::PlainObject,
                ofApp::ObjectKind::Square,
                ofApp::ObjectKind::Star
            };
            return kinds[index % (sizeof(kinds) / sizeof(kinds[0]))];
        }
    }
}

glm::vec2 worldToScreenPoint(const glm::vec2& worldPoint, int frameW, int frameH) {
    return glm::vec2(
        ofMap(worldPoint.x, -kWorldSide, kWorldSide, 0.0f, static_cast<float>(frameW), true),
        ofMap(worldPoint.y, kWorldFarY, kWorldNearY, 0.0f, static_cast<float>(frameH), true)
    );
}

glm::vec2 screenToWorldPoint(const glm::vec2& screenPoint, int frameW, int frameH) {
    return glm::vec2(
        ofMap(screenPoint.x, 0.0f, static_cast<float>(frameW), -kWorldSide, kWorldSide, true),
        ofMap(screenPoint.y, 0.0f, static_cast<float>(frameH), kWorldFarY, kWorldNearY, true)
    );
}

glm::vec2 clampWorldToCircle(const glm::vec2& worldPoint, float allowedRadius) {
    const float dist = glm::length(worldPoint);
    if (dist <= allowedRadius || dist <= 0.0001f) return worldPoint;
    return (worldPoint / dist) * allowedRadius;
}

glm::vec2 randomWorldPointInCircle(float allowedRadius) {
    const float ang = ofRandom(glm::two_pi<float>());
    const float rad = std::sqrt(ofRandomuf()) * allowedRadius;
    return glm::vec2(std::cos(ang) * rad, std::sin(ang) * rad);
}
}

ofApp::~ofApp() {
    teardownMidiInput();
}

void ofApp::setupMidiInput() {
#ifdef __APPLE__
    teardownMidiInput();

    const OSStatus clientErr = MIDIClientCreate(CFSTR("NSTSenderMIDI"), nullptr, nullptr, &midiClientRef);
    if (clientErr != noErr || midiClientRef == 0) {
        midiTakeoverStatus = "MIDI unavailable (client create failed)";
        return;
    }

    const OSStatus portErr = MIDIInputPortCreate(midiClientRef, CFSTR("NSTSenderMIDIIn"), &ofApp::midiReadProc, this, &midiInputPortRef);
    if (portErr != noErr || midiInputPortRef == 0) {
        midiTakeoverStatus = "MIDI unavailable (input port failed)";
        teardownMidiInput();
        return;
    }

    midiConnectedSourceCount = 0;
    const ItemCount sourceCount = MIDIGetNumberOfSources();
    for (ItemCount i = 0; i < sourceCount; ++i) {
        MIDIEndpointRef source = MIDIGetSource(i);
        if (source == 0) continue;
        if (MIDIPortConnectSource(midiInputPortRef, source, nullptr) == noErr) {
            ++midiConnectedSourceCount;
        }
    }

    if (midiConnectedSourceCount <= 0) {
        midiTakeoverStatus = "MIDI in ready (no sources connected)";
    } else {
        midiTakeoverStatus = "MIDI in connected: " + ofToString(midiConnectedSourceCount) + " source(s)";
    }
#else
    midiTakeoverStatus = "MIDI input unsupported on this platform";
#endif
}

void ofApp::teardownMidiInput() {
#ifdef __APPLE__
    if (midiInputPortRef != 0) {
        MIDIPortDispose(midiInputPortRef);
        midiInputPortRef = 0;
    }
    if (midiClientRef != 0) {
        MIDIClientDispose(midiClientRef);
        midiClientRef = 0;
    }
#endif
    midiConnectedSourceCount = 0;
}

void ofApp::midiReadProc(const MIDIPacketList* packetList, void* readProcRefCon, void* srcConnRefCon) {
    (void)srcConnRefCon;
    if (!packetList || !readProcRefCon) return;
    auto* app = static_cast<ofApp*>(readProcRefCon);
    app->handleMidiPacketList(packetList);
}

void ofApp::handleMidiPacketList(const MIDIPacketList* packetList) {
    if (!packetList) return;
    std::lock_guard<std::mutex> lock(midiQueueMutex);

    const MIDIPacket* packet = &packetList->packet[0];
    for (unsigned int i = 0; i < packetList->numPackets; ++i) {
        unsigned char runningStatus = 0;
        int expectedData = 0;
        bool haveData1 = false;
        unsigned char data1 = 0;

        for (unsigned int j = 0; j < packet->length; ++j) {
            const unsigned char byte = packet->data[j];

            if (byte & 0x80) {
                if (byte >= 0xF8) continue; // realtime
                if (byte == 0xF0 || byte == 0xF7) {
                    runningStatus = 0;
                    expectedData = 0;
                    haveData1 = false;
                    continue;
                }
                runningStatus = byte;
                expectedData = midiDataBytesForStatus(runningStatus);
                haveData1 = false;
                continue;
            }

            if (runningStatus == 0 || expectedData != 2) continue;

            if (!haveData1) {
                data1 = byte;
                haveData1 = true;
                continue;
            }

            const unsigned char data2 = byte;
            haveData1 = false;

            const unsigned char type = static_cast<unsigned char>(runningStatus & 0xF0);
            if (type != 0xB0) continue; // CC only

            const int channel = static_cast<int>(runningStatus & 0x0F) + 1;
            const int cc = static_cast<int>(data1);
            const int value = static_cast<int>(data2);
            midiCcQueue.emplace_back(channel, cc, value);
        }

        packet = MIDIPacketNext(packet);
    }
}

int ofApp::midiAxisForCc(int cc) const {
    for (int i = 0; i < static_cast<int>(midiTakeoverCcMap.size()); ++i) {
        if (midiTakeoverCcMap[i] == cc) return i;
    }
    return -1;
}

std::string ofApp::midiSourceName(MIDIEndpointRef source) const {
#ifdef __APPLE__
    if (source == 0) return "Unknown";
    CFStringRef cfName = nullptr;
    if (MIDIObjectGetStringProperty(source, kMIDIPropertyDisplayName, &cfName) != noErr || cfName == nullptr) {
        return "Unknown";
    }
    char buffer[256];
    const bool ok = CFStringGetCString(cfName, buffer, sizeof(buffer), kCFStringEncodingUTF8);
    CFRelease(cfName);
    return ok ? std::string(buffer) : std::string("Unknown");
#else
    (void)source;
    return "Unknown";
#endif
}

void ofApp::processMidiInputQueue() {
    std::vector<std::tuple<int, int, int>> queue;
    {
        std::lock_guard<std::mutex> lock(midiQueueMutex);
        if (midiCcQueue.empty()) return;
        queue.swap(midiCcQueue);
    }

    int applied = 0;
    for (const auto& msg : queue) {
        const int channel = std::get<0>(msg);
        const int cc = std::get<1>(msg);
        const int value = std::get<2>(msg);
        if (channel != midiTakeoverChannel) continue;
        const int axis = midiAxisForCc(cc);
        if (axis < 0) continue;
        midiTakeoverNorm[axis] = ofClamp(static_cast<float>(value) / 127.0f, 0.0f, 1.0f);
        midiTakeoverSeen[axis] = true;
        midiTakeoverUpdated[axis] = true;
        if (alwaysOnMode && midiTakeoverEnabled) {
            const int shapeIndex = axis / 2;
            if (shapeIndex >= 0 && shapeIndex < static_cast<int>(shapes.size())) {
                shapes[shapeIndex].naturalOn = true;
                shapes[shapeIndex].stateRemainingSec = 5.0f;
            }
        }
        ++applied;
    }

    if (applied > 0) {
        midiTakeoverStatus =
            "listening ch" + ofToString(midiTakeoverChannel) +
            " (mapped CC updates: " + ofToString(applied) + ", src " + ofToString(midiConnectedSourceCount) + ")";
    }
}

void ofApp::applyMidiTakeover(float dt) {
    if (!midiTakeoverEnabled) return;
    if (rainMode && !midiTakeoverAllowRain) return;
    if (dt <= 0.0f) return;

    const int controlled = std::min(4, static_cast<int>(shapes.size()));
    for (int i = 0; i < controlled; ++i) {
        const int xAxis = i * 2;
        const int yAxis = i * 2 + 1;
        if (!midiTakeoverSeen[xAxis] || !midiTakeoverSeen[yAxis]) continue;

        auto& s = shapes[i];
        const float worldRadius = ofMap(s.radius, 18.0f, 48.0f, 3.8f, 12.5f, true);
        const float allowed = std::max(1.0f, kHemisphereRadius - worldRadius);
        const glm::vec2 currentWorld = screenToWorldPoint(s.pos, frameW, frameH);

        const float xNorm = midiTakeoverNorm[xAxis];
        const float yNorm = midiTakeoverNorm[yAxis];
        glm::vec2 targetWorld(
            ofLerp(-kWorldSide, kWorldSide, xNorm),
            ofLerp(kWorldNearY, kWorldFarY, yNorm)
        );
        targetWorld = clampWorldToCircle(targetWorld, allowed);

        if (midiTakeoverPickUp) {
            const float currentXNorm = ofMap(currentWorld.x, -kWorldSide, kWorldSide, 0.0f, 1.0f, true);
            const float currentYNorm = ofMap(currentWorld.y, kWorldNearY, kWorldFarY, 0.0f, 1.0f, true);
            constexpr float pickupWindow = 0.05f;

            if (!midiTakeoverLatched[xAxis] && std::abs(xNorm - currentXNorm) <= pickupWindow) {
                midiTakeoverLatched[xAxis] = true;
            }
            if (!midiTakeoverLatched[yAxis] && std::abs(yNorm - currentYNorm) <= pickupWindow) {
                midiTakeoverLatched[yAxis] = true;
            }
            if (!midiTakeoverLatched[xAxis]) targetWorld.x = currentWorld.x;
            if (!midiTakeoverLatched[yAxis]) targetWorld.y = currentWorld.y;
            targetWorld = clampWorldToCircle(targetWorld, allowed);
        } else {
            midiTakeoverLatched[xAxis] = true;
            midiTakeoverLatched[yAxis] = true;
        }

        const glm::vec2 target = worldToScreenPoint(targetWorld, frameW, frameH);
        const float alpha = midiTakeoverPickUp ? 0.38f : 0.24f;
        s.pos = glm::mix(s.pos, target, alpha);
        s.vel *= 0.55f;
        applyCenterDeadZone(s, dt);
        keepInsideFrame(s);
        if (alwaysOnMode && (midiTakeoverUpdated[xAxis] || midiTakeoverUpdated[yAxis])) {
            s.naturalOn = true;
            s.stateRemainingSec = 5.0f;
        }
    }
    midiTakeoverUpdated.fill(false);
}

ofApp::MotionBounds ofApp::getMotionBounds(float radius) const {
    MotionBounds b;
    const float worldRadius = ofMap(radius, 18.0f, 48.0f, 3.8f, 12.5f, true);
    const float allowed = std::max(1.0f, kHemisphereRadius - worldRadius);
    const float halfExtent = allowed * 0.70710678f;
    const glm::vec2 minScreen = worldToScreenPoint(glm::vec2(-halfExtent, -halfExtent), frameW, frameH);
    const glm::vec2 maxScreen = worldToScreenPoint(glm::vec2(halfExtent, halfExtent), frameW, frameH);
    b.minX = minScreen.x;
    b.maxX = maxScreen.x;
    b.minY = maxScreen.y;
    b.maxY = minScreen.y;
    return b;
}

glm::vec2 ofApp::rainDirectionUnit() const {
    const float rad = glm::radians(rainAngleDeg);
    glm::vec2 d(std::cos(rad), std::sin(rad));
    if (glm::length2(d) < 0.000001f) return glm::vec2(0.0f, 1.0f);
    return glm::normalize(d);
}

glm::vec2 ofApp::rainTangentUnit() const {
    const glm::vec2 d = rainDirectionUnit();
    return glm::vec2(-d.y, d.x);
}

void ofApp::getRainProjectionExtents(float& alongDirHalfExtent, float& alongTangentHalfExtent) const {
    const glm::vec2 d = rainDirectionUnit();
    const glm::vec2 t = rainTangentUnit();
    const float halfW = static_cast<float>(frameW) * 0.5f;
    const float halfH = static_cast<float>(frameH) * 0.5f;
    alongDirHalfExtent = std::abs(d.x) * halfW + std::abs(d.y) * halfH;
    alongTangentHalfExtent = std::abs(t.x) * halfW + std::abs(t.y) * halfH;
}

void ofApp::setup() {
    ofSetFrameRate(40);
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

    initShapes();
    applyPeriodicBlinkControls();
    loadPresetFile();
    setupMidiInput();
}

void ofApp::applyPeriodicBlinkControls() {
    const float dutyBoost = ofLerp(-0.28f, 0.45f, ofClamp(onDutyControl, 0.05f, 0.95f));
    const float rateScale = ofLerp(2.6f, 0.28f, ofClamp(blinkRateControl, 0.0f, 1.0f));
    for (size_t i = 0; i < shapes.size(); ++i) {
        auto& s = shapes[i];
        const float basePeriod = 1.4f + 0.33f * static_cast<float>(i % 5);
        s.blinkPeriodSec = ofClamp(basePeriod * rateScale, 0.18f, 12.0f);
        const float baseDuty = 0.50f + 0.06f * static_cast<float>(i % 3);
        s.blinkDuty = ofClamp(baseDuty + dutyBoost, 0.05f, 0.98f);
    }
}

float ofApp::randomHoldDuration(bool onState) const {
    const float duty = ofClamp(onDutyControl, 0.05f, 0.95f);
    const float switchRate = ofLerp(0.08f, 1.8f, ofClamp(blinkRateControl, 0.0f, 1.0f));
    const float lambda = std::max(0.02f, onState ? switchRate * (1.0f - duty) : switchRate * duty);
    const float u = std::max(0.0001f, ofRandomuf());
    float sample = -std::log(1.0f - u) / lambda;
    // Bias toward longer ON windows and shorter OFF gaps (for musical continuity).
    if (onState) {
        sample *= 3.0f;
        return ofClamp(sample, 0.8f, 14.0f);
    }
    sample *= 0.35f;
    return ofClamp(sample, 0.08f, 4.0f);
}

std::string ofApp::objectPresetName() const {
    return objectPresetLabel(objectPreset);
}

void ofApp::assignObjectPreset() {
    for (int i = 0; i < static_cast<int>(shapes.size()); ++i) {
        shapes[i].objectKind = objectKindForPreset(objectPreset, i);
    }
}

glm::vec3 ofApp::shapeWorldPoint(const MovingShape& s) const {
    const float worldX = ofMap(s.pos.x, 0.0f, static_cast<float>(frameW), -kWorldSide, kWorldSide, true);
    const float worldY = ofMap(s.pos.y, 0.0f, static_cast<float>(frameH), kWorldFarY, kWorldNearY, true);

    float baseHeight = 0.0f;
    float extraHeight = 0.0f;
    switch (s.objectKind) {
        case ObjectKind::Person:
            baseHeight = 0.0f;
            extraHeight = ofLerp(0.0f, 2.5f, 1.0f - s.depth);
            break;
        case ObjectKind::Hand:
            baseHeight = 4.0f;
            extraHeight = ofLerp(0.0f, 10.0f, 1.0f - s.depth);
            break;
        case ObjectKind::Dog:
            baseHeight = 0.0f;
            extraHeight = ofLerp(0.0f, 1.5f, 1.0f - s.depth);
            break;
        case ObjectKind::PlainObject:
            baseHeight = 0.0f;
            extraHeight = ofLerp(0.0f, 6.0f, 1.0f - s.depth);
            break;
        case ObjectKind::Square:
            baseHeight = 0.0f;
            extraHeight = ofLerp(0.0f, 8.0f, 1.0f - s.depth);
            break;
        case ObjectKind::Star:
            baseHeight = 8.0f;
            extraHeight = ofLerp(2.0f, 18.0f, 1.0f - s.depth);
            break;
    }

    return glm::vec3(worldX, worldY, baseHeight + extraHeight);
}

glm::vec3 ofApp::cameraTargetWorld() const {
    return glm::vec3(0.0f, 0.0f, 0.0f);
}

glm::vec3 ofApp::cameraEyeWorld() const {
    float effectiveYawDeg = viewYawDeg;
    float effectivePitchDeg = viewPitchDeg;
    if (effectivePitchDeg > 90.0f) {
        effectivePitchDeg = 180.0f - effectivePitchDeg;
        effectiveYawDeg = wrapSignedDegrees(effectiveYawDeg + 180.0f);
    } else if (effectivePitchDeg < -90.0f) {
        effectivePitchDeg = -180.0f - effectivePitchDeg;
        effectiveYawDeg = wrapSignedDegrees(effectiveYawDeg + 180.0f);
    }

    const float yawRad = glm::radians(effectiveYawDeg);
    const float pitchRad = glm::radians(effectivePitchDeg);
    const float horizontalRadius = std::cos(pitchRad) * observerDistanceY;
    const float verticalRadius = std::sin(pitchRad) * observerDistanceY;
    return glm::vec3(
        observerOffsetX + std::sin(yawRad) * horizontalRadius,
        std::cos(yawRad) * horizontalRadius,
        verticalRadius
    );
}

bool ofApp::projectWorldPoint(const glm::vec3& worldPoint, glm::vec2& screenPoint, float* cameraDepth) const {
    const glm::vec3 eye = cameraEyeWorld();
    const glm::vec3 target = cameraTargetWorld();
    glm::vec3 forward = glm::normalize(target - eye);
    glm::vec3 up(0.0f, 0.0f, 1.0f);
    if (std::abs(glm::dot(forward, up)) > 0.98f) {
        up = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    const glm::mat4 view = glm::lookAt(eye, target, up);
    const glm::mat4 proj = glm::perspective(glm::radians(48.0f), static_cast<float>(frameW) / static_cast<float>(frameH), 0.1f, 400.0f);

    const glm::vec4 viewPos = view * glm::vec4(worldPoint, 1.0f);
    const float forwardDepth = -viewPos.z;
    if (cameraDepth) *cameraDepth = forwardDepth;
    if (forwardDepth <= 0.01f) return false;

    const glm::vec4 clip = proj * viewPos;
    if (std::abs(clip.w) <= 0.00001f) return false;

    const glm::vec3 ndc = glm::vec3(clip) / clip.w;
    if (!std::isfinite(ndc.x) || !std::isfinite(ndc.y) || !std::isfinite(ndc.z)) return false;
    screenPoint.x = (ndc.x * 0.5f + 0.5f) * static_cast<float>(frameW);
    screenPoint.y = (1.0f - (ndc.y * 0.5f + 0.5f)) * static_cast<float>(frameH);
    return true;
}

float ofApp::projectScaleAtWorld(const glm::vec3& worldPoint) const {
    glm::vec2 a, b;
    if (!projectWorldPoint(worldPoint, a, nullptr)) return 1.0f;
    if (!projectWorldPoint(worldPoint + glm::vec3(1.0f, 0.0f, 0.0f), b, nullptr)) return 1.0f;
    return std::max(0.75f, glm::distance(a, b));
}

float ofApp::projectRadius(const MovingShape& s) const {
    const glm::vec3 worldPoint = shapeWorldPoint(s);
    const float worldRadius = ofMap(s.radius, 18.0f, 48.0f, 3.8f, 12.5f, true);
    glm::vec2 center;
    glm::vec2 pxRight;
    glm::vec2 pxUp;
    if (!projectWorldPoint(worldPoint, center, nullptr)) return 4.0f;
    float r1 = 0.0f;
    float r2 = 0.0f;
    if (projectWorldPoint(worldPoint + glm::vec3(worldRadius, 0.0f, 0.0f), pxRight, nullptr)) {
        r1 = glm::distance(center, pxRight);
    }
    if (projectWorldPoint(worldPoint + glm::vec3(0.0f, 0.0f, worldRadius), pxUp, nullptr)) {
        r2 = glm::distance(center, pxUp);
    }
    const float baseRadius = std::max(r1, r2);
    const float radialNorm = ofClamp(glm::length(glm::vec2(worldPoint.x, worldPoint.y)) / kHemisphereRadius, 0.0f, 1.0f);
    const float radialScale = ofLerp(1.10f, 0.52f, radialNorm);
    return std::max(3.5f, baseRadius * radialScale);
}

void ofApp::drawStarGlyph(const glm::vec2& p, float size, int points) const {
    ofBeginShape();
    for (int i = 0; i < points * 2; ++i) {
        const float angle = glm::pi<float>() * static_cast<float>(i) / static_cast<float>(points) - glm::half_pi<float>();
        const float r = (i % 2 == 0) ? size : size * 0.46f;
        ofVertex(p.x + std::cos(angle) * r, p.y + std::sin(angle) * r);
    }
    ofEndShape(true);
}

void ofApp::drawPersonGlyph(const glm::vec2& p, float size) const {
    const float headR = size * 0.22f;
    ofDrawCircle(p.x, p.y - size * 0.62f, headR);
    ofDrawRectRounded(p.x - size * 0.18f, p.y - size * 0.30f, size * 0.36f, size * 0.58f, size * 0.08f);
    ofSetLineWidth(std::max(2.0f, size * 0.08f));
    ofDrawLine(p.x - size * 0.28f, p.y - size * 0.10f, p.x + size * 0.28f, p.y - size * 0.10f);
    ofDrawLine(p.x - size * 0.10f, p.y + size * 0.28f, p.x - size * 0.28f, p.y + size * 0.72f);
    ofDrawLine(p.x + size * 0.10f, p.y + size * 0.28f, p.x + size * 0.28f, p.y + size * 0.72f);
}

void ofApp::drawHandGlyph(const glm::vec2& p, float size) const {
    ofDrawRectRounded(p.x - size * 0.20f, p.y - size * 0.12f, size * 0.40f, size * 0.42f, size * 0.07f);
    const float fingerW = size * 0.08f;
    const float fingerH = size * 0.34f;
    for (int i = 0; i < 4; ++i) {
        const float x = p.x - size * 0.18f + i * size * 0.11f;
        ofDrawRectRounded(x, p.y - size * 0.46f, fingerW, fingerH, size * 0.04f);
    }
    ofPushMatrix();
    ofTranslate(p.x - size * 0.25f, p.y + size * 0.02f);
    ofRotateDeg(-34.0f);
    ofDrawRectRounded(-fingerW * 0.5f, -size * 0.07f, fingerW, size * 0.28f, size * 0.04f);
    ofPopMatrix();
}

void ofApp::drawDogGlyph(const glm::vec2& p, float size, float yawDeg) const {
    ofPushMatrix();
    ofTranslate(p);
    ofRotateDeg(yawDeg * 0.2f);
    ofDrawEllipse(0.0f, 0.0f, size * 1.05f, size * 0.52f);
    ofDrawCircle(size * 0.44f, -size * 0.16f, size * 0.19f);
    ofDrawTriangle(size * 0.52f, -size * 0.30f, size * 0.63f, -size * 0.50f, size * 0.38f, -size * 0.36f);
    ofDrawTriangle(size * 0.34f, -size * 0.25f, size * 0.28f, -size * 0.48f, size * 0.49f, -size * 0.30f);
    ofSetLineWidth(std::max(2.0f, size * 0.07f));
    for (float lx : {-0.24f, -0.02f, 0.18f, 0.34f}) {
        ofDrawLine(size * lx, size * 0.18f, size * lx, size * 0.56f);
    }
    ofDrawLine(-size * 0.52f, -size * 0.10f, -size * 0.78f, -size * 0.34f);
    ofPopMatrix();
}

void ofApp::drawPlainObjectGlyph(const glm::vec2& p, float size, float yawDeg) const {
    ofPushMatrix();
    ofTranslate(p);
    ofRotateDeg(yawDeg * 0.15f);
    ofDrawRectRounded(-size * 0.48f, -size * 0.34f, size * 0.96f, size * 0.68f, size * 0.12f);
    ofNoFill();
    ofSetLineWidth(std::max(2.0f, size * 0.05f));
    ofDrawRectangle(-size * 0.30f, -size * 0.18f, size * 0.60f, size * 0.36f);
    ofFill();
    ofPopMatrix();
}

void ofApp::drawShape3D(const MovingShape& s, int idx) const {
    const glm::vec3 worldPoint = shapeWorldPoint(s);
    glm::vec2 p;
    if (!projectWorldPoint(worldPoint, p, nullptr)) return;
    const float size = projectRadius(s);
    if (size < 4.0f) return;

    glm::vec2 groundPoint = p;
    projectWorldPoint(glm::vec3(worldPoint.x, worldPoint.y, 0.0f), groundPoint, nullptr);
    glm::vec2 depthAnchor = p;
    projectWorldPoint(worldPoint + glm::vec3(1.5f, 3.0f, 1.5f), depthAnchor, nullptr);
    glm::vec2 extrude = depthAnchor - p;
    if (glm::length2(extrude) < 1.0f) extrude = glm::vec2(3.0f, -3.0f);
    extrude = glm::clamp(extrude, glm::vec2(-14.0f), glm::vec2(14.0f));
    ofPushStyle();
    ofSetColor(0, 0, 0, 56);
    ofDrawEllipse(groundPoint.x, groundPoint.y + size * 0.18f, size * 1.4f, size * 0.46f);

    const ofColor base = s.color;
    const ofColor back(base.r * 0.32f, base.g * 0.32f, base.b * 0.38f, 210);
    ofSetColor(back);

    auto drawProjectedLine = [&](const glm::vec3& a3, const glm::vec3& b3) {
        glm::vec2 a2, b2;
        if (projectWorldPoint(a3, a2, nullptr) && projectWorldPoint(b3, b2, nullptr)) {
            ofDrawLine(a2, b2);
        }
    };

    auto drawProjectedCircle = [&](const glm::vec3& c3, float worldR) {
        glm::vec2 c2, r2;
        if (projectWorldPoint(c3, c2, nullptr) && projectWorldPoint(c3 + glm::vec3(worldR, 0.0f, 0.0f), r2, nullptr)) {
            ofDrawCircle(c2, std::max(2.0f, glm::distance(c2, r2)));
        }
    };

    auto drawProjectedLoop = [&](const std::vector<glm::vec3>& pts, bool closed) {
        if (pts.size() < 2) return;
        for (size_t i = 0; i + 1 < pts.size(); ++i) drawProjectedLine(pts[i], pts[i + 1]);
        if (closed) drawProjectedLine(pts.back(), pts.front());
    };

    auto drawProjectedFill = [&](const std::vector<glm::vec3>& pts, const ofColor& col) {
        if (pts.size() < 3) return;
        std::vector<glm::vec2> screenPts;
        screenPts.reserve(pts.size());
        for (const auto& p3 : pts) {
            glm::vec2 p2;
            if (!projectWorldPoint(p3, p2, nullptr)) return;
            screenPts.push_back(p2);
        }
        ofSetColor(col);
        ofBeginShape();
        for (const auto& p2 : screenPts) ofVertex(p2.x, p2.y);
        ofEndShape(true);
    };

    auto drawProjectedBox = [&](const glm::vec3& center3, const glm::vec3& half) {
        const glm::vec3 p000 = center3 + glm::vec3(-half.x, -half.y, -half.z);
        const glm::vec3 p001 = center3 + glm::vec3(-half.x, -half.y,  half.z);
        const glm::vec3 p010 = center3 + glm::vec3(-half.x,  half.y, -half.z);
        const glm::vec3 p011 = center3 + glm::vec3(-half.x,  half.y,  half.z);
        const glm::vec3 p100 = center3 + glm::vec3( half.x, -half.y, -half.z);
        const glm::vec3 p101 = center3 + glm::vec3( half.x, -half.y,  half.z);
        const glm::vec3 p110 = center3 + glm::vec3( half.x,  half.y, -half.z);
        const glm::vec3 p111 = center3 + glm::vec3( half.x,  half.y,  half.z);
        drawProjectedFill({p001, p101, p111, p011}, ofColor(base.r, base.g, base.b, 56));
        drawProjectedFill({p010, p110, p111, p011}, ofColor(base.r, base.g, base.b, 34));
        drawProjectedLoop({p000, p100, p110, p010}, true);
        drawProjectedLoop({p001, p101, p111, p011}, true);
        drawProjectedLine(p000, p001);
        drawProjectedLine(p100, p101);
        drawProjectedLine(p110, p111);
        drawProjectedLine(p010, p011);
    };

    switch (s.objectKind) {
        case ObjectKind::Person: {
            const float personHeight = ofMap(s.radius, 18.0f, 48.0f, 12.0f, 26.0f, true);
            const float legHalf = personHeight * 0.10f;
            const float shoulderHalf = personHeight * 0.16f;
            const float armReach = personHeight * 0.26f;
            const float shoulderZ = personHeight * 0.64f;
            const float hipZ = personHeight * 0.34f;
            const float headZ = personHeight * 0.88f;
            const float headR = personHeight * 0.11f;
            const float torsoHalfW = personHeight * 0.10f;
            const float torsoHalfD = personHeight * 0.06f;
            const float torsoHalfH = personHeight * 0.16f;
            const float hipHalfW = personHeight * 0.12f;
            const float hipHalfD = personHeight * 0.07f;
            const float hipHalfH = personHeight * 0.07f;

            const glm::vec3 pelvis(worldPoint.x, worldPoint.y, hipZ);
            const glm::vec3 chest(worldPoint.x, worldPoint.y, shoulderZ);
            const glm::vec3 head(worldPoint.x, worldPoint.y, headZ);
            const glm::vec3 leftFoot(worldPoint.x - legHalf, worldPoint.y, 0.0f);
            const glm::vec3 rightFoot(worldPoint.x + legHalf, worldPoint.y, 0.0f);
            const glm::vec3 leftHip(worldPoint.x - legHalf, worldPoint.y, hipZ);
            const glm::vec3 rightHip(worldPoint.x + legHalf, worldPoint.y, hipZ);
            const glm::vec3 leftShoulder(worldPoint.x - shoulderHalf, worldPoint.y, shoulderZ);
            const glm::vec3 rightShoulder(worldPoint.x + shoulderHalf, worldPoint.y, shoulderZ);
            const glm::vec3 leftHand(worldPoint.x - armReach, worldPoint.y, shoulderZ - personHeight * 0.12f);
            const glm::vec3 rightHand(worldPoint.x + armReach, worldPoint.y, shoulderZ - personHeight * 0.12f);
            const float handOpen = 0.5f + 0.5f * std::sin(simTime * 2.2f + idx * 0.4f);
            const float palmR = personHeight * 0.06f;
            const float fingerLen = personHeight * ofLerp(0.10f, 0.24f, handOpen);
            const float fingerSpread = personHeight * ofLerp(0.03f, 0.12f, handOpen);

            auto drawHandFan = [&](const glm::vec3& hand, float side) {
                drawProjectedCircle(hand, palmR);
                for (int f = 0; f < 5; ++f) {
                    const float fan = static_cast<float>(f - 2);
                    drawProjectedLine(
                        hand,
                        glm::vec3(
                            hand.x + side * fingerSpread,
                            hand.y - fingerSpread * fan * 0.35f,
                            hand.z + fingerLen * (1.0f - std::abs(fan) * 0.08f)
                        )
                    );
                }
                drawProjectedLine(
                    hand,
                    glm::vec3(
                        hand.x + side * fingerSpread * 0.7f,
                        hand.y + palmR * 1.8f,
                        hand.z + fingerLen * 0.35f
                    )
                );
            };

            ofSetLineWidth(std::max(2.0f, size * 0.08f));
            drawProjectedBox(glm::vec3(worldPoint.x, worldPoint.y, shoulderZ - torsoHalfH * 0.2f),
                             glm::vec3(torsoHalfW, torsoHalfD, torsoHalfH));
            drawProjectedBox(glm::vec3(worldPoint.x, worldPoint.y, hipZ),
                             glm::vec3(hipHalfW, hipHalfD, hipHalfH));
            drawProjectedLine(leftFoot, leftHip);
            drawProjectedLine(rightFoot, rightHip);
            drawProjectedLine(leftHip, pelvis);
            drawProjectedLine(rightHip, pelvis);
            drawProjectedLine(pelvis, chest);
            drawProjectedLine(leftShoulder, rightShoulder);
            drawProjectedLine(leftShoulder, leftHand);
            drawProjectedLine(rightShoulder, rightHand);
            drawProjectedLine(chest, head);
            drawProjectedBox(glm::vec3(leftFoot.x, leftFoot.y, personHeight * 0.03f),
                             glm::vec3(personHeight * 0.04f, personHeight * 0.07f, personHeight * 0.03f));
            drawProjectedBox(glm::vec3(rightFoot.x, rightFoot.y, personHeight * 0.03f),
                             glm::vec3(personHeight * 0.04f, personHeight * 0.07f, personHeight * 0.03f));
            drawProjectedCircle(leftFoot, personHeight * 0.03f);
            drawProjectedCircle(rightFoot, personHeight * 0.03f);
            drawProjectedCircle(leftShoulder, personHeight * 0.025f);
            drawProjectedCircle(rightShoulder, personHeight * 0.025f);
            drawProjectedCircle(head, headR);
            drawProjectedLine(glm::vec3(head.x - headR * 0.4f, head.y - headR * 0.85f, head.z + headR * 0.1f),
                              glm::vec3(head.x, head.y - headR * 1.25f, head.z + headR * 0.55f));
            drawProjectedLine(glm::vec3(head.x + headR * 0.4f, head.y - headR * 0.85f, head.z + headR * 0.1f),
                              glm::vec3(head.x, head.y - headR * 1.25f, head.z + headR * 0.55f));
            drawHandFan(leftHand, -1.0f);
            drawHandFan(rightHand, 1.0f);
            break;
        }
        case ObjectKind::Hand: {
            const float handH = ofMap(s.radius, 18.0f, 48.0f, 10.0f, 18.0f, true);
            const float palmW = handH * 0.44f;
            const float palmD = handH * 0.18f;
            const float palmZ0 = handH * 0.20f;
            const float palmZ1 = handH * 0.56f;
            const float fingerY = worldPoint.y - handH * 0.18f;
            const float fingerBaseZ = palmZ1;
            const std::array<float,4> fingerX{{-0.18f, -0.06f, 0.06f, 0.18f}};
            const std::array<float,4> fingerLen{{0.30f, 0.40f, 0.44f, 0.34f}};
            const float knuckleY = worldPoint.y - handH * 0.08f;

            drawProjectedBox(glm::vec3(worldPoint.x, worldPoint.y, (palmZ0 + palmZ1) * 0.5f),
                             glm::vec3(palmW, palmD, (palmZ1 - palmZ0) * 0.5f));
            ofSetColor(base);
            drawProjectedLine(glm::vec3(worldPoint.x, worldPoint.y + palmD * 1.2f, palmZ0),
                              glm::vec3(worldPoint.x, worldPoint.y, palmZ0 + handH * 0.04f));
            for (size_t i = 0; i < fingerX.size(); ++i) {
                const float x = worldPoint.x + handH * fingerX[i];
                const float midZ = fingerBaseZ + handH * fingerLen[i] * 0.52f;
                const float tipZ = fingerBaseZ + handH * fingerLen[i];
                drawProjectedLine(glm::vec3(x, knuckleY, fingerBaseZ), glm::vec3(x, fingerY, midZ));
                drawProjectedLine(glm::vec3(x, fingerY, midZ), glm::vec3(x, fingerY - handH * 0.02f, tipZ));
                drawProjectedCircle(glm::vec3(x, knuckleY, fingerBaseZ), handH * 0.018f);
                drawProjectedCircle(glm::vec3(x, fingerY, tipZ), handH * 0.03f);
            }
            drawProjectedLine(glm::vec3(worldPoint.x - palmW * 0.55f, worldPoint.y + palmD * 0.25f, palmZ0 + handH * 0.10f),
                              glm::vec3(worldPoint.x - palmW * 1.10f, worldPoint.y - palmD * 0.55f, palmZ0 + handH * 0.30f));
            drawProjectedLine(glm::vec3(worldPoint.x - palmW * 1.10f, worldPoint.y - palmD * 0.55f, palmZ0 + handH * 0.30f),
                              glm::vec3(worldPoint.x - palmW * 1.30f, worldPoint.y - palmD * 0.90f, palmZ0 + handH * 0.42f));
            break;
        }
        case ObjectKind::Dog: {
            const float dogL = ofMap(s.radius, 18.0f, 48.0f, 18.0f, 28.0f, true);
            const float dogH = dogL * 0.42f;
            const float bodyFrontY = worldPoint.y - dogL * 0.18f;
            const float bodyBackY = worldPoint.y + dogL * 0.18f;
            const float bodyZ = dogH * 0.75f;
            const float legX = dogL * 0.16f;
            const float headY = bodyFrontY - dogL * 0.18f;
            const float tailY = bodyBackY + dogL * 0.20f;
            const float headZ = bodyZ * 1.03f;
            const glm::vec3 bodyA(worldPoint.x, bodyBackY, bodyZ);
            const glm::vec3 bodyB(worldPoint.x, bodyFrontY, bodyZ);
            ofSetLineWidth(std::max(2.0f, size * 0.07f));
            drawProjectedBox(glm::vec3(worldPoint.x, worldPoint.y, bodyZ * 0.72f),
                             glm::vec3(dogL * 0.18f, dogL * 0.20f, dogH * 0.28f));
            drawProjectedBox(glm::vec3(worldPoint.x, worldPoint.y + dogL * 0.02f, bodyZ * 0.92f),
                             glm::vec3(dogL * 0.11f, dogL * 0.12f, dogH * 0.12f));
            drawProjectedLine(bodyA, bodyB);
            drawProjectedLine(glm::vec3(worldPoint.x - dogL * 0.18f, bodyBackY, bodyZ * 0.95f), glm::vec3(worldPoint.x + dogL * 0.18f, bodyBackY, bodyZ * 0.95f));
            drawProjectedLine(glm::vec3(worldPoint.x - dogL * 0.20f, bodyFrontY, bodyZ * 0.95f), glm::vec3(worldPoint.x + dogL * 0.20f, bodyFrontY, bodyZ * 0.95f));
            drawProjectedLine(glm::vec3(worldPoint.x - legX, bodyBackY, bodyZ * 0.8f), glm::vec3(worldPoint.x - legX, bodyBackY, 0.0f));
            drawProjectedLine(glm::vec3(worldPoint.x + legX, bodyBackY, bodyZ * 0.8f), glm::vec3(worldPoint.x + legX, bodyBackY, 0.0f));
            drawProjectedLine(glm::vec3(worldPoint.x - legX, bodyFrontY, bodyZ * 0.8f), glm::vec3(worldPoint.x - legX, bodyFrontY, 0.0f));
            drawProjectedLine(glm::vec3(worldPoint.x + legX, bodyFrontY, bodyZ * 0.8f), glm::vec3(worldPoint.x + legX, bodyFrontY, 0.0f));
            drawProjectedLine(glm::vec3(worldPoint.x, bodyFrontY, bodyZ), glm::vec3(worldPoint.x, headY, headZ));
            drawProjectedBox(glm::vec3(worldPoint.x, headY, headZ), glm::vec3(dogL * 0.09f, dogL * 0.08f, dogH * 0.10f));
            drawProjectedLine(glm::vec3(worldPoint.x, headY - dogL * 0.11f, headZ * 0.98f),
                              glm::vec3(worldPoint.x, headY - dogL * 0.19f, headZ * 0.88f));
            drawProjectedLine(glm::vec3(worldPoint.x - dogL * 0.04f, headY + dogL * 0.02f, headZ + dogH * 0.10f),
                              glm::vec3(worldPoint.x - dogL * 0.08f, headY + dogL * 0.09f, headZ + dogH * 0.22f));
            drawProjectedLine(glm::vec3(worldPoint.x + dogL * 0.04f, headY + dogL * 0.02f, headZ + dogH * 0.10f),
                              glm::vec3(worldPoint.x + dogL * 0.08f, headY + dogL * 0.09f, headZ + dogH * 0.22f));
            drawProjectedLine(glm::vec3(worldPoint.x, bodyBackY, bodyZ * 0.96f), glm::vec3(worldPoint.x, tailY, bodyZ * 1.08f));
            break;
        }
        case ObjectKind::PlainObject: {
            const float bottleH = ofMap(s.radius, 18.0f, 48.0f, 14.0f, 24.0f, true);
            const float bodyR = bottleH * 0.13f;
            const float neckR = bottleH * 0.06f;
            const float bodyZ = bottleH * 0.38f;
            drawProjectedBox(glm::vec3(worldPoint.x, worldPoint.y, bodyZ),
                             glm::vec3(bodyR, bodyR, bottleH * 0.30f));
            drawProjectedBox(glm::vec3(worldPoint.x, worldPoint.y, bottleH * 0.78f),
                             glm::vec3(neckR, neckR, bottleH * 0.12f));
            drawProjectedCircle(glm::vec3(worldPoint.x, worldPoint.y, bottleH * 0.98f), neckR * 0.9f);
            break;
        }
        case ObjectKind::Square: {
            const float edge = ofMap(s.radius, 18.0f, 48.0f, 10.0f, 18.0f, true);
            const glm::vec3 half(edge * 0.5f, edge * 0.5f, edge * 0.5f);
            drawProjectedBox(glm::vec3(worldPoint.x, worldPoint.y, half.z), half);
            drawProjectedLine(glm::vec3(worldPoint.x - half.x, worldPoint.y - half.y, half.z * 1.8f),
                              glm::vec3(worldPoint.x + half.x, worldPoint.y + half.y, half.z * 0.2f));
            drawProjectedLine(glm::vec3(worldPoint.x + half.x, worldPoint.y - half.y, half.z * 1.8f),
                              glm::vec3(worldPoint.x - half.x, worldPoint.y + half.y, half.z * 0.2f));
            break;
        }
        case ObjectKind::Star: {
            const float outer = ofMap(s.radius, 18.0f, 48.0f, 8.0f, 14.0f, true);
            const float inner = outer * 0.45f;
            const float depth = outer * 0.18f;
            std::vector<glm::vec3> front;
            std::vector<glm::vec3> backFace;
            front.reserve(10);
            backFace.reserve(10);
            for (int i = 0; i < 10; ++i) {
                const float ang = glm::pi<float>() * static_cast<float>(i) / 5.0f - glm::half_pi<float>();
                const float r = (i % 2 == 0) ? outer : inner;
                const float x = worldPoint.x + std::cos(ang) * r;
                const float z = outer + std::sin(ang) * r;
                front.emplace_back(x, worldPoint.y - depth, z);
                backFace.emplace_back(x, worldPoint.y + depth, z);
            }
            drawProjectedFill(front, ofColor(base.r, base.g, base.b, 70));
            drawProjectedFill(backFace, ofColor(back.r, back.g, back.b, 50));
            drawProjectedLoop(front, true);
            drawProjectedLoop(backFace, true);
            for (size_t i = 0; i < front.size(); ++i) drawProjectedLine(front[i], backFace[i]);
            break;
        }
    }
    ofPopStyle();
}

void ofApp::drawListenerHead() const {
    auto drawSphereRing = [&](const glm::vec3& axisA, const glm::vec3& axisB, int alpha) {
        ofPolyline line;
        for (int i = 0; i <= 48; ++i) {
            const float ang = ofMap(static_cast<float>(i), 0.0f, 48.0f, 0.0f, glm::two_pi<float>());
            const glm::vec3 p = axisA * std::cos(ang) + axisB * std::sin(ang);
            glm::vec2 s;
            if (projectWorldPoint(p, s, nullptr)) line.addVertex(s.x, s.y);
        }
        ofSetColor(176, 184, 196, alpha);
        line.draw();
    };

    glm::vec2 center;
    if (!projectWorldPoint(glm::vec3(0.0f, 0.0f, 0.0f), center, nullptr)) return;
    glm::vec2 forward;
    projectWorldPoint(glm::vec3(0.0f, -10.0f, 0.0f), forward, nullptr);

    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(2.0f);
    drawSphereRing(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.0f, 6.0f, 0.0f), 120);
    drawSphereRing(glm::vec3(6.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 6.0f), 90);
    drawSphereRing(glm::vec3(0.0f, 6.0f, 0.0f), glm::vec3(0.0f, 0.0f, 6.0f), 90);
    ofSetColor(88, 208, 255, 180);
    ofDrawLine(center, forward);
    ofDrawCircle(forward.x, forward.y, 3.5f);
    ofPopStyle();
}

void ofApp::drawGroundPlane() const {
    ofPushStyle();
    ofSetColor(9, 12, 18, 255);
    ofDrawRectangle(0.0f, 0.0f, static_cast<float>(frameW), static_cast<float>(frameH));

    glm::vec2 hzL;
    glm::vec2 hzR;
    if (projectWorldPoint(glm::vec3(-200.0f, kWorldFarY, 0.0f), hzL, nullptr) &&
        projectWorldPoint(glm::vec3(200.0f, kWorldFarY, 0.0f), hzR, nullptr)) {
        ofSetColor(40, 62, 88, 120);
        ofDrawLine(hzL, hzR);
    }

    const std::array<float, 9> yLines{{kWorldNearY, 75.0f, 50.0f, 25.0f, 0.0f, -25.0f, -50.0f, -75.0f, kWorldFarY}};
    for (float y : yLines) {
        glm::vec2 a;
        glm::vec2 b;
        if (!projectWorldPoint(glm::vec3(-kWorldSide, y, 0.0f), a, nullptr) ||
            !projectWorldPoint(glm::vec3(kWorldSide, y, 0.0f), b, nullptr)) {
            continue;
        }
        const float distWeight = ofMap(y, kWorldNearY, kWorldFarY, 0.0f, 1.0f, true);
        const int alpha = static_cast<int>(ofLerp(90.0f, 24.0f, distWeight));
        ofSetColor(28, 48, 72, alpha);
        ofDrawLine(a, b);
    }

    for (int xi = -5; xi <= 5; ++xi) {
        const float x = static_cast<float>(xi) * 20.0f;
        glm::vec2 a;
        glm::vec2 b;
        if (!projectWorldPoint(glm::vec3(x, kWorldNearY, 0.0f), a, nullptr) ||
            !projectWorldPoint(glm::vec3(x, kWorldFarY, 0.0f), b, nullptr)) {
            continue;
        }
        const int alpha = (xi == 0) ? 120 : 52;
        ofSetColor(34, 58, 84, alpha);
        ofDrawLine(a, b);
    }

    glm::vec2 axisStart;
    glm::vec2 axisEnd;
    if (projectWorldPoint(glm::vec3(0.0f, kWorldNearY, 0.0f), axisStart, nullptr) &&
        projectWorldPoint(glm::vec3(0.0f, kWorldFarY, 0.0f), axisEnd, nullptr)) {
        ofSetColor(88, 208, 255, 140);
        ofSetLineWidth(2.0f);
        ofDrawLine(axisStart, axisEnd);
    }

    ofPolyline boundary;
    for (int i = 0; i <= 96; ++i) {
        const float ang = ofMap(static_cast<float>(i), 0.0f, 96.0f, -glm::pi<float>(), glm::pi<float>());
        glm::vec2 s;
        if (projectWorldPoint(glm::vec3(std::sin(ang) * kHemisphereRadius, std::cos(ang) * kHemisphereRadius, 0.0f), s, nullptr)) {
            boundary.addVertex(s.x, s.y);
        }
    }
    ofSetColor(88, 208, 255, 85);
    boundary.draw();
    ofPopStyle();
}

void ofApp::drawHemisphereOverlay() const {
    const std::array<float, 5> elevs{{15.0f, 30.0f, 45.0f, 60.0f, 75.0f}};
    const std::array<float, 7> azims{{-150.0f, -100.0f, -50.0f, 0.0f, 50.0f, 100.0f, 150.0f}};

    ofPushStyle();
    ofNoFill();

    {
        ofPolyline equator;
        for (int i = 0; i <= 72; ++i) {
            const float azDeg = ofMap(static_cast<float>(i), 0.0f, 72.0f, -180.0f, 180.0f);
            const float azRad = glm::radians(azDeg);
            const glm::vec3 p(
                kHemisphereRadius * std::sin(azRad),
                -kHemisphereRadius * std::cos(azRad),
                0.0f
            );
            glm::vec2 s;
            if (projectWorldPoint(p, s, nullptr)) equator.addVertex(s.x, s.y);
        }
        ofSetColor(88, 208, 255, 70);
        equator.draw();
    }

    for (float elevDeg : elevs) {
        ofPolyline line;
        for (int i = 0; i <= 72; ++i) {
            const float azDeg = ofMap(static_cast<float>(i), 0.0f, 72.0f, -180.0f, 180.0f);
            const float elevRad = glm::radians(elevDeg);
            const float azRad = glm::radians(azDeg);
            const float xy = kHemisphereRadius * std::cos(elevRad);
            const glm::vec3 p(
                xy * std::sin(azRad),
                -xy * std::cos(azRad),
                kHemisphereRadius * std::sin(elevRad)
            );
            glm::vec2 s;
            if (projectWorldPoint(p, s, nullptr)) line.addVertex(s.x, s.y);
        }
        ofSetColor(88, 208, 255, 34);
        line.draw();
    }

    for (float azDeg : azims) {
        ofPolyline line;
        for (int i = 0; i <= 36; ++i) {
            const float elevDeg = ofMap(static_cast<float>(i), 0.0f, 36.0f, 0.0f, 90.0f);
            const float elevRad = glm::radians(elevDeg);
            const float azRad = glm::radians(azDeg);
            const float xy = kHemisphereRadius * std::cos(elevRad);
            const glm::vec3 p(
                xy * std::sin(azRad),
                -xy * std::cos(azRad),
                kHemisphereRadius * std::sin(elevRad)
            );
            glm::vec2 s;
            if (projectWorldPoint(p, s, nullptr)) line.addVertex(s.x, s.y);
        }
        ofSetColor(88, 208, 255, azDeg == 0.0f ? 54 : 28);
        line.draw();
    }

    ofPopStyle();
}

void ofApp::drawTopDownOverview() const {
    const float panelS = 180.0f;
    const float x0 = static_cast<float>(ofGetWidth()) - panelS - 24.0f;
    const float y0 = 86.0f;
    const float cx = x0 + panelS * 0.5f;
    const float cy = y0 + panelS * 0.5f;
    const float usableR = panelS * 0.5f - 18.0f;

    auto mapX = [&](float worldX) { return cx + (worldX / kWorldSide) * usableR; };
    auto mapY = [&](float worldY) { return cy + (worldY / kWorldNearY) * usableR; };

    ofPushStyle();
    ofSetColor(10, 14, 18, 220);
    ofDrawRectRounded(x0, y0, panelS, panelS, 8.0f);
    ofNoFill();
    ofSetColor(90, 210, 255, 140);
    ofDrawRectRounded(x0, y0, panelS, panelS, 8.0f);
    ofFill();

    ofSetColor(28, 48, 72, 100);
    for (float r : {0.25f, 0.5f, 0.75f, 1.0f}) {
        ofDrawCircle(cx, cy, usableR * r);
    }
    for (int ang = 0; ang < 180; ang += 30) {
        const float rad = glm::radians(static_cast<float>(ang));
        const float dx = std::sin(rad) * usableR;
        const float dy = std::cos(rad) * usableR;
        ofDrawLine(cx - dx, cy - dy, cx + dx, cy + dy);
    }

    ofSetColor(88, 208, 255, 200);
    ofDrawCircle(cx, cy, 5.0f);
    ofSetColor(88, 208, 255, 110);
    ofDrawLine(cx, cy - usableR, cx, cy + usableR);
    ofDrawLine(cx - usableR, cy, cx + usableR, cy);

    const int limit = std::min(activeBlobLimit, static_cast<int>(shapes.size()));
    for (int i = 0; i < limit; ++i) {
        const auto& s = shapes[i];
        if (!isShapeOn(s)) continue;
        const glm::vec3 w = shapeWorldPoint(s);
        const float px = mapX(ofClamp(w.x, -kWorldSide, kWorldSide));
        const float py = mapY(ofClamp(w.y, kWorldFarY, kWorldNearY));
        ofSetColor(s.color);
        ofDrawCircle(px, py, 4.5f);
        const float yawRad = glm::radians(s.yawDeg);
        const glm::vec2 dir(std::sin(yawRad), -std::cos(yawRad));
        ofSetColor(s.color, 140);
        ofDrawLine(px, py, px + dir.x * 8.0f, py + dir.y * 8.0f);
    }

    ofSetColor(255);
    ofDrawBitmapString("Top", x0 + 10.0f, y0 + 16.0f);
    ofDrawBitmapString("0", cx + 8.0f, cy - 8.0f);
    ofPopStyle();
}

void ofApp::updateDepthState(MovingShape& s, float dt, int idx) {
    const float noiseT = simTime * 0.33f + idx * 0.71f;
    const float minDepth = 0.10f;
    const float maxDepth = 0.92f;

    if (rainMode) {
        const float laneCycle = static_cast<float>((idx % 4) + 1) / 5.0f;
        const float target = ofClamp(0.22f + laneCycle * 0.52f + ofSignedNoise(noiseT) * 0.06f, minDepth, maxDepth);
        s.depthVel = ofLerp(s.depthVel, (target - s.depth) * 2.0f, 0.08f);
    } else if (airHockeyMode) {
        s.depthVel += ofSignedNoise(noiseT * 1.7f) * 0.22f * dt;
    } else if (bUseBrownianDrunkMotion) {
        s.depthVel += ofSignedNoise(noiseT * 1.4f) * 0.18f * dt;
    } else {
        const float target = 0.52f + 0.28f * std::sin(simTime * 0.45f + idx * 0.63f);
        s.depthVel = ofLerp(s.depthVel, (target - s.depth) * 1.8f, 0.06f);
    }

    s.depthVel = ofClamp(s.depthVel, -0.32f, 0.32f);
    s.depth = ofClamp(s.depth + s.depthVel * dt, minDepth, maxDepth);
    if (s.depth <= minDepth || s.depth >= maxDepth) {
        s.depthVel *= -0.55f;
    }
    s.yawDeg = wrapSignedDegrees(s.yawDeg + glm::length(s.vel) * dt * 0.18f + ofSignedNoise(noiseT * 0.9f) * 2.2f);
}

void ofApp::initShapes() {
    shapes.clear();
    shapes.reserve(10);

    for (int i = 0; i < 10; ++i) {
        MovingShape s;
        s.radius = ofRandom(18.0f, 48.0f);
        const float worldRadius = ofMap(s.radius, 18.0f, 48.0f, 3.8f, 12.5f, true);
        const float allowed = std::max(1.0f, kHemisphereRadius - worldRadius);
        const float ang = ofRandom(glm::two_pi<float>());
        const float rad = std::sqrt(ofRandomuf()) * allowed;
        s.pos = glm::vec2(
            ofMap(std::cos(ang) * rad, -kWorldSide, kWorldSide, 0.0f, static_cast<float>(frameW), true),
            ofMap(std::sin(ang) * rad, kWorldFarY, kWorldNearY, 0.0f, static_cast<float>(frameH), true)
        );
        for (int attempt = 0; attempt < 40; ++attempt) {
            bool overlaps = false;
            for (const auto& other : shapes) {
                const float minDist = s.radius + other.radius + 14.0f;
                if (glm::distance(s.pos, other.pos) < minDist) {
                    overlaps = true;
                    const float a2 = ofRandom(glm::two_pi<float>());
                    const float r2 = std::sqrt(ofRandomuf()) * allowed;
                    s.pos = glm::vec2(
                        ofMap(std::cos(a2) * r2, -kWorldSide, kWorldSide, 0.0f, static_cast<float>(frameW), true),
                        ofMap(std::sin(a2) * r2, kWorldFarY, kWorldNearY, 0.0f, static_cast<float>(frameH), true)
                    );
                    break;
                }
            }
            if (!overlaps) break;
        }

        s.vel = glm::vec2(ofRandomf(), ofRandomf()) * ofRandom(50.0f, 120.0f);
        s.walkDir = glm::normalize(glm::vec2(ofRandomf(), ofRandomf()));
        if (glm::length(s.walkDir) < 0.0001f) s.walkDir = glm::vec2(1.0f, 0.0f);

        s.motion = (i % 2 == 0) ? MotionType::Brownian : MotionType::Drunkard;
        s.bRect = (i % 3 == 0);

        s.blinkPeriodSec = ofRandom(2.0f, 5.2f);
        s.blinkDuty = ofRandom(0.62f, 0.90f);
        s.blinkPhaseSec = ofRandom(0.0f, s.blinkPeriodSec);
        s.naturalOn = (ofRandomuf() < onDutyControl);
        s.stateRemainingSec = randomHoldDuration(s.naturalOn);
        s.rainDormant = false;
        s.depth = ofRandom(0.14f, 0.88f);
        s.depthVel = ofRandom(-0.08f, 0.08f);
        s.yawDeg = ofRandom(-180.0f, 180.0f);
        s.objectKind = objectKindForPreset(objectPreset, i);

        float hue = fmodf(i * 27.0f, 255.0f);
        s.color = ofColor::fromHsb(static_cast<unsigned char>(hue), 220, 255);
        shapes.push_back(s);
    }

    if (rainMode) {
        for (std::size_t i = 0; i < shapes.size(); ++i) {
            resetShapeForRain(shapes[i], true, static_cast<int>(i));
        }
    }

    assignObjectPreset();
}

void ofApp::updateBlinkStates(float dt) {
    if (dt <= 0.0f) return;
    if (alwaysOnMode) {
        if (!midiTakeoverEnabled) {
            for (auto& s : shapes) {
                s.naturalOn = true;
            }
            return;
        }
        for (auto& s : shapes) {
            if (!s.naturalOn) continue;
            s.stateRemainingSec -= dt;
            if (s.stateRemainingSec <= 0.0f) {
                s.naturalOn = false;
                s.stateRemainingSec = 0.0f;
            }
        }
        return;
    }
    if (!naturalBlink) return;
    // Make On/Off Rate react immediately (not only at next state transition).
    const float rateWarp = ofLerp(0.35f, 2.8f, ofClamp(blinkRateControl, 0.0f, 1.0f));
    for (auto& s : shapes) {
        s.stateRemainingSec -= dt * rateWarp;
        if (s.stateRemainingSec <= 0.0f) {
            s.naturalOn = !s.naturalOn;
            s.stateRemainingSec = randomHoldDuration(s.naturalOn);
        }
    }
}

bool ofApp::isShapeOn(const MovingShape& shape) const {
    if (rainMode) return shape.naturalOn && !shape.rainDormant;
    if (alwaysOnMode) return shape.naturalOn;
    if (naturalBlink) return shape.naturalOn;
    if (shape.blinkPeriodSec <= 0.0001f) return true;
    float t = fmodf(simTime + shape.blinkPhaseSec, shape.blinkPeriodSec);
    return t < (shape.blinkPeriodSec * shape.blinkDuty);
}

float ofApp::edgeMetric01(const MovingShape& s) const {
    const glm::vec3 worldPoint = shapeWorldPoint(s);
    const float worldRadius = ofMap(s.radius, 18.0f, 48.0f, 3.8f, 12.5f, true);
    const float allowed = std::max(1.0f, kHemisphereRadius - worldRadius);
    return ofClamp(glm::length(glm::vec2(worldPoint.x, worldPoint.y)) / allowed, 0.0f, 1.0f);
}

ofRectangle ofApp::getSliderRect(int sliderIndex) const {
    const float w = 220.0f;
    const float h = 12.0f;
    const float x = 20.0f;
    const float y0 = static_cast<float>(ofGetHeight()) - 70.0f;
    return ofRectangle(x, y0 + sliderIndex * 24.0f, w, h);
}

ofRectangle ofApp::getFloodArmRect() const {
    const float w = 150.0f;
    const float h = 28.0f;
    const float x = (static_cast<float>(ofGetWidth()) - w) * 0.5f;
    const float y = static_cast<float>(ofGetHeight()) - 48.0f;
    return ofRectangle(x, y, w, h);
}

ofRectangle ofApp::getPresetCellRect(int row, int col) const {
    const float cellW = 74.0f;
    const float cellH = 18.0f;
    const float gap = 8.0f;
    const float totalW = 4.0f * cellW + 3.0f * gap;
    const float x0 = static_cast<float>(ofGetWidth()) - 20.0f - totalW + col * (cellW + gap);
    const float y0 = static_cast<float>(ofGetHeight()) - 92.0f + row * (cellH + 6.0f);
    return ofRectangle(x0, y0, cellW, cellH);
}

bool ofApp::handlePresetGridAt(int x, int y) {
    const float xf = static_cast<float>(x);
    const float yf = static_cast<float>(y);
    for (int col = 0; col < 4; ++col) {
        const ofRectangle loadR = getPresetCellRect(0, col);
        if (loadR.inside(xf, yf)) {
            loadPresetSlot(col);
            return true;
        }
        const ofRectangle saveR = getPresetCellRect(1, col);
        if (saveR.inside(xf, yf)) {
            savePresetSlot(col);
            return true;
        }
    }
    return false;
}

bool ofApp::handleSliderAt(int x, int y) {
    for (int i = 0; i < 2; ++i) {
        const ofRectangle r = getSliderRect(i);
        if (!r.inside(static_cast<float>(x), static_cast<float>(y))) continue;
        const float n = ofClamp((static_cast<float>(x) - r.getX()) / r.getWidth(), 0.0f, 1.0f);
        if (i == 0) {
            onDutyControl = ofLerp(0.05f, 0.95f, n);
            // Immediate audible/visible response to On Duty changes.
            for (auto& s : shapes) {
                if (ofRandomuf() < 0.55f) {
                    s.naturalOn = (ofRandomuf() < onDutyControl);
                }
                s.stateRemainingSec = randomHoldDuration(s.naturalOn);
            }
        } else {
            blinkRateControl = n;
            // Re-time all current states immediately when On/Off Rate changes.
            for (auto& s : shapes) {
                s.stateRemainingSec = randomHoldDuration(s.naturalOn);
            }
        }
        applyPeriodicBlinkControls();
        return true;
    }
    return false;
}

void ofApp::applyCenterDeadZone(MovingShape& shape, float dt) {
    if (!deadZoneEnabled || centerDeadZoneNorm <= 0.0001f || dt <= 0.0f) return;

    const float shortestSide = static_cast<float>(std::min(frameW, frameH));
    const float deadZoneRadius = centerDeadZoneNorm * shortestSide;
    // Keep a hard buffer so mapped panner values don't drift too close to center.
    const float guardRadius = deadZoneRadius + std::max(8.0f, shape.radius * 0.35f);
    // Horizontal-first dead zone with guaranteed top/bottom lanes.
    // This keeps center avoidance strong while allowing blobs to pass above/below.
    const float deadZoneRx = guardRadius * 1.15f;
    const float maxRy = std::max(24.0f, static_cast<float>(frameH) * 0.5f - 70.0f - shape.radius);
    const float deadZoneRy = std::min(guardRadius * 0.55f, maxRy);
    const glm::vec2 center(static_cast<float>(frameW) * 0.5f, static_cast<float>(frameH) * 0.5f);
    glm::vec2 offset = shape.pos - center;

    float ex = offset.x / std::max(1.0f, deadZoneRx);
    float ey = offset.y / std::max(1.0f, deadZoneRy);
    float q = ex * ex + ey * ey;
    if (q < 0.0001f) {
        offset = glm::vec2(1.0f, 0.0f);
        ex = 1.0f;
        ey = 0.0f;
        q = 0.0001f;
    }

    if (q < 1.0f) {
        // Ellipse normal
        glm::vec2 normal(offset.x / (deadZoneRx * deadZoneRx), offset.y / (deadZoneRy * deadZoneRy));
        float nlen = glm::length(normal);
        if (nlen < 0.0001f) normal = glm::vec2(1.0f, 0.0f);
        else normal /= nlen;
        glm::vec2 tangent(-normal.y, normal.x);
        if (glm::length(tangent) < 0.0001f) tangent = glm::vec2(0.0f, 1.0f);
        else tangent = glm::normalize(tangent);

        // Push to ellipse boundary + tiny margin.
        const float scaleToBoundary = 1.0f / std::sqrt(std::max(0.0001f, q));
        glm::vec2 boundary = offset * scaleToBoundary;
        const float penetration = glm::length(boundary - offset);
        shape.pos += normal * (penetration + 1.0f);

        if (!airHockeyMode) {
            // Normal motion mode: steer tangentially so blobs "go around" the dead zone
            // instead of repeatedly punching through the center.
            if (shape.motion == MotionType::Brownian) {
                float dirSign = (glm::dot(shape.vel, tangent) >= 0.0f) ? 1.0f : -1.0f;
                glm::vec2 t = tangent * dirSign;

                // Remove inward radial energy and keep motion mostly tangential.
                float inward = glm::dot(shape.vel, -normal);
                if (inward > 0.0f) shape.vel += normal * (inward * 1.25f);

                float tangentialSpeed = std::max(120.0f, std::abs(glm::dot(shape.vel, t)));
                shape.vel = t * tangentialSpeed + normal * std::max(0.0f, glm::dot(shape.vel, normal)) * 0.2f;
                shape.vel += t * (220.0f * dt + penetration * 12.0f);
            } else {
                float dirSign = (glm::dot(shape.walkDir, tangent) >= 0.0f) ? 1.0f : -1.0f;
                glm::vec2 t = tangent * dirSign;
                shape.walkDir = glm::normalize(shape.walkDir * 0.2f + t * 0.8f);
                shape.vel += t * (180.0f * dt + penetration * 8.0f);
            }
        } else {
            // Air-hockey mode keeps punchy radial bounce.
            if (shape.motion == MotionType::Brownian) {
                shape.vel += normal * (450.0f * dt + penetration * 25.0f);
            } else {
                shape.walkDir = glm::normalize(shape.walkDir + normal * 1.8f);
                shape.vel += normal * (280.0f * dt);
            }
        }
    }
}

void ofApp::applyMagnetForce(MovingShape& shape, float dt, const glm::vec2& target) {
    if (!magnetMode || dt <= 0.0f) return;
    glm::vec2 toTarget = target - shape.pos;
    float dist = glm::length(toTarget);
    if (dist < 0.0001f) return;
    glm::vec2 dir = toTarget / dist;
    float falloff = ofClamp(dist / (0.45f * static_cast<float>(std::min(frameW, frameH))), 0.45f, 1.15f);
    shape.vel += dir * (magnetStrength * 2.4f * falloff * dt);
}

void ofApp::keepInsideFrame(MovingShape& shape) {
    const float worldRadius = ofMap(shape.radius, 18.0f, 48.0f, 3.8f, 12.5f, true);
    const float allowed = std::max(1.0f, kHemisphereRadius - worldRadius);
    glm::vec2 worldPos(
        ofMap(shape.pos.x, 0.0f, static_cast<float>(frameW), -kWorldSide, kWorldSide, true),
        ofMap(shape.pos.y, 0.0f, static_cast<float>(frameH), kWorldFarY, kWorldNearY, true)
    );
    const float dist = glm::length(worldPos);
    if (dist > allowed) {
        glm::vec2 nrm = (dist > 0.0001f) ? (worldPos / dist) : glm::vec2(0.0f, 1.0f);
        if (edgeBounce) {
            glm::vec2 velWorld(
                shape.vel.x * ((2.0f * kWorldSide) / static_cast<float>(frameW)),
                shape.vel.y * ((kWorldNearY - kWorldFarY) / static_cast<float>(frameH))
            );
            glm::vec2 walkWorld(shape.walkDir.x, shape.walkDir.y);
            velWorld = glm::reflect(velWorld, nrm);
            walkWorld = glm::reflect(walkWorld, nrm);
            worldPos = nrm * allowed;
            shape.vel.x = velWorld.x * (static_cast<float>(frameW) / (2.0f * kWorldSide));
            shape.vel.y = velWorld.y * (static_cast<float>(frameH) / (kWorldNearY - kWorldFarY));
            shape.walkDir = glm::normalize(glm::vec2(walkWorld.x, walkWorld.y));
        } else {
            worldPos = -nrm * allowed;
        }
        shape.pos.x = ofMap(worldPos.x, -kWorldSide, kWorldSide, 0.0f, static_cast<float>(frameW), true);
        shape.pos.y = ofMap(worldPos.y, kWorldFarY, kWorldNearY, 0.0f, static_cast<float>(frameH), true);
    }
}

void ofApp::keepInsideFrameAirHockey(MovingShape& shape) {
    constexpr float restitution = 0.987f;
    const float worldRadius = ofMap(shape.radius, 18.0f, 48.0f, 3.8f, 12.5f, true);
    const float allowed = std::max(1.0f, kHemisphereRadius - worldRadius);
    glm::vec2 worldPos(
        ofMap(shape.pos.x, 0.0f, static_cast<float>(frameW), -kWorldSide, kWorldSide, true),
        ofMap(shape.pos.y, 0.0f, static_cast<float>(frameH), kWorldFarY, kWorldNearY, true)
    );
    const float dist = glm::length(worldPos);
    if (dist > allowed) {
        glm::vec2 nrm = (dist > 0.0001f) ? (worldPos / dist) : glm::vec2(0.0f, 1.0f);
        glm::vec2 velWorld(
            shape.vel.x * ((2.0f * kWorldSide) / static_cast<float>(frameW)),
            shape.vel.y * ((kWorldNearY - kWorldFarY) / static_cast<float>(frameH))
        );
        velWorld = glm::reflect(velWorld, nrm) * restitution;
        worldPos = nrm * allowed;
        shape.vel.x = velWorld.x * (static_cast<float>(frameW) / (2.0f * kWorldSide));
        shape.vel.y = velWorld.y * (static_cast<float>(frameH) / (kWorldNearY - kWorldFarY));
        shape.pos.x = ofMap(worldPos.x, -kWorldSide, kWorldSide, 0.0f, static_cast<float>(frameW), true);
        shape.pos.y = ofMap(worldPos.y, kWorldFarY, kWorldNearY, 0.0f, static_cast<float>(frameH), true);
    }
}

void ofApp::updateShapes(float dt) {
    if (dt <= 0.0f) return;
    if (floodActive) {
        floodRemainingSec -= dt;
        if (floodRemainingSec <= 0.0f) {
            floodActive = false;
            floodCooldownRemainingSec = floodCooldownSec;
        }
    } else if (floodCooldownRemainingSec > 0.0f) {
        floodCooldownRemainingSec -= dt;
    }

    const glm::vec2 frameCenter(static_cast<float>(frameW) * 0.5f, static_cast<float>(frameH) * 0.5f);
    const glm::vec2 rainDir = rainDirectionUnit();
    const glm::vec2 rainTan = rainTangentUnit();
    float rainDirHalfExtent = 0.0f;
    float rainTanHalfExtent = 0.0f;
    getRainProjectionExtents(rainDirHalfExtent, rainTanHalfExtent);
    glm::vec2 magnetTarget = frameCenter;
    glm::vec2 activeCentroid = frameCenter;
    float rainEdgePeak = 0.0f;
    int activeCount = 0;
    const int maxI = std::min(activeBlobLimit, static_cast<int>(shapes.size()));
    for (int i = 0; i < maxI; ++i) {
        if (!isShapeOn(shapes[i])) continue;
        activeCentroid += shapes[i].pos;
        ++activeCount;
    }
    if (activeCount > 0) {
        activeCentroid /= static_cast<float>(activeCount + 1); // includes center as a gentle anchor
    }
    if (magnetMode) {
        glm::vec2 sum(0.0f, 0.0f);
        int magnetActiveCount = 0;
        for (int i = 0; i < maxI; ++i) {
            if (!isShapeOn(shapes[i])) continue;
            sum += shapes[i].pos;
            ++magnetActiveCount;
        }
        if (magnetActiveCount >= 2) {
            magnetTarget = sum / static_cast<float>(magnetActiveCount);
        }
    }

    for (size_t idx = 0; idx < shapes.size(); ++idx) {
        auto& s = shapes[idx];
        if (rainMode) {
            const int laneCount = std::max(1, std::min(8, activeBlobLimit > 0 ? activeBlobLimit : 8));
            const int laneIndex = std::max(0, std::min(static_cast<int>(idx), laneCount - 1));
            if (s.rainDormant) {
                if (!floodEnabled || (!floodActive && floodCooldownRemainingSec <= 0.0f)) {
                    resetShapeForRain(s, false, laneIndex);
                }
                updateDepthState(s, dt, static_cast<int>(idx));
                continue;
            }

            if (!s.naturalOn) {
                s.naturalOn = true;
            }

            // Rain movement: flow direction set by rainAngleDeg + light lateral drift.
            const float floodMul = (floodEnabled && floodActive) ? 1.9f : 1.0f;
            const float laneX = (static_cast<float>(laneIndex) + 1.0f) * (static_cast<float>(frameW) / (static_cast<float>(laneCount) + 1.0f));
            const float laneErrorX = laneX - s.pos.x;
            const float laneAssist = ofClamp(laneErrorX * 1.8f, -180.0f, 180.0f);
            s.walkDir.x = ofClamp(s.walkDir.x + ofRandomf() * 0.35f * dt + laneAssist * 3.8f * dt, -28.0f, 28.0f);
            const float targetForward = s.walkDir.y * floodMul;
            const float targetLateral = s.walkDir.x * floodMul;
            const glm::vec2 targetVel = rainDir * targetForward + rainTan * targetLateral;
            s.vel = glm::mix(s.vel, targetVel, 0.06f);
            const float forwardNow = glm::dot(s.vel, rainDir);
            if (forwardNow < 120.0f) {
                s.vel += rainDir * (120.0f - forwardNow);
            }
            s.pos += s.vel * dt;
            // Dead zone should remain global across all motion modes, including rain.
            applyCenterDeadZone(s, dt);

            if (idx < 8) {
                const float edgeNow = edgeMetric01(s);
                rainEdgePeak = std::max(rainEdgePeak, edgeNow);
                if (floodEnabled && edgeNow >= 0.985f) {
                    s.naturalOn = false;
                    s.rainDormant = true;
                    s.vel = glm::vec2(0.0f, 0.0f);
                    updateDepthState(s, dt, static_cast<int>(idx));
                    continue;
                }
            }

            const glm::vec2 rainDirWorld = glm::normalize(glm::vec2(rainDir.x, rainDir.y));
            const glm::vec2 worldPos = screenToWorldPoint(s.pos, frameW, frameH);
            const float worldRadius = ofMap(s.radius, 18.0f, 48.0f, 3.8f, 12.5f, true);
            const float allowed = std::max(1.0f, kHemisphereRadius - worldRadius);
            if (glm::dot(worldPos, rainDirWorld) > allowed + std::max(8.0f, worldRadius * 0.8f)) {
                resetShapeForRain(s, false, laneIndex);
            }
            updateDepthState(s, dt, static_cast<int>(idx));
            continue;
        }

        if (airHockeyMode) {
            if (!s.naturalOn) {
                s.stateRemainingSec -= dt;
                if (s.stateRemainingSec <= 0.0f) {
                    resetShapeForAirHockey(s);
                }
                updateDepthState(s, dt, static_cast<int>(idx));
                continue;
            }

            s.pos += s.vel * dt;
            // Air-hockey feel: lively, but should still bleed energy after repeated hits.
            s.vel *= std::pow(0.9986f, dt * 60.0f);

            applyMagnetForce(s, dt, magnetTarget);
            applyCenterDeadZone(s, dt);
            keepInsideFrameAirHockey(s);

            float spd = glm::length(s.vel);
            if (spd < 17.5f) {
                // Blob "dies", then respawns after a short off window.
                s.naturalOn = false;
                s.stateRemainingSec = ofRandom(0.45f, 1.3f);
            }
            updateDepthState(s, dt, static_cast<int>(idx));
            continue;
        }

        if (!bUseBrownianDrunkMotion) {
            // Dedicated NORMAL mode: smooth orbital flow (distinct from Brownian/Drunkard).
            const glm::vec2 center(static_cast<float>(frameW) * 0.5f, static_cast<float>(frameH) * 0.5f);
            glm::vec2 fromCenter = s.pos - center;
            float r = glm::length(fromCenter);
            if (r < 0.001f) fromCenter = glm::vec2(1.0f, 0.0f), r = 1.0f;
            glm::vec2 radial = fromCenter / r;
            glm::vec2 tangent(-radial.y, radial.x);

            const float i = static_cast<float>(idx);
            const float desiredRadius = ofLerp(90.0f, 240.0f, std::fmod(i * 0.173f, 1.0f));
            const float radialErr = desiredRadius - r;
            const glm::vec2 orbitForce = tangent * 180.0f;
            const glm::vec2 radialForce = radial * (radialErr * 2.0f);
            const glm::vec2 drift(
                ofSignedNoise(simTime * 0.25f + i * 0.91f),
                ofSignedNoise(simTime * 0.21f + i * 1.37f)
            );

            s.vel += (orbitForce + radialForce + drift * 20.0f) * dt;
            s.vel *= std::pow(0.992f, dt * 60.0f);

            float spd = glm::length(s.vel);
            if (spd < 45.0f) s.vel = glm::normalize(s.vel + glm::vec2(0.0001f, 0.0f)) * 45.0f;
            else if (spd > 120.0f) s.vel = glm::normalize(s.vel) * 120.0f;

            s.pos += s.vel * dt;
        } else if (s.motion == MotionType::Brownian) {
            const glm::vec2 jitter(ofRandomf() * 900.0f, ofRandomf() * 900.0f);
            const glm::vec2 toCenter(
                static_cast<float>(frameW) * 0.5f - s.pos.x,
                static_cast<float>(frameH) * 0.5f - s.pos.y
            );
            s.vel += (jitter + toCenter * 0.35f) * dt;
            s.vel *= std::pow(0.985f, dt * 60.0f);

            float spd = glm::length(s.vel);
            if (spd < 70.0f) {
                if (spd < 0.0001f) s.vel = glm::vec2(1.0f, 0.0f) * 70.0f;
                else s.vel = glm::normalize(s.vel) * 70.0f;
            } else if (spd > 260.0f) {
                s.vel = glm::normalize(s.vel) * 260.0f;
            }
            s.pos += s.vel * dt;
        } else {
            float turnChance = ofClamp(0.08f * dt * 60.0f, 0.0f, 1.0f);
            if (ofRandomuf() < turnChance) {
                float turnDeg = ofRandom(-70.0f, 70.0f);
                float rad = glm::radians(turnDeg);
                float c = cosf(rad);
                float sn = sinf(rad);
                glm::vec2 d = s.walkDir;
                s.walkDir = glm::vec2(d.x * c - d.y * sn, d.x * sn + d.y * c);
            }

            if (glm::length(s.walkDir) < 0.0001f) s.walkDir = glm::vec2(1.0f, 0.0f);
            else s.walkDir = glm::normalize(s.walkDir);

            float walkSpeed = 120.0f + 0.9f * s.radius;
            s.vel = s.walkDir * walkSpeed;
            s.pos += s.vel * dt;
        }

        if (activeCount >= 2 && isShapeOn(s)) {
            glm::vec2 toCentroid = activeCentroid - s.pos;
            float distToCentroid = glm::length(toCentroid);
            if (distToCentroid > 0.001f) {
                glm::vec2 dirToCentroid = toCentroid / distToCentroid;
                // Stronger cohesion in normal mode so grouping is visually obvious.
                float pull = std::min(520.0f, distToCentroid * 1.05f);
                s.vel += dirToCentroid * (pull * dt);
            }
        }

        applyMagnetForce(s, dt, magnetTarget);
        applyCenterDeadZone(s, dt);
        keepInsideFrame(s);
        updateDepthState(s, dt, static_cast<int>(idx));
    }

    if (rainMode && floodEnabled) {
        // Rising-edge trigger with hysteresis to avoid armed/active chatter.
        if (!floodEdgeLatch && rainEdgePeak >= 0.985f && !floodActive && floodCooldownRemainingSec <= 0.0f) {
            floodActive = true;
            floodRemainingSec = floodDurationSec;
            floodEdgeLatch = true;
        } else if (floodEdgeLatch && rainEdgePeak <= 0.94f) {
            floodEdgeLatch = false;
        }
    } else {
        floodEdgeLatch = false;
    }

    applyBlobRepulsion(dt);
}

void ofApp::resetShapeForAirHockey(MovingShape& s) {
    const float worldRadius = ofMap(s.radius, 18.0f, 48.0f, 3.8f, 12.5f, true);
    const float allowed = std::max(1.0f, kHemisphereRadius - worldRadius);
    s.pos = worldToScreenPoint(randomWorldPointInCircle(allowed), frameW, frameH);
    glm::vec2 dir = glm::normalize(glm::vec2(ofRandomf(), ofRandomf()));
    if (glm::length(dir) < 0.0001f) dir = glm::vec2(1.0f, 0.0f);
    s.vel = dir * ofRandom(240.0f, 420.0f);
    s.naturalOn = true;
    s.stateRemainingSec = randomHoldDuration(true);
    s.depth = ofRandom(0.12f, 0.86f);
    s.depthVel = ofRandom(-0.14f, 0.14f);
    s.yawDeg = ofRandom(-180.0f, 180.0f);
}

void ofApp::resetShapeForRain(MovingShape& s, bool firstInit, int rainIndex) {
    const glm::vec2 dir = glm::normalize(rainDirectionUnit());
    const glm::vec2 tan = glm::normalize(rainTangentUnit());
    const float worldRadius = ofMap(s.radius, 18.0f, 48.0f, 3.8f, 12.5f, true);
    const float allowed = std::max(1.0f, kHemisphereRadius - worldRadius);
    const int laneCount = std::max(1, std::min(8, activeBlobLimit > 0 ? activeBlobLimit : 8));
    const int safeIndex = (rainIndex >= 0) ? std::min(rainIndex, laneCount - 1) : 0;
    const float laneNorm = (laneCount <= 1) ? 0.0f : ofMap(static_cast<float>(safeIndex), 0.0f, static_cast<float>(laneCount - 1), -1.0f, 1.0f);
    const float lateral = ofRandom(-2.0f, 2.0f);
    const float forward = ofRandom(210.0f, 360.0f);
    s.walkDir = glm::vec2(lateral, forward);
    s.vel = dir * forward + tan * lateral;
    const float laneOffset = ofClamp(
        laneNorm * allowed * 0.78f + ofRandom(firstInit ? -6.0f : -3.0f, firstInit ? 6.0f : 3.0f),
        -allowed * 0.92f,
        allowed * 0.92f
    );
    const float along = std::sqrt(std::max(0.0f, allowed * allowed - laneOffset * laneOffset));
    glm::vec2 spawnWorld = (-dir * along) + tan * laneOffset;
    if (firstInit) spawnWorld += tan * ofRandom(-4.0f, 4.0f);
    s.pos = worldToScreenPoint(spawnWorld, frameW, frameH);
    s.naturalOn = true;
    s.rainDormant = false;
    s.stateRemainingSec = randomHoldDuration(true);
    s.depth = ofClamp(0.20f + (static_cast<float>(safeIndex) / static_cast<float>(std::max(1, laneCount - 1))) * 0.58f, 0.15f, 0.88f);
    s.depthVel = ofRandom(-0.03f, 0.03f);
    s.yawDeg = ofRandom(-18.0f, 18.0f);
}

void ofApp::applyBlobRepulsion(float dt) {
    if (!collisionPhysics || dt <= 0.0f) return;
    const int n = static_cast<int>(shapes.size());
    const float restitution = airHockeyMode ? 0.945f : 0.90f;
    const float collisionScale = airHockeyMode ? 0.80f : (magnetMode ? 0.35f : 1.0f);
    for (int i = 0; i < n; ++i) {
        if (!isShapeOn(shapes[i])) continue;
        for (int j = i + 1; j < n; ++j) {
            if (!isShapeOn(shapes[j])) continue;
            glm::vec2 d = shapes[i].pos - shapes[j].pos;
            float dist = glm::length(d);
            const float minDist = shapes[i].radius + shapes[j].radius + 2.0f;
            if (dist < 0.0001f || dist >= minDist) continue;

            const glm::vec2 nrm = d / dist;
            const glm::vec2 relVel = shapes[i].vel - shapes[j].vel;
            const float relNormalSpeed = glm::dot(relVel, nrm);

            // Mass ~ area so larger blobs feel heavier.
            const float m1 = std::max(1.0f, shapes[i].radius * shapes[i].radius);
            const float m2 = std::max(1.0f, shapes[j].radius * shapes[j].radius);
            const float invM1 = 1.0f / m1;
            const float invM2 = 1.0f / m2;

            if (relNormalSpeed < 0.0f) {
                float jImpulse = -(1.0f + restitution) * relNormalSpeed;
                jImpulse /= (invM1 + invM2);
                // Keep artistic control from collisionStrength.
                jImpulse *= (collisionStrength / 1200.0f) * collisionScale;
                const glm::vec2 impulse = jImpulse * nrm;
                shapes[i].vel += impulse * invM1;
                shapes[j].vel -= impulse * invM2;
                if (airHockeyMode) {
                    // Keep some life, just stop runaway energy build-up.
                    shapes[i].vel *= 0.982f;
                    shapes[j].vel *= 0.982f;
                    const float maxHockeySpeed = 760.0f;
                    const float spd1 = glm::length(shapes[i].vel);
                    const float spd2 = glm::length(shapes[j].vel);
                    if (spd1 > maxHockeySpeed) shapes[i].vel = glm::normalize(shapes[i].vel) * maxHockeySpeed;
                    if (spd2 > maxHockeySpeed) shapes[j].vel = glm::normalize(shapes[j].vel) * maxHockeySpeed;
                }
            }

            // Positional correction (prevents sinking/sticking).
            const float overlap = minDist - dist;
            const float corr = std::max(0.0f, overlap - 0.2f) * 0.8f;
            const glm::vec2 correction = (corr / (invM1 + invM2)) * nrm;
            shapes[i].pos += correction * invM1;
            shapes[j].pos -= correction * invM2;
        }
    }
}

void ofApp::applyPushField(const glm::vec2& pt, float strength) {
    const int active = std::max(1, activeBlobLimit);
    const int maxI = std::min(active, static_cast<int>(shapes.size()));
    for (int i = 0; i < maxI; ++i) {
        auto& s = shapes[i];
        if (!isShapeOn(s)) continue;
        glm::vec2 d = s.pos - pt;
        float dist = std::max(1.0f, glm::length(d));
        glm::vec2 nrm = d / dist;
        float falloff = 1.0f / (1.0f + 0.01f * dist);
        glm::vec2 kick = nrm * (strength * falloff);
        s.vel += kick;
        s.pos += nrm * (3.0f * falloff);
    }
}

void ofApp::renderFrame() {
    fbo.begin();
    ofClear(10, 10, 14, 255);

    ofPushStyle();
    ofBackgroundGradient(ofColor(8, 10, 16), ofColor(3, 5, 9), OF_GRADIENT_LINEAR);
    drawGroundPlane();
    drawHemisphereOverlay();

    if (deadZoneEnabled && centerDeadZoneNorm > 0.0001f) {
        float deadZoneRadius = centerDeadZoneNorm * static_cast<float>(std::min(frameW, frameH));
        float deadZoneRx = deadZoneRadius * 1.15f;
        float deadZoneRy = std::min(deadZoneRadius * 0.55f, std::max(24.0f, static_cast<float>(frameH) * 0.5f - 70.0f));
        ofNoFill();
        ofSetColor(255, 80, 80, 130);
        ofDrawEllipse(static_cast<float>(frameW) * 0.5f, static_cast<float>(frameH) * 0.5f, deadZoneRx * 2.0f, deadZoneRy * 2.0f);
    }

    ofFill();

    struct VisibleShape {
        int idx = 0;
        float cameraDepth = 0.0f;
    };
    std::vector<VisibleShape> visible;
    int considered = 0;
    const int limit = (rainMode || bUseBrownianDrunkMotion) ? static_cast<int>(shapes.size()) : std::min(5, static_cast<int>(shapes.size()));
    for (int i = 0; i < limit; ++i) {
        if (considered >= activeBlobLimit) break;
        considered++;

        const auto& s = shapes[i];
        if (!isShapeOn(s)) continue;
        glm::vec2 projected;
        float cameraDepth = 0.0f;
        if (!projectWorldPoint(shapeWorldPoint(s), projected, &cameraDepth)) continue;
        visible.push_back({i, cameraDepth});
    }

    std::sort(visible.begin(), visible.end(), [](const VisibleShape& a, const VisibleShape& b) {
        return a.cameraDepth > b.cameraDepth;
    });

    for (const auto& item : visible) {
        const auto& s = shapes[item.idx];
        ofSetColor(s.color);
        drawShape3D(s, item.idx);
    }

    drawListenerHead();

    ofPopStyle();
    fbo.end();
}

void ofApp::update() {
    float dt = paused ? 0.0f : ofGetLastFrameTime() * speed;
    processMidiInputQueue();

    int maxBlobs = (rainMode || bUseBrownianDrunkMotion) ? static_cast<int>(shapes.size()) : 5;
    if (autoBlobCount) {
        static const int seq[] = {0, 1, 2, 4, 6, 3, 0, 5, 2};
        const int phase = static_cast<int>(simTime / 1.1f) % static_cast<int>(sizeof(seq) / sizeof(seq[0]));
        activeBlobLimit = std::min(seq[phase], maxBlobs);
    } else {
        activeBlobLimit = ofClamp(manualBlobCount, 0, maxBlobs);
    }
    if (rainMode) {
        // Rain uses the manual blob count so we can perform with different lane densities.
        autoBlobCount = false;
        manualBlobCount = ofClamp(manualBlobCount, 0, maxBlobs);
        activeBlobLimit = manualBlobCount;
    }

    if (!airHockeyMode && !rainMode) {
        updateBlinkStates(dt);
    }
    // Shape simulation now drives both motion modes.
    updateShapes(dt);
    applyMidiTakeover(dt);

    simTime += dt;
    renderFrame();

    if (ndiSender.isSetup()) {
        fbo.readToPixels(pixels);
        ndiVideo.send(pixels);
    }
}

void ofApp::draw() {
    ofSetColor(255);
    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
    drawTopDownOverview();

    ofDrawBitmapStringHighlight("NST NDI Motion Test 3D", 20, 24);
    ofDrawBitmapStringHighlight(
        std::string("Mode: ") +
        (rainMode
            ? ("Rain (" + ofToString(activeBlobLimit) + ", " + ofToString(rainAngleDeg, 1) + "deg)")
            : (bUseBrownianDrunkMotion
            ? (airHockeyMode ? "Hockey" : "Brownian")
            : "Normal")) +
        " | N: " + std::string(airHockeyMode ? "Respawn" : (alwaysOnMode ? "Always On" : (naturalBlink ? "Natural" : "Periodic"))) +
        " | Obj: " + objectPresetName() +
        " | Flood: " + std::string(rainMode ? (floodEnabled ? "On" : "Off") : "Off") +
        " | MIDI: " + std::string(midiTakeoverEnabled ? (midiTakeoverPickUp ? "Pick-up" : "Scaled") : "Off"),
        20, 44
    );
    ofDrawBitmapStringHighlight(
        std::string("Blobs: ") + ofToString(activeBlobLimit) + (autoBlobCount ? " auto" : " manual") +
        " | Edge: " + std::string(edgeBounce ? "On" : "Off") +
        " | Dead: " + std::string(deadZoneEnabled ? (ofToString(centerDeadZoneNorm * 100.0f, 0) + "%") : "Off") +
        " | Magnet: " + std::string(magnetMode ? ("On " + ofToString(magnetStrength, 0)) : "Off") +
        " | View: " + ofToString(viewYawDeg, 0) + "/" + ofToString(viewPitchDeg, 0) +
        " | Obs: " + ofToString(observerOffsetX, 0) + "/" + ofToString(observerDistanceY, 0) +
        " | Phys: " + std::string(collisionPhysics ? "On" : "Off") +
        " | Coll: " + ofToString(collisionStrength, 0) +
        " | ?: help",
        20, 64
    );
    if (!manualBlobInput.empty()) {
        ofDrawBitmapStringHighlight("Blob input: " + manualBlobInput + " (Enter)", 20, 84);
    }
    if (!presetStatus.empty() && ofGetElapsedTimef() <= presetStatusUntil) {
        ofDrawBitmapStringHighlight(presetStatus, 20, 104);
    }
    ofDrawBitmapStringHighlight("MIDI in: " + midiTakeoverStatus, 20, 124);
    if (showHelpOverlay) {
        ofDrawBitmapStringHighlight("Mode: [m] normal/brownian, [h] hockey, [g] rain, [f] flood, [n] natural/periodic/always-on", 20, 160);
        ofDrawBitmapStringHighlight("Objects: [o] mixed/people/hands/dogs/objects/squares/stars", 20, 178);
        ofDrawBitmapStringHighlight("Count: [b] auto, [0-10]+Enter manual, [[]/[]] +/-1 blob", 20, 196);
        ofDrawBitmapStringHighlight("Motion: [k] magnet, [</>] rain angle, [,/.] magnet strength, [p] physics, [c/v] collision", 20, 214);
        ofDrawBitmapStringHighlight("Bounds: [e] bounce, [d] dead-zone, [z/x] dead-zone size, [q] reset top view", 20, 232);
        ofDrawBitmapStringHighlight("View: arrows orbit/tilt camera, shift+up/down zoom, shift+left/right sidestep", 20, 250);
        ofDrawBitmapStringHighlight("Transport: [space] pause, [+/-] speed, [r] reset, mouse-drag push", 20, 268);
        ofDrawBitmapStringHighlight("MIDI: [t] takeover, [y] pick-up/scaled, Ch16 CC0-1, 6-11", 20, 286);
        ofDrawBitmapStringHighlight("Presets: click LOAD/SAVE buttons (slots 1-4)", 20, 304);
    }

    for (int col = 0; col < 4; ++col) {
        const bool valid = presetSlots[col].valid;
        const ofRectangle loadR = getPresetCellRect(0, col);
        const ofRectangle saveR = getPresetCellRect(1, col);

        ofSetColor(valid ? ofColor(30, 170, 90, 180) : ofColor(65, 65, 65, 180));
        ofDrawRectangle(loadR);
        ofSetColor(255);
        ofNoFill();
        ofDrawRectangle(loadR);
        ofFill();
        ofDrawBitmapStringHighlight("L" + ofToString(col + 1), loadR.getX() + 26.0f, loadR.getY() + 13.0f);

        ofSetColor(140, 85, 25, 190);
        ofDrawRectangle(saveR);
        ofSetColor(255);
        ofNoFill();
        ofDrawRectangle(saveR);
        ofFill();
        ofDrawBitmapStringHighlight("S" + ofToString(col + 1), saveR.getX() + 26.0f, saveR.getY() + 13.0f);
    }

    const ofRectangle dutyRect = getSliderRect(0);
    const ofRectangle rateRect = getSliderRect(1);
    ofSetColor(40, 40, 40, 180);
    ofDrawRectangle(dutyRect);
    ofDrawRectangle(rateRect);
    ofSetColor(80, 210, 255, 220);
    ofDrawRectangle(dutyRect.getX(), dutyRect.getY(), dutyRect.getWidth() * ((onDutyControl - 0.05f) / 0.90f), dutyRect.getHeight());
    ofDrawRectangle(rateRect.getX(), rateRect.getY(), rateRect.getWidth() * blinkRateControl, rateRect.getHeight());
    ofSetColor(255);
    ofNoFill();
    ofDrawRectangle(dutyRect);
    ofDrawRectangle(rateRect);
    ofFill();
    ofDrawBitmapStringHighlight("On Duty", dutyRect.getX() + dutyRect.getWidth() + 10.0f, dutyRect.getY() + 11.0f);
    ofDrawBitmapStringHighlight(ofToString(onDutyControl * 100.0f, 0) + "%", dutyRect.getX() + dutyRect.getWidth() + 80.0f, dutyRect.getY() + 11.0f);
    ofDrawBitmapStringHighlight("On/Off Rate", rateRect.getX() + rateRect.getWidth() + 10.0f, rateRect.getY() + 11.0f);
    ofDrawBitmapStringHighlight(ofToString(blinkRateControl * 100.0f, 0) + "%", rateRect.getX() + rateRect.getWidth() + 80.0f, rateRect.getY() + 11.0f);

    const ofRectangle floodRect = getFloodArmRect();
    if (!rainMode) {
        ofSetColor(50, 50, 50, 180);
    } else if (floodEnabled) {
        ofSetColor(floodActive ? ofColor(255, 90, 70, 220) : ofColor(235, 170, 60, 210));
    } else {
        ofSetColor(60, 60, 60, 190);
    }
    ofDrawRectangle(floodRect);
    ofSetColor(255);
    ofNoFill();
    ofDrawRectangle(floodRect);
    ofFill();
    ofDrawBitmapStringHighlight(
        (rainMode && floodEnabled) ? (floodActive ? "FLOOD MODE (ACTIVE)" : "FLOOD MODE (ON)") : "FLOOD MODE (OFF)",
        floodRect.getX() + 8.0f, floodRect.getY() + 18.0f
    );

    ofDrawBitmapStringHighlight(
        "Sending moving NDI stream: " + streamName +
        " | " + (paused ? "PAUSED" : "LIVE") +
        " | speed=" + ofToString(speed, 2),
        20, ofGetHeight() - 20
    );
}

void ofApp::commitManualBlobInput() {
    if (manualBlobInput.empty()) return;
    int parsed = ofToInt(manualBlobInput);
    manualBlobCount = ofClamp(parsed, 0, 10);
    autoBlobCount = false;
    manualBlobInput.clear();
}

void ofApp::keyPressed(int key) {
    if (key >= '0' && key <= '9') {
        if (manualBlobInput.size() < 2) manualBlobInput.push_back(static_cast<char>(key));
        return;
    }
    const bool shiftHeld = ofGetKeyPressed(OF_KEY_SHIFT);
    if (key == OF_KEY_LEFT) {
        if (shiftHeld) observerOffsetX = ofClamp(observerOffsetX - 4.0f, -60.0f, 60.0f);
        else viewYawDeg = wrapSignedDegrees(viewYawDeg - 2.0f);
        return;
    }
    if (key == OF_KEY_RIGHT) {
        if (shiftHeld) observerOffsetX = ofClamp(observerOffsetX + 4.0f, -60.0f, 60.0f);
        else viewYawDeg = wrapSignedDegrees(viewYawDeg + 2.0f);
        return;
    }
    if (key == OF_KEY_UP) {
        if (shiftHeld) observerDistanceY = ofClamp(observerDistanceY - 6.0f, 20.0f, 220.0f);
        else viewPitchDeg = wrapSignedDegrees(viewPitchDeg + 2.0f);
        return;
    }
    if (key == OF_KEY_DOWN) {
        if (shiftHeld) observerDistanceY = ofClamp(observerDistanceY + 6.0f, 20.0f, 220.0f);
        else viewPitchDeg = wrapSignedDegrees(viewPitchDeg - 2.0f);
        return;
    }
    if (key == OF_KEY_BACKSPACE || key == OF_KEY_DEL) {
        if (!manualBlobInput.empty()) manualBlobInput.pop_back();
        return;
    }
    if (key == OF_KEY_RETURN) { commitManualBlobInput(); return; }
    if (key == OF_KEY_ESC) { manualBlobInput.clear(); return; }
    if (key == ' ') { paused = !paused; return; }

    if (key == '+' || key == '=') speed = std::min(4.0f, speed + 0.1f);
    else if (key == '-' || key == '_') speed = std::max(0.1f, speed - 0.1f);
    else if (key == 'b' || key == 'B') autoBlobCount = !autoBlobCount;
    else if (key == 'o' || key == 'O') {
        objectPreset = static_cast<ObjectPreset>((static_cast<int>(objectPreset) + 1) % 7);
        assignObjectPreset();
    }
    else if (key == 'n' || key == 'N') {
        if (naturalBlink && !alwaysOnMode) {
            naturalBlink = false;
            alwaysOnMode = false;
            applyPeriodicBlinkControls();
        } else if (!naturalBlink && !alwaysOnMode) {
            naturalBlink = false;
            alwaysOnMode = true;
            for (auto& s : shapes) {
                s.naturalOn = true;
                s.stateRemainingSec = 5.0f;
            }
        } else {
            naturalBlink = true;
            alwaysOnMode = false;
            applyPeriodicBlinkControls();
            for (auto& s : shapes) {
                s.stateRemainingSec = randomHoldDuration(s.naturalOn);
            }
        }
    }
    else if (key == 't' || key == 'T') {
        midiTakeoverEnabled = !midiTakeoverEnabled;
        midiTakeoverLatched.fill(false);
    }
    else if (key == 'y' || key == 'Y') {
        midiTakeoverPickUp = !midiTakeoverPickUp;
        midiTakeoverLatched.fill(false);
    }
    else if (key == '?') {
        showHelpOverlay = !showHelpOverlay;
    }
    else if (key == 'k' || key == 'K') magnetMode = !magnetMode;
    else if (key == 'f' || key == 'F') {
        floodEnabled = !floodEnabled;
        if (!floodEnabled) {
            floodActive = false;
            floodRemainingSec = 0.0f;
            floodEdgeLatch = false;
        }
    }
    else if (key == 'g' || key == 'G') {
        rainMode = !rainMode;
        if (rainMode) {
            midiTakeoverEnabled = false;
            midiTakeoverLatched.fill(false);
            airHockeyMode = false;
            bUseBrownianDrunkMotion = true;
            autoBlobCount = false;
            manualBlobCount = ofClamp(manualBlobCount > 0 ? manualBlobCount : 8, 0, static_cast<int>(shapes.size()));
            magnetMode = false;
            collisionPhysics = false;
            // Rain should begin with all blobs continuously on until edge death/flood logic takes over.
            naturalBlink = false;
            onDutyControl = 0.90f;
            blinkRateControl = 0.20f;
            floodEnabled = false;
            floodActive = false;
            floodRemainingSec = 0.0f;
            floodCooldownRemainingSec = 0.0f;
            floodEdgeLatch = false;
            for (auto& s : shapes) {
                resetShapeForRain(s, true, static_cast<int>(&s - &shapes[0]));
                s.naturalOn = true;
                s.rainDormant = false;
            }
        } else {
            collisionPhysics = true;
            initShapes();
            applyPeriodicBlinkControls();
        }
    }
    else if (key == 'h' || key == 'H') {
        airHockeyMode = !airHockeyMode;
        if (airHockeyMode) rainMode = false;
        for (auto& s : shapes) {
            if (airHockeyMode) {
                resetShapeForAirHockey(s);
            } else {
                s.naturalOn = (ofRandomuf() < onDutyControl);
                s.stateRemainingSec = randomHoldDuration(s.naturalOn);
            }
        }
    }
    else if (key == 'm' || key == 'M') {
        rainMode = false;
        bUseBrownianDrunkMotion = !bUseBrownianDrunkMotion;
        if (bUseBrownianDrunkMotion) initShapes();
    } else if (key == ']') { manualBlobCount = std::min(10, manualBlobCount + 1); autoBlobCount = false; }
    else if (key == '[') { manualBlobCount = std::max(0, manualBlobCount - 1); autoBlobCount = false; }
    else if (key == 'e' || key == 'E') edgeBounce = !edgeBounce;
    else if (key == 'q' || key == 'Q') {
        viewYawDeg = 0.0f;
        viewPitchDeg = 89.0f;
        observerOffsetX = 0.0f;
        observerDistanceY = 160.0f;
    }
    else if (key == 'd' || key == 'D') deadZoneEnabled = !deadZoneEnabled;
    else if (key == 'x' || key == 'X') { centerDeadZoneNorm = std::min(0.45f, centerDeadZoneNorm + 0.02f); deadZoneEnabled = true; }
    else if (key == 'z' || key == 'Z') { centerDeadZoneNorm = std::max(0.0f, centerDeadZoneNorm - 0.02f); if (centerDeadZoneNorm <= 0.0001f) deadZoneEnabled = false; }
    else if (key == 'p' || key == 'P') collisionPhysics = !collisionPhysics;
    else if (key == ',' || key == '<') {
        if (rainMode) {
            rainAngleDeg = wrapDegrees(rainAngleDeg - 5.0f);
            for (std::size_t i = 0; i < shapes.size(); ++i) resetShapeForRain(shapes[i], true, static_cast<int>(i));
        } else {
            magnetStrength = std::max(50.0f, magnetStrength - 50.0f);
        }
    }
    else if (key == '.' || key == '>') {
        if (rainMode) {
            rainAngleDeg = wrapDegrees(rainAngleDeg + 5.0f);
            for (std::size_t i = 0; i < shapes.size(); ++i) resetShapeForRain(shapes[i], true, static_cast<int>(i));
        } else {
            magnetStrength = std::min(3000.0f, magnetStrength + 50.0f);
        }
    }
    else if (key == 'c' || key == 'C') collisionStrength = std::max(100.0f, collisionStrength - 100.0f);
    else if (key == 'v' || key == 'V') collisionStrength = std::min(6000.0f, collisionStrength + 100.0f);
    else if (key == 'r' || key == 'R') { initShapes(); simTime = 0.0f; }
}

ofApp::SenderPreset ofApp::captureCurrentPreset() const {
    SenderPreset p;
    p.valid = true;
    p.speed = speed;
    p.bUseBrownianDrunkMotion = bUseBrownianDrunkMotion;
    p.airHockeyMode = airHockeyMode;
    p.rainMode = rainMode;
    p.autoBlobCount = autoBlobCount;
    p.manualBlobCount = manualBlobCount;
    p.edgeBounce = edgeBounce;
    p.squareMotionBounds = false;
    p.deadZoneEnabled = deadZoneEnabled;
    p.centerDeadZoneNorm = centerDeadZoneNorm;
    p.collisionPhysics = collisionPhysics;
    p.collisionStrength = collisionStrength;
    p.naturalBlink = naturalBlink;
    p.alwaysOnMode = alwaysOnMode;
    p.onDutyControl = onDutyControl;
    p.blinkRateControl = blinkRateControl;
    p.magnetMode = magnetMode;
    p.magnetStrength = magnetStrength;
    p.floodEnabled = floodEnabled;
    p.floodDurationSec = floodDurationSec;
    p.floodCooldownSec = floodCooldownSec;
    p.rainAngleDeg = rainAngleDeg;
    p.viewYawDeg = viewYawDeg;
    p.viewPitchDeg = viewPitchDeg;
    p.observerOffsetX = observerOffsetX;
    p.observerDistanceY = observerDistanceY;
    p.midiTakeoverEnabled = midiTakeoverEnabled;
    p.midiTakeoverPickUp = midiTakeoverPickUp;
    p.objectPreset = static_cast<int>(objectPreset);
    return p;
}

void ofApp::applyPreset(const SenderPreset& p) {
    speed = p.speed;
    bUseBrownianDrunkMotion = p.bUseBrownianDrunkMotion;
    airHockeyMode = p.airHockeyMode;
    rainMode = p.rainMode;
    autoBlobCount = p.autoBlobCount;
    manualBlobCount = ofClamp(p.manualBlobCount, 0, 10);
    edgeBounce = p.edgeBounce;
    squareMotionBounds = false;
    deadZoneEnabled = p.deadZoneEnabled;
    centerDeadZoneNorm = ofClamp(p.centerDeadZoneNorm, 0.0f, 0.45f);
    collisionPhysics = p.collisionPhysics;
    collisionStrength = ofClamp(p.collisionStrength, 100.0f, 6000.0f);
    naturalBlink = p.naturalBlink;
    alwaysOnMode = p.alwaysOnMode;
    onDutyControl = ofClamp(p.onDutyControl, 0.05f, 0.95f);
    blinkRateControl = ofClamp(p.blinkRateControl, 0.0f, 1.0f);
    magnetMode = p.magnetMode;
    magnetStrength = ofClamp(p.magnetStrength, 50.0f, 3000.0f);
    floodEnabled = p.floodEnabled;
    floodDurationSec = ofClamp(p.floodDurationSec, 0.5f, 8.0f);
    floodCooldownSec = ofClamp(p.floodCooldownSec, 0.2f, 6.0f);
    rainAngleDeg = wrapDegrees(p.rainAngleDeg);
    viewYawDeg = wrapSignedDegrees(p.viewYawDeg);
    viewPitchDeg = wrapSignedDegrees(p.viewPitchDeg);
    observerOffsetX = ofClamp(p.observerOffsetX, -60.0f, 60.0f);
    observerDistanceY = ofClamp(p.observerDistanceY, 20.0f, 220.0f);
    midiTakeoverEnabled = p.midiTakeoverEnabled;
    midiTakeoverPickUp = p.midiTakeoverPickUp;
    objectPreset = static_cast<ObjectPreset>(ofClamp(p.objectPreset, 0, 6));
    midiTakeoverLatched.fill(false);
    floodActive = false;
    floodRemainingSec = 0.0f;
    floodCooldownRemainingSec = 0.0f;
    floodEdgeLatch = false;

    if (rainMode) {
        midiTakeoverEnabled = false;
        midiTakeoverLatched.fill(false);
        autoBlobCount = false;
        manualBlobCount = ofClamp(manualBlobCount > 0 ? manualBlobCount : 8, 0, static_cast<int>(shapes.size()));
        naturalBlink = false;
        for (auto& s : shapes) {
            resetShapeForRain(s, true, static_cast<int>(&s - &shapes[0]));
            s.naturalOn = true;
            s.rainDormant = false;
        }
    }

    applyPeriodicBlinkControls();
    assignObjectPreset();
    for (auto& s : shapes) {
        s.stateRemainingSec = randomHoldDuration(s.naturalOn);
    }
}

void ofApp::savePresetFile() const {
    ofJson j;
    j["slots"] = ofJson::array();
    for (int i = 0; i < static_cast<int>(presetSlots.size()); ++i) {
        const SenderPreset& p = presetSlots[i];
        ofJson s;
        s["valid"] = p.valid;
        s["speed"] = p.speed;
        s["bUseBrownianDrunkMotion"] = p.bUseBrownianDrunkMotion;
        s["airHockeyMode"] = p.airHockeyMode;
        s["rainMode"] = p.rainMode;
        s["autoBlobCount"] = p.autoBlobCount;
        s["manualBlobCount"] = p.manualBlobCount;
        s["edgeBounce"] = p.edgeBounce;
        s["squareMotionBounds"] = p.squareMotionBounds;
        s["deadZoneEnabled"] = p.deadZoneEnabled;
        s["centerDeadZoneNorm"] = p.centerDeadZoneNorm;
        s["collisionPhysics"] = p.collisionPhysics;
        s["collisionStrength"] = p.collisionStrength;
        s["naturalBlink"] = p.naturalBlink;
        s["alwaysOnMode"] = p.alwaysOnMode;
        s["onDutyControl"] = p.onDutyControl;
        s["blinkRateControl"] = p.blinkRateControl;
        s["magnetMode"] = p.magnetMode;
        s["magnetStrength"] = p.magnetStrength;
        s["floodEnabled"] = p.floodEnabled;
        s["floodDurationSec"] = p.floodDurationSec;
        s["floodCooldownSec"] = p.floodCooldownSec;
        s["rainAngleDeg"] = p.rainAngleDeg;
        s["viewYawDeg"] = p.viewYawDeg;
        s["viewPitchDeg"] = p.viewPitchDeg;
        s["observerOffsetX"] = p.observerOffsetX;
        s["observerDistanceY"] = p.observerDistanceY;
        s["midiTakeoverEnabled"] = p.midiTakeoverEnabled;
        s["midiTakeoverPickUp"] = p.midiTakeoverPickUp;
        s["objectPreset"] = p.objectPreset;
        j["slots"].push_back(s);
    }
    ofSavePrettyJson(ofToDataPath("sender_slots_3d.json", true), j);
}

void ofApp::loadPresetFile() {
    const std::string path = ofToDataPath("sender_slots_3d.json", true);
    if (!ofFile::doesFileExist(path)) return;

    ofJson j = ofLoadJson(path);
    if (!j.contains("slots") || !j["slots"].is_array()) return;

    const auto& arr = j["slots"];
    for (int i = 0; i < static_cast<int>(presetSlots.size()) && i < static_cast<int>(arr.size()); ++i) {
        const ofJson& s = arr[i];
        SenderPreset p;
        p.valid = s.value("valid", false);
        p.speed = s.value("speed", p.speed);
        p.bUseBrownianDrunkMotion = s.value("bUseBrownianDrunkMotion", p.bUseBrownianDrunkMotion);
        p.airHockeyMode = s.value("airHockeyMode", p.airHockeyMode);
        p.rainMode = s.value("rainMode", p.rainMode);
        p.autoBlobCount = s.value("autoBlobCount", p.autoBlobCount);
        p.manualBlobCount = s.value("manualBlobCount", p.manualBlobCount);
        p.edgeBounce = s.value("edgeBounce", p.edgeBounce);
        p.squareMotionBounds = s.value("squareMotionBounds", p.squareMotionBounds);
        p.deadZoneEnabled = s.value("deadZoneEnabled", p.deadZoneEnabled);
        p.centerDeadZoneNorm = s.value("centerDeadZoneNorm", p.centerDeadZoneNorm);
        p.collisionPhysics = s.value("collisionPhysics", p.collisionPhysics);
        p.collisionStrength = s.value("collisionStrength", p.collisionStrength);
        p.naturalBlink = s.value("naturalBlink", p.naturalBlink);
        p.alwaysOnMode = s.value("alwaysOnMode", p.alwaysOnMode);
        p.onDutyControl = s.value("onDutyControl", p.onDutyControl);
        p.blinkRateControl = s.value("blinkRateControl", p.blinkRateControl);
        p.magnetMode = s.value("magnetMode", p.magnetMode);
        p.magnetStrength = s.value("magnetStrength", p.magnetStrength);
        p.floodEnabled = s.value("floodEnabled", p.floodEnabled);
        p.floodDurationSec = s.value("floodDurationSec", p.floodDurationSec);
        p.floodCooldownSec = s.value("floodCooldownSec", p.floodCooldownSec);
        p.rainAngleDeg = s.value("rainAngleDeg", p.rainAngleDeg);
        p.viewYawDeg = s.value("viewYawDeg", p.viewYawDeg);
        p.viewPitchDeg = s.value("viewPitchDeg", p.viewPitchDeg);
        p.observerOffsetX = s.value("observerOffsetX", p.observerOffsetX);
        p.observerDistanceY = s.value("observerDistanceY", p.observerDistanceY);
        p.midiTakeoverEnabled = s.value("midiTakeoverEnabled", p.midiTakeoverEnabled);
        p.midiTakeoverPickUp = s.value("midiTakeoverPickUp", p.midiTakeoverPickUp);
        p.objectPreset = s.value("objectPreset", p.objectPreset);
        presetSlots[i] = p;
    }
}

void ofApp::savePresetSlot(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= static_cast<int>(presetSlots.size())) return;
    presetSlots[slotIndex] = captureCurrentPreset();
    currentPresetSlot = slotIndex;
    presetStatus = "Saved sender state to slot " + ofToString(slotIndex + 1);
    presetStatusUntil = ofGetElapsedTimef() + 2.0f;
    savePresetFile();
}

void ofApp::loadPresetSlot(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= static_cast<int>(presetSlots.size())) return;
    if (!presetSlots[slotIndex].valid) {
        presetStatus = "Slot " + ofToString(slotIndex + 1) + " is empty";
        presetStatusUntil = ofGetElapsedTimef() + 2.0f;
        return;
    }
    applyPreset(presetSlots[slotIndex]);
    currentPresetSlot = slotIndex;
    presetStatus = "Loaded sender state from slot " + ofToString(slotIndex + 1);
    presetStatusUntil = ofGetElapsedTimef() + 2.0f;
}

void ofApp::mousePressed(int x, int y, int button) {
    (void)button;
    if (handlePresetGridAt(x, y)) return;
    if (getFloodArmRect().inside(static_cast<float>(x), static_cast<float>(y))) {
        if (!rainMode) return;
        floodEnabled = !floodEnabled;
        if (!floodEnabled) {
            floodActive = false;
            floodRemainingSec = 0.0f;
            floodEdgeLatch = false;
        }
        return;
    }
    if (handleSliderAt(x, y)) return;
    const float sx = static_cast<float>(frameW) / std::max(1.0f, static_cast<float>(ofGetWidth()));
    const float sy = static_cast<float>(frameH) / std::max(1.0f, static_cast<float>(ofGetHeight()));
    applyPushField(glm::vec2(static_cast<float>(x) * sx, static_cast<float>(y) * sy), pushStrength);
}

void ofApp::mouseDragged(int x, int y, int button) {
    (void)button;
    if (handleSliderAt(x, y)) return;
    const float sx = static_cast<float>(frameW) / std::max(1.0f, static_cast<float>(ofGetWidth()));
    const float sy = static_cast<float>(frameH) / std::max(1.0f, static_cast<float>(ofGetHeight()));
    applyPushField(glm::vec2(static_cast<float>(x) * sx, static_cast<float>(y) * sy), pushStrength * 0.35f);
}
