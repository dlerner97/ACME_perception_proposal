#pragma once

#include <array>
#include <vector>

#include "Detection.hpp"

class PositionEstimator {
  private:
    double NO_HUMAN_DETECTED = -1;
    double prob_threshold = 0;
    double avg_human_height = 0;
    bool human_detected = false;
    std::array<std::array<double, 4>, 4> cam2robot_transform{};

  public:
    PositionEstimator(/* args */);
    ~PositionEstimator();

    /**
     * @brief This function removes noise by discarding frames with low probability of human detection.
     * 
     * @param probability Human detection probability
     * @result human_detected bool flag is updated
     */
    void threshold_frame(double probability);

    /**
     * @brief This function approximates the z location of the human in the CAMERA frame based on the size of the bounding box.
     * 
     * @param detection Detection obj
     * @return approximate depth of human in camera frame UNIT: [m] 
     */
    double approximate_camera_z(Detection& detection);

    /**
     * @brief This method estimates the xyz position of a SINGLE detected human in the WORLD frame.
     * 
     * @param detection Detection obj
     * @return x, y, z position of a single human.
     */
    std::array<double, 3> estimate_xyz(Detection&);

    /**
     * @brief  This method estimates the xyz position of EACH detected human in the WORLD frame.
     * 
     * @param detections vector of Detection objs
     * @return x, y, z position of EACH human in ROBOT frame UNIT: [m]
     */
    std::vector<std::array<double, 3>> estimate_all_xyz(std::vector<Detection>& detection);
};

