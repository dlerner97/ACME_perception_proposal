/**
 * @file PositionEstimator.cpp
 * @author Dani Lerner
 * @author Diane Ngo
 * @brief Position Estimator definition
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <math.h>
#include <eigen3/Eigen/Dense>

#include <array>
#include <vector>
#include <memory>

#include "../include/PositionEstimator.hpp"

void PositionEstimator::set_values(double x, double y, double z,
          double pitch, double f, double pix_density,
          double img_w, double img_h, double avg_height) {
     compute_transform_from_xyzp(x, y, z, pitch);
     cam_focal_len = f;
     cam_pix_density = pix_density;
     avg_human_height = avg_height;
     img_center = {img_w/2.0, img_h/2.0};
}

void PositionEstimator::compute_transform_from_xyzp(
          double x, double y, double z, double p) {
     auto sin_p = sin(p);
     auto cos_p = cos(p);

     cam2robot_transform <<  cos_p, 0, sin_p, x,
                                   0, 1,     0, y,
                              -sin_p, 0, cos_p, z,
                                   0, 0,     0, 1;
}

double PositionEstimator::approximate_camera_z(const Detection& detection) {
     return avg_human_height*cam_focal_len*cam_pix_density/detection.height;
}

std::array<double, 3> PositionEstimator::estimate_xyz(
          const Detection& detection) {
     auto camera_z = approximate_camera_z(detection);
     double middle_detection_x = detection.x + detection.width/2;
     double middle_detection_y = detection.y + detection.height/2;

     double camz_over_fxdensity = camera_z/(cam_focal_len*cam_pix_density);
     double camera_x = (middle_detection_x - img_center[0])*camz_over_fxdensity;
     double camera_y = (middle_detection_y - img_center[1])*camz_over_fxdensity;

     Eigen::Vector4d camera_frame;
     camera_frame << camera_x, camera_y, camera_z, 1;
     auto rob_frame = cam2robot_transform*camera_frame;
     return std::array<double, 3>{rob_frame[0], rob_frame[1], rob_frame[2]};
}

std::shared_ptr<std::vector<std::array<double, 3> > >
          PositionEstimator::estimate_all_xyz(
          const std::vector<Detection>& detections) {
     auto all_xyz = std::make_shared<std::vector<std::array<double, 3> > >();
     for (const auto& detection : detections)
          all_xyz->push_back(estimate_xyz(detection));

     return all_xyz;
}
