#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <opencv2/opencv.hpp>

#include "../include/LabelParser.hpp"

std::string cutdown_name(std::string name) {
    auto first_slash = find(name.begin(), name.end(), '/');
    if (first_slash != name.end()) {
        return cutdown_name(std::string(first_slash+1, name.end()));
    }
    auto dot = find(name.begin(), name.end(), '.');
    if (dot == name.end())
        throw std::invalid_argument("Cannot find file type.");

    return std::string(name.begin(), dot);
}

std::vector<TestImage> LabelParser::read_labeled_test_images(const std::string& dir_path) {
    for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
        std::cout << cutdown_name(entry.path()) << std::endl;
    }
}