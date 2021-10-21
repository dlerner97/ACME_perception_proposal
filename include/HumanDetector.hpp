#pragma once

#include <array>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <opencv2/opencv.hpp>

#include "Detection.hpp"

class HumanDetector {
  private:
    /**
     * @brief Necessary img dimension
     * 
     * @details width, height
     */
    std::array<int, 2> img_dim{};
    std::vector<std::string> detection_classes{};

    // void populate_detection_classes(std::string coco_name_path);

  public:
    HumanDetector(const std::unordered_map<std::string, double>& robot_params, const std::string& coco_name_path,
                  const std::string& yolo_cfg_path, const std::string& yolo_weight_path) {
      img_dim[0] = robot_params.at("IMG_WIDTH_REQ");
      img_dim[1] = robot_params.at("IMG_HEIGHT_REQ");

      // detection_classes = populate_detection_classes();

    }
    // ~HumanDetector();

    /**
     * @brief Prepares frame for human detection and NN input
     * 
     * @param img description
     * @return shared pointer to the NN prepared frame
     */
    std::shared_ptr<cv::Mat> prep_frame(cv::Mat&);

    /**
     * @brief Detects humans in a given image.
     * 
     * @param prepped_frame A pre-processed frame for NN input
     * @return A detection obj for each human detected in frame.
     */
    std::vector<Detection> detect(cv::Mat&);
};

