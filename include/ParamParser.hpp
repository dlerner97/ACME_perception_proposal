/**
 * @file Detection.hpp
 * @author Dani Lerner
 * @author Diane Ngo
 * @brief Param Parser header
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <array>
#include <vector>
#include <string>
#include <unordered_map>

struct Var {
    Var(std::string _name, std::string _default_unit) :
        name{_name}, default_unit{_default_unit} {}

    std::string name;
    std::string default_unit;
};

class ParamParser {
 private:
    const std::vector<Var>& _var_list;

    /**
     * @brief Non checks whether character is not alpha-numeric
     * 
     * @param c 
     * @return boolean  
     */
    bool isnot_alnum(char c);

 public:
    explicit ParamParser(const std::vector<Var>& var_list):
        _var_list{var_list} {}

    /**
     * @brief Extracts the unit from a string
     * 
     * @param line of text
     * @return the unit specified and the rest of the text on that line
     */
    std::array<std::string, 2> get_unit(const std::string &line);

    /**
     * @brief Splits variable into name, value, unit
     * 
     * @param line of text
     * @return an array of strings corresponding to name, value, unit
     */
    std::array<std::string, 3> split_variable(const std::string &line);

    /**
     * @brief Uses the value and unit to determine true value for a given variable
     * 
     * @param var Variable information
     * @return true variable value
     */
    double set_variable(const std::array<std::string, 3>& var);

    /**
     * @brief Parse robot parameter textfile.
     * 
     * @param file name and path of the robot parameter file
     * @return a dictionary corresponding to each robot parameter and their corresponding values.
     */
    std::unordered_map<std::string, double> parse_robot_params(
        std::string file);
};
