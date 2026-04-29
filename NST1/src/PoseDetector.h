#pragma once

#include <memory>
#include <string>

#include <glm/vec2.hpp>
#include <opencv2/core.hpp>

namespace mtb {

struct PoseJoint {
    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    float confidence = 0.0f;
    bool valid = false;
};

struct PoseDetection {
    bool valid = false;
    float confidence = 0.0f;
    cv::Rect2f boundingBox;

    PoseJoint root;
    PoseJoint neck;
    PoseJoint leftShoulder;
    PoseJoint rightShoulder;
    PoseJoint leftElbow;
    PoseJoint rightElbow;
    PoseJoint leftWrist;
    PoseJoint rightWrist;
    PoseJoint leftHip;
    PoseJoint rightHip;
    PoseJoint leftKnee;
    PoseJoint rightKnee;
    PoseJoint leftAnkle;
    PoseJoint rightAnkle;
    PoseJoint torso;
};

struct PoseDetectorConfig {
    float minJointConfidence = 0.18f;
};

class PoseDetectorBackend {
public:
    virtual ~PoseDetectorBackend() = default;

    virtual bool load(std::string& error) = 0;
    virtual bool infer(const cv::Mat& currentMat,
                       const PoseDetectorConfig& config,
                       PoseDetection& detection,
                       std::string& error) = 0;
    virtual std::string backendName() const = 0;
};

#ifdef __APPLE__
std::unique_ptr<PoseDetectorBackend> createVisionPoseDetector();
#endif

}  // namespace mtb
