/**
 * @file HumanDetector.hpp
 * @author Dani Lerner
 * @author Diane Ngo
 * @brief Human Detector header
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
#include <fstream>
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
    std::array<int, 2> img_dim_{};
    std::vector<cv::String> detection_classes{};
    std::vector<std::string> classes{};

    double detection_probability_threshold{};
    double nms_threshold{};
    double score_threshold{};

    const std::string coco_path;

    cv::dnn::Net net;

    /**
     * @brief Parse the DNN return values.
     * 
     * @param detections 
     * @param show_detections 
     * @return std::shared_ptr<std::vector<Detection> > all detections in image.
     */
    std::shared_ptr<std::vector<Detection> > parse_dnn_output(
      const std::vector<cv::Mat>& detections,
      cv::Mat* img_ptr, bool show_detections);

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
    void draw_pred(int classId, float conf, int left, int top,
      int right, int bottom, cv::Mat* frame);

 public:
    HumanDetector(const std::unordered_map<std::string, double>& robot_params,
      const std::string& _coco_name_path,
      const std::string& _yolo_cfg_path, const std::string& _yolo_weight_path) :
      net{cv::dnn::readNetFromDarknet(_yolo_cfg_path, _yolo_weight_path)}
    {
      img_dim_[0] = static_cast<int>(robot_params.at("IMG_WIDTH_REQ"));
      img_dim_[1] = static_cast<int>(robot_params.at("IMG_HEIGHT_REQ"));
      detection_probability_threshold = robot_params.at(
        "DETECTION_PROBABILITY_THRESHOLD");
      nms_threshold = robot_params.at("NMS_THRESHOLD");
      score_threshold = robot_params.at("SCORE_THRESHOLD");

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

    /**
     * @brief Prepares frame for human detection and NN input
     * 
     * @cite https://github.com/spmallick/learnopencv
     * 
     * @param img Original image to be prepared for NN
     * @return CV matrix for NN prepared frame
     */
    std::shared_ptr<cv::Mat> prep_frame(const cv::Mat& img);

    /**
     * @brief Detects humans in a given image.
     * 
     * @param prepped_frame A pre-processed frame for NN input
     * @return A detection obj for each human detected in frame.
     */
    std::shared_ptr<std::vector<Detection> > detect(cv::Mat&,
      bool show_detections = false);

    /**
     * @brief Gets the image dimensions (width and height)
     * @return Array of image dimensions
     */
    std::array<int, 2> get_img_dims();
};

