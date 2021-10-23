#include <math.h>
#include <vector>
#include <gtest/gtest.h>
#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>

#include "../include/Detection.hpp"
#include "../include/ParamParser.hpp"
#include "../include/HumanDetector.hpp"

const std::string coco_name_path = "../robot_params/coco.names";
const std::string yolo_cfg_path = "../robot_params/yolov4.cfg";
const std::string yolo_weights_path = "../robot_params/yolov4.weights";

TEST(HumanDetectorTests, MissingRobotParamsTest) {
    std::unordered_map<std::string, double> ret_params{};
    ret_params["Hello"] = 3.0;
    EXPECT_ANY_THROW(HumanDetector testimator(ret_params, coco_name_path, yolo_cfg_path, yolo_weights_path));
}

TEST(HumanDetectorTests, MissingYoloFilesTest) {
    std::ifstream yolo_cfg("../robot_params/yolov4.cfg");
    ASSERT_TRUE(yolo_cfg);
    std::ifstream yolo_weights("../robot_params/yolov4.weights");
    ASSERT_TRUE(yolo_weights);
    std::ifstream coco_names("../robot_params/coco.names");
    ASSERT_TRUE(coco_names);
}

TEST(HumanDetectorTests, CorrectFrameSizeTest) {
    std::unordered_map<std::string, double> ret_params{};
    ret_params["IMG_WIDTH_REQ"] = 13.0;
    ret_params["IMG_HEIGHT_REQ"] = 21.0;
    HumanDetector testimator(ret_params, coco_name_path, yolo_cfg_path, yolo_weights_path);

    cv::Mat img = cv::imread("../dataset/0/0_0.png");
    std::shared_ptr<cv::Mat> img_ptr = testimator.prep_frame(img);
    int prep_frame_width = img_ptr -> cols;
    int prep_frame_height = img_ptr -> rows;

    ASSERT_EQ(13, prep_frame_width);
    ASSERT_EQ(21, prep_frame_height);

}

