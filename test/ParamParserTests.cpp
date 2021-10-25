/**
 * @file ParamParserTests.cpp
 * @author Dani Lerner
 * @author Diane Ngo
 * @brief Param Parser Tests
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <gtest/gtest.h>
#include <fstream>

#include "../include/ParamParser.hpp"

TEST(ParamParserTest, TestTextFileExistence) {
    std::vector<Var> params{};
    ParamParser parser(params);
    EXPECT_ANY_THROW(parser.parse_robot_params(
        "../test/robot_params_textfiles/TextFileDoesNotExist.txt"));
    EXPECT_NO_THROW(parser.parse_robot_params(
        "../test/robot_params_textfiles/TextFileDoesExist.txt"));
}

TEST(ParamParserTest, VarVectorParserMismatchTest) {
    std::vector<Var> params{{"test", "m"}};
    ParamParser parser(params);
    EXPECT_ANY_THROW(parser.parse_robot_params(
        "../test/robot_params_textfiles/VarVectorMismatch.txt"));
    EXPECT_NO_THROW(parser.parse_robot_params(
        "../test/robot_params_textfiles/VarVectorMatch.txt"));
}

TEST(ParamParserTest, UnitTest) {
    typedef std::vector<Var> vec;
    vec params{{"no_unit_m", "m"}, {"m", "m"}, {"cm", "m"}, {"mm", "m"},
               {"no_unit_rad", "rad"}, {"rad", "rad"}, {"radians", "rad"},
                {"deg", "rad"}, {"degrees", "rad"},
               {"no_unit_frac", "frac"}, {"fraction", "frac"}, {"frac", "frac"},
                {"percent_sign", "frac"}, {"percent", "frac"},
               {"no_unit_px", "px"}, {"px", "px"}, {"pixels", "px"},
               {"no_unit_ppm", "ppm"}, {"ppm", "ppm"}, {"ppi", "ppm"},
                {"ppmm", "ppm"}};

    ParamParser parser(params);
    auto result = parser.parse_robot_params(
        "../test/robot_params_textfiles/UnitEq.txt");

    for (vec::size_type i = 0; i < 4; i++)
        EXPECT_NEAR(result.at(params[0].name), result.at(params[i].name), 0.1);

    for (vec::size_type i = 4; i < 9; i++)
        EXPECT_NEAR(result.at(params[4].name), result.at(params[i].name), 0.1);

    for (vec::size_type i = 9; i < 14; i++)
        EXPECT_NEAR(result.at(params[9].name), result.at(params[i].name), 0.1);

    for (vec::size_type i = 14; i < 17; i++)
        EXPECT_NEAR(result.at(params[14].name), result.at(params[i].name), 0.1);

    for (vec::size_type i = 17; i < 21; i++)
        EXPECT_NEAR(result.at(params[17].name), result.at(params[i].name), 0.1);
}

TEST(ParamParserTest, UnitNotAllowedTest) {
    typedef std::vector<Var> vec;
    vec params{{"a", "m"}, {"b", "rad"}, {"c", "frac"},
        {"d", "px"}, {"e", "ppm"}};
    ParamParser parser(params);

    std::ofstream ofs;
    std::string path = "../test/robot_params_textfiles/UnitNotAllowed.txt";
    std::vector<std::string> vector{"a = 1 [px]", "b = 1 [e]",
        "c = 1 [m]", "d = 1 [ppm]", "e = 1 [%]"};
    for (const auto& str : vector) {
        ofs.open(path, std::ofstream::out | std::ofstream::trunc);
        ofs << str << std::endl;
        ofs.close();

        ASSERT_ANY_THROW(parser.parse_robot_params(path));
    }
}

TEST(ParamParserTest, VariousInputsTest) {
    typedef std::vector<Var> vec;
    vec params{{"a", "m"}};
    ParamParser parser(params);

    std::ofstream ofs;
    std::string path =
        "../test/robot_params_textfiles/VariousInvalidInputs.txt";
    std::vector<std::string> vector{"a = 1 m]", "a = 1 [m", "a = 1 m",
        "1 = a [m]", "a = h [m]", "a = 1 = 1 [m]"};
    for (const auto& str : vector) {
        ofs.open(path, std::ofstream::out | std::ofstream::trunc);
        ofs << str << std::endl;
        ofs.close();

        ASSERT_ANY_THROW(parser.parse_robot_params(path));
    }

    vector = {"a = 1 [m]", "a = 1[m]", "a =1[m]", "a=1[m]",
        "    a =     1    [m]", "a = 1", "This is a comment\na = 1"};
    for (const auto& str : vector) {
        ofs.open(path, std::ofstream::out | std::ofstream::trunc);
        ofs << str << std::endl;
        ofs.close();

        ASSERT_NO_THROW(parser.parse_robot_params(path));
        EXPECT_EQ(parser.parse_robot_params(path).at("a"), 1);
    }
}
