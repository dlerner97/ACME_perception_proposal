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
    double avg_human_height{};
    double cam_focal_len{};
    double cam_pix_density{};
    std::array<double, 2> img_center{};
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
    PositionEstimator(double x, double y, double z, double pitch, double f, double pix_density, 
                      double img_w, double img_h, double threshold, double avg_height) {     
      compute_transform_from_xyzp(x, y, z, pitch);
      cam_focal_len = f;
      cam_pix_density = pix_density;
      avg_human_height = avg_height;
      img_center = {img_w/2.0, img_h/2.0};
      prob_threshold = threshold;
    }

    PositionEstimator(const std::unordered_map<std::string, double>& robot_params) {
      double x = robot_params.at("DX_CAM2ROBOT_CENTER");
      double y = robot_params.at("DY_CAM2ROBOT_CENTER");
      double z = robot_params.at("DZ_CAM2ROBOT_CENTER");
      double pitch = robot_params.at("PITCH_CAM2ROBOT_CENTER");
      
      double f = robot_params.at("CAM_FOCAL_LEN");
      double pix_density = robot_params.at("CAM_PIXEL_DENSITY");
      
      double avg_height = robot_params.at("AVG_HUMAN_HEIGHT");
      double threshold = robot_params.at("DETECTION_PROBABILITY_THRESHOLD");

      double img_w = robot_params.at("IMG_WIDTH_REQ");
      double img_h = robot_params.at("IMG_HEIGHT_REQ");

      PositionEstimator(x, y, z, pitch, f, pix_density, img_w, img_h, threshold, avg_height);
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
};

