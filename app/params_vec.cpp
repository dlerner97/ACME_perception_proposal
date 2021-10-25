/**
 * @file params_vec.cpp
 * @author Dani Lerner
 * @author Diane Ngo
 * @brief params vector declaration
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <vector>
#include "../include/params_vec.hpp"
#include "../include/ParamParser.hpp"

std::vector<Var> all_params::params = {
    {"DX_CAM2ROBOT_CENTER", "m"},
    {"DY_CAM2ROBOT_CENTER", "m"},
    {"DZ_CAM2ROBOT_CENTER", "m"},
    {"PITCH_CAM2ROBOT_CENTER", "rad"},
    {"AVG_HUMAN_HEIGHT", "m"},
    {"CAM_FOCAL_LEN", "m"},
    {"CAM_PIXEL_DENSITY", "ppm"},
    {"DETECTION_PROBABILITY_THRESHOLD", "fraction"},
    {"SCORE_THRESHOLD", "fraction"},
    {"NMS_THRESHOLD", "fraction"},
    {"IMG_WIDTH_REQ", "px"},
    {"IMG_HEIGHT_REQ", "px"},
    {"LOW_ALERT_THRESHOLD", "m"},
    {"HIGH_ALERT_THRESHOLD", "m"}
};
