#include<utility>

#include "Test.h"

#include <Evaluator.h>


int main(const int argc, const char *argv[])
{
    std::string s1 = "12 45 + 43";
    Parser p1(s1);
    TEST(p1.GetError() == ErrorType::TWO_NUMS_IN_ROW);

    std::string s2 = "12.23 + 457 - 9.9,9";
    Parser p2(s2);
    TEST(p2.GetError() == ErrorType::TOO_MANY_DOTS);

    std::string s3 = "123921342.45 * 999999";
    Parser p3(s3);
    TEST(p3.GetError() == ErrorType::NUM_OVERFLOW);

    std::string s4 = "12.3 + a * 12.23";
    Parser p4(s4);
    TEST(p4.GetError() == ErrorType::WRONG_CHAR);

    std::string s5 = "((12.23 + 457) - 9.9";
    Parser p5(s5);
    Evaluator e5(std::move(p5));
    TEST(e5.GetError() == ErrorType::BRACKETS_MESS);

    std::string s6 = "12 / (5.5 - 1.1 * 5)";
    Parser p6(s6);
    Evaluator e6(std::move(p6));
    e6.GetAnswer();
    TEST(e6.GetError() == ErrorType::DIVISION_BY_ZERO);

    
    return 0;
}
