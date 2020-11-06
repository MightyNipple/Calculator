#include "Test.h"

#include <Evaluator.h>

#define EPSILON 0.005

float abs(float f)
{
    return f < 0 ? -f : f;
}

bool performTest(std::string s, float f)
{
    Evaluator e = (Evaluator)Parser(s);
    float f2 = e.GetAnswer();

    if (e.GetError())
    {
        return false;
    }

    return abs(f2 - f) < EPSILON;
}

int main(const int argc, const char *argv[])
{
    std::string s1 = "123.34 + 34 - 3.4";
    float f1 = 123.34 + 34 - 3.4;
    TEST(performTest(s1, f1));

    std::string s2 = "-12.7 * (1000 - 34.11)";
    float f2 = -12.7 * (1000 - 34.11);
    TEST(performTest(s2, f2));

    std::string s3 = "(3 + 5) * (-12.4 * -53.6)";
    float f3 = (3 + 5) * (-12.4 * -53.6);
    TEST(performTest(s3, f3));

    std::string s4 = "1 / 2/ 3 / 4/ 5 / 6";
    float f4 = 1 / 2 / 3 / 4 / 5 / 6;
    TEST(performTest(s4, f4));

    std::string s5 = "17.6 / ((-1.11 * 9.3) - 44)";
    float f5 = 17.6 / ((-1.11 * 9.3) - 44.0);
    TEST(performTest(s5, f5));

    std::string s6 = "0 + 0 * 2 - (12.3 - 3,55)";
    float f6 = 0 + 0 * 2 - (12.3 - 3.55);
    TEST(performTest(s6, f6));

    std::string s7 = "2.2 * 3.3 / 4.4 + 12.4 - 54.99 * (2 / 3)";
    float f7 = 2.2 * 3.3 / 4.4 + 12.4 - 54.99 * (2.0 / 3.0);
    TEST(performTest(s7, f7));
}
