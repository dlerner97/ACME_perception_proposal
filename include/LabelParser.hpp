/**
 * @file Detection.hpp
 * @author Dani Lerner
 * @author Diane Ngo
 * @brief Label Parser header
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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
    /**
     * @brief Parses an individual corner. Conversion from string form to int
     * 
     * @param corner 
     * @return std::array<int, 2> corner x-coord, y-coord
     */
    std::array<int, 2> parse_corner(const std::string& corner);

    /**
     * @brief Parses an individual detection
     * 
     * @param corner1: std::string
     * @param corner2: std::string
     * @return Detection instance
     */
    Detection parse_detection(const std::string& corner1,
      const std::string& corner2);

 public:
    /**
     * @brief Parses labeled image file
     * 
     * @param file_path: std::string
     * @return std::shared_ptr<TestImage> shared pointer to a TestImage instance. 
     */
    std::shared_ptr<TestImage> parse_file(const std::string& file_path);

    /**
     * @brief Parses ever labeled image file in the input directory
     * 
     * @param dir_path: path of the desired dir
     * @return std::vector<std::shared_ptr<TestImage> >
     */
    std::vector<std::shared_ptr<TestImage> > read_labeled_test_images(
      const std::string& dir_path);
};
