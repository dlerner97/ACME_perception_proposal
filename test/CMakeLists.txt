set(GTEST_SHUFFLE 1)

add_executable(
    cpp-test
    main.cpp
    PositionEstimatorTests.cpp
    ParamParserTests.cpp
    HumanDetectorTests.cpp
    ../app/LabelParser.cpp
    ../app/PositionEstimator.cpp
    ../app/ParamParser.cpp
    ../app/utils.cpp
)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

target_include_directories(cpp-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(cpp-test PUBLIC gtest ${OpenCV_LIBS})

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)