#ifdef __APPLE__

#include "YoloDetector.h"

#include "ofMain.h"

#import <CoreML/CoreML.h>
#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>

#include <cmath>
#include <cstring>
#include <memory>
#include <sstream>

#include <opencv2/imgproc.hpp>

namespace mtb {

namespace {

std::string yoloClassName(int classId) {
    static const std::vector<std::string> names = {
        "person","bicycle","car","motorcycle","airplane","bus","train","truck","boat","traffic light",
        "fire hydrant","stop sign","parking meter","bench","bird","cat","dog","horse","sheep","cow",
        "elephant","bear","zebra","giraffe","backpack","umbrella","handbag","tie","suitcase","frisbee",
        "skis","snowboard","sports ball","kite","baseball bat","baseball glove","skateboard","surfboard","tennis racket","bottle",
        "wine glass","cup","fork","knife","spoon","bowl","banana","apple","sandwich","orange",
        "broccoli","carrot","hot dog","pizza","donut","cake","chair","couch","potted plant","bed",
        "dining table","toilet","tv","laptop","mouse","remote","keyboard","cell phone","microwave","oven",
        "toaster","sink","refrigerator","book","clock","vase","scissors","teddy bear","hair drier","toothbrush"
    };
    if (classId < 0 || classId >= static_cast<int>(names.size())) return "obj";
    return names[classId];
}

float multiArrayValueAt(MLMultiArray* array, NSInteger row, NSInteger col) {
    if (!array || array.shape.count < 2 || array.strides.count < 2) return 0.0f;

    const NSInteger stride0 = array.strides[0].integerValue;
    const NSInteger stride1 = array.strides[1].integerValue;
    const NSInteger offset = row * stride0 + col * stride1;

    switch (array.dataType) {
        case MLMultiArrayDataTypeFloat32:
            return static_cast<float*>(array.dataPointer)[offset];
        case MLMultiArrayDataTypeFloat16:
            return static_cast<float>(static_cast<uint16_t*>(array.dataPointer)[offset]);
        case MLMultiArrayDataTypeDouble:
            return static_cast<float>(static_cast<double*>(array.dataPointer)[offset]);
        case MLMultiArrayDataTypeInt32:
            return static_cast<float>(static_cast<int32_t*>(array.dataPointer)[offset]);
        default:
            return 0.0f;
    }
}

std::string nsErrorToString(NSError* error) {
    if (!error) return "unknown Core ML error";
    NSString* description = error.localizedDescription ?: @"unknown Core ML error";
    return std::string(description.UTF8String ? description.UTF8String : "unknown Core ML error");
}

bool createPixelBufferFromMat(const cv::Mat& bgrMat, int targetSize, CVPixelBufferRef* outBuffer, std::string& error) {
    if (!outBuffer) {
        error = "null pixel buffer output";
        return false;
    }

    cv::Mat resized;
    cv::resize(bgrMat, resized, cv::Size(targetSize, targetSize), 0, 0, cv::INTER_LINEAR);

    cv::Mat bgra;
    cv::cvtColor(resized, bgra, cv::COLOR_BGR2BGRA);

    CVPixelBufferRef pixelBuffer = nullptr;
    const CVReturn status = CVPixelBufferCreate(kCFAllocatorDefault,
                                                targetSize,
                                                targetSize,
                                                kCVPixelFormatType_32BGRA,
                                                nullptr,
                                                &pixelBuffer);
    if (status != kCVReturnSuccess || pixelBuffer == nullptr) {
        error = "CVPixelBufferCreate failed";
        return false;
    }

    CVPixelBufferLockBaseAddress(pixelBuffer, 0);
    void* dstBase = CVPixelBufferGetBaseAddress(pixelBuffer);
    const size_t dstBytesPerRow = CVPixelBufferGetBytesPerRow(pixelBuffer);
    const size_t srcBytesPerRow = static_cast<size_t>(bgra.step[0]);
    const size_t copyBytesPerRow = std::min(dstBytesPerRow, srcBytesPerRow);
    for (int y = 0; y < targetSize; ++y) {
        std::memcpy(static_cast<uint8_t*>(dstBase) + y * dstBytesPerRow,
                    bgra.ptr(y),
                    copyBytesPerRow);
    }
    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);

