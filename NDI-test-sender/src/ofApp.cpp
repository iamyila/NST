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

    initShapes();
}

void ofApp::initShapes() {
    shapes.clear();
    shapes.reserve(10);

    for (int i = 0; i < 10; ++i) {
        MovingShape s;
        s.pos = glm::vec2(
            ofRandom(80.0f, static_cast<float>(frameW - 80)),
            ofRandom(80.0f, static_cast<float>(frameH - 80))
        );
        s.vel = glm::vec2(ofRandomf(), ofRandomf()) * ofRandom(50.0f, 120.0f);
        s.walkDir = glm::normalize(glm::vec2(ofRandomf(), ofRandomf()));
        if (glm::length(s.walkDir) < 0.0001f) {
            s.walkDir = glm::vec2(1.0f, 0.0f);
        }
        s.radius = ofRandom(18.0f, 48.0f);
        s.motion = (i % 2 == 0) ? MotionType::Brownian : MotionType::Drunkard;
        s.bRect = (i % 3 == 0);
        s.blinkPeriodSec = ofRandom(1.2f, 3.8f);
        s.blinkDuty = ofRandom(0.35f, 0.75f);
        s.blinkPhaseSec = ofRandom(0.0f, s.blinkPeriodSec);

        // bright test colors for easier visual tracking
        float hue = fmodf(i * 27.0f, 255.0f);
        s.color = ofColor::fromHsb(static_cast<unsigned char>(hue), 220, 255);
        shapes.push_back(s);
    }
}

bool ofApp::isShapeOn(const MovingShape& shape) const {
    if (shape.blinkPeriodSec <= 0.0001f) return true;
    float t = fmodf(simTime + shape.blinkPhaseSec, shape.blinkPeriodSec);
    return t < (shape.blinkPeriodSec * shape.blinkDuty);
}

void ofApp::keepInsideFrame(MovingShape& shape) {
    const float minX = shape.radius;
    const float maxX = static_cast<float>(frameW) - shape.radius;
    const float minY = shape.radius;
    const float maxY = static_cast<float>(frameH) - shape.radius;

    if (shape.pos.x < minX) {
        shape.pos.x = minX;
        shape.vel.x = std::abs(shape.vel.x);
        shape.walkDir.x = std::abs(shape.walkDir.x);
    } else if (shape.pos.x > maxX) {
        shape.pos.x = maxX;
        shape.vel.x = -std::abs(shape.vel.x);
        shape.walkDir.x = -std::abs(shape.walkDir.x);
    }

    if (shape.pos.y < minY) {
        shape.pos.y = minY;
        shape.vel.y = std::abs(shape.vel.y);
        shape.walkDir.y = std::abs(shape.walkDir.y);
    } else if (shape.pos.y > maxY) {
        shape.pos.y = maxY;
        shape.vel.y = -std::abs(shape.vel.y);
        shape.walkDir.y = -std::abs(shape.walkDir.y);
    }
}

void ofApp::updateShapes(float dt) {
    if (dt <= 0.0f) return;

    for (auto& s : shapes) {
        if (s.motion == MotionType::Brownian) {
            // Brownian: continuous random kicks with speed floor so motion stays visible.
            const glm::vec2 jitter(ofRandomf() * 900.0f, ofRandomf() * 900.0f);
            const glm::vec2 toCenter(
                static_cast<float>(frameW) * 0.5f - s.pos.x,
                static_cast<float>(frameH) * 0.5f - s.pos.y
            );
            s.vel += (jitter + toCenter * 0.35f) * dt;
            s.vel *= std::pow(0.985f, dt * 60.0f);

            float spd = glm::length(s.vel);
            if (spd < 70.0f) {
                if (spd < 0.0001f) {
                    s.vel = glm::vec2(1.0f, 0.0f) * 70.0f;
                } else {
                    s.vel = glm::normalize(s.vel) * 70.0f;
                }
            } else if (spd > 260.0f) {
                s.vel = glm::normalize(s.vel) * 260.0f;
            }
            s.pos += s.vel * dt;
        } else {
            // Persistent drunkard walk: mostly keep direction, occasionally turn.
            float turnChance = ofClamp(0.08f * dt * 60.0f, 0.0f, 1.0f);
            if (ofRandomuf() < turnChance) {
                float turnDeg = ofRandom(-70.0f, 70.0f);
                float rad = glm::radians(turnDeg);
                float c = cosf(rad);
                float sn = sinf(rad);
                glm::vec2 d = s.walkDir;
                s.walkDir = glm::vec2(
                    d.x * c - d.y * sn,
                    d.x * sn + d.y * c
                );
            }

            if (glm::length(s.walkDir) < 0.0001f) {
                s.walkDir = glm::vec2(1.0f, 0.0f);
            } else {
                s.walkDir = glm::normalize(s.walkDir);
            }

            float walkSpeed = 120.0f + 0.9f * s.radius;
            s.vel = s.walkDir * walkSpeed;
            s.pos += s.vel * dt;
        }

        keepInsideFrame(s);
    }
}

