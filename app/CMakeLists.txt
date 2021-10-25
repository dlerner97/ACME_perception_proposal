add_executable(shell-app
               main.cpp
               ParamParser.cpp
               PositionEstimator.cpp
               VisionAPI.cpp
               HumanDetector.cpp
               LabelParser.cpp
               utils.cpp
               Detection.cpp
               params_vec.cpp
)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS filesystem) 

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
target_link_libraries(shell-app ${OpenCV_LIBS} ${Boost_LIBRARIES})

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
