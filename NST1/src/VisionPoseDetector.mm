#ifdef __APPLE__

#include "PoseDetector.h"

#include "ofMain.h"

#import <CoreGraphics/CoreGraphics.h>
#import <CoreVideo/CoreVideo.h>
#import <Foundation/Foundation.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <limits>
#include <sstream>
#include <vector>

#include <opencv2/imgproc.hpp>

namespace mtb {

namespace {

@class VNRecognizedPoint;
@class VNHumanBodyPoseObservation;
@class VNDetectHumanBodyPoseRequest;
@class VNImageRequestHandler;

extern NSString* const VNHumanBodyPoseObservationJointNameRoot;
extern NSString* const VNHumanBodyPoseObservationJointNameNeck;
extern NSString* const VNHumanBodyPoseObservationJointNameLeftShoulder;
extern NSString* const VNHumanBodyPoseObservationJointNameRightShoulder;
extern NSString* const VNHumanBodyPoseObservationJointNameLeftElbow;
extern NSString* const VNHumanBodyPoseObservationJointNameRightElbow;
extern NSString* const VNHumanBodyPoseObservationJointNameLeftWrist;
extern NSString* const VNHumanBodyPoseObservationJointNameRightWrist;
extern NSString* const VNHumanBodyPoseObservationJointNameLeftHip;
extern NSString* const VNHumanBodyPoseObservationJointNameRightHip;
extern NSString* const VNHumanBodyPoseObservationJointNameLeftKnee;
extern NSString* const VNHumanBodyPoseObservationJointNameRightKnee;
extern NSString* const VNHumanBodyPoseObservationJointNameLeftAnkle;
extern NSString* const VNHumanBodyPoseObservationJointNameRightAnkle;

@interface VNRecognizedPoint : NSObject
@property(nonatomic, readonly) float x;
@property(nonatomic, readonly) float y;
@property(nonatomic, readonly) float confidence;
@end

@interface VNHumanBodyPoseObservation : NSObject
@property(nonatomic, readonly) CGRect boundingBox;
@property(nonatomic, readonly) float confidence;
- (nullable VNRecognizedPoint*)recognizedPointForJointName:(NSString*)jointName error:(NSError**)error;
@end

@interface VNDetectHumanBodyPoseRequest : NSObject
@property(nonatomic, readonly, nullable, copy) NSArray<VNHumanBodyPoseObservation*>* results;
@end

@interface VNImageRequestHandler : NSObject
- (instancetype)initWithCVPixelBuffer:(CVPixelBufferRef)pixelBuffer
                              options:(NSDictionary<NSString*, id>*)options;
- (BOOL)performRequests:(NSArray*)requests error:(NSError**)error;
@end

std::string nsErrorToString(NSError* error) {
    if (!error) return "unknown Vision error";
    NSString* description = error.localizedDescription ?: @"unknown Vision error";
    return std::string(description.UTF8String ? description.UTF8String : "unknown Vision error");
}

bool createPixelBufferFromMat(const cv::Mat& bgrMat,
                              int targetWidth,
                              int targetHeight,
                              CVPixelBufferRef* outBuffer,
                              std::string& error) {
    if (!outBuffer) {
        error = "null pixel buffer output";
        return false;
    }

    cv::Mat resized;
    if (bgrMat.cols != targetWidth || bgrMat.rows != targetHeight) {
        cv::resize(bgrMat, resized, cv::Size(targetWidth, targetHeight), 0, 0, cv::INTER_LINEAR);
    } else {
        resized = bgrMat;
    }

    cv::Mat bgra;
    cv::cvtColor(resized, bgra, cv::COLOR_BGR2BGRA);

    CVPixelBufferRef pixelBuffer = nullptr;
    const CVReturn status = CVPixelBufferCreate(kCFAllocatorDefault,
                                                targetWidth,
                                                targetHeight,
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
    for (int y = 0; y < targetHeight; ++y) {
        std::memcpy(static_cast<uint8_t*>(dstBase) + y * dstBytesPerRow,
                    bgra.ptr(y),
                    copyBytesPerRow);
    }
    CVPixelBufferUnlockBaseAddress(pixelBuffer, 0);

    *outBuffer = pixelBuffer;
    return true;
}

PoseJoint readJoint(VNHumanBodyPoseObservation* observation,
                    VNHumanBodyPoseObservationJointName jointName,
                    const cv::Size& imageSize,
                    float minConfidence) {
    PoseJoint joint;
    if (!observation) return joint;

    NSError* error = nil;
    VNRecognizedPoint* point = [observation recognizedPointForJointName:jointName error:&error];
    if (!point || point.confidence < minConfidence) {
        return joint;
    }

    joint.valid = true;
    joint.confidence = point.confidence;
    joint.position = glm::vec2(point.x * imageSize.width,
                               (1.0f - point.y) * imageSize.height);
    return joint;
}

PoseJoint averageJoints(const std::vector<PoseJoint>& joints) {
    PoseJoint out;
    glm::vec2 sum(0.0f, 0.0f);
    float confidenceSum = 0.0f;
    int count = 0;

    for (const PoseJoint& joint : joints) {
        if (!joint.valid) continue;
        sum += joint.position;
        confidenceSum += joint.confidence;
        count++;
    }

    if (count == 0) {
        return out;
    }

    out.valid = true;
    out.position = sum / static_cast<float>(count);
    out.confidence = confidenceSum / static_cast<float>(count);
    return out;
}

cv::Rect2f rectFromObservationBoundingBox(CGRect normalizedBox, const cv::Size& imageSize) {
    const float x = normalizedBox.origin.x * imageSize.width;
    const float y = (1.0f - normalizedBox.origin.y - normalizedBox.size.height) * imageSize.height;
    const float width = normalizedBox.size.width * imageSize.width;
    const float height = normalizedBox.size.height * imageSize.height;
    return cv::Rect2f(x, y, width, height);
}

void expandBoundsWithJoint(const PoseJoint& joint,
                           float& minX,
                           float& minY,
                           float& maxX,
                           float& maxY) {
    if (!joint.valid) return;
    minX = std::min(minX, joint.position.x);
    minY = std::min(minY, joint.position.y);
    maxX = std::max(maxX, joint.position.x);
    maxY = std::max(maxY, joint.position.y);
}

PoseDetection buildDetection(VNHumanBodyPoseObservation* observation,
                             const cv::Size& imageSize,
                             float minConfidence) {
    PoseDetection detection;
    if (!observation) return detection;

    detection.boundingBox = rectFromObservationBoundingBox(observation.boundingBox, imageSize);
    detection.root = readJoint(observation, VNHumanBodyPoseObservationJointNameRoot, imageSize, minConfidence);
    detection.neck = readJoint(observation, VNHumanBodyPoseObservationJointNameNeck, imageSize, minConfidence);
    detection.leftShoulder = readJoint(observation, VNHumanBodyPoseObservationJointNameLeftShoulder, imageSize, minConfidence);
    detection.rightShoulder = readJoint(observation, VNHumanBodyPoseObservationJointNameRightShoulder, imageSize, minConfidence);
    detection.leftElbow = readJoint(observation, VNHumanBodyPoseObservationJointNameLeftElbow, imageSize, minConfidence);
    detection.rightElbow = readJoint(observation, VNHumanBodyPoseObservationJointNameRightElbow, imageSize, minConfidence);
    detection.leftWrist = readJoint(observation, VNHumanBodyPoseObservationJointNameLeftWrist, imageSize, minConfidence);
    detection.rightWrist = readJoint(observation, VNHumanBodyPoseObservationJointNameRightWrist, imageSize, minConfidence);
    detection.leftHip = readJoint(observation, VNHumanBodyPoseObservationJointNameLeftHip, imageSize, minConfidence);
    detection.rightHip = readJoint(observation, VNHumanBodyPoseObservationJointNameRightHip, imageSize, minConfidence);
    detection.leftKnee = readJoint(observation, VNHumanBodyPoseObservationJointNameLeftKnee, imageSize, minConfidence);
    detection.rightKnee = readJoint(observation, VNHumanBodyPoseObservationJointNameRightKnee, imageSize, minConfidence);
    detection.leftAnkle = readJoint(observation, VNHumanBodyPoseObservationJointNameLeftAnkle, imageSize, minConfidence);
    detection.rightAnkle = readJoint(observation, VNHumanBodyPoseObservationJointNameRightAnkle, imageSize, minConfidence);

    detection.torso = averageJoints({
        detection.leftShoulder,
        detection.rightShoulder,
        detection.leftHip,
        detection.rightHip,
        detection.root,
        detection.neck
    });

    if (!detection.torso.valid) {
        detection.torso = averageJoints({detection.root, detection.neck});
    }

    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float maxY = std::numeric_limits<float>::lowest();
    const std::array<PoseJoint, 13> allJoints = {
        detection.root,
        detection.neck,
        detection.leftShoulder,
        detection.rightShoulder,
        detection.leftElbow,
        detection.rightElbow,
        detection.leftWrist,
        detection.rightWrist,
        detection.leftHip,
        detection.rightHip,
        detection.leftKnee,
        detection.rightKnee,
        detection.leftAnkle
    };
    for (const PoseJoint& joint : allJoints) {
        expandBoundsWithJoint(joint, minX, minY, maxX, maxY);
    }
    expandBoundsWithJoint(detection.rightAnkle, minX, minY, maxX, maxY);

    if (minX <= maxX && minY <= maxY) {
        const cv::Rect2f jointBounds(minX, minY, maxX - minX, maxY - minY);
        if (detection.boundingBox.width <= 1.0f || detection.boundingBox.height <= 1.0f) {
            detection.boundingBox = jointBounds;
        } else {
            const float blend = 0.35f;
            detection.boundingBox = cv::Rect2f(
                ofLerp(detection.boundingBox.x, jointBounds.x, blend),
                ofLerp(detection.boundingBox.y, jointBounds.y, blend),
                ofLerp(detection.boundingBox.width, jointBounds.width, blend),
                ofLerp(detection.boundingBox.height, jointBounds.height, blend)
            );
        }
    }

    std::vector<PoseJoint> confidenceJoints;
    confidenceJoints.reserve(6);
    confidenceJoints.push_back(detection.torso);
    confidenceJoints.push_back(detection.leftWrist);
    confidenceJoints.push_back(detection.rightWrist);
    confidenceJoints.push_back(detection.leftAnkle);
    confidenceJoints.push_back(detection.rightAnkle);
    confidenceJoints.push_back(detection.root);
    PoseJoint confidenceJoint = averageJoints(confidenceJoints);
    detection.confidence = confidenceJoint.valid ? confidenceJoint.confidence : observation.confidence;
    detection.valid = detection.torso.valid || detection.root.valid;
    return detection;
}

float rankingScore(const PoseDetection& detection, const cv::Size& imageSize) {
    if (!detection.valid || imageSize.width <= 0 || imageSize.height <= 0) return -1.0f;
    const float frameArea = static_cast<float>(imageSize.width * imageSize.height);
    const float area = std::max(detection.boundingBox.width, 1.0f) * std::max(detection.boundingBox.height, 1.0f);
    const float areaScore = std::min(area / std::max(frameArea, 1.0f), 1.0f);
    return detection.confidence + (areaScore * 0.35f);
}

class VisionPoseDetector final : public PoseDetectorBackend {
public:
    bool load(std::string& error) override {
        request = [[VNDetectHumanBodyPoseRequest alloc] init];
        if (!request) {
            error = "failed to create VNDetectHumanBodyPoseRequest";
            return false;
        }
        return true;
    }

    bool infer(const cv::Mat& currentMat,
               const PoseDetectorConfig& config,
               PoseDetection& detection,
               std::string& error) override {
        detection = PoseDetection{};
        if (!request) {
            error = "Vision pose backend not loaded";
            return false;
        }
        if (currentMat.empty()) {
            return true;
        }

        CVPixelBufferRef pixelBuffer = nullptr;
        if (!createPixelBufferFromMat(currentMat, currentMat.cols, currentMat.rows, &pixelBuffer, error)) {
            return false;
        }

        @autoreleasepool {
            VNImageRequestHandler* handler =
                [[VNImageRequestHandler alloc] initWithCVPixelBuffer:pixelBuffer options:@{}];

            NSError* requestError = nil;
            const BOOL ok = [handler performRequests:@[request] error:&requestError];
            CVPixelBufferRelease(pixelBuffer);
            if (!ok) {
                error = nsErrorToString(requestError);
                return false;
            }

            NSArray<VNHumanBodyPoseObservation*>* results = request.results;
            if (!results || results.count == 0) {
                return true;
            }

            PoseDetection bestDetection;
            float bestScore = -1.0f;
            for (VNHumanBodyPoseObservation* observation in results) {
                PoseDetection candidate = buildDetection(observation,
                                                         currentMat.size(),
                                                         config.minJointConfidence);
                const float score = rankingScore(candidate, currentMat.size());
                if (score > bestScore) {
                    bestScore = score;
                    bestDetection = candidate;
                }
            }

            if (bestScore >= 0.0f) {
                detection = bestDetection;
            }
        }

        return true;
    }

    std::string backendName() const override {
        return "Vision Pose";
    }

private:
    VNDetectHumanBodyPoseRequest* request = nil;
};

}  // namespace

std::unique_ptr<PoseDetectorBackend> createVisionPoseDetector() {
    return std::make_unique<VisionPoseDetector>();
}

}  // namespace mtb

#endif
