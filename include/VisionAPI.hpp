#pragma once

#include <array>
#include <vector>
#include <opencv2/opencv.hpp>

#include "./HumanDetector.hpp"
#include "./PositionEstimator.hpp"
#include "./Detection.hpp"

class VisionAPI {
  private:
    HumanDetector detector{};
    PositionEstimator estimator{};
    std::array<double, 2> alert_thresholds{};
  public:
    VisionAPI(/* args */);
    ~VisionAPI();

    /**
     * @brief This method takes an image, finds all people within the image, and outputs the estimated postions in the ROBOT frame.
     * 
     * @param img
     * @return All estimated x, y, z positions of people in a given image.
     */
    std::vector<std::array<double, 3>> get_xyz(cv::Mat);
};
