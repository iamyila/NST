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
    applyPeriodicBlinkControls();
    loadPresetFile();
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
        MotionBounds b = getMotionBounds(80.0f);
        s.pos = glm::vec2(ofRandom(b.minX, b.maxX), ofRandom(b.minY, b.maxY));
        s.vel = glm::vec2(ofRandomf(), ofRandomf()) * ofRandom(50.0f, 120.0f);
        s.walkDir = glm::normalize(glm::vec2(ofRandomf(), ofRandomf()));
        if (glm::length(s.walkDir) < 0.0001f) s.walkDir = glm::vec2(1.0f, 0.0f);

        s.radius = ofRandom(18.0f, 48.0f);
        s.motion = (i % 2 == 0) ? MotionType::Brownian : MotionType::Drunkard;
        s.bRect = (i % 3 == 0);

        s.blinkPeriodSec = ofRandom(2.0f, 5.2f);
        s.blinkDuty = ofRandom(0.62f, 0.90f);
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
    const glm::vec2 frameCenter(static_cast<float>(frameW) * 0.5f, static_cast<float>(frameH) * 0.5f);
    glm::vec2 magnetTarget = frameCenter;
    glm::vec2 activeCentroid = frameCenter;
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
    const float collisionScale = magnetMode ? 0.35f : 1.0f;
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
    const int limit = bUseBrownianDrunkMotion ? static_cast<int>(shapes.size()) : std::min(5, static_cast<int>(shapes.size()));
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
    // Shape simulation now drives both motion modes.
    updateShapes(dt);

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
        " | Magnet: " + std::string(magnetMode ? ("On@" + ofToString(magnetStrength, 0)) : "Off") +
        " | Physics: " + std::string(collisionPhysics ? "On" : "Off") +
        " | Coll: " + ofToString(collisionStrength, 0) +
        " | Blink: " + std::string(airHockeyMode ? "Inertia Respawn" : (naturalBlink ? "Natural" : "Periodic")) +
        " | N:" + std::string(naturalBlink ? "Natural" : "Periodic"),
        20, 144
    );
    if (!manualBlobInput.empty()) {
        ofDrawBitmapStringHighlight("Manual blob input: " + manualBlobInput + " (press Enter)", 20, 164);
    }
    ofDrawBitmapStringHighlight("Mode: [m] normal/brownian, [h] air-hockey, [n] natural/periodic blink", 20, 184);
    ofDrawBitmapStringHighlight("Count: [b] auto, [0-10]+Enter manual, [[]/[]] +/-1 blob", 20, 202);
    ofDrawBitmapStringHighlight("Motion: [k] magnet, [,/.] magnet strength, [p] physics, [c/v] collision strength", 20, 220);
    ofDrawBitmapStringHighlight("Bounds: [e] edge bounce, [d] dead-zone on/off, [z/x] dead-zone size, [q] square bounds", 20, 238);
    ofDrawBitmapStringHighlight("Transport: [space] pause, [+/-] speed, [r] reset, mouse-drag push", 20, 256);
    ofDrawBitmapStringHighlight("Presets: click LOAD/SAVE buttons (slots 1-4)", 20, 274);
    if (!presetStatus.empty() && ofGetElapsedTimef() <= presetStatusUntil) {
        ofDrawBitmapStringHighlight(presetStatus, 20, 292);
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
        naturalBlink = !naturalBlink;
        applyPeriodicBlinkControls();
        for (auto& s : shapes) {
            if (naturalBlink) {
                s.stateRemainingSec = randomHoldDuration(s.naturalOn);
            }
        }
    }
    else if (key == 'k' || key == 'K') magnetMode = !magnetMode;
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
    else if (key == ',') magnetStrength = std::max(50.0f, magnetStrength - 50.0f);
    else if (key == '.') magnetStrength = std::min(3000.0f, magnetStrength + 50.0f);
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
    p.autoBlobCount = autoBlobCount;
    p.manualBlobCount = manualBlobCount;
    p.edgeBounce = edgeBounce;
    p.squareMotionBounds = squareMotionBounds;
    p.deadZoneEnabled = deadZoneEnabled;
    p.centerDeadZoneNorm = centerDeadZoneNorm;
    p.collisionPhysics = collisionPhysics;
    p.collisionStrength = collisionStrength;
    p.naturalBlink = naturalBlink;
    p.onDutyControl = onDutyControl;
    p.blinkRateControl = blinkRateControl;
    p.magnetMode = magnetMode;
    p.magnetStrength = magnetStrength;
    return p;
}

void ofApp::applyPreset(const SenderPreset& p) {
    speed = p.speed;
    bUseBrownianDrunkMotion = p.bUseBrownianDrunkMotion;
    airHockeyMode = p.airHockeyMode;
    autoBlobCount = p.autoBlobCount;
    manualBlobCount = ofClamp(p.manualBlobCount, 0, 10);
    edgeBounce = p.edgeBounce;
    squareMotionBounds = p.squareMotionBounds;
    deadZoneEnabled = p.deadZoneEnabled;
    centerDeadZoneNorm = ofClamp(p.centerDeadZoneNorm, 0.0f, 0.45f);
    collisionPhysics = p.collisionPhysics;
    collisionStrength = ofClamp(p.collisionStrength, 100.0f, 6000.0f);
    naturalBlink = p.naturalBlink;
    onDutyControl = ofClamp(p.onDutyControl, 0.05f, 0.95f);
    blinkRateControl = ofClamp(p.blinkRateControl, 0.0f, 1.0f);
    magnetMode = p.magnetMode;
    magnetStrength = ofClamp(p.magnetStrength, 50.0f, 3000.0f);

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
        s["autoBlobCount"] = p.autoBlobCount;
        s["manualBlobCount"] = p.manualBlobCount;
        s["edgeBounce"] = p.edgeBounce;
        s["squareMotionBounds"] = p.squareMotionBounds;
        s["deadZoneEnabled"] = p.deadZoneEnabled;
        s["centerDeadZoneNorm"] = p.centerDeadZoneNorm;
        s["collisionPhysics"] = p.collisionPhysics;
        s["collisionStrength"] = p.collisionStrength;
        s["naturalBlink"] = p.naturalBlink;
        s["onDutyControl"] = p.onDutyControl;
        s["blinkRateControl"] = p.blinkRateControl;
        s["magnetMode"] = p.magnetMode;
        s["magnetStrength"] = p.magnetStrength;
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
        p.autoBlobCount = s.value("autoBlobCount", p.autoBlobCount);
        p.manualBlobCount = s.value("manualBlobCount", p.manualBlobCount);
        p.edgeBounce = s.value("edgeBounce", p.edgeBounce);
        p.squareMotionBounds = s.value("squareMotionBounds", p.squareMotionBounds);
        p.deadZoneEnabled = s.value("deadZoneEnabled", p.deadZoneEnabled);
        p.centerDeadZoneNorm = s.value("centerDeadZoneNorm", p.centerDeadZoneNorm);
        p.collisionPhysics = s.value("collisionPhysics", p.collisionPhysics);
        p.collisionStrength = s.value("collisionStrength", p.collisionStrength);
        p.naturalBlink = s.value("naturalBlink", p.naturalBlink);
        p.onDutyControl = s.value("onDutyControl", p.onDutyControl);
        p.blinkRateControl = s.value("blinkRateControl", p.blinkRateControl);
        p.magnetMode = s.value("magnetMode", p.magnetMode);
        p.magnetStrength = s.value("magnetStrength", p.magnetStrength);
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
