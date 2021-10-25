/**
 * @file HumanDetectorTests.cpp
 * @author Dani Lerner
 * @author Diane Ngo
 * @brief Human Detector Tests
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <math.h>
#include <gtest/gtest.h>
#include <eigen3/Eigen/Dense>

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <boost/filesystem.hpp>

#include "../include/Detection.hpp"
#include "../include/LabelParser.hpp"
#include "../include/ParamParser.hpp"
#include "../include/HumanDetector.hpp"

const auto coco_name_path = "../robot_params/coco.names";
const auto yolo_cfg_path = "../robot_params/yolov4.cfg";
const auto yolo_weights_path = "../robot_params/yolov4.weights";

std::vector<Var> params{{"DX_CAM2ROBOT_CENTER", "m"},
        {"DY_CAM2ROBOT_CENTER", "m"}, {"DZ_CAM2ROBOT_CENTER", "m"},
        {"PITCH_CAM2ROBOT_CENTER", "rad"}, {"AVG_HUMAN_HEIGHT", "m"},
        {"CAM_FOCAL_LEN", "m"}, {"CAM_PIXEL_DENSITY", "ppm"},
        {"DETECTION_PROBABILITY_THRESHOLD", "fraction"},
        {"SCORE_THRESHOLD", "fraction"}, {"NMS_THRESHOLD", "fraction"},
        {"IMG_WIDTH_REQ", "px"}, {"IMG_HEIGHT_REQ", "px"},
        {"LOW_ALERT_THRESHOLD", "m"}, {"HIGH_ALERT_THRESHOLD", "m"}};

TEST(HumanDetectorTests, MissingRobotParamsTest) {
    std::unordered_map<std::string, double> ret_params{};
    ret_params["Hello"] = 3.0;
    EXPECT_ANY_THROW(HumanDetector detector(ret_params, coco_name_path,
        yolo_cfg_path, yolo_weights_path));
}

TEST(HumanDetectorTests, MissingYoloFilesTest) {
    std::ifstream yolo_cfg(yolo_cfg_path);
    ASSERT_TRUE(yolo_cfg);
    std::ifstream yolo_weights(yolo_weights_path);
    ASSERT_TRUE(yolo_weights);
    std::ifstream coco_names(coco_name_path);
    ASSERT_TRUE(coco_names);
}

TEST(HumanDetectorTests, CorrectFrameSizeTest) {
    std::unordered_map<std::string, double> ret_params{};
    int width = 100;
    int height = 200;

    ret_params["IMG_WIDTH_REQ"] = static_cast<double>(width);
    ret_params["IMG_HEIGHT_REQ"] = static_cast<double>(height);
    ret_params["DETECTION_PROBABILITY_THRESHOLD"] = 0.0;
    ret_params["SCORE_THRESHOLD"] = 0.0;
    ret_params["NMS_THRESHOLD"] = 0.0;

    HumanDetector detector(ret_params, coco_name_path,
        yolo_cfg_path, yolo_weights_path);
    cv::Mat img = cv::imread("../dataset/0/0_0.png");
    auto img_ptr = detector.prep_frame(img);
    int prep_frame_width = img_ptr->cols;
    int prep_frame_height = img_ptr->rows;

    ASSERT_EQ(width, prep_frame_width);
    ASSERT_EQ(height, prep_frame_height);
}

Detection getClosestDiff(const Detection& detection,
        const std::vector<Detection>& all_true) {
    int min_sum = 5000;
    Detection closest_diff{};
    for (const auto& single_true : all_true) {
        Detection diff = detection - single_true;
        int sum = diff.x + diff.y + diff.width + diff.height;
        if (sum < min_sum) {
            min_sum = sum;
            closest_diff = diff;
        }
    }
    return closest_diff;
}

/**
 * @brief This test specifically looks through images that have >= 1 detection.
 * 
 */
TEST(HumanDetectorTests, HumanDetectionAccuracyTest) {
    if (boost::filesystem::exists("../robot_params/yolov4.weights")) {
        ParamParser parser(params);
        auto ret_params = parser.parse_robot_params(
            "../robot_params/robot_params.txt");

        HumanDetector detector(ret_params, coco_name_path,
            yolo_cfg_path, yolo_weights_path);

        int num_imgs = 0;
        int num_true_detections = 0;
        int num_detected_detections = 0;
        Detection sum_detect_diff{};

        LabelParser label_parser;
        auto labels = label_parser.read_labeled_test_images(
            "../dataset/labels");
        for (const auto& label : labels) {
            if (num_imgs > 50) break;
            const std::vector<Detection>&
                true_detections = label->all_detections;
            cv::Mat& img = label->img;
            auto prep_img = detector.prep_frame(img);
            auto output_detections = detector.detect(*prep_img);

            num_true_detections += true_detections.size();
            num_detected_detections += output_detections->size();

            for (const auto& output_detection : *output_detections) {
                sum_detect_diff += getClosestDiff(
                    output_detection, true_detections);
            }
            num_imgs++;
        }

        double percent_detections = num_detected_detections/
            static_cast<double>(num_true_detections);
        double average_x_diff = sum_detect_diff.x/
            static_cast<double>(num_true_detections);
        double average_y_diff = sum_detect_diff.y/
            static_cast<double>(num_true_detections);
        double average_width_diff = sum_detect_diff.width/
            static_cast<double>(num_true_detections);
        double average_height_diff = sum_detect_diff.height/
            static_cast<double>(num_true_detections);

        std::cout << "Percent detected: " << 100*percent_detections
            << " %" << std::endl;

        EXPECT_GE(percent_detections, 0.80);
        EXPECT_LT(average_x_diff, 30);
        EXPECT_LT(average_y_diff, 30);
        EXPECT_LT(average_width_diff, 30);
        EXPECT_LT(average_height_diff, 30);
    }
    EXPECT_TRUE(true);
}

/**
 * @brief Checks if string ends with a given substr
 * @cite https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c
 * 
 * @param fullString 
 * @param ending 
 * @return true 
 * @return false 
 */
bool hasEnding(std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(),
            ending.length(), ending));
    } else {
        return false;
    }
}

/**
 * @brief This test specifically looks at imgs with no humans present
 * 
 */
TEST(HumanDetectorTests, NoDetectionsPresentTest) {
    if (boost::filesystem::exists("../robot_params/yolov4.weights")) {
        ParamParser parser(params);
        auto ret_params = parser.parse_robot_params(
            "../robot_params/robot_params.txt");

        HumanDetector detector(ret_params, coco_name_path,
            yolo_cfg_path, yolo_weights_path);

        int num_images_w_fps = 0;
        int num_imgs = 0;

        for (const auto& entry :
                boost::filesystem::directory_iterator("../dataset/0")) {
            if (hasEnding(entry.path().string(), ".png")) {
                if (num_imgs > 50) break;
                auto img = cv::imread(entry.path().string());
                auto prepped_img = detector.prep_frame(img);
                auto results = detector.detect(*prepped_img);

                if (results->size() > 0)
                    num_images_w_fps++;
                num_imgs++;
            }
        }
        double accuracy = (num_imgs - num_images_w_fps)/
            static_cast<double>(num_imgs);
        std::cout << "Percent of no detections: " << 100*accuracy <<
            " %" << std::endl;
        EXPECT_GT(accuracy, 0.8);
    }
    EXPECT_TRUE(true);
}
