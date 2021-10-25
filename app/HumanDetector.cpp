/**
 * @file HumanDetector.cpp
 * @author Dani Lerner
 * @author Diane Ngo
 * @brief Human Detector definition
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <vector>
#include <memory>
#include <opencv2/opencv.hpp>

#include "../include/Detection.hpp"
#include "../include/HumanDetector.hpp"

std::shared_ptr<cv::Mat> HumanDetector::prep_frame(const cv::Mat& img) {
    std::array<int, 2> prepped_img_dims = get_img_dims();
    int prepped_img_width = prepped_img_dims[0];
    int prepped_img_height = prepped_img_dims[1];
    auto prepped_img = std::make_shared<cv::Mat>();
    cv::resize(img, *prepped_img, cv::Size(prepped_img_width,
        prepped_img_height), cv::INTER_LINEAR);
    return prepped_img;
}

std::shared_ptr<std::vector<Detection> >
        HumanDetector::parse_dnn_output(const std::vector<cv::Mat>&
        detections, cv::Mat* img, bool show_detections) {
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;
    for (std::size_t i = 0; i < detections.size(); i++) {
        auto data = reinterpret_cast<float*>(detections[i].data);
        for (int j = 0; j < detections[i].rows; ++j, data+=detections[i].cols) {
            cv::Mat scores = detections[i].row(j).colRange(5,
                detections[i].cols);
            cv::Point classIdPt;
            double confidence;
            cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPt);
            if ((confidence > detection_probability_threshold) &&
                (classes[classIdPt.x] == "person")) {
                int centerX = static_cast<int>(data[0] * img_dim_[0]);
                int centerY = static_cast<int>(data[1] * img_dim_[1]);
                int width = static_cast<int>(data[2] * img_dim_[0]);
                int height = static_cast<int>(data[3] * img_dim_[1]);
                int left = centerX - width / 2;
                int top = centerY - height / 2;

                classIds.push_back(classIdPt.x);
                confidences.push_back(static_cast<float>(confidence));
                boxes.push_back(cv::Rect(left, top, width, height));
            }
        }
    }

    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, score_threshold,
                      nms_threshold, indices);

    auto ret_detections_ptr = std::make_shared<std::vector<Detection> >();
    for (size_t i = 0; i < indices.size(); ++i) {
        int idx = indices[i];
        cv::Rect box = boxes[idx];
        if (show_detections)
            draw_pred(classIds[idx], confidences[idx], box.x, box.y,
                     box.x + box.width, box.y + box.height, img);
        ret_detections_ptr->push_back({box.x, box.y, box.width, box.height});
    }
    return ret_detections_ptr;
}

std::shared_ptr<std::vector<Detection> > HumanDetector::detect(
        cv::Mat& prepped_img, bool show_detections) {
    cv::Mat blob;
    cv::dnn::blobFromImage(prepped_img, blob, 1/255.0,
        cv::Size(img_dim_[0], img_dim_[1]), cv::Scalar(0, 0, 0), true, false);
    net.setInput(blob);

    std::vector<cv::Mat> detections;
    net.forward(detections, detection_classes);
    auto ret_detections_ptr = parse_dnn_output(detections, &prepped_img,
        show_detections);

    return ret_detections_ptr;
}

void HumanDetector::draw_pred(int classId, float conf, int left, int top,
        int right, int bottom, cv::Mat* frame) {
    rectangle(*frame, cv::Point(left, top), cv::Point(right, bottom),
        cv::Scalar(255, 178, 50), 3);
    std::string label = cv::format("%.2f", conf);
    if (!classes.empty()) {
        CV_Assert(classId < static_cast<int>(classes.size()));
        label = classes[classId] + ":" + label;
    }

    int baseLine;
    cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX,
        0.5, 1, &baseLine);
    top = cv::max(top, labelSize.height);
    rectangle(*frame, cv::Point(left, top - std::round(1.5*labelSize.height)),
        cv::Point(left + std::round(1.5*labelSize.width), top + baseLine),
        cv::Scalar(255, 255, 255), cv::FILLED);
    putText(*frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX,
        0.75, cv::Scalar(0, 0, 0), 1);
}

std::array<int, 2> HumanDetector::get_img_dims() {
    return img_dim_;
}
