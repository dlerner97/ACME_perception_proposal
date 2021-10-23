#include <vector>
#include <memory>
#include <opencv2/opencv.hpp>

#include "../include/Detection.hpp"
#include "../include/HumanDetector.hpp"

std::shared_ptr<cv::Mat> HumanDetector::prep_frame(cv::Mat& /* orig_frame */) {
    
}

std::vector<Detection> HumanDetector::detect(cv::Mat& /* prepped_frame */) {return std::vector<Detection>{};}

std::array<int, 2> HumanDetector::get_img_dims() {
    return img_dim_;
}