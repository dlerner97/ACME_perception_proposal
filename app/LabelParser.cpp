/**
 * @file LabelParser.cpp
 * @author Dani Lerner
 * @author Diane Ngo
 * @brief Label Parser definition
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>

#include "../include/utils.hpp"
#include "../include/Detection.hpp"
#include "../include/LabelParser.hpp"

std::array<int, 2> LabelParser::parse_corner(const std::string& corner) {
    auto open_bracket = std::find(corner.begin(), corner.end(), '[');
    if (open_bracket == corner.end())
        throw InvalidFile();

    auto close_bracket = std::find(open_bracket, corner.end(), ']');
    if (close_bracket == corner.end())
        throw InvalidFile();

    auto corner_vals = split(std::string(open_bracket+1, close_bracket), ',');
    if (corner_vals.size() != 2)
        throw InvalidFile();

    std::array<int, 2> out{};
    for (std::size_t i=0; i < 2; i++) {
        try {
            out[i] = std::stoi(corner_vals[i]);
        } catch (std::invalid_argument const&) {
            throw InvalidFile();
        }
    }
    return out;
}

Detection LabelParser::parse_detection(const std::string& corner1,
        const std::string& corner2) {
    Detection detection;
    std::array<int, 2> corner_coords1;
    std::array<int, 2> corner_coords2;

    try {
        corner_coords1 = parse_corner(corner1);
        corner_coords2 = parse_corner(corner2);
    } catch (InvalidFile const&) {
        throw InvalidFile();
    }

    detection.x = std::min(corner_coords1[0], corner_coords2[0]);
    detection.y = std::min(corner_coords1[1], corner_coords2[1]);
    detection.width = std::max(corner_coords1[0],
        corner_coords2[0]) - detection.x;
    detection.height = std::max(corner_coords1[1],
        corner_coords2[1]) - detection.y;
    return detection;
}

std::shared_ptr<TestImage> LabelParser::parse_file(
        const std::string& file_path) {
    std::ifstream infile(file_path.c_str());
    std::shared_ptr<TestImage> test_image_ptr = std::make_shared<TestImage>();
    if (infile) {
        std::string file_name;
        getline(infile, file_name);

        std::string line;
        while (getline(infile, line)) {
            if (line == "Detection") {
                std::string top_left, bottom_right;
                getline(infile, top_left);
                getline(infile, bottom_right);
                try {
                    auto detection = parse_detection(top_left, bottom_right);
                    test_image_ptr->all_detections.push_back(detection);
                } catch (InvalidFile const&) {
                    throw InvalidFile("File " + file_name +
                        " is invalid. Please fix file before continuing.");
                }
            }
        }
        test_image_ptr->name = file_name;
        test_image_ptr->img = cv::imread("../dataset/1/" + file_name + ".png");
        return test_image_ptr;
    }
    throw InvalidFile("Path " + file_path +
        " is invalid. Please add the file before continuing.");
}

std::vector<std::shared_ptr<TestImage> > LabelParser::read_labeled_test_images(
        const std::string& dir_path) {
    std::vector<std::shared_ptr<TestImage> > out{};
    for (const auto& entry : boost::filesystem::directory_iterator(dir_path)) {
            auto test_image_ptr = parse_file(entry.path().string());
            out.push_back(test_image_ptr);
    }

    return out;
}
