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
    int prepped_img_height = prepped_img_dims[0];
    int prepped_img_width = prepped_img_dims[1];
    auto prepped_img = std::make_shared<cv::Mat>();
    cv::resize(img, *prepped_img, Size(prepped_img_width, prepped_img_height), INTER_LINEAR);
    return prepped_img;
}

std::vector<Detection> HumanDetector::detect(cv::Mat& prepped_img) {
    // Load the network
    Net net = readNetFromDarknet(yolo_cfg_path, yolo_weights_path);
    // Set CPU
    net.setPreferableBackend(DNN_TARGET_CPU);

    std::array<int, 2> prepped_img_dims = get_img_dims();
    int prepped_img_height = prepped_img_dims[0];
    int prepped_img_width = prepped_img_dims[1];
    // Create a 4D blob from a frame.
    cv::Mat blob;
    blobFromImage(prepped_img, blob, 1/255.0, cv::Size(prepped_img_width, prepped_img_height), Scalar(0,0,0), true, false);
        
    //Sets the input to the network
    net.setInput(blob);
        
    // Runs the forward pass to get output of the output layers
    std::vector<cv::Mat> outs;
    // net.forward(outs, getOutputsNames(net));

    return std::vector<Detection>{};

}

std::array<int, 2> HumanDetector::get_img_dims() {
    return img_dim_;
}