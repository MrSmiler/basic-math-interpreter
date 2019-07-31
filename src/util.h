#ifndef UTIL_H
#define UTIL_H

/*
    this file contains
    code about usefull utilities

*/

#include <string>
#include <vector>


namespace util{

// create substring from a string
// it cuts the string from the 'begin' to 'end' position
std::string createString(int begin, int end, std::string);


// determines a character is a alphabet character
bool isAlpha(char ch);


// determines a character is a number
bool isNumber(char ch);

bool isOperator(char ch);
bool isOperator(std::string ch);

// split string with a deliminator
std::vector<std::string> split(std::string str, char delim);

// convert a string to integer
int convertToNumber(std::string num);

}

#endif // UTIL_H
