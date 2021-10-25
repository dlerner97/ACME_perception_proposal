#include <vector>
#include <opencv2/opencv.hpp>
#include <math.h>
#include "../include/VisionAPI.hpp"

std::vector<std::array<double, 3> > VisionAPI::get_xyz(const cv::Mat&  orig_frame) {
    //Wraps detector + estimator, returns position of human in x, y, z
    auto prep_img = detector.prep_frame(orig_frame);
    auto detected = detector.detect(*prep_img);
    std::vector<std::array<double, 3> > ret;
    for (const auto& single_detected : detected) {
        if (estimator.threshold_frame(single_detected.probabilty)) {
            ret.push_back(estimator.estimate_xyz(single_detected));
        }
    }
    
    return ret;

}

double VisionAPI::calculate_distance(std::array<double, 3> xyz) {
    return std::hypot(xyz[0], xyz[1]);
}

void VisionAPI::print_alerts(const std::vector<std::array<double, 3> > &all_xyz) {
    double min_distance = 10;
    for (const auto& xyz : all_xyz) {
        double distance = calculate_distance(xyz);
        if (distance < min_distance) {
            min_distance = distance;
        }
    }
    if (min_distance < alert_thresholds[1]) {
        std::cout << "Human is " << min_distance << " meters away, danger!" << std::endl;
        std::cout << "Robot needs to stop." << std::endl;
    }
    else if (min_distance >= alert_thresholds[1] && min_distance <= alert_thresholds[0]) {
        std::cout << "Human is " << min_distance << " meters away. " << std::endl;
        std::cout << "Robot needs to redirect its path. " << std::endl;
    }
    else if (min_distance >= alert_thresholds[0]) {
        std::cout << "Human is " << min_distance << " meters away. " << std::endl;
        std::cout << "Robot will continue its current path. " << std::endl;
    }
}

