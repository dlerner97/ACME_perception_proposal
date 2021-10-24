#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>

#include "../include/Detection.hpp"
#include "../include/LabelParser.hpp"
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

    cv::Mat img = cv::imread("/home/diane/ACME_perception_proposal/dataset/0/0_0.png");
    cv::Mat img_ptr = testimator.prep_frame(img);
    int prep_frame_width = img_ptr.cols;
    int prep_frame_height = img_ptr.rows;

    ASSERT_EQ(13, prep_frame_width);
    ASSERT_EQ(21, prep_frame_height);
}

TEST(HumanDetectorTests, HumanDetectionAccuracyTest) {
    /*
     * Create test that goes through all of the different images and run it through NN
     * See upper left corner, width + height
     * and see how accurate our human detector class is
     */
    LabelParser label_parser;
    auto labels = label_parser.read_labeled_test_images("../dataset/labels");
    for (const auto& label : labels) {
        const std::vector<Detection>& true_detections = label->all_detections;
        const std::string& name = label->name;
        cv::Mat& img = label->img; //removed const

        // Basically in this for loop, I go through every single label in the /dataset/label
        // directory. This not only contains the list of all detections in a given image, it
        // also contains the image itself. So all you have to do here is run the human detector
        // (first the image preprocessing then the detection itself) using the "cv::Mat img" as input.
        // The output of the human_detector.detect() should also be a list of detections.
        // Therefore, compare the output detections of the detect() method to the true_detections I've
        // defined above.
        std::unordered_map<std::string, double> ret_params{};
        HumanDetector testimator(ret_params, coco_name_path, yolo_cfg_path, yolo_weights_path);
        cv::Mat prep_img = testimator.prep_frame(img); //could'nt use const for prep frame
        std::vector<Detection> output_detections = testimator.detect(prep_img);

        // accuracy calculation?
    }
}

