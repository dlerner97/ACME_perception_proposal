#pragma once

#include <array>
#include <vector>
#include <memory>
#include <opencv2/opencv.hpp>

#include "Detection.hpp"

class HumanDetector {
  private:
    std::array<int, 2> img_dim;
  public:
    HumanDetector(/* args */);
    ~HumanDetector();

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

