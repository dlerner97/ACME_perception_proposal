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

class HumanDetector {
  private:
    /**
     * @brief Necessary img dimension
     *
     * @details width, height
     */
    std::array<int, 2> img_dim_{};
    std::vector<cv::String> detection_classes{};
    std::vector<std::string> classes{};

    const std::string coco_path;

    cv::dnn::Net net;

    /**
     * @brief Draws prediction on image
     * 
     * @cite https://github.com/spmallick/learnopencv
     * 
     * @param classId 
     * @param conf 
     * @param left 
     * @param top 
     * @param right 
     * @param bottom 
     * @param frame 
     */
    void drawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat& frame);

  public:
    HumanDetector(const std::unordered_map<std::string, double>& robot_params, const std::string& _coco_name_path,
                  const std::string& _yolo_cfg_path, const std::string& _yolo_weight_path) :
                  net{cv::dnn::readNetFromDarknet(_yolo_cfg_path, _yolo_weight_path)} {

      img_dim_[0] = static_cast<int>(robot_params.at("IMG_WIDTH_REQ"));
      img_dim_[1] = static_cast<int>(robot_params.at("IMG_HEIGHT_REQ"));
      net.setPreferableBackend(cv::dnn::DNN_TARGET_CPU);

      std::ifstream ifs(_coco_name_path.c_str());
      std::string line;
      while (getline(ifs, line)) classes.push_back(line);

      auto outLayers = net.getUnconnectedOutLayers();
      auto layerNames = net.getLayerNames();
      detection_classes.resize(outLayers.size());
      for (std::size_t i = 0; i < outLayers.size(); i++) 
          detection_classes[i] = layerNames[outLayers[i] - 1];
    }
    // ~HumanDetector();

    /**
     * @brief Prepares frame for human detection and NN input
     * 
     * @cite https://github.com/spmallick/learnopencv
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

