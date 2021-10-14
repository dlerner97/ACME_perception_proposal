#include <vector>
#include <memory>
#include <opencv4/opencv2/opencv.hpp>

#include "../include/HumanDetector.hpp"

std::shared_ptr<cv::Mat> HumanDetector::prep_frame(cv::Mat& orig_frame) {}

std::vector<Detection> HumanDetector::detect(cv::Mat& prepped_frame) {}