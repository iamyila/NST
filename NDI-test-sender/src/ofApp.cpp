#include "ofApp.h"
#include <cmath>
#include <sstream>

namespace {
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
                shapes[shapeIndex].stateRemainingSec = 3.0f;
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
        MotionBounds b = getMotionBounds(s.radius);

        const float xNorm = midiTakeoverNorm[xAxis];
        const float yNorm = midiTakeoverNorm[yAxis];
        float targetX = ofLerp(b.minX, b.maxX, xNorm);
        float targetY = ofLerp(b.maxY, b.minY, yNorm); // top = 100%

        if (midiTakeoverPickUp) {
            const float currentXNorm = ofMap(s.pos.x, b.minX, b.maxX, 0.0f, 1.0f, true);
            const float currentYNorm = ofMap(s.pos.y, b.maxY, b.minY, 0.0f, 1.0f, true);
            constexpr float pickupWindow = 0.05f;

            if (!midiTakeoverLatched[xAxis] && std::abs(xNorm - currentXNorm) <= pickupWindow) {
                midiTakeoverLatched[xAxis] = true;
            }
            if (!midiTakeoverLatched[yAxis] && std::abs(yNorm - currentYNorm) <= pickupWindow) {
                midiTakeoverLatched[yAxis] = true;
            }
            if (!midiTakeoverLatched[xAxis]) targetX = s.pos.x;
            if (!midiTakeoverLatched[yAxis]) targetY = s.pos.y;
        } else {
            midiTakeoverLatched[xAxis] = true;
            midiTakeoverLatched[yAxis] = true;
        }

        const glm::vec2 target(targetX, targetY);
        const float alpha = midiTakeoverPickUp ? 0.38f : 0.24f;
        s.pos = glm::mix(s.pos, target, alpha);
        s.vel *= 0.55f;
        applyCenterDeadZone(s, dt);
        keepInsideFrame(s);
        if (alwaysOnMode && (midiTakeoverUpdated[xAxis] || midiTakeoverUpdated[yAxis])) {
            s.naturalOn = true;
            s.stateRemainingSec = 3.0f;
        }
    }
    midiTakeoverUpdated.fill(false);
}

