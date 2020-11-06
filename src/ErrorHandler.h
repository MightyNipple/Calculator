#pragma once


#include <string>

enum ErrorType
{
    NO_ERROR = 0,
    TWO_NUMS_IN_ROW,
    TOO_MANY_DOTS,
    NUM_OVERFLOW,
    WRONG_CHAR,
    BRACKETS_MESS,
    DIVISION_BY_ZERO
};


extern std::string GetErrorDescription(ErrorType error);
