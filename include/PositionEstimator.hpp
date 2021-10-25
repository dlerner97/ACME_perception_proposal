#pragma once

#include <array>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <eigen3/Eigen/Dense>

#include "Detection.hpp"

class PositionEstimator {
  private:
    double avg_human_height{};
    double cam_focal_len{};
    double cam_pix_density{};
    std::array<double, 2> img_center{};
    Eigen::Matrix<double, 4, 4> cam2robot_transform{};

  /**
   * @brief This method sets all instance variables to avoid repeated code in constructors.
   * 
   * @param x 
   * @param y 
   * @param z 
   * @param pitch 
   * @param f 
   * @param pix_density 
   * @param img_w 
   * @param img_h 
   * @param avg_height 
   * 
   * @result Input instance vars should be defined.
   */
  void set_values(double x, double y, double z, double pitch, double f, double pix_density, 
                  double img_w, double img_h, double avg_height);

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
                      double img_w, double img_h, double avg_height) {     
      set_values(x, y, z, pitch, f, pix_density, img_w, img_h, avg_height);
    }

    PositionEstimator(const std::unordered_map<std::string, double>& robot_params) {
      double x = robot_params.at("DX_CAM2ROBOT_CENTER");
      double y = robot_params.at("DY_CAM2ROBOT_CENTER");
      double z = robot_params.at("DZ_CAM2ROBOT_CENTER");
      double pitch = robot_params.at("PITCH_CAM2ROBOT_CENTER");
      
      double f = robot_params.at("CAM_FOCAL_LEN");
      double pix_density = robot_params.at("CAM_PIXEL_DENSITY");
      
      double avg_height = robot_params.at("AVG_HUMAN_HEIGHT");

      double img_w = robot_params.at("IMG_WIDTH_REQ");
      double img_h = robot_params.at("IMG_HEIGHT_REQ");

      set_values(x, y, z, pitch, f, pix_density, img_w, img_h, avg_height);
    }

    /**
     * @brief This function approximates the z location of the human in the CAMERA frame based on the size of the bounding box.
     * 
     * @param detection Detection obj
     * @return approximate depth of human in camera frame UNIT: [m] 
     */
    double approximate_camera_z(const Detection& detection);

    /**
     * @brief This method estimates the xyz position of a SINGLE detected human in the WORLD frame.
     * 
     * @param detection Detection obj
     * @return std::array<double, 3>: x, y, z position of a single human.
     */
    std::array<double, 3> estimate_xyz(const Detection&);

    /**
     * @brief  This method estimates the xyz position of EACH detected human in the WORLD frame.
     * 
     * @param detections vector of Detection objs
     * @return std::shared_ptr<std::vector<std::array<double, 3>>>: x, y, z position of EACH human in ROBOT frame UNIT: [m]
     */
    std::shared_ptr<std::vector<std::array<double, 3> > > estimate_all_xyz(const std::vector<Detection>& detection);

    /**
     * @brief Get the cam2robot transform object
     * 
     * @return const Eigen::Matrix<double, 4, 4>& 
     */
    const Eigen::Matrix<double, 4, 4>& get_cam2robot_transform() {
      return cam2robot_transform;
    }
};

