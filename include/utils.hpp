#pragma once

#include <string>
#include <vector>

/**
 * @brief Splits a string into a series of alpha-numeric words
 * 
 * @cite https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
 * 
 * @param input 
 * @result Changes "out" container
 */
template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

/**
 * @brief Splits string by the delimeter and returns a vector
 * 
 * @param s 
 * @param delim 
 * @return std::vector<std::string> 
 */
std::vector<std::string> split(const std::string &s, char delim=' ') {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}