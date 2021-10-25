#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "../include/ParamParser.hpp"
#include "../include/HumanDetector.hpp"
// #include "../include/VisionAPI.hpp"
#include "../include/LabelParser.hpp"

using std::cout;
using std::endl;
using std::vector;

int main() {
    std::string coco_name_path = "../robot_params/coco.names";
    std::string yolo_cfg_path = "../robot_params/yolov4.cfg";
    std::string yolo_weights_path = "../robot_params/yolov4.weights";

    vector<Var> params{{"DX_CAM2ROBOT_CENTER", "m"}, {"DZ_CAM2ROBOT_CENTER", "m"},
                       {"DY_CAM2ROBOT_CENTER", "m"}, {"PITCH_CAM2ROBOT_CENTER", "rad"},
                       {"CAM_FOCAL_LEN", "m"}, {"CAM_PIXEL_DENSITY", "ppm"},
                       {"AVG_HUMAN_HEIGHT", "m"}, {"DETECTION_PROBABILITY_THRESHOLD", "fraction"}, 
                       {"IMG_WIDTH_REQ", "px"}, {"IMG_HEIGHT_REQ", "px"},
                       {"LOW_ALERT_THRESHOLD", "m"}, {"HIGH_ALERT_THRESHOLD", "m"}};

    ParamParser parser(params);
    auto ret_params = parser.parse_robot_params("../robot_params/robot_params.txt");
    HumanDetector detector(ret_params, coco_name_path, yolo_cfg_path, yolo_weights_path);
    auto img = cv::imread("../dataset/1/1_500.png");
    auto prepped = detector.prep_frame(img);
    detector.detect(*prepped);
    
    return 0;
}
