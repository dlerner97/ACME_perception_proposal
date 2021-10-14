#include <array>
#include <vector>

#include "../include/PositionEstimator.hpp"

void PositionEstimator::threshold_frame(double probability) {}

double PositionEstimator::approximate_camera_z(Detection& detection) {}

std::array<double, 3> PositionEstimator::estimate_xyz(Detection& detection) {}

std::vector<std::array<double, 3>> PositionEstimator::estimate_all_xyz(std::vector<Detection>& detections) {}