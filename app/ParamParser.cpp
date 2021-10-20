
#include <iostream>
#include <math.h>
#include <cctype>
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>

#include "../include/ParamParser.hpp"

bool ParamParser::isnot_alnum(char c) {
    return !std::isalnum(c);
}

template <typename Out>
void ParamParser::split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> ParamParser::split(const std::string &s, char delim=' ') {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::array<std::string, 2> ParamParser::get_unit(const std::string &line) {
    typedef std::array<std::string, 2> strs; 
    auto unit_begin = std::find(line.begin(), line.end(), '[');
    if (unit_begin != line.end()) {
        auto unit_end = std::find(unit_begin, line.end(), ']');
        if (unit_end != line.end())
            return strs{std::string(unit_begin+1, unit_end), std::string(line.begin(), unit_begin)};
        else
            throw std::runtime_error("No end bracket provided. Please fix '" + line + "' line robot parameter text document.");
    } else
        std::cerr << "No unit provided. Assigning default unit." << std::endl;
    
    return strs{std::string(""), line};
}

std::array<std::string, 3> ParamParser::split_variable(const std::string &line) {
    std::array<std::string, 3> ret;
    std::vector<std::string> line_vec;

    auto unit_ret = get_unit(line);
    ret[2] = unit_ret[0];

    auto line_no_unit = unit_ret[1];

    if (std::find(line_no_unit.begin(), line_no_unit.end(), '=') != line_no_unit.end()) {
        line_vec = split(line_no_unit, '=');

        if (line_vec.size() > 2) 
            throw std::runtime_error("Multiple '=' signs on line. Please fix '" + line + "' line robot parameter text document.");

        for (auto& val : line_vec) {
            val.erase(std::remove_if(val.begin(), val.end(), isspace), val.end());
        }
        ret[0] = line_vec[0];
        ret[1] = line_vec[1];
    }
    return ret;
}

double ParamParser::set_variable(const std::array<std::string, 3>& var) {
    
    double out{};
    try {
        out = std::stod(var[1]);
    } catch (std::invalid_argument) {
        throw std::runtime_error("Conversion to double not working. Please fix the '" + var[0] + "' variable on robot parameter text document.");
    }
    
    bool name_found{false};
    for (const auto &expected_var : _var_list) {
        if (var[0] == expected_var.name) {
            name_found = true;
            std::string upon_error = "Unnacceptable unit: '" + var[2] + "'. " + var[0] + " should have units of ";
            std::string upon_error_end = " Please fix the robot parameter text document.";
            if (expected_var.default_unit == "m") {
                if (var[2] == "" || var[2] == "m");
                else if (var[2] == "cm") out /= 100.0;
                else if (var[2] == "mm") out /= 1000.0;
                else throw std::runtime_error(upon_error + "m, cm, or mm." + upon_error_end);
            } else if (expected_var.default_unit == "radians" || expected_var.default_unit == "rad") {
                static const double PI = std::atan(1.0)*4;
                if (var[2] == "" || var[2] == "rad" || var[2] == "rads" || var[2] == "radian" || var[2] == "radians");
                else if (var[2] == "deg" || var[2] == "degs" || var[2] == "degrees" || var[2] == "degree") out *= PI/180;
                else throw std::runtime_error(upon_error + "radians, rad, deg, or degrees." + upon_error_end);
            } else if (expected_var.default_unit == "fraction" || expected_var.default_unit == "frac") {
                if (var[2] == "" || var[2] == "fraction" || var[2] == "frac");
                else if (var[2] == "per" || var[2] == "percent" || var[2] == "%") out /= 100.0;
                else throw std::runtime_error(upon_error + "fraction, percent, or %." + upon_error_end);
            } else if (expected_var.default_unit == "px" || expected_var.default_unit == "pixels") {
                if (var[2] == "" || var[2] == "px" || var[2] == "pixels" || var[2] == "pixels");
                else throw std::runtime_error(upon_error + "pixels or px." + upon_error_end);
            } else if (expected_var.default_unit == "ppm") {
                if (var[2] == "" || var[2] == "ppm");
                else if (var[2] == "ppi") out *= 1000/25.4;
                else if (var[2] == "ppmm") out *= 1000;
                else throw std::runtime_error(upon_error + "ppi, ppmm or ppm (i.e. pixels per inch, mm, or meter)." + upon_error_end);
            }
            break;
        }
    }
    if (!name_found) throw std::runtime_error("Cannot find '" + var[0] + "' in the expected robot parameters. Please update 'main.cpp' by adding the {'name', 'default_unit'} to the 'params' vector.");

    return out;
}

std::unordered_map<std::string, double> ParamParser::parse_robot_params(std::string file) {
    std::unordered_map<std::string, double> robot_param_dict;
    std::ifstream infile(file.c_str());
    std::string line;
    if (infile) {
        while (getline(infile, line)) {
            if (line.length() < 3) continue;
            auto variable = split_variable(line);
            robot_param_dict[variable[0]] = set_variable(variable);
        }
    } else
        throw std::runtime_error("Cannot find robot params file.");
    infile.close();
    return robot_param_dict;   
}
