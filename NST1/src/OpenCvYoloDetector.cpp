#include "YoloDetector.h"

#include "ofMain.h"

#include <opencv2/dnn.hpp>

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

class OpenCvYoloDetector final : public YoloDetectorBackend {
public:
    bool load(const YoloDetectorConfig& config, std::string& error) override {
        try {
            net = cv::dnn::readNet(config.onnxModelPath);
            net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
            net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
        } catch (const std::exception& e) {
            error = e.what();
            net = cv::dnn::Net();
            return false;
        }
        if (net.empty()) {
            error = "OpenCV DNN returned an empty net";
            return false;
        }
        return true;
    }

    bool infer(const cv::Mat& currentMat,
               const YoloDetectorConfig& config,
               std::vector<YoloDetection>& detections,
               std::string& error) override {
        detections.clear();
        if (net.empty()) {
            error = "OpenCV YOLO backend not loaded";
            return false;
        }

        cv::Mat out;
        try {
            cv::Mat blob = cv::dnn::blobFromImage(currentMat,
                                                  1.0 / 255.0,
                                                  cv::Size(config.inputSize, config.inputSize),
                                                  cv::Scalar(),
                                                  true,
                                                  false);
            net.setInput(blob);
            std::vector<cv::Mat> outputs;
            net.forward(outputs, net.getUnconnectedOutLayersNames());
            if (outputs.empty()) return true;
            out = outputs[0];
        } catch (const cv::Exception& e) {
            error = e.what();
            return false;
        } catch (const std::exception& e) {
            error = e.what();
            return false;
        }

        if (out.dims == 3 && out.size[1] < out.size[2]) {
            out = out.reshape(1, out.size[1]);
            cv::transpose(out, out);
        } else if (out.dims == 3) {
            out = out.reshape(1, out.size[1]);
        }

        const float xFactor = static_cast<float>(currentMat.cols) / static_cast<float>(config.inputSize);
        const float yFactor = static_cast<float>(currentMat.rows) / static_cast<float>(config.inputSize);

        std::vector<int> nmsClassIds;
        std::vector<float> nmsScores;
        std::vector<cv::Rect> nmsBoxes;

        for (int i = 0; i < out.rows; ++i) {
            const float* data = out.ptr<float>(i);
            if (!data) continue;

            int classId = -1;
            float maxClassScore = -1.0f;
            for (int c = 0; c < out.cols - 4; ++c) {
                const std::string className = ofToLower(yoloClassName(c));
                if (!config.classFilter.empty() && config.classFilter.count(className) == 0) continue;
                const float score = data[4 + c];
                if (score > maxClassScore) {
                    maxClassScore = score;
                    classId = c;
                }
            }
            if (classId < 0 || maxClassScore < config.confidenceThreshold) continue;

            const float cx = data[0];
            const float cy = data[1];
            const float w = data[2];
            const float h = data[3];

            const int left = std::max(0, static_cast<int>((cx - 0.5f * w) * xFactor));
            const int top = std::max(0, static_cast<int>((cy - 0.5f * h) * yFactor));
            const int width = std::min(currentMat.cols - left, static_cast<int>(w * xFactor));
            const int height = std::min(currentMat.rows - top, static_cast<int>(h * yFactor));
            if (width <= 1 || height <= 1) continue;

            nmsClassIds.push_back(classId);
            nmsScores.push_back(static_cast<float>(maxClassScore));
            nmsBoxes.emplace_back(left, top, width, height);
        }

        std::vector<int> indices;
        cv::dnn::NMSBoxes(nmsBoxes, nmsScores, config.confidenceThreshold, config.nmsThreshold, indices);
        detections.reserve(indices.size());
        for (int idx : indices) {
            YoloDetection det;
            det.box = nmsBoxes[idx];
            det.classId = nmsClassIds[idx];
            det.score = nmsScores[idx];
            detections.push_back(det);
        }
        return true;
    }

    std::string backendName() const override {
        return "OpenCV CPU";
    }

private:
    cv::dnn::Net net;
};

}  // namespace

std::unique_ptr<YoloDetectorBackend> createOpenCvYoloDetector() {
    return std::make_unique<OpenCvYoloDetector>();
}

}  // namespace mtb
