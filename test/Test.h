#pragma once


#include <iostream>


inline void debug_test(bool statement, const char* file, int lineNo, const char* statmentStr)
{
    if (!statement)
    {
        std::cout << "[Test failed] \"" << statmentStr << "\" expected to be true at " << file << ":" << lineNo << std::endl;
        exit(-1);
    }
}

#define TEST(x) debug_test(x,__FILE__,__LINE__,#x)
