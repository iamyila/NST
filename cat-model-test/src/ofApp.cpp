#include "ofApp.h"

#include <fstream>
#include <limits>
#include <sstream>

namespace {
constexpr float kTargetCatHeight = 32.0f;
constexpr const char* kSnapshotPath = "/tmp/cat-model-test-snapshot.png";
constexpr const char* kDebugPath = "/tmp/cat-model-test-debug.txt";

int parseObjIndex(const std::string& token, std::size_t vertexCount) {
    const auto slashPos = token.find('/');
    const std::string raw = token.substr(0, slashPos);
    if (raw.empty()) {
        return -1;
    }

    const int idx = std::stoi(raw);
    if (idx > 0) {
        return idx - 1;
    }
    if (idx < 0) {
        return static_cast<int>(vertexCount) + idx;
    }
    return -1;
}
}

void ofApp::setup() {
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofBackground(10, 10, 14);

    cam.setDistance(78.0f);
    cam.setNearClip(0.1f);
    cam.setFarClip(500.0f);
    cam.setTarget(glm::vec3(0.0f, 12.0f, 0.0f));
    cam.disableMouseInput();
    cam.setPosition(glm::vec3(0.0f, 24.0f, 68.0f));

    catLoaded = loadCatObj();
    snapshotSaved = false;
}

bool ofApp::loadCatObj() {
    catMesh.clear();
    catMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    loadedPath.clear();
    catMin = glm::vec3(std::numeric_limits<float>::max());
    catMax = glm::vec3(std::numeric_limits<float>::lowest());
    catHeight = 1.0f;

    const auto exeDir = ofFilePath::getCurrentExeDir();
    const std::vector<of::filesystem::path> candidatePaths = {
        ofToDataPath("catsit.obj", true),
        ofToDataPath("models/catsit.obj", true),
        ofFilePath::join(exeDir, "../Resources/data/catsit.obj"),
        ofFilePath::join(exeDir, "../Resources/data/models/catsit.obj"),
        ofFilePath::join(exeDir, "../../../data/catsit.obj"),
        ofFilePath::join(exeDir, "../../../data/models/catsit.obj"),
        "/Users/alastairmcneill/Documents/GitHub/NST/NDI-test-sender-3d/bin/data/models/catsit.obj",
    };

    std::string objPath;
    for (const auto& candidate : candidatePaths) {
        if (ofFile::doesFileExist(candidate)) {
            objPath = candidate.string();
            break;
        }
    }

    if (objPath.empty()) {
        writeDebugFile("not-found");
        return false;
    }

    ofBuffer buffer = ofBufferFromFile(objPath);
    if (buffer.size() == 0) {
        loadedPath = objPath;
        writeDebugFile("empty-buffer");
        return false;
    }

    std::vector<glm::vec3> vertices;
    vertices.reserve(250000);

    for (const auto& rawLine : buffer.getLines()) {
        if (rawLine.size() < 2) {
            continue;
        }

        if (rawLine.rfind("v ", 0) == 0) {
            std::istringstream iss(rawLine.substr(2));
            glm::vec3 v;
            if (!(iss >> v.x >> v.y >> v.z)) {
                continue;
            }
            vertices.push_back(v);
            catMin = glm::min(catMin, v);
            catMax = glm::max(catMax, v);
            continue;
        }

        if (rawLine.rfind("f ", 0) == 0) {
            std::istringstream iss(rawLine.substr(2));
            std::vector<int> face;
            std::string token;
            while (iss >> token) {
                try {
                    const int idx = parseObjIndex(token, vertices.size());
                    if (idx >= 0 && static_cast<std::size_t>(idx) < vertices.size()) {
                        face.push_back(idx);
                    }
                } catch (...) {
                }
            }

            if (face.size() < 3) {
                continue;
            }

            for (std::size_t i = 1; i + 1 < face.size(); ++i) {
                catMesh.addVertex(vertices[face[0]]);
                catMesh.addVertex(vertices[face[i]]);
                catMesh.addVertex(vertices[face[i + 1]]);
            }
        }
    }

    loadedPath = objPath;
    if (catMesh.getNumVertices() == 0 || vertices.empty()) {
        writeDebugFile("no-geometry");
        return false;
    }

    catHeight = std::max(0.001f, catMax.y - catMin.y);
    writeDebugFile("ok");
    return true;
}

