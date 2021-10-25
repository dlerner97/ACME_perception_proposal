/**
 * @file main.cpp
 * @author Dani Lerner
 * @author Diane Ngo
 * @brief main
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "../include/VisionAPI.hpp"
#include "../include/params_vec.hpp"
#include "../include/ParamParser.hpp"
#include "../include/LabelParser.hpp"
#include "../include/HumanDetector.hpp"

using std::vector;

int main() {
    std::string coco_name_path = "../robot_params/coco.names";
    std::string yolo_cfg_path = "../robot_params/yolov4.cfg";
    std::string yolo_weights_path = "../robot_params/yolov4.weights";

    ParamParser parser(all_params::params);
    auto ret_params = parser.parse_robot_params(
        "../robot_params/robot_params.txt"
    );

    VisionAPI vision(ret_params,
                     coco_name_path,
                     yolo_cfg_path,
                     yolo_weights_path
    );

    auto img = cv::imread("../dataset/1/1_500.png");
    auto all_xyz = vision.get_xyz(img, true);

    for (const auto& one_detect : *all_xyz) {
        std::cout << "Position of Human: x\t: " 
                  << one_detect[0] << "\ty: "
                  << one_detect[1] << "\tz: "
                  << one_detect[2]
                  << std::endl;
    }

    vision.print_alerts(*all_xyz);
    cv::waitKey(0);
    return 0;
}
