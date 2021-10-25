/**
 * @file utils.cpp
 * @author Dani Lerner
 * @author Diane Ngo
 * @brief utils definition
 * @version 0.1
 * @date 2021-10-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include <vector>
#include <sstream>

#include "../include/utils.hpp"

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim /* =' ' */) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}