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
    Eigen::Matrix<double, 4, 4> cam2robot_transform{};
    Eigen::Matrix<double, 3, 3> inv_camera_matrix{};

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

    /**
     * @brief Compute camera matrix from parameters
     * 
     * @param f_x 
     * @param f_y 
     * @param s 
     */
    void compute_inv_camera_matrix(double f_x, double f_y, double s, double px, double py);

  public:
    PositionEstimator(double x, double y, double z, 
                      double pitch, double f_x, double f_y, double s, 
                      double px, double py, double avg_height) {     
      compute_transform_from_xyzp(x, y, z, pitch);
      compute_inv_camera_matrix(f_x, f_y, s, px, py);
      avg_human_height = avg_height;
    }

    PositionEstimator(const std::unordered_map<std::string, double>& robot_params) {
      double x = robot_params.at("DX_CAM2ROBOT_CENTER");
      double y = robot_params.at("DY_CAM2ROBOT_CENTER");
      double z = robot_params.at("DZ_CAM2ROBOT_CENTER");
      double pitch = robot_params.at("PITCH_CAM2ROBOT_CENTER");
      
      double f_x = robot_params.at("CAM_FOCAL_LEN_X");
      double f_y = robot_params.at("CAM_FOCAL_LEN_Y");
      double s = robot_params.at("CAM_SKEW");
      double avg_height = robot_params.at("AVG_HUMAN_HEIGHT");

      double img_w = robot_params.at("IMG_WIDTH_REQ");
      double img_h = robot_params.at("IMG_HEIGHT_REQ");

      PositionEstimator(x, y, z, pitch, f_x, f_y, s, img_w/2, img_h/2, avg_height);
    }
    // ~PositionEstimator();

    /**
     * @brief This function removes noise by discarding frames with low probability of human detection.
     * 
     * @param probability Human detection probability
     * @return whether we have decided the frame has a human in it or not
     */
    bool threshold_frame(double probability);

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
     * @return std::array<double, 3>: x, y, z position of a single human.
     */
    std::array<double, 3> estimate_xyz(Detection&);

    /**
     * @brief  This method estimates the xyz position of EACH detected human in the WORLD frame.
     * 
     * @param detections vector of Detection objs
     * @return std::vector<std::array<double, 3>>: x, y, z position of EACH human in ROBOT frame UNIT: [m]
     */
    std::vector<std::array<double, 3>> estimate_all_xyz(std::vector<Detection>& detection);

    /**
     * @brief Get the cam2robot transform object
     * 
     * @return const Eigen::Matrix<double, 4, 4>& 
     */
    const Eigen::Matrix<double, 4, 4>& get_cam2robot_transform() {
      return cam2robot_transform;
    }

    /**
     * @brief Get the camera matrix object
     * 
     * @return const Eigen::Matrix<2, 2, double>&
     */
    const Eigen::Matrix<double, 3, 3>& get_inv_camera_matrix() {
      return inv_camera_matrix;
    }
};

