#pragma once

#include <string>
#include <vector>
#include <stdexcept>

/**
 * @brief InvalidFile exception for parsers.
 * 
 */
class InvalidFile : public std::exception {
  private:
    std::string msg;

  public:
    explicit InvalidFile(const std::string& message = "") : msg{message} {}
	const char* what () const throw() {
    	return msg.c_str();
    }
};

/**
 * @brief Splits a string into a series of alpha-numeric words
 * 
 * @cite https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
 * 
 * @param input 
 * @result Changes "out" container
 */
template <typename Out>
void split(const std::string &s, char delim, Out result);

/**
 * @brief Splits string by the delimeter and returns a vector
 * 
 * @param s 
 * @param delim 
 * @return std::vector<std::string> 
 */
std::vector<std::string> split(const std::string &s, char delim=' ');