#pragma once

#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


#include "Detection.hpp"

using namespace cv;
using namespace dnn;

class HumanDetector {
  private:
    /**
     * @brief Necessary img dimension
     *
     * @details width, height
     */
    std::array<int, 2> img_dim_{};
    std::vector<std::string> detection_classes{};

    const std::string coco_path;
    const std::string yolo_cfg_path;
    const std::string yolo_weights_path;

    // void populate_detection_classes(std::string coco_name_path);

  public:
    HumanDetector(const std::unordered_map<std::string, double>& robot_params, const std::string& _coco_name_path,
                  const std::string& _yolo_cfg_path, const std::string& _yolo_weight_path) :
                  coco_path{_coco_name_path}, yolo_cfg_path{_yolo_cfg_path}, yolo_weights_path{_yolo_weight_path} {
      img_dim_[0] = robot_params.at("IMG_WIDTH_REQ");
      img_dim_[1] = robot_params.at("IMG_HEIGHT_REQ");


//      get_img_dims(img_dim_);

      // detection_classes = populate_detection_classes();

    }
    // ~HumanDetector();

    /**
     * @brief Prepares frame for human detection and NN input
     *
     * @param img Original image to be prepared for NN
     * @return CV matrix for NN prepared frame
     */
    std::shared_ptr<cv::Mat> prep_frame(cv::Mat& img);

    /**
     * @brief Detects humans in a given image.
     * 
     * @param prepped_frame A pre-processed frame for NN input
     * @return A detection obj for each human detected in frame.
     */
    std::vector<Detection> detect(cv::Mat&);

    /**
     * @brief Gets the image dimensions (width and height)
     * @return Array of image dimensions
     */
    std::array<int, 2> get_img_dims();
};

