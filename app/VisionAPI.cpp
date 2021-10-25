#include <vector>
#include <opencv2/opencv.hpp>

#include "../include/VisionAPI.hpp"

std::vector<std::array<double, 3> > VisionAPI::get_xyz(const cv::Mat& /* orig_frame */) {return std::vector<std::array<double, 3>>{};}