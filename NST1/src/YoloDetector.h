#pragma once

#include <memory>
#include <set>
#include <string>
#include <vector>

#include <opencv2/core.hpp>

namespace mtb {

struct YoloDetection {
    cv::Rect box;
    int classId = -1;
    float score = 0.0f;
};

struct YoloDetectorConfig {
    std::string onnxModelPath;
    std::string coreMlModelPath;
    int inputSize = 320;
    float confidenceThreshold = 0.25f;
    float nmsThreshold = 0.45f;
    std::set<std::string> classFilter;
};

class YoloDetectorBackend {
public:
    virtual ~YoloDetectorBackend() = default;

    virtual bool load(const YoloDetectorConfig& config, std::string& error) = 0;
    virtual bool infer(const cv::Mat& currentMat,
                       const YoloDetectorConfig& config,
                       std::vector<YoloDetection>& detections,
                       std::string& error) = 0;
    virtual std::string backendName() const = 0;
};

std::unique_ptr<YoloDetectorBackend> createOpenCvYoloDetector();

#ifdef __APPLE__
std::unique_ptr<YoloDetectorBackend> createCoreMLYoloDetector();
#endif

}  // namespace mtb
