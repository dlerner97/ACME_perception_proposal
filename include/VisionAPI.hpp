#pragma once

#include <array>
#include <vector>
#include <string>
#include <unordered_map>
#include <opencv2/opencv.hpp>

#include "./HumanDetector.hpp"
#include "./PositionEstimator.hpp"
#include "./Detection.hpp"

class VisionAPI {
  private:
    const std::unordered_map<std::string, double>& robot_params;
    HumanDetector detector;
    PositionEstimator estimator;
    std::array<double, 2> alert_thresholds{};

  public:
    VisionAPI(const std::unordered_map<std::string, double>& _robot_params, const std::string& _coco_name_path,
              const std::string& _yolo_cfg_path, const std::string& _yolo_weight_path) : 
      robot_params{_robot_params},
      detector(_robot_params, _coco_name_path, _yolo_cfg_path, _yolo_weight_path),
      estimator(_robot_params) {
        alert_thresholds[0] = robot_params.at("LOW_ALERT_THRESHOLD");
        alert_thresholds[1] = robot_params.at("HIGH_ALERT_THRESHOLD");
      }

    /**
     * @brief This method takes an image, finds all people within the image, and outputs the estimated postions in the ROBOT frame.
     * 
     * @param img
     * @return All estimated x, y, z positions of people in a given image.
     */
    std::vector<std::array<double, 3> > get_xyz(const cv::Mat&);

    /**
     * @brief Calculates the distance of how far the human is away from the robot
     * 
     * @param xyz passes in x, y z position
     * @return double distance of how far the human is away
     */
    double calculate_distance(std::array<double, 3> xyz);

    /**
     * @brief Prints the robot's actions based on how far the human is away from the robot
     * 
     * @param alert_thresholds high alert is 1m, low alert is 3m
     */
    void print_alerts(const std::vector<std::array<double, 3> > &alert_thresholds);
};
