#include <iostream>
#include <vector>

#include "../include/ParamParser.hpp"
#include "../include/VisionAPI.hpp"

using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<Var> params{{"DX_CAM2ROBOT_CENTER", "m"}, {"DZ_CAM2ROBOT_CENTER", "m"},
                       {"DY_CAM2ROBOT_CENTER", "m"}, {"PITCH_CAM2ROBOT_CENTER", "rad"},
                       {"CAM_FOCAL_LEN", "m"}, {"CAM_PIXEL_DENSITY", "ppm"},
                       {"AVG_HUMAN_HEIGHT", "m"}, {"DETECTION_PROBABILITY_THRESHOLD", "fraction"}, 
                       {"IMG_WIDTH_REQ", "px"}, {"IMG_HEIGHT_REQ", "px"},
                       {"LOW_ALERT_THRESHOLD", "m"}, {"HIGH_ALERT_THRESHOLD", "m"}};

    ParamParser parser(params);
    auto ret_params = parser.parse_robot_params("../robot_params/robot_params.txt");
    for (const auto& param : ret_params) {
        cout << param.first << ", " << param.second << endl;
    }
    VisionAPI vision_api(ret_params);
    return 0;
}
