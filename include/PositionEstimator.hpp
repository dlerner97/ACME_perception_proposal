#pragma once

#include <array>
#include <vector>
#include <string>
#include <unordered_map>
#include <eigen3/Eigen/Dense>

#include "Detection.hpp"

class PositionEstimator {
  private:
    double NO_HUMAN_DETECTED = -1;
    double prob_threshold = 0;
    double avg_human_height = 0;
    bool human_detected = false;
    Eigen::Matrix<double, 4, 4> cam2robot_transform{};

  /**
   * @brief Computes homogenous transform between robot center and camera
   * 
   * @param x change in x
   * @param y change in y
   * @param z change in z
   * @param p change in pitch
   * @result Changes the cam2robot_transform variable
   */
    void compute_transform_from_xyzp(double x, double y, double z, double p);

  public:
    PositionEstimator(const std::unordered_map<std::string, double>& robot_params) {
      double x = robot_params.at("DX_CAM2ROBOT_CENTER");
      double y = robot_params.at("DY_CAM2ROBOT_CENTER");
      double z = robot_params.at("DZ_CAM2ROBOT_CENTER");
      double pitch = robot_params.at("PITCH_CAM2ROBOT_CENTER");
      compute_transform_from_xyzp(x, y, z, pitch);
    }
    // ~PositionEstimator();

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

