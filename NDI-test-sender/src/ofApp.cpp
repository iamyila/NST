#include "ofApp.h"
#include <cmath>

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

    initShapes();
}

float ofApp::randomHoldDuration(bool onState) const {
    const float duty = ofClamp(onDutyControl, 0.05f, 0.95f);
    const float switchRate = ofLerp(0.2f, 3.0f, ofClamp(blinkRateControl, 0.0f, 1.0f));
    const float lambda = std::max(0.02f, onState ? switchRate * (1.0f - duty) : switchRate * duty);
    const float u = std::max(0.0001f, ofRandomuf());
    float sample = -std::log(1.0f - u) / lambda;
    // Bias toward longer ON windows and shorter OFF gaps.
    sample *= onState ? 1.35f : 0.75f;
    return ofClamp(sample, 0.12f, 10.0f);
}

void ofApp::initShapes() {
    shapes.clear();
    shapes.reserve(10);

    for (int i = 0; i < 10; ++i) {
        MovingShape s;
        MotionBounds b = getMotionBounds(80.0f);
        s.pos = glm::vec2(ofRandom(b.minX, b.maxX), ofRandom(b.minY, b.maxY));
        s.vel = glm::vec2(ofRandomf(), ofRandomf()) * ofRandom(50.0f, 120.0f);
        s.walkDir = glm::normalize(glm::vec2(ofRandomf(), ofRandomf()));
        if (glm::length(s.walkDir) < 0.0001f) s.walkDir = glm::vec2(1.0f, 0.0f);

        s.radius = ofRandom(18.0f, 48.0f);
        s.motion = (i % 2 == 0) ? MotionType::Brownian : MotionType::Drunkard;
        s.bRect = (i % 3 == 0);

        s.blinkPeriodSec = ofRandom(1.2f, 3.8f);
        s.blinkDuty = ofRandom(0.35f, 0.75f);
        s.blinkPhaseSec = ofRandom(0.0f, s.blinkPeriodSec);
        s.naturalOn = (ofRandomuf() < onDutyControl);
        s.stateRemainingSec = randomHoldDuration(s.naturalOn);

        float hue = fmodf(i * 27.0f, 255.0f);
        s.color = ofColor::fromHsb(static_cast<unsigned char>(hue), 220, 255);
        shapes.push_back(s);
    }
}

void ofApp::updateBlinkStates(float dt) {
    if (!naturalBlink || dt <= 0.0f) return;
    for (auto& s : shapes) {
        s.stateRemainingSec -= dt;
        if (s.stateRemainingSec <= 0.0f) {
            s.naturalOn = !s.naturalOn;
            s.stateRemainingSec = randomHoldDuration(s.naturalOn);
        }
    }
}

bool ofApp::isShapeOn(const MovingShape& shape) const {
    if (naturalBlink) return shape.naturalOn;
    if (shape.blinkPeriodSec <= 0.0001f) return true;
    float t = fmodf(simTime + shape.blinkPhaseSec, shape.blinkPeriodSec);
    return t < (shape.blinkPeriodSec * shape.blinkDuty);
}

ofRectangle ofApp::getSliderRect(int sliderIndex) const {
    const float w = 220.0f;
    const float h = 12.0f;
    const float x = 20.0f;
    const float y0 = static_cast<float>(ofGetHeight()) - 70.0f;
    return ofRectangle(x, y0 + sliderIndex * 24.0f, w, h);
}

bool ofApp::handleSliderAt(int x, int y) {
    for (int i = 0; i < 2; ++i) {
        const ofRectangle r = getSliderRect(i);
        if (!r.inside(static_cast<float>(x), static_cast<float>(y))) continue;
        const float n = ofClamp((static_cast<float>(x) - r.getX()) / r.getWidth(), 0.0f, 1.0f);
        if (i == 0) onDutyControl = ofLerp(0.05f, 0.95f, n);
        else blinkRateControl = n;
        return true;
    }
    return false;
}

