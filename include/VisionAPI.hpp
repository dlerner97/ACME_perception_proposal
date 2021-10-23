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
//    HumanDetector detector;
    PositionEstimator estimator;
    std::array<double, 2> alert_thresholds{};

  public:
    VisionAPI(const std::unordered_map<std::string, double>& _robot_params) : 
      robot_params{_robot_params},
//      detector(_robot_params),
      estimator(_robot_params) {
        alert_thresholds[0] = robot_params.at("LOW_ALERT_THRESHOLD");
        alert_thresholds[1] = robot_params.at("HIGH_ALERT_THRESHOLD");
      }

    // ~VisionAPI();

    /**
     * @brief This method takes an image, finds all people within the image, and outputs the estimated postions in the ROBOT frame.
     * 
     * @param img
     * @return All estimated x, y, z positions of people in a given image.
     */
    std::vector<std::array<double, 3>> get_xyz(cv::Mat);
};