    *outBuffer = pixelBuffer;
    return true;
}

class CoreMLYoloDetector final : public YoloDetectorBackend {
public:
    bool load(const YoloDetectorConfig& config, std::string& error) override {
        model = nil;
        NSString* path = [NSString stringWithUTF8String:config.coreMlModelPath.c_str()];
        if (!path) {
            error = "invalid Core ML model path";
            return false;
        }

        NSURL* url = [NSURL fileURLWithPath:path];
        MLModelConfiguration* modelConfig = [[MLModelConfiguration alloc] init];
        // Avoid the more crash-prone mixed "all units" routing we were seeing in BNNS.
        // For this app, a stable GPU-backed path is preferable to opportunistic CPU/ANE
        // routing that can SIGILL inside Apple's runtime.
        modelConfig.computeUnits = MLComputeUnitsCPUAndGPU;

        NSError* loadError = nil;
        model = [MLModel modelWithContentsOfURL:url configuration:modelConfig error:&loadError];
        if (!model) {
            error = nsErrorToString(loadError);
            return false;
        }
        return true;
    }

    bool infer(const cv::Mat& currentMat,
               const YoloDetectorConfig& config,
               std::vector<YoloDetection>& detections,
               std::string& error) override {
        detections.clear();
        if (!model) {
            error = "Core ML YOLO backend not loaded";
            return false;
        }
        if (currentMat.empty()) {
            return true;
        }

        CVPixelBufferRef pixelBuffer = nullptr;
        if (!createPixelBufferFromMat(currentMat, config.inputSize, &pixelBuffer, error)) {
            return false;
        }

        @autoreleasepool {
            NSError* providerError = nil;
            NSMutableDictionary<NSString*, MLFeatureValue*>* inputs = [NSMutableDictionary dictionary];
            inputs[@"image"] = [MLFeatureValue featureValueWithPixelBuffer:pixelBuffer];
            inputs[@"iouThreshold"] = [MLFeatureValue featureValueWithDouble:config.nmsThreshold];
            inputs[@"confidenceThreshold"] = [MLFeatureValue featureValueWithDouble:config.confidenceThreshold];

            MLDictionaryFeatureProvider* provider =
                [[MLDictionaryFeatureProvider alloc] initWithDictionary:inputs error:&providerError];
            if (!provider) {
                CVPixelBufferRelease(pixelBuffer);
                error = nsErrorToString(providerError);
                return false;
            }

            NSError* predictionError = nil;
            id<MLFeatureProvider> result = [model predictionFromFeatures:provider error:&predictionError];
            CVPixelBufferRelease(pixelBuffer);
            if (!result) {
                error = nsErrorToString(predictionError);
                return false;
            }

            MLMultiArray* coordinates = [result featureValueForName:@"coordinates"].multiArrayValue;
            MLMultiArray* confidence = [result featureValueForName:@"confidence"].multiArrayValue;
            if (!coordinates || !confidence || coordinates.shape.count < 2 || confidence.shape.count < 2) {
                return true;
            }

            const NSInteger detectionCount = coordinates.shape[0].integerValue;
            const NSInteger classCount = confidence.shape[1].integerValue;
            detections.reserve(static_cast<std::size_t>(std::max<NSInteger>(0, detectionCount)));

            for (NSInteger i = 0; i < detectionCount; ++i) {
                int bestClassId = -1;
                float bestScore = -1.0f;
                for (NSInteger c = 0; c < classCount; ++c) {
                    const std::string className = ofToLower(yoloClassName(static_cast<int>(c)));
                    if (!config.classFilter.empty() && config.classFilter.count(className) == 0) continue;
                    const float score = multiArrayValueAt(confidence, i, c);
                    if (score > bestScore) {
                        bestScore = score;
                        bestClassId = static_cast<int>(c);
                    }
                }

                if (bestClassId < 0) continue;

                const float cx = multiArrayValueAt(coordinates, i, 0) * currentMat.cols;
                const float cy = multiArrayValueAt(coordinates, i, 1) * currentMat.rows;
                const float width = multiArrayValueAt(coordinates, i, 2) * currentMat.cols;
                const float height = multiArrayValueAt(coordinates, i, 3) * currentMat.rows;

                const int left = std::max(0, static_cast<int>(std::round(cx - width * 0.5f)));
                const int top = std::max(0, static_cast<int>(std::round(cy - height * 0.5f)));
                const int boxWidth = std::min(currentMat.cols - left, static_cast<int>(std::round(width)));
                const int boxHeight = std::min(currentMat.rows - top, static_cast<int>(std::round(height)));
                if (boxWidth <= 1 || boxHeight <= 1) continue;

                YoloDetection detection;
                detection.box = cv::Rect(left, top, boxWidth, boxHeight);
                detection.classId = bestClassId;
                detection.score = bestScore;
                detections.push_back(detection);
            }
        }

        return true;
    }

    std::string backendName() const override {
        return "Core ML";
    }

private:
    MLModel* model = nil;
};

}  // namespace

std::unique_ptr<YoloDetectorBackend> createCoreMLYoloDetector() {
    return std::make_unique<CoreMLYoloDetector>();
}

}  // namespace mtb

#endif
