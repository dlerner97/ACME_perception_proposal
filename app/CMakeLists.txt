add_executable(shell-app
               main.cpp
               ParamParser.cpp
               PositionEstimator.cpp
               VisionAPI.cpp
               HumanDetector.cpp
               LabelParser.cpp
               utils.cpp
)

find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(/home/diane/opencv/build)
include_directories(/usr/local/include/opencv4)
target_link_libraries(shell-app ${OpenCV_LIBS})

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
