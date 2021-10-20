#include <math.h>
#include <vector>
#include <gtest/gtest.h>
#include <eigen3/Eigen/Dense>

#include "../include/Detection.hpp"
#include "../include/ParamParser.hpp"
#include "../include/PositionEstimator.hpp"

TEST(PositionEstimatorTests, MissingRobotParamsTest) {
  std::unordered_map<std::string, double> ret_params{};
  ret_params["Hello"] = 3.0;
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

TEST(PositionEstimatorTests, ThresholdFrameTest) {
  PositionEstimator testimator(0, 0, 0, 0, 0, 0, 0, 0, 0.8, 0);
  EXPECT_TRUE(testimator.threshold_frame(0.9));
  EXPECT_FALSE(testimator.threshold_frame(0.7));
}

TEST(PositionEstimatorTests, ApproximateZTest) {
  Detection detection;
  detection.height = 100;

  std::vector<Var> params{{"DX_CAM2ROBOT_CENTER", "m"}, {"DY_CAM2ROBOT_CENTER", "m"},
                          {"DZ_CAM2ROBOT_CENTER", "m"}, {"PITCH_CAM2ROBOT_CENTER", "rad"},
                          {"CAM_FOCAL_LEN", "m"}, {"CAM_PIXEL_DENSITY", "ppm"},
                          {"AVG_HUMAN_HEIGHT", "m"}, {"DETECTION_PROBABILITY_THRESHOLD", "fraction"},
                          {"IMG_WIDTH_REQ", "px"}, {"IMG_HEIGHT_REQ", "px"}};

  ParamParser parser(params);
  auto ret_params = parser.parse_robot_params("../test/robot_params_textfiles/position_estimator_params_test.txt");
  PositionEstimator testimator(ret_params);
  auto result = testimator.approximate_camera_z(detection);
  EXPECT_NEAR(result, 1, .01);
}

TEST(PositionEstimatorTests, EstimateXYZTest) {
  Detection detection;
  detection.x = 70;
  detection.y = 50;
  detection.width = 60;
  detection.height = 100;

  std::vector<Var> params{{"DX_CAM2ROBOT_CENTER", "m"}, {"DZ_CAM2ROBOT_CENTER", "m"},
                          {"DY_CAM2ROBOT_CENTER", "m"}, {"PITCH_CAM2ROBOT_CENTER", "rad"},
                          {"CAM_FOCAL_LEN", "m"}, {"CAM_PIXEL_DENSITY", "ppm"},
                          {"AVG_HUMAN_HEIGHT", "m"}, {"DETECTION_PROBABILITY_THRESHOLD", "fraction"}, 
                          {"IMG_WIDTH_REQ", "px"}, {"IMG_HEIGHT_REQ", "px"}};

  ParamParser parser(params);
  auto ret_params = parser.parse_robot_params("../test/robot_params_textfiles/position_estimator_params_test.txt");
  PositionEstimator testimator(ret_params);
  auto result = testimator.estimate_xyz(detection);
  
  typedef std::array<double, 3> XYZ;
  XYZ true_vals{1.02, 0, .03};
  for (XYZ::size_type i = 0; i < result.size(); i++) 
    EXPECT_NEAR(result[i], true_vals[i], .01);
}

TEST(PositionEstimatorTests, EstimateAllXYZTest) {
  Detection detection1;
  detection1.x = 80;
  detection1.y = 65;
  detection1.width = 20;
  detection1.height = 50;

  Detection detection2;
  detection2.x = 80;
  detection2.y = 60;
  detection2.width = 60;
  detection2.height = 100;  

  std::vector<Detection> all_detections{detection1, detection2};

  std::vector<Var> params{{"DX_CAM2ROBOT_CENTER", "m"}, {"DZ_CAM2ROBOT_CENTER", "m"},
                          {"DY_CAM2ROBOT_CENTER", "m"}, {"PITCH_CAM2ROBOT_CENTER", "rad"},
                          {"CAM_FOCAL_LEN", "m"}, {"CAM_PIXEL_DENSITY", "ppm"},
                          {"AVG_HUMAN_HEIGHT", "m"}, {"DETECTION_PROBABILITY_THRESHOLD", "fraction"}, 
                          {"IMG_WIDTH_REQ", "px"}, {"IMG_HEIGHT_REQ", "px"}};

  ParamParser parser(params);
  auto ret_params = parser.parse_robot_params("../test/robot_params_textfiles/position_estimator_params_test.txt");
  PositionEstimator testimator(ret_params);
  auto result = testimator.estimate_all_xyz(all_detections);
  
  typedef std::array<double, 3> XYZ;
  std::vector<XYZ> true_vals{{2.02, -0.4, 0.43}, {1.02, 0.2, -.17}};
  
  ASSERT_EQ(result.size(), std::vector<XYZ>::size_type{2});
  
  for (std::vector<XYZ>::size_type i = 0; i < result.size(); i++) {
    for (XYZ::size_type j = 0; j < result[i].size(); j++) 
      EXPECT_NEAR(result[i][j], true_vals[i][j], .01);
  }
}
