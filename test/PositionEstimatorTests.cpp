#include <math.h>
#include <vector>
#include <gtest/gtest.h>
#include <eigen3/Eigen/Dense>

#include "../include/Detection.hpp"
#include "../include/ParamParser.hpp"
#include "../include/PositionEstimator.hpp"

TEST(PositionEstimatorTests, MissingRobotParamsTest) {
  std::vector<Var> params{{"DX_CAM2ROBOT_CENTER", "m"}, {"DZ_CAM2ROBOT_CENTER", "m"}, {"DY_CAM2ROBOT_CENTER", "m"},
                          {"PITCH_CAM2ROBOT_CENTER", "rad"}, {"CAM_SCEW", "px"},
                          {"CAM_FOCAL_LEN_X", "px"}, {"CAM_FOCAL_LEN_Y", "px"},
                          {"IMG_HEIGHT_REQ", "px"}, {"IMG_WIDTH_REQ", "px"},
                          {"AVG_HUMAN_HEIGHT", "m"}, {"DETECTION_PROBABILITY_THRESHOLD", "fraction"}};

  ParamParser parser(params);
  auto ret_params = parser.parse_robot_params("./robot_params_test.txt");
  EXPECT_ANY_THROW(PositionEstimator testimator(ret_params));
}

TEST(PositionEstimatorTests, BuildRobot2HumanTransformTest) {
  const double PI = std::atan(1.0)*4;
  PositionEstimator testimator(2.3, 5, 2.3, 90*PI/180.0, 0, 0, 0, 0, 0, 0);
  Eigen::Matrix<double, 4, 4> test_matrix;
  test_matrix <<  0, 0, 1, 2.3,
                  0, 1, 0,   5,
                 -1, 0, 0, 2.3,
                  0, 0, 0,   1;
  EXPECT_TRUE(test_matrix.isApprox(testimator.get_cam2robot_transform()));

  PositionEstimator testimator2(0, 0, -2.3, 0*PI/180.0, 0, 0, 0, 0, 0, 0);
  test_matrix << 1, 0, 0,    0,
                 0, 1, 0,    0,
                 0, 0, 1, -2.3,
                 0, 0, 0,    1;
  EXPECT_TRUE(test_matrix.isApprox(testimator2.get_cam2robot_transform()));
}

TEST(PositionEstimatorTests, BuildInvCamMatTest) {
  PositionEstimator testimator(0, 0, 0, 0, 1, 1, 0, 0, 0, 0);
  Eigen::Matrix<double, 3, 3> test_mat;
  test_mat << 1, 0, 0,
              0, 1, 0,
              0, 0, 1;
  EXPECT_TRUE(test_mat.isApprox(testimator.get_inv_camera_matrix()));
}

TEST(PositionEstimatorTests, ThresholdFrameTest) {
  PositionEstimator testimator(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  EXPECT_TRUE(testimator.threshold_frame(0.9));
  EXPECT_FALSE(testimator.threshold_frame(0.7));
}

TEST(PositionEstimatorTests, EstimateXYZTest) {
  Detection detection;
  detection.x = 100;
  detection.y = 200;
  detection.width = 50;
  detection.height = 130;

  std::vector<Var> params{{"DX_CAM2ROBOT_CENTER", "m"}, {"DZ_CAM2ROBOT_CENTER", "m"}, {"DY_CAM2ROBOT_CENTER", "m"},
                          {"PITCH_CAM2ROBOT_CENTER", "rad"}, {"CAM_SCEW", "px"},
                          {"CAM_FOCAL_LEN_X", "px"}, {"CAM_FOCAL_LEN_Y", "px"},
                          {"IMG_HEIGHT_REQ", "px"}, {"IMG_WIDTH_REQ", "px"},
                          {"AVG_HUMAN_HEIGHT", "m"}, {"DETECTION_PROBABILITY_THRESHOLD", "fraction"}};

  ParamParser parser(params);
  auto ret_params = parser.parse_robot_params("../robot_params/robot_params.txt");
  PositionEstimator testimator(ret_params);
  auto cam_mat = testimator.get_inv_camera_matrix();
  auto cam2robot = testimator.get_cam2robot_transform();
  auto result = testimator.estimate_xyz(detection);

}