void ofApp::renderFrame() {
    fbo.begin();
    ofClear(10, 10, 14, 255);

    ofPushStyle();
    int considered = 0;

    if (bUseBrownianDrunkMotion) {
        for (int i = 0; i < static_cast<int>(shapes.size()); ++i) {
            if (considered >= activeBlobLimit) break;
            considered++;

            const auto& s = shapes[i];
            if (!isShapeOn(s)) {
                continue; // Candidate exists but is currently "off".
            }

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
        // Repeatable 0..N blob-count pattern so note-off behavior is testable.
        static const int seq[] = {0, 1, 2, 4, 6, 3, 0, 5, 2};
        const int phase = static_cast<int>(simTime / 1.1f) % static_cast<int>(sizeof(seq) / sizeof(seq[0]));
        activeBlobLimit = std::min(seq[phase], maxBlobs);
    } else {
        activeBlobLimit = ofClamp(manualBlobCount, 0, maxBlobs);
    }

    if (bUseBrownianDrunkMotion) {
        updateShapes(dt);
    }
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
        std::string("Motion: ") + (bUseBrownianDrunkMotion ? "Brownian + Drunkard (10 shapes)" : "Normal"),
        20, 64
    );
    ofDrawBitmapStringHighlight("Shapes pulse on/off automatically", 20, 84);
    ofDrawBitmapStringHighlight("Time: " + ofToString(simTime, 2), 20, 104);
    ofDrawBitmapStringHighlight(
        "Blob count: " + ofToString(activeBlobLimit) + (autoBlobCount ? " (auto)" : " (manual)"),
        20, 124
    );
    if (!manualBlobInput.empty()) {
        ofDrawBitmapStringHighlight("Manual blob input: " + manualBlobInput + " (press Enter)", 20, 144);
    }
    ofDrawBitmapStringHighlight("Keys: m motion, b auto blobs, type 0-10 + Enter, [ ] count, +/- speed, space pause, r reset", 20, 164);
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
        if (manualBlobInput.size() < 2) {
            manualBlobInput.push_back(static_cast<char>(key));
        }
        return;
    }

    if (key == OF_KEY_BACKSPACE || key == OF_KEY_DEL) {
        if (!manualBlobInput.empty()) {
            manualBlobInput.pop_back();
        }
        return;
    }

    if (key == OF_KEY_RETURN) {
        commitManualBlobInput();
        return;
    }

    if (key == OF_KEY_ESC) {
        manualBlobInput.clear();
        return;
    }

    if (key == ' ') {
        paused = !paused;
        return;
    }

    if (key == '+' || key == '=') {
        speed = std::min(4.0f, speed + 0.1f);
    } else if (key == '-' || key == '_') {
        speed = std::max(0.1f, speed - 0.1f);
    } else if (key == 'b' || key == 'B') {
        autoBlobCount = !autoBlobCount;
    } else if (key == 'm' || key == 'M') {
        bUseBrownianDrunkMotion = !bUseBrownianDrunkMotion;
        if (bUseBrownianDrunkMotion) {
            initShapes();
        }
    } else if (key == ']') {
        manualBlobCount = std::min(10, manualBlobCount + 1);
        autoBlobCount = false;
    } else if (key == '[') {
        manualBlobCount = std::max(0, manualBlobCount - 1);
        autoBlobCount = false;
    } else if (key == 'r' || key == 'R') {
        initShapes();
        simTime = 0.0f;
    }
}
