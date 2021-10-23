#pragma once

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

#include "./Detection.hpp"

struct TestImage {
    std::vector<Detection> all_detections{};
    cv::Mat img;
};


class LabelParser {
//   private:

  public:
    std::vector<TestImage> read_labeled_test_images(const std::string& dir_path);
};