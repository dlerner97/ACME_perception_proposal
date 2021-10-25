#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "../include/Detection.hpp"
#include "../include/HumanDetector.hpp"

std::shared_ptr<cv::Mat> HumanDetector::prep_frame(cv::Mat& img) {
    std::array<int, 2> prepped_img_dims = get_img_dims();
    int prepped_img_width = prepped_img_dims[0];
    int prepped_img_height = prepped_img_dims[1];
    auto prepped_img = std::make_shared<cv::Mat>();
    cv::resize(img, *prepped_img, cv::Size(prepped_img_width, prepped_img_height), cv::INTER_LINEAR);
    return prepped_img;
}

std::vector<Detection> HumanDetector::detect(cv::Mat& prepped_img) {
    std::array<int, 2> prepped_img_dims = get_img_dims();
    int prepped_img_height = prepped_img_dims[0];
    int prepped_img_width = prepped_img_dims[1];
    // Create a 4D blob from a frame.
    cv::Mat blob;
    cv::dnn::blobFromImage(prepped_img, blob, 1/255.0, cv::Size(prepped_img_width, prepped_img_height), cv::Scalar(0,0,0), true, false);
        
    //Sets the input to the network
    net.setInput(blob);
        
    // Runs the forward pass to get output of the output layers
    std::vector<cv::Mat> detections;
    net.forward(detections, detection_classes);

    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    std::vector<Detection> ret_detections{};
    for (std::size_t i=0; i<detections.size(); i++) {
        auto data = (float*)(detections[i].data);
        for (std::size_t j = 0; j < detections[i].rows; ++j, data+=detections[i].cols) {
            cv::Mat scores = detections[i].row(j).colRange(5, detections[i].cols);
            cv::Point classIdPt;
            double confidence;
            cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPt);
            if (confidence > 0.8) {
                int centerX = static_cast<int>(data[0] * prepped_img.cols);
                int centerY = static_cast<int>(data[1] * prepped_img.rows);
                int width = static_cast<int>(data[2] * prepped_img.cols);
                int height = static_cast<int>(data[3] * prepped_img.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;  

                classIds.push_back(classIdPt.x);
                confidences.push_back(static_cast<float>(confidence));
                boxes.push_back(cv::Rect(left, top, width, height));
            }
        }
    }

    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, 0.8, 0.4, indices);

    for (size_t i = 0; i < indices.size(); ++i) {
        int idx = indices[i];
        cv::Rect box = boxes[idx];
        drawPred(classIds[idx], confidences[idx], box.x, box.y,
                 box.x + box.width, box.y + box.height, prepped_img);
        ret_detections.push_back({confidences[idx], box.x, box.y, box.width, box.height});      
    }

    cv::imshow("img", prepped_img);
    cv::waitKey(0);

    return ret_detections;
}

void HumanDetector::drawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat& frame) {
    //Draw a rectangle displaying the bounding box
    rectangle(frame, cv::Point(left, top), cv::Point(right, bottom), cv::Scalar(255, 178, 50), 3);
    
    //Get the label for the class name and its confidence
    std::string label = cv::format("%.2f", conf);
    if (!classes.empty())
    {
        CV_Assert(classId < (int)classes.size());
        label = classes[classId] + ":" + label;
    }
    
    //Display the label at the top of the bounding box
    int baseLine;
    cv::Size labelSize = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
    top = cv::max(top, labelSize.height);
    rectangle(frame, cv::Point(left, top - std::round(1.5*labelSize.height)), cv::Point(left + std::round(1.5*labelSize.width), top + baseLine), cv::Scalar(255, 255, 255), cv::FILLED);
    putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0,0,0),1);
}

std::array<int, 2> HumanDetector::get_img_dims() {
    return img_dim_;
}