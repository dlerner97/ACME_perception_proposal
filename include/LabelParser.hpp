#pragma once

#include <array>
#include <vector>
#include <string>
#include <memory>
#include <opencv2/opencv.hpp>

#include "./Detection.hpp"

struct TestImage {
    std::string name;
    std::vector<Detection> all_detections{};
    cv::Mat img;
};

class LabelParser {
  private:
    std::array<int, 2> parse_corner(const std::string& corner);
    Detection parse_detection(const std::string& corner1, const std::string& corner2);

  public:
    std::shared_ptr<TestImage> parse_file(const std::string& file_path); 
    std::vector<std::shared_ptr<TestImage> > read_labeled_test_images(const std::string& dir_path);
};