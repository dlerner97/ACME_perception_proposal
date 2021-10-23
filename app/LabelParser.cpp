#include <vector>
#include <string>
#include <filesystem>

#include "../include/LabelParser.hpp"

std::vector<TestImage> LabelParser::read_labeled_test_images(const std::string& dir_path) {
    for (const auto& entry : std::filesystem::directory_iterator(dir_path)) {
        std::cout << entry.path() << std::endl;
    }
}