void ofApp::writeDebugFile(const std::string& status) const {
    std::ofstream dbg(kDebugPath, std::ios::out | std::ios::trunc);
    dbg << "status=" << status << "\n";
    dbg << "path=" << loadedPath << "\n";
    dbg << "vertices=" << catMesh.getNumVertices() << "\n";
    dbg << "boundsMin=" << catMin.x << "," << catMin.y << "," << catMin.z << "\n";
    dbg << "boundsMax=" << catMax.x << "," << catMax.y << "," << catMax.z << "\n";
    dbg << "catHeight=" << catHeight << "\n";
    dbg << "loaded=" << (catLoaded ? 1 : 0) << "\n";
}

void ofApp::update() {
    turntableDeg = std::fmod(ofGetElapsedTimef() * 12.0f, 360.0f);
}

void ofApp::drawFallbackCat() const {
    ofPushMatrix();
    ofSetColor(255, 182, 197);
    ofDrawBox(0.0f, 9.0f, 0.0f, 12.0f, 8.0f, 22.0f);
    ofDrawBox(0.0f, 13.0f, -13.0f, 8.0f, 7.0f, 8.0f);
    ofDrawCone(-2.0f, 17.0f, -15.0f, 2.5f, 5.0f);
    ofDrawCone(2.0f, 17.0f, -15.0f, 2.5f, 5.0f);
    ofDrawCylinder(-4.0f, 3.5f, -7.0f, 1.2f, 7.0f);
    ofDrawCylinder(4.0f, 3.5f, -7.0f, 1.2f, 7.0f);
    ofDrawCylinder(-4.0f, 3.5f, 7.0f, 1.2f, 7.0f);
    ofDrawCylinder(4.0f, 3.5f, 7.0f, 1.2f, 7.0f);
    ofDrawCylinder(0.0f, 12.0f, 13.0f, 0.7f, 12.0f);
    ofPopMatrix();
}

void ofApp::draw() {
    ofBackground(10, 10, 14);

    ofEnableDepthTest();
    cam.begin();

    ofPushMatrix();
    ofSetColor(25, 30, 38);
    ofRotateDeg(90.0f, 1.0f, 0.0f, 0.0f);
    ofDrawPlane(0.0f, 0.0f, 140.0f, 140.0f);
    ofPopMatrix();

    ofPushMatrix();
    ofRotateDeg(turntableDeg, 0.0f, 1.0f, 0.0f);

    if (catLoaded) {
        const float scale = kTargetCatHeight / std::max(0.001f, catHeight);
        const float centerX = 0.5f * (catMin.x + catMax.x);
        const float centerZ = 0.5f * (catMin.z + catMax.z);

        ofScale(scale, scale, scale);
        ofTranslate(-centerX, -catMin.y, -centerZ);

        ofSetColor(255, 184, 206, 255);
        catMesh.drawFaces();

        ofNoFill();
        ofSetColor(45, 22, 28, 220);
        catMesh.drawWireframe();
        ofFill();
    } else {
        drawFallbackCat();
    }

    ofPopMatrix();
    cam.end();
    ofDisableDepthTest();

    if (!snapshotSaved && ofGetFrameNum() >= 30) {
        ofSaveScreen(kSnapshotPath);
        snapshotSaved = true;
    }
}

void ofApp::keyPressed(int key) {
    if (key == 'r' || key == 'R') {
        catLoaded = loadCatObj();
        snapshotSaved = false;
    }
}
