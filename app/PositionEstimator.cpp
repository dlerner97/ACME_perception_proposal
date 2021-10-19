#include <math.h>
#include <array>
#include <vector>
#include <eigen3/Eigen/Dense>

#include "../include/PositionEstimator.hpp"

void PositionEstimator::set_values(double x, double y, double z, double pitch, double f, double pix_density, 
                double img_w, double img_h, double threshold, double avg_height) {
     compute_transform_from_xyzp(x, y, z, pitch);
     cam_focal_len = f;
     cam_pix_density = pix_density;
     avg_human_height = avg_height;
     img_center = {img_w/2.0, img_h/2.0};
     prob_threshold = threshold;
}

void PositionEstimator::compute_transform_from_xyzp(double x, double y, double z, double p) {
    auto sin_p = sin(p);
    auto cos_p = cos(p);
    
    cam2robot_transform <<  cos_p, 0, sin_p, x,
                                0, 1,     0, y,
                           -sin_p, 0, cos_p, z,
                                0, 0,     0, 1;
}

bool PositionEstimator::threshold_frame(double probability) {
     return probability > prob_threshold;
}

double PositionEstimator::approximate_camera_z(Detection& detection) {
     return avg_human_height*cam_focal_len*cam_pix_density/detection.height;
}

std::array<double, 3> PositionEstimator::estimate_xyz(Detection& /* detection */) {return std::array<double, 3>{};}

std::vector<std::array<double, 3> > PositionEstimator::estimate_all_xyz(std::vector<Detection>& /* detections */) {return std::vector<std::array<double, 3> > {};}