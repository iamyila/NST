#include "ofApp.h"
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <limits>
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
        case ofApp::ObjectPreset::Cats: return "Cats";
        case ofApp::ObjectPreset::Dogs: return "Dogs";
        case ofApp::ObjectPreset::PlainObjects: return "Cubes";
        case ofApp::ObjectPreset::Cars: return "Cars";
    }
    return "Mixed";
}

const char* objectKindLabel(ofApp::ObjectKind kind) {
    switch (kind) {
        case ofApp::ObjectKind::Person: return "person";
        case ofApp::ObjectKind::Hand: return "hand";
        case ofApp::ObjectKind::Cat: return "cat";
        case ofApp::ObjectKind::Dog: return "dog";
        case ofApp::ObjectKind::PlainObject: return "object";
        case ofApp::ObjectKind::Car: return "car";
    }
    return "object";
}

double wallTimeSeconds() {
    const auto now = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration<double>(now).count();
}

ofApp::ObjectKind objectKindForPreset(ofApp::ObjectPreset preset, int index) {
    switch (preset) {
        case ofApp::ObjectPreset::People: return ofApp::ObjectKind::Person;
        case ofApp::ObjectPreset::Hands: return ofApp::ObjectKind::Hand;
        case ofApp::ObjectPreset::Cats: return ofApp::ObjectKind::Cat;
        case ofApp::ObjectPreset::Dogs: return ofApp::ObjectKind::Dog;
        case ofApp::ObjectPreset::PlainObjects: return ofApp::ObjectKind::PlainObject;
        case ofApp::ObjectPreset::Cars: return ofApp::ObjectKind::Car;
        case ofApp::ObjectPreset::Mixed:
        default: {
            const ofApp::ObjectKind kinds[] = {
                ofApp::ObjectKind::Person,
                ofApp::ObjectKind::Cat,
                ofApp::ObjectKind::Car,
                ofApp::ObjectKind::Dog,
                ofApp::ObjectKind::Hand,
                ofApp::ObjectKind::PlainObject,
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

int parseObjIndex(const std::string& token, std::size_t vertexCount) {
    const auto slashPos = token.find('/');
    const std::string raw = token.substr(0, slashPos);
    if (raw.empty()) return -1;

    const int idx = std::stoi(raw);
    if (idx > 0) return idx - 1;
    if (idx < 0) return static_cast<int>(vertexCount) + idx;
    return -1;
}

int parseObjComponentIndex(const std::string& raw, std::size_t count) {
    if (raw.empty()) return -1;

    const int idx = std::stoi(raw);
    if (idx > 0) return idx - 1;
    if (idx < 0) return static_cast<int>(count) + idx;
    return -1;
}

struct ObjFaceRef {
    int vertex = -1;
    int texcoord = -1;
};

ObjFaceRef parseObjFaceRef(const std::string& token, std::size_t vertexCount, std::size_t texCoordCount) {
    ObjFaceRef ref;
    const auto firstSlash = token.find('/');
    if (firstSlash == std::string::npos) {
        ref.vertex = parseObjComponentIndex(token, vertexCount);
        return ref;
    }

    ref.vertex = parseObjComponentIndex(token.substr(0, firstSlash), vertexCount);
    const auto secondSlash = token.find('/', firstSlash + 1);
    if (secondSlash == std::string::npos) {
        ref.texcoord = parseObjComponentIndex(token.substr(firstSlash + 1), texCoordCount);
    } else if (secondSlash > firstSlash + 1) {
        ref.texcoord = parseObjComponentIndex(token.substr(firstSlash + 1, secondSlash - firstSlash - 1), texCoordCount);
    }
    return ref;
}

bool loadTexturedObjAsset(const std::vector<of::filesystem::path>& objCandidatePaths,
                         const std::string& logLabel,
                         ofVboMesh& mesh,
                         ofImage& texture,
                         bool& textureLoaded,
                         glm::vec3& modelMin,
                         glm::vec3& modelMax,
                         float& modelHeight,
                         float& modelDepth) {
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    texture.clear();
    textureLoaded = false;
    modelMin = glm::vec3(std::numeric_limits<float>::max());
    modelMax = glm::vec3(std::numeric_limits<float>::lowest());
    modelHeight = 1.0f;
    modelDepth = 1.0f;

    std::string objPath;
    for (const auto& candidate : objCandidatePaths) {
        if (ofFile::doesFileExist(candidate)) {
            objPath = candidate.string();
            break;
        }
    }

    if (objPath.empty()) return false;

    ofBuffer buffer = ofBufferFromFile(objPath);
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    std::vector<std::array<ObjFaceRef, 3>> triangles;
    std::string mtllibName;
    vertices.reserve(250000);
    texCoords.reserve(250000);
    triangles.reserve(250000);

    for (const auto& rawLine : buffer.getLines()) {
        if (rawLine.size() < 2) continue;

        if (rawLine.rfind("mtllib ", 0) == 0) {
            mtllibName = rawLine.substr(7);
            continue;
        }

        if (rawLine.rfind("v ", 0) == 0) {
            std::istringstream iss(rawLine.substr(2));
            glm::vec3 v;
            if (!(iss >> v.x >> v.y >> v.z)) continue;
            vertices.push_back(v);
            modelMin = glm::min(modelMin, v);
            modelMax = glm::max(modelMax, v);
            continue;
        }

        if (rawLine.rfind("vt ", 0) == 0) {
            std::istringstream iss(rawLine.substr(3));
            glm::vec2 vt;
            if (!(iss >> vt.x >> vt.y)) continue;
            texCoords.push_back(vt);
            continue;
        }

        if (rawLine.rfind("f ", 0) == 0) {
            std::istringstream iss(rawLine.substr(2));
            std::vector<ObjFaceRef> face;
            std::string token;
            while (iss >> token) {
                try {
                    const ObjFaceRef ref = parseObjFaceRef(token, vertices.size(), texCoords.size());
                    if (ref.vertex >= 0 && static_cast<std::size_t>(ref.vertex) < vertices.size()) {
                        face.push_back(ref);
                    }
                } catch (...) {
                }
            }

            if (face.size() < 3) continue;
            for (std::size_t i = 1; i + 1 < face.size(); ++i) {
                triangles.push_back({face[0], face[i], face[i + 1]});
            }
        }
    }

    std::filesystem::path texturePath;
    if (!mtllibName.empty()) {
        const std::filesystem::path objFilePath(objPath);
        const std::filesystem::path mtlPath = objFilePath.parent_path() / mtllibName;
        if (ofFile::doesFileExist(mtlPath)) {
            ofBuffer mtlBuffer = ofBufferFromFile(mtlPath.string());
            for (const auto& rawLine : mtlBuffer.getLines()) {
                if (rawLine.rfind("map_Kd ", 0) == 0) {
                    texturePath = mtlPath.parent_path() / rawLine.substr(7);
                    break;
                }
            }
        }
    }

    if (!texturePath.empty() && ofFile::doesFileExist(texturePath)) {
        textureLoaded = texture.load(texturePath.string());
        if (textureLoaded) {
            texture.getTexture().setTextureMinMagFilter(GL_LINEAR, GL_LINEAR);
        }
    }

    if (!triangles.empty() && !vertices.empty()) {
        for (const auto& tri : triangles) {
            for (const auto& ref : tri) {
                mesh.addVertex(vertices[ref.vertex]);
                if (textureLoaded && ref.texcoord >= 0 && static_cast<std::size_t>(ref.texcoord) < texCoords.size()) {
                    const glm::vec2 uv = texCoords[ref.texcoord];
                    mesh.addTexCoord(glm::vec2(
                        uv.x * static_cast<float>(texture.getWidth()),
                        (1.0f - uv.y) * static_cast<float>(texture.getHeight())
                    ));
                }
            }
        }
    }

    if (mesh.getNumVertices() > 0 && !vertices.empty()) {
        mesh.setUsage(GL_STATIC_DRAW);
        modelHeight = std::max(0.001f, modelMax.y - modelMin.y);
        modelDepth = std::max(0.001f, modelMax.z - modelMin.z);
        ofLogNotice("ofApp") << "Loaded " << logLabel << " OBJ: " << objPath
                             << " verts=" << mesh.getNumVertices()
                             << " textured=" << (textureLoaded ? "yes" : "no")
                             << " boundsMin=" << modelMin
                             << " boundsMax=" << modelMax;
        return true;
    }

    return false;
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
        const float worldRadius = shapeWorldCollisionRadius(s);
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

namespace {
constexpr const char* kSenderSnapshotPath = "/tmp/ndi-test-sender-3d-snapshot.png";
}

void ofApp::setup() {
    ofSetFrameRate(30);
    ofBackground(16);
    setupTruthLog();

    ofFbo::Settings fboSettings;
    fboSettings.width = frameW;
    fboSettings.height = frameH;
    fboSettings.internalformat = GL_RGBA;
    fboSettings.useDepth = true;
    fboSettings.depthStencilAsTexture = false;
    fboSettings.textureTarget = GL_TEXTURE_2D;
    fbo.allocate(fboSettings);
    fbo.begin();
    ofClear(0, 0, 0, 255);
    fbo.end();

    if (!ndiSender.setup(streamName)) {
        ofLogError("ofApp") << "Failed to set up NDI sender: " << streamName;
    } else {
        ndiVideo.setup(ndiSender);
        ndiVideo.setAsync(true);
        ndiVideo.setFrameRate(static_cast<int>(ndiSendTargetFps), 1);
        ofLogNotice("ofApp") << "NDI sender ready: " << streamName;
    }

    initShapes();
    loadCatModel();
    loadPersonModel();
    loadCarModel();
    applyPeriodicBlinkControls();
    loadPresetFile();
    setupMidiInput();
    startupSnapshotSaved = false;
}

void ofApp::setupTruthLog() {
    const char* path = std::getenv("NST_SENDER_TRUTH_PATH");
    if (!path || path[0] == '\0') {
        truthLogEnabled = false;
        return;
    }

    truthLog.open(path, std::ios::out | std::ios::trunc);
    truthLogEnabled = truthLog.is_open();
    if (!truthLogEnabled) {
        ofLogWarning("ofApp") << "Unable to open sender truth log: " << path;
        return;
    }

    truthLog
        << std::fixed << std::setprecision(6)
        << "wall_time,frame,index,kind,x,y,radius,depth,active_blob_limit,visible_count\n";
}

void ofApp::writeTruthLog(const std::vector<int>& visibleShapeIndices) {
    if (!truthLogEnabled || !truthLog.is_open()) return;

    const double now = wallTimeSeconds();
    const int frame = ofGetFrameNum();
    const int visibleCount = static_cast<int>(visibleShapeIndices.size());
    for (const int idx : visibleShapeIndices) {
        if (idx < 0 || idx >= static_cast<int>(shapes.size())) continue;
        const MovingShape& s = shapes[idx];

        glm::vec2 projected;
        float cameraDepth = 0.0f;
        if (!projectWorldPoint(shapeWorldPoint(s), projected, &cameraDepth)) continue;

        truthLog
            << now << ','
            << frame << ','
            << idx << ','
            << objectKindLabel(s.objectKind) << ','
            << (projected.x / static_cast<float>(frameW)) << ','
            << (projected.y / static_cast<float>(frameH)) << ','
            << (projectRadius(s) / static_cast<float>(std::min(frameW, frameH))) << ','
            << cameraDepth << ','
            << activeBlobLimit << ','
            << visibleCount << '\n';
    }
    truthLog.flush();
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

void ofApp::loadCatModel() {
    catObjLoaded = false;
    catObjTextureLoaded = false;
    catModelLoaded = false;
    catModelMeshes.clear();

    const auto exeDir = ofFilePath::getCurrentExeDir();
    const std::vector<of::filesystem::path> objCandidatePaths = {
        ofToDataPath("models/Meshy_AI_standing_cat_0328230256_texture_obj/Meshy_AI_standing_cat_0328230256_texture.obj", true),
        ofToDataPath("models/Meshy_AI_Sitting_orange_tabby__0328134407_texture_obj/Meshy_AI_Sitting_orange_tabby__0328134407_texture.obj", true),
        ofToDataPath("catsit.obj", true),
        ofToDataPath("cat.obj", true),
        ofToDataPath("models/catsit.obj", true),
        ofToDataPath("models/cat.obj", true),
        ofFilePath::join(exeDir, "../Resources/data/models/Meshy_AI_standing_cat_0328230256_texture_obj/Meshy_AI_standing_cat_0328230256_texture.obj"),
        ofFilePath::join(exeDir, "../Resources/data/models/Meshy_AI_Sitting_orange_tabby__0328134407_texture_obj/Meshy_AI_Sitting_orange_tabby__0328134407_texture.obj"),
        ofFilePath::join(exeDir, "../Resources/data/catsit.obj"),
        ofFilePath::join(exeDir, "../Resources/data/cat.obj"),
        ofFilePath::join(exeDir, "../Resources/data/models/catsit.obj"),
        ofFilePath::join(exeDir, "../Resources/data/models/cat.obj"),
        ofFilePath::join(exeDir, "../../../data/models/Meshy_AI_standing_cat_0328230256_texture_obj/Meshy_AI_standing_cat_0328230256_texture.obj"),
        ofFilePath::join(exeDir, "../../../data/models/Meshy_AI_Sitting_orange_tabby__0328134407_texture_obj/Meshy_AI_Sitting_orange_tabby__0328134407_texture.obj"),
        ofFilePath::join(exeDir, "../../../data/catsit.obj"),
        ofFilePath::join(exeDir, "../../../data/cat.obj"),
        ofFilePath::join(exeDir, "../../../data/models/catsit.obj"),
        ofFilePath::join(exeDir, "../../../data/models/cat.obj"),
    };

    catObjLoaded = loadTexturedObjAsset(objCandidatePaths, "cat", catObjMesh, catObjTexture, catObjTextureLoaded,
                                        catModelMin, catModelMax, catModelHeight, catModelDepth);
    if (catObjLoaded) return;

    catModelMin = glm::vec3(0.0f);
    catModelMax = glm::vec3(0.0f);
    const std::vector<of::filesystem::path> glbCandidatePaths = {
        ofToDataPath("catsit.glb", true),
        ofToDataPath("cat.glb", true),
        ofToDataPath("models/catsit.glb", true),
        ofToDataPath("models/cat.glb", true),
        ofFilePath::join(exeDir, "../Resources/data/catsit.glb"),
        ofFilePath::join(exeDir, "../Resources/data/cat.glb"),
        ofFilePath::join(exeDir, "../Resources/data/models/catsit.glb"),
        ofFilePath::join(exeDir, "../Resources/data/models/cat.glb"),
        ofFilePath::join(exeDir, "../../../data/catsit.glb"),
        ofFilePath::join(exeDir, "../../../data/cat.glb"),
        ofFilePath::join(exeDir, "../../../data/models/catsit.glb"),
        ofFilePath::join(exeDir, "../../../data/models/cat.glb"),
    };

    of::filesystem::path catPath;
    for (const auto& candidate : glbCandidatePaths) {
        if (ofFile::doesFileExist(candidate)) {
            catPath = candidate;
            break;
        }
    }

    if (catPath.empty()) {
        std::ostringstream oss;
        oss << "Cat model not found. Tried OBJ and GLB paths.";
        ofLogWarning("ofApp") << oss.str();
        return;
    }

    catModel.setScaleNormalization(false);
    if (!catModel.load(catPath, ofxAssimpModelLoader::OPTIMIZE_DEFAULT)) {
        ofLogError("ofApp") << "Failed to load cat model: " << catPath;
        return;
    }

    catModelLoaded = true;
    catModelMeshes.clear();
    for (int i = 0; i < catModel.getNumMeshes(); ++i) {
        catModelMeshes.push_back(catModel.getMesh(i));
    }

    if (catModelMeshes.empty()) {
        catModelLoaded = false;
        ofLogError("ofApp") << "Cat model loaded but contained no meshes: " << catPath;
        return;
    }

    catModelMin = glm::vec3(std::numeric_limits<float>::max());
    catModelMax = glm::vec3(std::numeric_limits<float>::lowest());
    for (const auto& mesh : catModelMeshes) {
        for (const auto& v : mesh.getVertices()) {
            catModelMin = glm::min(catModelMin, v);
            catModelMax = glm::max(catModelMax, v);
        }
    }
    catModelHeight = std::max(0.001f, catModelMax.y - catModelMin.y);
    catModelDepth = std::max(0.001f, catModelMax.z - catModelMin.z);
}

void ofApp::loadPersonModel() {
    personObjLoaded = false;
    personObjTextureLoaded = false;
    const auto exeDir = ofFilePath::getCurrentExeDir();
    const std::vector<of::filesystem::path> objCandidatePaths = {
        ofToDataPath("models/MAn Meshy_AI_Open_Arms_0328134507_texture_obj/Meshy_AI_Open_Arms_0328134507_texture.obj", true),
        ofFilePath::join(exeDir, "../Resources/data/models/MAn Meshy_AI_Open_Arms_0328134507_texture_obj/Meshy_AI_Open_Arms_0328134507_texture.obj"),
        ofFilePath::join(exeDir, "../../../data/models/MAn Meshy_AI_Open_Arms_0328134507_texture_obj/Meshy_AI_Open_Arms_0328134507_texture.obj"),
    };
    personObjLoaded = loadTexturedObjAsset(objCandidatePaths, "person", personObjMesh, personObjTexture,
                                           personObjTextureLoaded, personModelMin, personModelMax,
                                           personModelHeight, personModelDepth);
}

void ofApp::loadCarModel() {
    carObjLoaded = false;
    carObjTextureLoaded = false;
    const auto exeDir = ofFilePath::getCurrentExeDir();
    const std::vector<of::filesystem::path> objCandidatePaths = {
        ofToDataPath("models/Car Meshy_AI_Crimson_Velocity_0328135326_texture_obj/Meshy_AI_Crimson_Velocity_0328135326_texture.obj", true),
        ofFilePath::join(exeDir, "../Resources/data/models/Car Meshy_AI_Crimson_Velocity_0328135326_texture_obj/Meshy_AI_Crimson_Velocity_0328135326_texture.obj"),
        ofFilePath::join(exeDir, "../../../data/models/Car Meshy_AI_Crimson_Velocity_0328135326_texture_obj/Meshy_AI_Crimson_Velocity_0328135326_texture.obj"),
    };
    carObjLoaded = loadTexturedObjAsset(objCandidatePaths, "car", carObjMesh, carObjTexture, carObjTextureLoaded,
                                        carModelMin, carModelMax, carModelHeight, carModelDepth);
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
        case ObjectKind::Cat:
            baseHeight = 0.0f;
            extraHeight = ofLerp(0.0f, 1.8f, 1.0f - s.depth);
            break;
        case ObjectKind::Dog:
            baseHeight = 0.0f;
            extraHeight = ofLerp(0.0f, 1.5f, 1.0f - s.depth);
            break;
        case ObjectKind::PlainObject:
            baseHeight = 0.0f;
            extraHeight = ofLerp(0.0f, 6.0f, 1.0f - s.depth);
            break;
        case ObjectKind::Car:
            baseHeight = 0.0f;
            extraHeight = ofLerp(0.0f, 1.0f, 1.0f - s.depth);
            break;
    }

    return glm::vec3(worldX, worldY, baseHeight + extraHeight);
}

float ofApp::shapeWorldCollisionRadius(const MovingShape& shape) const {
    const float genericRadius = ofMap(shape.radius, 18.0f, 48.0f, 3.8f, 12.5f, true);
    auto contactRadius = [](float width, float depth) {
        const float major = std::max(width, depth);
        const float minor = std::min(width, depth);
        return std::max(1.5f, major * 0.45f + minor * 0.10f);
    };

    switch (shape.objectKind) {
        case ObjectKind::Person:
            if (personObjLoaded) {
                const float scale = 0.5f * ofMap(shape.radius, 18.0f, 48.0f, 18.0f, 28.0f, true);
                const float width = std::max(0.001f, personModelMax.x - personModelMin.x) * scale;
                const float depth = std::max(0.001f, personModelDepth) * scale;
                return contactRadius(width, depth);
            }
            break;
        case ObjectKind::Cat:
            if (catObjLoaded || (catModelLoaded && !catModelMeshes.empty())) {
                const float catL = ofMap(shape.radius, 18.0f, 48.0f, 18.0f, 28.0f, true);
                const float scale = 0.5f * ((catL * 0.95f) / std::max(0.001f, catModelHeight));
                const float width = std::max(0.001f, catModelMax.x - catModelMin.x) * scale;
                const float depth = std::max(0.001f, catModelDepth) * scale;
                return contactRadius(width, depth);
            }
            break;
        case ObjectKind::Car:
            if (carObjLoaded) {
                const float scale = 0.5f * ofMap(shape.radius, 18.0f, 48.0f, 18.0f, 28.0f, true);
                const float width = std::max(0.001f, carModelMax.x - carModelMin.x) * scale;
                const float depth = std::max(0.001f, carModelDepth) * scale;
                return contactRadius(width, depth);
            }
            break;
        default:
            break;
    }

    return genericRadius;
}

glm::vec2 ofApp::velocityScreenToWorld(const glm::vec2& screenVel) const {
    return glm::vec2(
        screenVel.x * ((2.0f * kWorldSide) / static_cast<float>(frameW)),
        screenVel.y * ((kWorldNearY - kWorldFarY) / static_cast<float>(frameH))
    );
}

glm::vec2 ofApp::velocityWorldToScreen(const glm::vec2& worldVel) const {
    return glm::vec2(
        worldVel.x * (static_cast<float>(frameW) / (2.0f * kWorldSide)),
        worldVel.y * (static_cast<float>(frameH) / (kWorldNearY - kWorldFarY))
    );
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

void ofApp::drawCatGlyph(const glm::vec2& p, float size, float yawDeg) const {
    ofPushMatrix();
    ofTranslate(p);
    ofRotateDeg(yawDeg * 0.12f);

    const float bodyW = size * 1.10f;
    const float bodyH = size * 0.48f;
    const float headR = size * 0.20f;
    const float legTop = size * 0.10f;
    const float legBottom = size * 0.58f;

    ofDrawEllipse(0.0f, 0.0f, bodyW, bodyH);
    ofDrawCircle(size * 0.46f, -size * 0.15f, headR);
    ofDrawTriangle(size * 0.34f, -size * 0.28f, size * 0.42f, -size * 0.52f, size * 0.22f, -size * 0.34f);
    ofDrawTriangle(size * 0.54f, -size * 0.26f, size * 0.66f, -size * 0.48f, size * 0.44f, -size * 0.32f);

    ofSetLineWidth(std::max(2.0f, size * 0.06f));
    for (float lx : {-0.26f, -0.06f, 0.12f, 0.28f}) {
        ofDrawLine(size * lx, legTop, size * lx, legBottom);
    }

    ofDrawLine(-size * 0.46f, -size * 0.04f, -size * 0.70f, -size * 0.26f);
    ofDrawLine(-size * 0.70f, -size * 0.26f, -size * 0.82f, -size * 0.48f);

    const glm::vec2 nose(size * 0.66f, -size * 0.12f);
    ofDrawLine(nose.x - size * 0.02f, nose.y, nose.x + size * 0.10f, nose.y - size * 0.01f);
    ofDrawLine(nose.x - size * 0.02f, nose.y + size * 0.04f, nose.x + size * 0.12f, nose.y + size * 0.08f);
    ofDrawLine(nose.x - size * 0.02f, nose.y - size * 0.04f, nose.x + size * 0.12f, nose.y - size * 0.10f);
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
    ofRotateDeg(yawDeg * 0.18f);
    const glm::vec2 offset(size * 0.16f, -size * 0.14f);
    ofDrawRectangle(-size * 0.42f, -size * 0.42f, size * 0.84f, size * 0.84f);
    ofNoFill();
    ofSetLineWidth(std::max(2.0f, size * 0.05f));
    ofDrawRectangle(-size * 0.42f, -size * 0.42f, size * 0.84f, size * 0.84f);
    ofDrawRectangle(-size * 0.42f + offset.x, -size * 0.42f + offset.y, size * 0.84f, size * 0.84f);
    ofDrawLine(-size * 0.42f, -size * 0.42f, -size * 0.42f + offset.x, -size * 0.42f + offset.y);
    ofDrawLine(size * 0.42f, -size * 0.42f, size * 0.42f + offset.x, -size * 0.42f + offset.y);
    ofDrawLine(-size * 0.42f, size * 0.42f, -size * 0.42f + offset.x, size * 0.42f + offset.y);
    ofDrawLine(size * 0.42f, size * 0.42f, size * 0.42f + offset.x, size * 0.42f + offset.y);
    ofFill();
    ofPopMatrix();
}

void ofApp::drawShape3D(const MovingShape& s, int idx) {
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

    auto projectedPixelRadius = [&](const glm::vec3& c3, float worldR) {
        glm::vec2 c2, r2;
        if (projectWorldPoint(c3, c2, nullptr) && projectWorldPoint(c3 + glm::vec3(worldR, 0.0f, 0.0f), r2, nullptr)) {
            return std::max(2.0f, glm::distance(c2, r2));
        }
        if (projectWorldPoint(c3, c2, nullptr) && projectWorldPoint(c3 + glm::vec3(0.0f, 0.0f, worldR), r2, nullptr)) {
            return std::max(2.0f, glm::distance(c2, r2));
        }
        return 2.0f;
    };

    auto drawProjectedCircle = [&](const glm::vec3& c3, float worldR) {
        glm::vec2 c2;
        if (projectWorldPoint(c3, c2, nullptr)) {
            ofDrawCircle(c2, projectedPixelRadius(c3, worldR));
        }
    };

    auto drawProjectedTube = [&](const glm::vec3& a3, const glm::vec3& b3, float worldR, const ofColor& fillCol) {
        glm::vec2 a2, b2;
        if (!projectWorldPoint(a3, a2, nullptr) || !projectWorldPoint(b3, b2, nullptr)) return;
        glm::vec2 axis = b2 - a2;
        const float len = glm::length(axis);
        if (len < 0.001f) {
            ofSetColor(fillCol);
            ofDrawCircle(a2, projectedPixelRadius(a3, worldR));
            return;
        }
        glm::vec2 perp(-axis.y / len, axis.x / len);
        const float ra = projectedPixelRadius(a3, worldR);
        const float rb = projectedPixelRadius(b3, worldR);
        ofSetColor(fillCol);
        ofBeginShape();
        ofVertex(a2 + perp * ra);
        ofVertex(b2 + perp * rb);
        ofVertex(b2 - perp * rb);
        ofVertex(a2 - perp * ra);
        ofEndShape(true);
        ofDrawCircle(a2, ra);
        ofDrawCircle(b2, rb);
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
        glm::vec2 centroid(0.0f, 0.0f);
        for (const auto& p2 : screenPts) centroid += p2;
        centroid /= static_cast<float>(screenPts.size());

        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        mesh.addVertex(glm::vec3(centroid.x, centroid.y, 0.0f));
        for (const auto& p2 : screenPts) {
            mesh.addVertex(glm::vec3(p2.x, p2.y, 0.0f));
        }
        for (size_t i = 0; i < screenPts.size(); ++i) {
            const ofIndexType a = 0;
            const ofIndexType b = static_cast<ofIndexType>(i + 1);
            const ofIndexType c = static_cast<ofIndexType>(((i + 1) % screenPts.size()) + 1);
            mesh.addIndex(a);
            mesh.addIndex(b);
            mesh.addIndex(c);
        }
        ofSetColor(col);
        mesh.draw();
    };

    auto drawProjectedPrism = [&](const std::vector<glm::vec2>& footprint, float z0, float z1, const ofColor& sideCol, const ofColor& topCol) {
        if (footprint.size() < 3) return;
        std::vector<glm::vec3> bottom;
        std::vector<glm::vec3> top;
        bottom.reserve(footprint.size());
        top.reserve(footprint.size());
        for (const auto& pt : footprint) {
            bottom.emplace_back(pt.x, pt.y, z0);
            top.emplace_back(pt.x, pt.y, z1);
        }
        drawProjectedFill(top, topCol);
        for (size_t i = 0; i < footprint.size(); ++i) {
            const size_t j = (i + 1) % footprint.size();
            drawProjectedFill({bottom[i], bottom[j], top[j], top[i]}, sideCol);
        }
        drawProjectedLoop(bottom, true);
        drawProjectedLoop(top, true);
        for (size_t i = 0; i < footprint.size(); ++i) drawProjectedLine(bottom[i], top[i]);
    };

    auto makeOvalFootprint = [&](const glm::vec2& center2, float rx, float ry, int steps = 18) {
        std::vector<glm::vec2> pts;
        pts.reserve(steps);
        for (int i = 0; i < steps; ++i) {
            const float ang = glm::two_pi<float>() * static_cast<float>(i) / static_cast<float>(steps);
            pts.emplace_back(center2.x + std::cos(ang) * rx, center2.y + std::sin(ang) * ry);
        }
        return pts;
    };

    auto makeScaledFootprint = [&](const glm::vec2& center2, float sx, float sy, std::initializer_list<glm::vec2> unitPts) {
        std::vector<glm::vec2> pts;
        pts.reserve(unitPts.size());
        for (const auto& pt : unitPts) {
            pts.emplace_back(center2.x + pt.x * sx, center2.y + pt.y * sy);
        }
        return pts;
    };

    switch (s.objectKind) {
        case ObjectKind::Person: {
            if (drawPersonModel3D(s)) break;

            const float personHeight = ofMap(s.radius, 18.0f, 48.0f, 12.0f, 26.0f, true);
            const float legHalf = personHeight * 0.10f;
            const float shoulderHalf = personHeight * 0.16f;
            const float armReach = personHeight * 0.26f;
            const float shoulderZ = personHeight * 0.64f;
            const float hipZ = personHeight * 0.34f;
            const float headZ = personHeight * 0.88f;
            const float headR = personHeight * 0.11f;
            const float torsoHalfH = personHeight * 0.16f;
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

            const auto torsoFootprint = makeScaledFootprint(
                glm::vec2(worldPoint.x, worldPoint.y),
                personHeight * 0.34f,
                personHeight * 0.28f,
                {
                    {-0.62f, 0.24f}, {-0.78f, 0.02f}, {-0.64f, -0.28f},
                    {-0.24f, -0.58f}, {0.24f, -0.58f}, {0.64f, -0.28f},
                    {0.78f, 0.02f}, {0.62f, 0.24f}, {0.30f, 0.42f}, {-0.30f, 0.42f}
                }
            );
            const auto hipFootprint = makeScaledFootprint(
                glm::vec2(worldPoint.x, worldPoint.y + personHeight * 0.03f),
                personHeight * 0.28f,
                personHeight * 0.18f,
                {
                    {-0.72f, 0.28f}, {-0.50f, -0.30f}, {0.50f, -0.30f}, {0.72f, 0.28f},
                    {0.30f, 0.54f}, {-0.30f, 0.54f}
                }
            );
            const auto leftShoe = makeScaledFootprint(
                glm::vec2(leftFoot.x, leftFoot.y + personHeight * 0.02f),
                personHeight * 0.09f,
                personHeight * 0.16f,
                {
                    {-0.55f, 0.52f}, {0.20f, 0.52f}, {0.42f, 0.18f}, {0.40f, -0.40f},
                    {-0.34f, -0.48f}, {-0.62f, -0.10f}
                }
            );
            const auto rightShoe = makeScaledFootprint(
                glm::vec2(rightFoot.x, rightFoot.y + personHeight * 0.02f),
                personHeight * 0.09f,
                personHeight * 0.16f,
                {
                    {-0.20f, 0.52f}, {0.55f, 0.52f}, {0.62f, -0.10f}, {0.34f, -0.48f},
                    {-0.40f, -0.40f}, {-0.42f, 0.18f}
                }
            );

            auto drawHandFan = [&](const glm::vec3& hand, float side) {
                const auto palm = makeScaledFootprint(
                    glm::vec2(hand.x, hand.y),
                    palmR * 1.9f,
                    palmR * 2.8f,
                    {
                        {-0.62f, 0.75f}, {0.44f, 0.75f}, {0.56f, 0.18f}, {0.46f, -0.18f},
                        {0.14f, -0.36f}, {-0.26f, -0.28f}, {-0.58f, 0.12f}
                    }
                );
                drawProjectedPrism(
                    palm,
                    hand.z - palmR * 0.55f,
                    hand.z + palmR * 0.25f,
                    ofColor(base.r, base.g, base.b, 160),
                    ofColor(base.r, base.g, base.b, 92)
                );
                for (int f = 0; f < 5; ++f) {
                    const float fan = static_cast<float>(f - 2);
                    drawProjectedTube(
                        glm::vec3(hand.x + side * palmR * 0.12f, hand.y - palmR * 0.25f, hand.z),
                        glm::vec3(
                            hand.x + side * (fingerSpread * 0.65f + std::abs(fan) * palmR * 0.08f),
                            hand.y - palmR * 0.55f - fingerSpread * fan * 0.34f,
                            hand.z + fingerLen * (1.0f - std::abs(fan) * 0.08f)
                        ),
                        palmR * 0.32f,
                        ofColor(base.r, base.g, base.b, 220)
                    );
                }
                drawProjectedTube(
                    hand,
                    glm::vec3(
                        hand.x + side * fingerSpread * 0.7f,
                        hand.y + palmR * 1.8f,
                        hand.z + fingerLen * 0.35f
                    ),
                    palmR * 0.28f,
                    ofColor(base.r, base.g, base.b, 220)
                );
            };

            ofSetLineWidth(std::max(2.0f, size * 0.08f));
            drawProjectedPrism(torsoFootprint,
                              shoulderZ - torsoHalfH * 1.15f,
                              shoulderZ + torsoHalfH * 0.65f,
                              ofColor(base.r, base.g, base.b, 148),
                              ofColor(base.r, base.g, base.b, 84));
            drawProjectedPrism(hipFootprint,
                              hipZ - hipHalfH * 0.95f,
                              hipZ + hipHalfH * 0.95f,
                              ofColor(base.r, base.g, base.b, 152),
                              ofColor(base.r, base.g, base.b, 88));
            drawProjectedTube(leftFoot, leftHip, personHeight * 0.035f, ofColor(base.r, base.g, base.b, 210));
            drawProjectedTube(rightFoot, rightHip, personHeight * 0.035f, ofColor(base.r, base.g, base.b, 210));
            drawProjectedTube(leftHip, pelvis, personHeight * 0.032f, ofColor(base.r, base.g, base.b, 210));
            drawProjectedTube(rightHip, pelvis, personHeight * 0.032f, ofColor(base.r, base.g, base.b, 210));
            drawProjectedTube(pelvis, chest, personHeight * 0.040f, ofColor(base.r, base.g, base.b, 220));
            drawProjectedTube(leftShoulder, rightShoulder, personHeight * 0.028f, ofColor(base.r, base.g, base.b, 210));
            drawProjectedTube(leftShoulder, leftHand, personHeight * 0.026f, ofColor(base.r, base.g, base.b, 210));
            drawProjectedTube(rightShoulder, rightHand, personHeight * 0.026f, ofColor(base.r, base.g, base.b, 210));
            drawProjectedTube(chest, head, personHeight * 0.028f, ofColor(base.r, base.g, base.b, 220));
            drawProjectedPrism(leftShoe, 0.0f, personHeight * 0.06f, ofColor(base.r, base.g, base.b, 150), ofColor(base.r, base.g, base.b, 94));
            drawProjectedPrism(rightShoe, 0.0f, personHeight * 0.06f, ofColor(base.r, base.g, base.b, 150), ofColor(base.r, base.g, base.b, 94));
            drawProjectedCircle(leftShoulder, personHeight * 0.025f);
            drawProjectedCircle(rightShoulder, personHeight * 0.025f);
            drawProjectedPrism(
                makeOvalFootprint(glm::vec2(head.x, head.y), headR * 0.92f, headR * 1.06f),
                head.z - headR * 0.84f,
                head.z + headR * 0.84f,
                ofColor(base.r, base.g, base.b, 152),
                ofColor(base.r, base.g, base.b, 96)
            );
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
            const float open = 0.5f + 0.5f * std::sin(simTime * 1.8f + idx * 0.45f);
            const float fingerReach = ofLerp(0.46f, 0.78f, open);
            const float thumbSpread = ofLerp(0.16f, 0.34f, open);
            const float thickness = handH * 0.26f;
            const auto handOutline = makeScaledFootprint(
                glm::vec2(worldPoint.x, worldPoint.y),
                handH * 0.52f,
                handH * 0.68f,
                {
                    {-0.42f, 0.72f}, {-0.16f, 0.80f}, {0.16f, 0.80f}, {0.34f, 0.62f},
                    {0.36f, 0.24f}, {0.56f, 0.08f - thumbSpread}, {0.82f, -0.12f - thumbSpread},
                    {0.44f, 0.18f}, {0.28f, 0.08f}, {0.23f, -fingerReach * 0.78f},
                    {0.12f, -fingerReach}, {0.02f, -fingerReach * 1.06f}, {-0.08f, -fingerReach},
                    {-0.18f, -fingerReach * 0.92f}, {-0.28f, -fingerReach * 0.74f},
                    {-0.30f, 0.12f}, {-0.38f, 0.28f}, {-0.48f, 0.46f}
                }
            );
            drawProjectedPrism(
                handOutline,
                worldPoint.z - thickness * 0.55f,
                worldPoint.z + thickness * 0.55f,
                ofColor(base.r, base.g, base.b, 160),
                ofColor(base.r, base.g, base.b, 95)
            );
            drawProjectedCircle(glm::vec3(worldPoint.x + handH * 0.12f, worldPoint.y - handH * 0.38f, worldPoint.z + thickness * 0.35f), handH * 0.028f);
            drawProjectedCircle(glm::vec3(worldPoint.x + handH * 0.04f, worldPoint.y - handH * 0.44f, worldPoint.z + thickness * 0.35f), handH * 0.026f);
            drawProjectedCircle(glm::vec3(worldPoint.x - handH * 0.05f, worldPoint.y - handH * 0.42f, worldPoint.z + thickness * 0.35f), handH * 0.024f);
            drawProjectedCircle(glm::vec3(worldPoint.x - handH * 0.14f, worldPoint.y - handH * 0.34f, worldPoint.z + thickness * 0.35f), handH * 0.022f);
            break;
        }
        case ObjectKind::Dog: {
            const float dogL = ofMap(s.radius, 18.0f, 48.0f, 18.0f, 28.0f, true);
            const float dogH = dogL * 0.42f;
            const float bodyFrontY = worldPoint.y - dogL * 0.18f;
            const float bodyBackY = worldPoint.y + dogL * 0.18f;
            const float bodyZ = dogH * 0.78f;
            const float legX = dogL * 0.16f;
            const float headY = bodyFrontY - dogL * 0.16f;
            const float tailY = bodyBackY + dogL * 0.20f;
            const float headZ = bodyZ * 1.02f;
            drawProjectedPrism(
                makeScaledFootprint(
                    glm::vec2(worldPoint.x, worldPoint.y),
                    dogL * 0.28f,
                    dogL * 0.36f,
                    {
                        {-0.52f, 0.46f}, {0.50f, 0.46f}, {0.66f, 0.18f}, {0.60f, -0.06f},
                        {0.30f, -0.44f}, {-0.18f, -0.46f}, {-0.46f, -0.10f}, {-0.62f, 0.16f}
                    }
                ),
                0.0f, bodyZ * 1.02f, ofColor(base.r, base.g, base.b, 145), ofColor(base.r, base.g, base.b, 72));
            drawProjectedPrism(
                makeScaledFootprint(
                    glm::vec2(worldPoint.x, worldPoint.y + dogL * 0.01f),
                    dogL * 0.20f,
                    dogL * 0.22f,
                    {
                        {-0.48f, 0.42f}, {0.48f, 0.42f}, {0.56f, 0.08f}, {0.28f, -0.34f},
                        {-0.26f, -0.34f}, {-0.56f, 0.10f}
                    }
                ),
                bodyZ * 0.82f, bodyZ * 1.18f, ofColor(base.r, base.g, base.b, 145), ofColor(base.r, base.g, base.b, 82));
            drawProjectedTube(glm::vec3(worldPoint.x - legX, bodyBackY, bodyZ * 0.78f), glm::vec3(worldPoint.x - legX, bodyBackY, 0.0f), dogL * 0.026f, ofColor(base.r, base.g, base.b, 220));
            drawProjectedTube(glm::vec3(worldPoint.x + legX, bodyBackY, bodyZ * 0.78f), glm::vec3(worldPoint.x + legX, bodyBackY, 0.0f), dogL * 0.026f, ofColor(base.r, base.g, base.b, 220));
            drawProjectedTube(glm::vec3(worldPoint.x - legX, bodyFrontY, bodyZ * 0.78f), glm::vec3(worldPoint.x - legX, bodyFrontY, 0.0f), dogL * 0.026f, ofColor(base.r, base.g, base.b, 220));
            drawProjectedTube(glm::vec3(worldPoint.x + legX, bodyFrontY, bodyZ * 0.78f), glm::vec3(worldPoint.x + legX, bodyFrontY, 0.0f), dogL * 0.026f, ofColor(base.r, base.g, base.b, 220));
            drawProjectedPrism(
                makeScaledFootprint(
                    glm::vec2(worldPoint.x, headY),
                    dogL * 0.14f,
                    dogL * 0.18f,
                    {
                        {-0.42f, 0.36f}, {0.42f, 0.36f}, {0.54f, 0.00f}, {0.36f, -0.32f},
                        {-0.26f, -0.34f}, {-0.52f, -0.04f}
                    }
                ),
                bodyZ * 0.78f, headZ * 1.10f, ofColor(base.r, base.g, base.b, 145), ofColor(base.r, base.g, base.b, 82));
            drawProjectedPrism(
                makeScaledFootprint(
                    glm::vec2(worldPoint.x, headY - dogL * 0.14f),
                    dogL * 0.05f,
                    dogL * 0.10f,
                    {
                        {-0.48f, 0.24f}, {0.48f, 0.24f}, {0.34f, -0.62f}, {-0.34f, -0.62f}
                    }
                ),
                headZ * 0.80f, headZ * 0.96f, ofColor(base.r, base.g, base.b, 150), ofColor(base.r, base.g, base.b, 90));
            drawProjectedFill({glm::vec3(worldPoint.x - dogL * 0.04f, headY + dogL * 0.01f, headZ + dogH * 0.08f), glm::vec3(worldPoint.x - dogL * 0.10f, headY + dogL * 0.09f, headZ + dogH * 0.23f), glm::vec3(worldPoint.x - dogL * 0.01f, headY + dogL * 0.08f, headZ + dogH * 0.12f)}, ofColor(base.r, base.g, base.b, 190));
            drawProjectedFill({glm::vec3(worldPoint.x + dogL * 0.04f, headY + dogL * 0.01f, headZ + dogH * 0.08f), glm::vec3(worldPoint.x + dogL * 0.10f, headY + dogL * 0.09f, headZ + dogH * 0.23f), glm::vec3(worldPoint.x + dogL * 0.01f, headY + dogL * 0.08f, headZ + dogH * 0.12f)}, ofColor(base.r, base.g, base.b, 190));
            drawProjectedTube(glm::vec3(worldPoint.x, bodyBackY, bodyZ * 0.96f), glm::vec3(worldPoint.x, tailY, bodyZ * 1.08f), dogL * 0.014f, ofColor(base.r, base.g, base.b, 220));
            break;
        }
        case ObjectKind::PlainObject: {
            const float cubeH = ofMap(s.radius, 18.0f, 48.0f, 12.0f, 22.0f, true);
            const float cubeHalf = cubeH * 0.24f;
            const auto footprint = makeScaledFootprint(
                glm::vec2(worldPoint.x, worldPoint.y),
                cubeHalf,
                cubeHalf,
                {
                    {-1.0f, -1.0f}, {1.0f, -1.0f}, {1.0f, 1.0f}, {-1.0f, 1.0f}
                }
            );
            drawProjectedPrism(footprint, 0.0f, cubeH * 0.92f, ofColor(base.r, base.g, base.b, 150), ofColor(base.r, base.g, base.b, 78));
            drawProjectedLine(glm::vec3(worldPoint.x - cubeHalf, worldPoint.y - cubeHalf, cubeH * 0.46f),
                              glm::vec3(worldPoint.x + cubeHalf, worldPoint.y + cubeHalf, cubeH * 0.46f));
            drawProjectedLine(glm::vec3(worldPoint.x - cubeHalf, worldPoint.y + cubeHalf, cubeH * 0.46f),
                              glm::vec3(worldPoint.x + cubeHalf, worldPoint.y - cubeHalf, cubeH * 0.46f));
            break;
        }
        case ObjectKind::Cat: {
            if (drawCatModel3D(s)) break;

            const float catL = ofMap(s.radius, 18.0f, 48.0f, 18.0f, 28.0f, true);
            const float bodyRx = catL * 0.16f;
            const float bodyRy = catL * 0.30f;
            const float bodyTopZ = catL * 0.34f;
            const float bodyBottomZ = bodyTopZ * 0.08f;
            const float chestZ0 = bodyTopZ * 0.18f;
            const float chestZ1 = bodyTopZ * 0.95f;
            const float headY = worldPoint.y - bodyRy - catL * 0.10f;
            const float headRx = catL * 0.10f;
            const float headRy = catL * 0.12f;
            const float headZ0 = bodyTopZ * 0.42f;
            const float headZ1 = bodyTopZ * 1.18f;
            const float muzzleY = headY - headRy * 0.72f;
            const float muzzleZ0 = bodyTopZ * 0.55f;
            const float muzzleZ1 = bodyTopZ * 0.82f;
            const float legSpreadX = bodyRx * 0.72f;
            const float frontLegY = worldPoint.y - bodyRy * 0.52f;
            const float backLegY = worldPoint.y + bodyRy * 0.52f;
            const float legTopZ = bodyTopZ * 0.78f;
            const float legRadius = catL * 0.014f;
            const float tailBaseY = worldPoint.y + bodyRy * 0.92f;
            const float tailMidY = tailBaseY + catL * 0.18f;
            const float tailTipY = tailMidY + catL * 0.14f;

            drawProjectedPrism(
                makeOvalFootprint(glm::vec2(worldPoint.x, worldPoint.y), bodyRx, bodyRy, 20),
                bodyBottomZ,
                bodyTopZ,
                ofColor(base.r, base.g, base.b, 150),
                ofColor(base.r, base.g, base.b, 86)
            );
            drawProjectedPrism(
                makeOvalFootprint(glm::vec2(worldPoint.x, worldPoint.y - bodyRy * 0.18f), bodyRx * 0.78f, bodyRy * 0.34f, 16),
                chestZ0,
                chestZ1,
                ofColor(base.r, base.g, base.b, 158),
                ofColor(base.r, base.g, base.b, 96)
            );
            drawProjectedPrism(
                makeOvalFootprint(glm::vec2(worldPoint.x, headY), headRx, headRy, 18),
                headZ0,
                headZ1,
                ofColor(base.r, base.g, base.b, 154),
                ofColor(base.r, base.g, base.b, 98)
            );
            drawProjectedPrism(
                makeOvalFootprint(glm::vec2(worldPoint.x, muzzleY), headRx * 0.46f, headRy * 0.34f, 14),
                muzzleZ0,
                muzzleZ1,
                ofColor(base.r, base.g, base.b, 166),
                ofColor(base.r, base.g, base.b, 108)
            );

            drawProjectedTube(glm::vec3(worldPoint.x - legSpreadX, backLegY, legTopZ), glm::vec3(worldPoint.x - legSpreadX, backLegY, 0.0f), legRadius, ofColor(base.r, base.g, base.b, 220));
            drawProjectedTube(glm::vec3(worldPoint.x + legSpreadX, backLegY, legTopZ), glm::vec3(worldPoint.x + legSpreadX, backLegY, 0.0f), legRadius, ofColor(base.r, base.g, base.b, 220));
            drawProjectedTube(glm::vec3(worldPoint.x - legSpreadX, frontLegY, legTopZ), glm::vec3(worldPoint.x - legSpreadX, frontLegY, 0.0f), legRadius, ofColor(base.r, base.g, base.b, 220));
            drawProjectedTube(glm::vec3(worldPoint.x + legSpreadX, frontLegY, legTopZ), glm::vec3(worldPoint.x + legSpreadX, frontLegY, 0.0f), legRadius, ofColor(base.r, base.g, base.b, 220));

            drawProjectedFill(
                {
                    glm::vec3(worldPoint.x - headRx * 0.84f, headY - headRy * 0.10f, headZ1 - headRy * 0.04f),
                    glm::vec3(worldPoint.x - headRx * 1.08f, headY - headRy * 0.64f, headZ1 + headRy * 0.54f),
                    glm::vec3(worldPoint.x - headRx * 0.32f, headY - headRy * 0.56f, headZ1 + headRy * 0.18f)
                },
                ofColor(base.r, base.g, base.b, 196)
            );
            drawProjectedFill(
                {
                    glm::vec3(worldPoint.x + headRx * 0.84f, headY - headRy * 0.10f, headZ1 - headRy * 0.04f),
                    glm::vec3(worldPoint.x + headRx * 1.08f, headY - headRy * 0.64f, headZ1 + headRy * 0.54f),
                    glm::vec3(worldPoint.x + headRx * 0.32f, headY - headRy * 0.56f, headZ1 + headRy * 0.18f)
                },
                ofColor(base.r, base.g, base.b, 196)
            );

            drawProjectedTube(
                glm::vec3(worldPoint.x, tailBaseY, bodyTopZ * 0.96f),
                glm::vec3(worldPoint.x + catL * 0.06f, tailMidY, bodyTopZ * 1.22f),
                catL * 0.010f,
                ofColor(base.r, base.g, base.b, 220)
            );
            drawProjectedTube(
                glm::vec3(worldPoint.x + catL * 0.06f, tailMidY, bodyTopZ * 1.22f),
                glm::vec3(worldPoint.x + catL * 0.12f, tailTipY, bodyTopZ * 1.40f),
                catL * 0.008f,
                ofColor(base.r, base.g, base.b, 220)
            );
            break;
        }
        case ObjectKind::Car: {
            if (drawCarModel3D(s)) break;

            const float carL = ofMap(s.radius, 18.0f, 48.0f, 18.0f, 30.0f, true);
            const float carW = carL * 0.22f;
            const float bodyH = carL * 0.12f;
            const float cabinH = carL * 0.10f;
            const float wheelR = carL * 0.07f;
            const std::vector<glm::vec2> body = {
                {worldPoint.x - carW, worldPoint.y + carL * 0.22f},
                {worldPoint.x + carW, worldPoint.y + carL * 0.22f},
                {worldPoint.x + carW * 1.08f, worldPoint.y + carL * 0.06f},
                {worldPoint.x + carW * 1.08f, worldPoint.y - carL * 0.14f},
                {worldPoint.x + carW * 0.55f, worldPoint.y - carL * 0.24f},
                {worldPoint.x - carW * 0.70f, worldPoint.y - carL * 0.24f},
                {worldPoint.x - carW * 1.08f, worldPoint.y - carL * 0.10f},
                {worldPoint.x - carW * 1.08f, worldPoint.y + carL * 0.10f}
            };
            const std::vector<glm::vec2> cabin = {
                {worldPoint.x - carW * 0.55f, worldPoint.y + carL * 0.04f},
                {worldPoint.x + carW * 0.18f, worldPoint.y + carL * 0.04f},
                {worldPoint.x + carW * 0.50f, worldPoint.y - carL * 0.08f},
                {worldPoint.x - carW * 0.35f, worldPoint.y - carL * 0.08f}
            };
            drawProjectedPrism(body, wheelR, wheelR + bodyH * 2.0f, ofColor(base.r, base.g, base.b, 150), ofColor(base.r, base.g, base.b, 80));
            drawProjectedPrism(cabin, wheelR + bodyH * 1.6f, wheelR + bodyH * 2.8f + cabinH * 0.6f, ofColor(base.r, base.g, base.b, 140), ofColor(base.r, base.g, base.b, 85));
            drawProjectedCircle(glm::vec3(worldPoint.x - carW * 0.86f, worldPoint.y - carL * 0.12f, wheelR), wheelR);
            drawProjectedCircle(glm::vec3(worldPoint.x + carW * 0.86f, worldPoint.y - carL * 0.12f, wheelR), wheelR);
            drawProjectedCircle(glm::vec3(worldPoint.x - carW * 0.86f, worldPoint.y + carL * 0.13f, wheelR), wheelR);
            drawProjectedCircle(glm::vec3(worldPoint.x + carW * 0.86f, worldPoint.y + carL * 0.13f, wheelR), wheelR);
            drawProjectedFill({glm::vec3(worldPoint.x - carW * 0.46f, worldPoint.y + carL * 0.02f, wheelR + bodyH * 2.2f), glm::vec3(worldPoint.x + carW * 0.14f, worldPoint.y + carL * 0.02f, wheelR + bodyH * 2.2f), glm::vec3(worldPoint.x + carW * 0.40f, worldPoint.y - carL * 0.07f, wheelR + bodyH * 2.8f), glm::vec3(worldPoint.x - carW * 0.27f, worldPoint.y - carL * 0.07f, wheelR + bodyH * 2.8f)}, ofColor(255, 255, 255, 55));
            break;
        }
    }
    ofPopStyle();
}

bool ofApp::drawPersonModel3D(const MovingShape& s) {
    if (!personObjLoaded) return false;

    const glm::vec3 worldPoint = shapeWorldPoint(s);
    // Keep Meshy model proportions relative to each other instead of normalizing
    // each class independently. If the person was authored larger than the cat,
    // it should stay larger in the scene.
    const float scale = 0.5f * ofMap(s.radius, 18.0f, 48.0f, 18.0f, 28.0f, true);
    const float centerX = 0.5f * (personModelMin.x + personModelMax.x);
    const float centerZ = 0.5f * (personModelMin.z + personModelMax.z);

    glm::vec3 up(0.0f, 0.0f, 1.0f);
    const glm::vec3 eye = cameraEyeWorld();
    const glm::vec3 target = cameraTargetWorld();
    const glm::vec3 forward = glm::normalize(target - eye);
    if (std::abs(glm::dot(forward, up)) > 0.98f) {
        up = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    ofPushStyle();
    ofEnableDepthTest();
    ofFill();

    ofCamera cam;
    cam.setFov(48.0f);
    cam.setNearClip(0.1f);
    cam.setFarClip(400.0f);
    cam.setPosition(eye);
    cam.lookAt(target, up);

    cam.begin();
    ofPushMatrix();
    ofTranslate(worldPoint);
    ofRotateDeg(180.0f + s.yawDeg, 0.0f, 0.0f, 1.0f);
    ofScale(scale, scale, scale);
    ofRotateDeg(90.0f, 1.0f, 0.0f, 0.0f);
    ofTranslate(-centerX, -personModelMin.y, -centerZ);

    if (personObjTextureLoaded) {
        ofSetColor(255);
        personObjTexture.bind();
        personObjMesh.drawFaces();
        personObjTexture.unbind();
    } else {
        ofSetColor(228, 74, 74, 255);
        personObjMesh.drawFaces();
    }
    ofNoFill();
    ofSetColor(70, 20, 20, 90);
    personObjMesh.drawWireframe();

    ofPopMatrix();
    cam.end();

    ofDisableDepthTest();
    ofPopStyle();
    return true;
}

bool ofApp::drawCarModel3D(const MovingShape& s) {
    if (!carObjLoaded) return false;

    const glm::vec3 worldPoint = shapeWorldPoint(s);
    const float scale = 0.5f * ofMap(s.radius, 18.0f, 48.0f, 18.0f, 28.0f, true);
    const float centerX = 0.5f * (carModelMin.x + carModelMax.x);
    const float centerZ = 0.5f * (carModelMin.z + carModelMax.z);

    glm::vec3 up(0.0f, 0.0f, 1.0f);
    const glm::vec3 eye = cameraEyeWorld();
    const glm::vec3 target = cameraTargetWorld();
    const glm::vec3 forward = glm::normalize(target - eye);
    if (std::abs(glm::dot(forward, up)) > 0.98f) {
        up = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    ofPushStyle();
    ofEnableDepthTest();
    ofFill();

    ofCamera cam;
    cam.setFov(48.0f);
    cam.setNearClip(0.1f);
    cam.setFarClip(400.0f);
    cam.setPosition(eye);
    cam.lookAt(target, up);

    cam.begin();
    ofPushMatrix();
    ofTranslate(worldPoint);
    ofRotateDeg(180.0f + s.yawDeg, 0.0f, 0.0f, 1.0f);
    ofScale(scale, scale, scale);
    ofRotateDeg(90.0f, 1.0f, 0.0f, 0.0f);
    ofTranslate(-centerX, -carModelMin.y, -centerZ);

    if (carObjTextureLoaded) {
        ofSetColor(255);
        carObjTexture.bind();
        carObjMesh.drawFaces();
        carObjTexture.unbind();
    } else {
        ofSetColor(188, 40, 40, 255);
        carObjMesh.drawFaces();
    }
    ofNoFill();
    ofSetColor(40, 8, 8, 85);
    carObjMesh.drawWireframe();

    ofPopMatrix();
    cam.end();

    ofDisableDepthTest();
    ofPopStyle();
    return true;
}

bool ofApp::drawCatModel3D(const MovingShape& s) {
    if (!catObjLoaded && (!catModelLoaded || catModelMeshes.empty())) return false;

    const glm::vec3 worldPoint = shapeWorldPoint(s);
    const float catL = ofMap(s.radius, 18.0f, 48.0f, 18.0f, 28.0f, true);
    const float desiredHeight = catL * 0.95f;
    const float scale = 0.5f * (desiredHeight / std::max(0.001f, catModelHeight));
    const float centerX = 0.5f * (catModelMin.x + catModelMax.x);
    const float centerZ = 0.5f * (catModelMin.z + catModelMax.z);

    glm::vec3 up(0.0f, 0.0f, 1.0f);
    const glm::vec3 eye = cameraEyeWorld();
    const glm::vec3 target = cameraTargetWorld();
    const glm::vec3 forward = glm::normalize(target - eye);
    if (std::abs(glm::dot(forward, up)) > 0.98f) {
        up = glm::vec3(0.0f, 1.0f, 0.0f);
    }

    ofPushStyle();
    ofEnableDepthTest();
    ofFill();

    ofCamera cam;
    cam.setFov(48.0f);
    cam.setNearClip(0.1f);
    cam.setFarClip(400.0f);
    cam.setPosition(eye);
    cam.lookAt(target, up);

    cam.begin();
    ofPushMatrix();
    ofTranslate(worldPoint);
    ofRotateDeg(180.0f + s.yawDeg, 0.0f, 0.0f, 1.0f);
    ofScale(scale, scale, scale);
    ofRotateDeg(90.0f, 1.0f, 0.0f, 0.0f);
    ofTranslate(-centerX, -catModelMin.y, -centerZ);

    if (catObjLoaded) {
        if (catObjTextureLoaded) {
            ofSetColor(255);
            catObjTexture.bind();
            catObjMesh.drawFaces();
            catObjTexture.unbind();
        } else {
            ofSetColor(230, 165, 102, 255);
            catObjMesh.drawFaces();
        }
        ofNoFill();
        ofSetColor(92, 46, 24, 110);
        catObjMesh.drawWireframe();
    } else {
        ofSetColor(255, 184, 206, 255);
        for (const auto& mesh : catModelMeshes) {
            mesh.drawFaces();
        }
        ofNoFill();
        ofSetColor(40, 18, 26, 180);
        for (const auto& mesh : catModelMeshes) {
            mesh.drawWireframe();
        }
    }

    ofPopMatrix();
    cam.end();

    ofDisableDepthTest();
    ofPopStyle();
    return true;
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
        s.objectKind = objectKindForPreset(objectPreset, i);
        const float worldRadius = shapeWorldCollisionRadius(s);
        const float allowed = std::max(1.0f, kHemisphereRadius - worldRadius);
        const float ang = ofRandom(glm::two_pi<float>());
        const float rad = std::sqrt(ofRandomuf()) * allowed;
        glm::vec2 candidateWorld(std::cos(ang) * rad, std::sin(ang) * rad);
        s.pos = worldToScreenPoint(candidateWorld, frameW, frameH);
        for (int attempt = 0; attempt < 40; ++attempt) {
            bool overlaps = false;
            for (const auto& other : shapes) {
                const glm::vec2 otherWorld = screenToWorldPoint(other.pos, frameW, frameH);
                const float minDist = shapeWorldCollisionRadius(s) + shapeWorldCollisionRadius(other) + 0.5f;
                if (glm::distance(candidateWorld, otherWorld) < minDist) {
                    overlaps = true;
                    const float a2 = ofRandom(glm::two_pi<float>());
                    const float r2 = std::sqrt(ofRandomuf()) * allowed;
                    candidateWorld = glm::vec2(std::cos(a2) * r2, std::sin(a2) * r2);
                    s.pos = worldToScreenPoint(candidateWorld, frameW, frameH);
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
    const float worldRadius = shapeWorldCollisionRadius(s);
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
    const float worldRadius = shapeWorldCollisionRadius(shape);
    const float allowed = std::max(1.0f, kHemisphereRadius - worldRadius);
    glm::vec2 worldPos(
        ofMap(shape.pos.x, 0.0f, static_cast<float>(frameW), -kWorldSide, kWorldSide, true),
        ofMap(shape.pos.y, 0.0f, static_cast<float>(frameH), kWorldFarY, kWorldNearY, true)
    );
    const float dist = glm::length(worldPos);
    if (dist > allowed) {
        glm::vec2 nrm = (dist > 0.0001f) ? (worldPos / dist) : glm::vec2(0.0f, 1.0f);
        if (edgeBounce) {
            glm::vec2 velWorld = velocityScreenToWorld(shape.vel);
            glm::vec2 walkWorld(shape.walkDir.x, shape.walkDir.y);
            velWorld = glm::reflect(velWorld, nrm);
            walkWorld = glm::reflect(walkWorld, nrm);
            worldPos = nrm * allowed;
            shape.vel = velocityWorldToScreen(velWorld);
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
    const float worldRadius = shapeWorldCollisionRadius(shape);
    const float allowed = std::max(1.0f, kHemisphereRadius - worldRadius);
    glm::vec2 worldPos(
        ofMap(shape.pos.x, 0.0f, static_cast<float>(frameW), -kWorldSide, kWorldSide, true),
        ofMap(shape.pos.y, 0.0f, static_cast<float>(frameH), kWorldFarY, kWorldNearY, true)
    );
    const float dist = glm::length(worldPos);
    if (dist > allowed) {
        glm::vec2 nrm = (dist > 0.0001f) ? (worldPos / dist) : glm::vec2(0.0f, 1.0f);
        glm::vec2 velWorld = velocityScreenToWorld(shape.vel);
        velWorld = glm::reflect(velWorld, nrm) * restitution;
        worldPos = nrm * allowed;
        shape.vel = velocityWorldToScreen(velWorld);
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
            const float worldRadius = shapeWorldCollisionRadius(s);
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
    const float worldRadius = shapeWorldCollisionRadius(s);
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
    const float worldRadius = shapeWorldCollisionRadius(s);
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
    std::vector<glm::vec2> worldPos(n);
    std::vector<glm::vec2> worldVel(n);
    std::vector<float> footprint(n);
    std::vector<glm::vec2> halfExtents(n);
    std::vector<glm::vec2> rightAxes(n);
    std::vector<glm::vec2> forwardAxes(n);
    auto modelHalfExtents = [&](const MovingShape& shape) {
        const float trim = 0.44f;
        switch (shape.objectKind) {
            case ObjectKind::Person:
                if (personObjLoaded) {
                    const float scale = 0.5f * ofMap(shape.radius, 18.0f, 48.0f, 18.0f, 28.0f, true);
                    return glm::vec2(
                        std::max(0.8f, (personModelMax.x - personModelMin.x) * scale * trim),
                        std::max(0.8f, personModelDepth * scale * trim)
                    );
                }
                break;
            case ObjectKind::Cat:
                if (catObjLoaded || (catModelLoaded && !catModelMeshes.empty())) {
                    const float catL = ofMap(shape.radius, 18.0f, 48.0f, 18.0f, 28.0f, true);
                    const float scale = 0.5f * ((catL * 0.95f) / std::max(0.001f, catModelHeight));
                    return glm::vec2(
                        std::max(0.8f, (catModelMax.x - catModelMin.x) * scale * trim),
                        std::max(0.8f, catModelDepth * scale * trim)
                    );
                }
                break;
            case ObjectKind::Car:
                if (carObjLoaded) {
                    const float scale = 0.5f * ofMap(shape.radius, 18.0f, 48.0f, 18.0f, 28.0f, true);
                    return glm::vec2(
                        std::max(0.8f, (carModelMax.x - carModelMin.x) * scale * trim),
                        std::max(0.8f, carModelDepth * scale * trim)
                    );
                }
                break;
            default:
                break;
        }
        const float r = shapeWorldCollisionRadius(shape);
        return glm::vec2(r, r);
    };
    auto supportRadiusAlong = [](const glm::vec2& normal,
                                 const glm::vec2& axisX,
                                 const glm::vec2& axisY,
                                 const glm::vec2& extents) {
        return std::abs(glm::dot(normal, axisX)) * extents.x +
               std::abs(glm::dot(normal, axisY)) * extents.y;
    };
    for (int i = 0; i < n; ++i) {
        worldPos[i] = screenToWorldPoint(shapes[i].pos, frameW, frameH);
        worldVel[i] = velocityScreenToWorld(shapes[i].vel);
        footprint[i] = shapeWorldCollisionRadius(shapes[i]);
        halfExtents[i] = modelHalfExtents(shapes[i]);
        const float yaw = glm::radians(shapes[i].yawDeg);
        rightAxes[i] = glm::vec2(std::cos(yaw), std::sin(yaw));
        forwardAxes[i] = glm::vec2(-std::sin(yaw), std::cos(yaw));
    }

    for (int solverPass = 0; solverPass < 2; ++solverPass) {
        for (int i = 0; i < n; ++i) {
            if (!isShapeOn(shapes[i])) continue;
            for (int j = i + 1; j < n; ++j) {
                if (!isShapeOn(shapes[j])) continue;
                glm::vec2 d = worldPos[i] - worldPos[j];
                float dist = glm::length(d);
                if (dist < 0.0001f) {
                    d = glm::vec2(1.0f, 0.0f);
                    dist = 0.0001f;
                }
                const glm::vec2 nrm = d / dist;
                const float minDist =
                    supportRadiusAlong(nrm, rightAxes[i], forwardAxes[i], halfExtents[i]) +
                    supportRadiusAlong(nrm, rightAxes[j], forwardAxes[j], halfExtents[j]) +
                    0.10f;
                if (dist < 0.0001f || dist >= minDist) continue;

                const glm::vec2 relVel = worldVel[i] - worldVel[j];
                const float relNormalSpeed = glm::dot(relVel, nrm);

                // Mass ~ footprint area so larger physical objects feel heavier.
                const float m1 = std::max(1.0f, halfExtents[i].x * halfExtents[i].y * 4.0f);
                const float m2 = std::max(1.0f, halfExtents[j].x * halfExtents[j].y * 4.0f);
                const float invM1 = 1.0f / m1;
                const float invM2 = 1.0f / m2;

                if (relNormalSpeed < 0.0f) {
                    float jImpulse = -(1.0f + restitution) * relNormalSpeed;
                    jImpulse /= (invM1 + invM2);
                    // Keep artistic control from collisionStrength.
                    jImpulse *= (collisionStrength / 1200.0f) * collisionScale;
                    const glm::vec2 impulse = jImpulse * nrm;
                    worldVel[i] += impulse * invM1;
                    worldVel[j] -= impulse * invM2;
                    if (airHockeyMode) {
                        // Keep some life, just stop runaway energy build-up.
                        worldVel[i] *= 0.982f;
                        worldVel[j] *= 0.982f;
                        const float maxHockeySpeedWorld = 240.0f;
                        const float spd1 = glm::length(worldVel[i]);
                        const float spd2 = glm::length(worldVel[j]);
                        if (spd1 > maxHockeySpeedWorld) worldVel[i] = glm::normalize(worldVel[i]) * maxHockeySpeedWorld;
                        if (spd2 > maxHockeySpeedWorld) worldVel[j] = glm::normalize(worldVel[j]) * maxHockeySpeedWorld;
                    }
                }

                // Positional correction (prevents sinking/sticking/tunneling).
                const float overlap = minDist - dist;
                const float corr = std::max(0.0f, overlap - 0.02f) * 0.95f;
                const glm::vec2 correction = (corr / (invM1 + invM2)) * nrm;
                worldPos[i] += correction * invM1;
                worldPos[j] -= correction * invM2;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!isShapeOn(shapes[i])) continue;
        const float allowed = std::max(1.0f, kHemisphereRadius - footprint[i]);
        worldPos[i] = clampWorldToCircle(worldPos[i], allowed);
        shapes[i].pos = worldToScreenPoint(worldPos[i], frameW, frameH);
        shapes[i].vel = velocityWorldToScreen(worldVel[i]);
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

    std::vector<int> visibleShapeIndices;
    visibleShapeIndices.reserve(visible.size());
    for (const auto& item : visible) {
        const auto& s = shapes[item.idx];
        visibleShapeIndices.push_back(item.idx);
        ofSetColor(s.color);
        drawShape3D(s, item.idx);
    }
    writeTruthLog(visibleShapeIndices);

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
        const double nowSec = ofGetElapsedTimef();
        const double minSendIntervalSec = 1.0 / std::max(1.0f, ndiSendTargetFps);
        if (lastNdiSendTimeSec >= 0.0 && (nowSec - lastNdiSendTimeSec) < minSendIntervalSec) {
            return;
        }
        fbo.readToPixels(pixels);
        ndiVideo.send(pixels);
        lastNdiSendTimeSec = nowSec;
    }
}

void ofApp::draw() {
    ofSetColor(255);
    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofPushMatrix();
    ofScale(static_cast<float>(ofGetWidth()) / static_cast<float>(frameW),
            static_cast<float>(ofGetHeight()) / static_cast<float>(frameH));
    drawHemisphereOverlay();
    ofPopMatrix();
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
        ofDrawBitmapStringHighlight("Objects: [o] mixed/people/hands/cats/dogs/cubes/cars", 20, 178);
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

    if (!startupSnapshotSaved && ofGetFrameNum() >= 30) {
        ofSaveScreen(kSenderSnapshotPath);
        startupSnapshotSaved = true;
    }
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
        viewPitchDeg = 18.0f;
        observerOffsetX = 0.0f;
        observerDistanceY = 130.0f;
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