void ofApp::applyCenterDeadZone(MovingShape& shape, float dt) {
    if (!deadZoneEnabled || centerDeadZoneNorm <= 0.0001f || dt <= 0.0f) return;

    const float shortestSide = static_cast<float>(std::min(frameW, frameH));
    const float deadZoneRadius = centerDeadZoneNorm * shortestSide;
    const glm::vec2 center(static_cast<float>(frameW) * 0.5f, static_cast<float>(frameH) * 0.5f);
    glm::vec2 offset = shape.pos - center;
    float dist = glm::length(offset);
    if (dist < 0.0001f) {
        offset = glm::vec2(1.0f, 0.0f);
        dist = 0.0001f;
    }

    if (dist < deadZoneRadius) {
        glm::vec2 normal = offset / dist;
        float penetration = deadZoneRadius - dist;
        shape.pos += normal * (penetration + 1.0f);

        if (shape.motion == MotionType::Brownian) {
            shape.vel += normal * (450.0f * dt + penetration * 25.0f);
        } else {
            shape.walkDir = glm::normalize(shape.walkDir + normal * 1.8f);
            shape.vel += normal * (280.0f * dt);
        }
    }
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
    constexpr float restitution = 0.995f;

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

    for (auto& s : shapes) {
        if (airHockeyMode) {
            if (!s.naturalOn) {
                s.stateRemainingSec -= dt;
                if (s.stateRemainingSec <= 0.0f) {
                    resetShapeForAirHockey(s);
                }
                continue;
            }

            s.pos += s.vel * dt;
            // Air-hockey feel: very low drag, keeps inertia after hits.
            s.vel *= std::pow(0.9992f, dt * 60.0f);

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

        if (s.motion == MotionType::Brownian) {
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

        applyCenterDeadZone(s, dt);
        keepInsideFrame(s);
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

void ofApp::applyBlobRepulsion(float dt) {
    if (!collisionPhysics || dt <= 0.0f) return;
    const int n = static_cast<int>(shapes.size());
    const float restitution = airHockeyMode ? 0.98f : 0.90f;
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
                jImpulse *= (collisionStrength / 1200.0f);
                const glm::vec2 impulse = jImpulse * nrm;
                shapes[i].vel += impulse * invM1;
                shapes[j].vel -= impulse * invM2;
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
        ofNoFill();
        ofSetColor(255, 80, 80, 130);
        ofDrawCircle(static_cast<float>(frameW) * 0.5f, static_cast<float>(frameH) * 0.5f, deadZoneRadius);
    }

    ofFill();

    int considered = 0;
    if (bUseBrownianDrunkMotion) {
        for (int i = 0; i < static_cast<int>(shapes.size()); ++i) {
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
    } else {
        for (int i = 0; i < 5; ++i) {
            if (considered >= activeBlobLimit) break;
            considered++;

            float period = 1.2f + 0.35f * static_cast<float>(i);
            float duty = 0.45f + 0.08f * static_cast<float>(i % 3);
            float t = fmodf(simTime + 0.47f * static_cast<float>(i), period);
            bool on = t < (period * duty);
            if (!on) continue;

            float phase = simTime * (0.7f + 0.2f * i) + i * 1.2f;
            float x = ofMap(sinf(phase), -1.0f, 1.0f, 80.0f, frameW - 80.0f);
            float y = ofMap(cosf(phase * 1.37f), -1.0f, 1.0f, 80.0f, frameH - 80.0f);
            float r = 22.0f + 10.0f * i;

            if (i == 4) {
                ofSetColor(245, 90, 40);
                ofDrawRectangle(x - 90.0f, y - 60.0f, 180, 110);
            } else {
                ofSetColor(40 + i * 45, 200 - i * 25, 255 - i * 35);
                ofDrawCircle(x, y, r);
            }
        }
    }

    ofPopStyle();
    fbo.end();
}

void ofApp::update() {
    float dt = paused ? 0.0f : ofGetLastFrameTime() * speed;
    int maxBlobs = bUseBrownianDrunkMotion ? static_cast<int>(shapes.size()) : 5;
    if (autoBlobCount) {
        static const int seq[] = {0, 1, 2, 4, 6, 3, 0, 5, 2};
        const int phase = static_cast<int>(simTime / 1.1f) % static_cast<int>(sizeof(seq) / sizeof(seq[0]));
        activeBlobLimit = std::min(seq[phase], maxBlobs);
    } else {
        activeBlobLimit = ofClamp(manualBlobCount, 0, maxBlobs);
    }

    if (!airHockeyMode) {
        updateBlinkStates(dt);
    }
    if (bUseBrownianDrunkMotion) updateShapes(dt);

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
    ofDrawBitmapStringHighlight("Stream: " + streamName, 20, 44);
    ofDrawBitmapStringHighlight(
        std::string("Motion: ") +
        (bUseBrownianDrunkMotion
            ? (airHockeyMode ? "Air Hockey (inertia + respawn)" : "Brownian + Drunkard (10 shapes)")
            : "Normal"),
        20, 64
    );
    ofDrawBitmapStringHighlight("Shapes pulse on/off automatically", 20, 84);
    ofDrawBitmapStringHighlight("Time: " + ofToString(simTime, 2), 20, 104);
    ofDrawBitmapStringHighlight("Blob count: " + ofToString(activeBlobLimit) + (autoBlobCount ? " (auto)" : " (manual)"), 20, 124);
    ofDrawBitmapStringHighlight(
        std::string("Bounds: ") + (squareMotionBounds ? "Square" : "Frame") +
        " | Edge: " + (edgeBounce ? "Bounce" : "Wrap") +
        " | Dead zone: " + std::string(deadZoneEnabled ? (ofToString(centerDeadZoneNorm * 100.0f, 0) + "%") : "OFF") +
        " | Physics: " + std::string(collisionPhysics ? "On" : "Off") +
        " | Coll: " + ofToString(collisionStrength, 0) +
        " | Blink: " + std::string(airHockeyMode ? "Inertia Respawn" : (naturalBlink ? "Natural" : "Periodic")) +
        " | N:" + std::string(naturalBlink ? "Natural" : "Periodic"),
        20, 144
    );
    if (!manualBlobInput.empty()) {
        ofDrawBitmapStringHighlight("Manual blob input: " + manualBlobInput + " (press Enter)", 20, 164);
    }
    ofDrawBitmapStringHighlight("Keys: m motion, h air-hockey, b auto blobs, n natural/periodic", 20, 184);
    ofDrawBitmapStringHighlight("Keys: 0-10 + Enter, [ ] count, +/- speed, e bounce, q square, d dead-zone on/off, z/x dead zone size", 20, 202);
    ofDrawBitmapStringHighlight("Keys: p physics, c/v collision, mouse drag push, space pause, r reset", 20, 220);

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
    else if (key == 'n' || key == 'N') naturalBlink = !naturalBlink;
    else if (key == 'h' || key == 'H') {
        airHockeyMode = !airHockeyMode;
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
    else if (key == 'c' || key == 'C') collisionStrength = std::max(100.0f, collisionStrength - 100.0f);
    else if (key == 'v' || key == 'V') collisionStrength = std::min(6000.0f, collisionStrength + 100.0f);
    else if (key == 'r' || key == 'R') { initShapes(); simTime = 0.0f; }
}

void ofApp::mousePressed(int x, int y, int button) {
    (void)button;
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