ofApp::MotionBounds ofApp::getMotionBounds(float radius) const {
    MotionBounds b;
    if (squareMotionBounds) {
        const float side = static_cast<float>(std::min(frameW, frameH));
        const float xOffset = (static_cast<float>(frameW) - side) * 0.5f;
        const float yOffset = (static_cast<float>(frameH) - side) * 0.5f;
        b.minX = xOffset + radius;
        b.maxX = xOffset + side - radius;
        b.minY = yOffset + radius;
        b.maxY = yOffset + side - radius;
    } else {
        b.minX = radius;
        b.maxX = static_cast<float>(frameW) - radius;
        b.minY = radius;
        b.maxY = static_cast<float>(frameH) - radius;
    }
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

void ofApp::initShapes() {
    shapes.clear();
    shapes.reserve(10);

    for (int i = 0; i < 10; ++i) {
        MovingShape s;
        s.radius = ofRandom(18.0f, 48.0f);
        MotionBounds b = getMotionBounds(s.radius);
        s.pos = glm::vec2(ofRandom(b.minX, b.maxX), ofRandom(b.minY, b.maxY));
        for (int attempt = 0; attempt < 40; ++attempt) {
            bool overlaps = false;
            for (const auto& other : shapes) {
                const float minDist = s.radius + other.radius + 14.0f;
                if (glm::distance(s.pos, other.pos) < minDist) {
                    overlaps = true;
                    s.pos = glm::vec2(ofRandom(b.minX, b.maxX), ofRandom(b.minY, b.maxY));
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

        float hue = fmodf(i * 27.0f, 255.0f);
        s.color = ofColor::fromHsb(static_cast<unsigned char>(hue), 220, 255);
        shapes.push_back(s);
    }

    if (rainMode) {
        for (std::size_t i = 0; i < shapes.size(); ++i) {
            resetShapeForRain(shapes[i], true, static_cast<int>(i));
        }
    }
}

void ofApp::updateBlinkStates(float dt) {
    if (dt <= 0.0f) return;
    if (alwaysOnMode) {
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
    MotionBounds b = getMotionBounds(s.radius);
    const float w = std::max(1.0f, b.maxX - b.minX);
    const float h = std::max(1.0f, b.maxY - b.minY);
    const float nx = ofClamp((s.pos.x - b.minX) / w, 0.0f, 1.0f);
    const float ny = ofClamp((s.pos.y - b.minY) / h, 0.0f, 1.0f);
    return std::max(std::abs(nx * 2.0f - 1.0f), std::abs(ny * 2.0f - 1.0f));
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
    MotionBounds b = getMotionBounds(shape.radius);

    if (edgeBounce) {
        if (shape.pos.x < b.minX) {
            shape.pos.x = b.minX;
            shape.vel.x = std::abs(shape.vel.x);
            shape.walkDir.x = std::abs(shape.walkDir.x);
        } else if (shape.pos.x > b.maxX) {
            shape.pos.x = b.maxX;
            shape.vel.x = -std::abs(shape.vel.x);
            shape.walkDir.x = -std::abs(shape.walkDir.x);
        }

        if (shape.pos.y < b.minY) {
            shape.pos.y = b.minY;
            shape.vel.y = std::abs(shape.vel.y);
            shape.walkDir.y = std::abs(shape.walkDir.y);
        } else if (shape.pos.y > b.maxY) {
            shape.pos.y = b.maxY;
            shape.vel.y = -std::abs(shape.vel.y);
            shape.walkDir.y = -std::abs(shape.walkDir.y);
        }
    } else {
        if (shape.pos.x < b.minX) shape.pos.x = b.maxX;
        else if (shape.pos.x > b.maxX) shape.pos.x = b.minX;
        if (shape.pos.y < b.minY) shape.pos.y = b.maxY;
        else if (shape.pos.y > b.maxY) shape.pos.y = b.minY;
    }
}

void ofApp::keepInsideFrameAirHockey(MovingShape& shape) {
    MotionBounds b = getMotionBounds(shape.radius);
    constexpr float restitution = 0.987f;

    if (shape.pos.x < b.minX) {
        shape.pos.x = b.minX + (b.minX - shape.pos.x);
        shape.vel.x = std::abs(shape.vel.x) * restitution;
    } else if (shape.pos.x > b.maxX) {
        shape.pos.x = b.maxX - (shape.pos.x - b.maxX);
        shape.vel.x = -std::abs(shape.vel.x) * restitution;
    }

    if (shape.pos.y < b.minY) {
        shape.pos.y = b.minY + (b.minY - shape.pos.y);
        shape.vel.y = std::abs(shape.vel.y) * restitution;
    } else if (shape.pos.y > b.maxY) {
        shape.pos.y = b.maxY - (shape.pos.y - b.maxY);
        shape.vel.y = -std::abs(shape.vel.y) * restitution;
    }

    // Safety clamp to avoid sticking outside bounds on extreme frames.
    shape.pos.x = ofClamp(shape.pos.x, b.minX, b.maxX);
    shape.pos.y = ofClamp(shape.pos.y, b.minY, b.maxY);
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
                    continue;
                }
            }

            const float exitMargin = std::max(90.0f, s.radius * 2.6f);
            // Keep rain visually clean: spawn from above and only recycle once it has
            // clearly fallen past the bottom edge, not when it briefly clips a side.
            if (s.pos.y - s.radius > static_cast<float>(frameH) + exitMargin) {
                resetShapeForRain(s, false, laneIndex);
            }
            continue;
        }

        if (airHockeyMode) {
            if (!s.naturalOn) {
                s.stateRemainingSec -= dt;
                if (s.stateRemainingSec <= 0.0f) {
                    resetShapeForAirHockey(s);
                }
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
    MotionBounds b = getMotionBounds(s.radius);
    s.pos = glm::vec2(ofRandom(b.minX, b.maxX), ofRandom(b.minY, b.maxY));
    glm::vec2 dir = glm::normalize(glm::vec2(ofRandomf(), ofRandomf()));
    if (glm::length(dir) < 0.0001f) dir = glm::vec2(1.0f, 0.0f);
    s.vel = dir * ofRandom(240.0f, 420.0f);
    s.naturalOn = true;
    s.stateRemainingSec = randomHoldDuration(true);
}

void ofApp::resetShapeForRain(MovingShape& s, bool firstInit, int rainIndex) {
    const glm::vec2 dir = rainDirectionUnit();
    const glm::vec2 tan = rainTangentUnit();
    const float margin = std::max(60.0f, s.radius * 2.2f);
    const int laneCount = std::max(1, std::min(8, activeBlobLimit > 0 ? activeBlobLimit : 8));
    const int safeIndex = (rainIndex >= 0) ? std::min(rainIndex, laneCount - 1) : 0;
    const float laneX = (static_cast<float>(safeIndex) + 1.0f) * (static_cast<float>(frameW) / (static_cast<float>(laneCount) + 1.0f));

    const float lateral = ofRandom(-2.0f, 2.0f);
    const float forward = ofRandom(210.0f, 360.0f);
    s.walkDir = glm::vec2(lateral, forward);
    s.vel = dir * forward + tan * lateral;

    const float topY = -margin - ofRandom(0.0f, margin * 0.9f);
    const float entryX = ofClamp(laneX + ofRandom(firstInit ? -10.0f : -5.0f, firstInit ? 10.0f : 5.0f), s.radius, static_cast<float>(frameW) - s.radius);
    const float vy = (s.vel.y > 40.0f) ? s.vel.y : 40.0f;
    const float timeToTop = (-topY) / vy;
    float spawnX = entryX - s.vel.x * timeToTop;

    if (firstInit) {
        spawnX += ofRandom(-18.0f, 18.0f);
    }

    s.pos = glm::vec2(spawnX, topY);
    s.naturalOn = true;
    s.rainDormant = false;
    s.stateRemainingSec = randomHoldDuration(true);
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
    MotionBounds frameBounds = getMotionBounds(0.0f);
    if (squareMotionBounds) {
        ofNoFill();
        ofSetColor(70, 200, 255, 120);
        ofDrawRectangle(frameBounds.minX, frameBounds.minY, frameBounds.maxX - frameBounds.minX, frameBounds.maxY - frameBounds.minY);
    }

    if (deadZoneEnabled && centerDeadZoneNorm > 0.0001f) {
        float deadZoneRadius = centerDeadZoneNorm * static_cast<float>(std::min(frameW, frameH));
        float deadZoneRx = deadZoneRadius * 1.15f;
        float deadZoneRy = std::min(deadZoneRadius * 0.55f, std::max(24.0f, static_cast<float>(frameH) * 0.5f - 70.0f));
        ofNoFill();
        ofSetColor(255, 80, 80, 130);
        ofDrawEllipse(static_cast<float>(frameW) * 0.5f, static_cast<float>(frameH) * 0.5f, deadZoneRx * 2.0f, deadZoneRy * 2.0f);
    }

    ofFill();

    int considered = 0;
    const int limit = (rainMode || bUseBrownianDrunkMotion) ? static_cast<int>(shapes.size()) : std::min(5, static_cast<int>(shapes.size()));
    for (int i = 0; i < limit; ++i) {
        if (considered >= activeBlobLimit) break;
        considered++;

        const auto& s = shapes[i];
        if (!isShapeOn(s)) continue;

        ofSetColor(s.color);
        if (s.bRect) {
            ofPushMatrix();
            ofTranslate(s.pos);
            ofRotateDeg(ofSignedNoise(simTime * 0.6f + i) * 35.0f);
            float size = s.radius * 1.9f;
            ofDrawRectangle(-size * 0.5f, -size * 0.5f, size, size);
            ofPopMatrix();
        } else {
            ofDrawCircle(s.pos.x, s.pos.y, s.radius);
        }
    }

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

    ofDrawBitmapStringHighlight("NST NDI Motion Test", 20, 24);
    ofDrawBitmapStringHighlight(
        std::string("Mode: ") +
        (rainMode
            ? ("Rain (" + ofToString(activeBlobLimit) + ", " + ofToString(rainAngleDeg, 1) + "deg)")
            : (bUseBrownianDrunkMotion
            ? (airHockeyMode ? "Hockey" : "Brownian")
            : "Normal")) +
        " | Blink: " + std::string(airHockeyMode ? "Respawn" : (alwaysOnMode ? "Always On" : (naturalBlink ? "Natural" : "Periodic"))) +
        " | Flood: " + std::string(rainMode ? (floodEnabled ? "On" : "Off") : "Off") +
        " | MIDI: " + std::string(midiTakeoverEnabled ? (midiTakeoverPickUp ? "Pick-up" : "Scaled") : "Off"),
        20, 44
    );
    ofDrawBitmapStringHighlight(
        std::string("Blobs: ") + ofToString(activeBlobLimit) + (autoBlobCount ? " auto" : " manual") +
        " | Dead: " + std::string(deadZoneEnabled ? (ofToString(centerDeadZoneNorm * 100.0f, 0) + "%") : "Off") +
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
        ofDrawBitmapStringHighlight("Count: [b] auto, [0-10]+Enter manual, [[]/[]] +/-1 blob", 20, 178);
        ofDrawBitmapStringHighlight("Motion: [k] magnet, [</>] rain angle, [,/.] magnet strength, [p] physics, [c/v] collision", 20, 196);
        ofDrawBitmapStringHighlight("Bounds: [e] bounce, [d] dead-zone, [z/x] dead-zone size, [q] square bounds", 20, 214);
        ofDrawBitmapStringHighlight("Transport: [space] pause, [+/-] speed, [r] reset, mouse-drag push", 20, 232);
        ofDrawBitmapStringHighlight("MIDI: [t] takeover, [y] pick-up/scaled, Ch16 CC0-1, 6-11", 20, 250);
        ofDrawBitmapStringHighlight("Presets: click LOAD/SAVE buttons (slots 1-4)", 20, 268);
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
                s.stateRemainingSec = 3.0f;
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
    else if (key == 'q' || key == 'Q') { squareMotionBounds = !squareMotionBounds; initShapes(); }
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
    p.squareMotionBounds = squareMotionBounds;
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
    p.midiTakeoverEnabled = midiTakeoverEnabled;
    p.midiTakeoverPickUp = midiTakeoverPickUp;
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
    squareMotionBounds = p.squareMotionBounds;
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
    midiTakeoverEnabled = p.midiTakeoverEnabled;
    midiTakeoverPickUp = p.midiTakeoverPickUp;
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
        s["midiTakeoverEnabled"] = p.midiTakeoverEnabled;
        s["midiTakeoverPickUp"] = p.midiTakeoverPickUp;
        j["slots"].push_back(s);
    }
    ofSavePrettyJson(ofToDataPath("sender_slots.json", true), j);
}

void ofApp::loadPresetFile() {
    const std::string path = ofToDataPath("sender_slots.json", true);
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
        p.midiTakeoverEnabled = s.value("midiTakeoverEnabled", p.midiTakeoverEnabled);
        p.midiTakeoverPickUp = s.value("midiTakeoverPickUp", p.midiTakeoverPickUp);
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
