#include "Test.h"
#include "Parser.h"

#include <vector>

using EntryType::NUMBER;
using EntryType::OPEN_BRACKET;
using EntryType::CLOSED_BRACKET;
using EntryType::OPERATOR;

bool performTest(const std::string& s, const std::vector<EntryType>& v)
{
    Parser p(s);

    for (EntryType et : v)
    {
        ExpressionEntry expr;
        if (!p.TryGetNextEntry(expr) || expr.type != et)
        {
            return false;
        }
    }
    return true;
}


int main(const int argc, const char *argv[])
{
    std::string s1 = "(1 + 2)*3.3";
    std::vector<EntryType> v1 = {OPEN_BRACKET, NUMBER, OPERATOR, NUMBER, CLOSED_BRACKET, OPERATOR, NUMBER};
    TEST(performTest(s1, v1));
    
    std::string s2 = "1 + 2+ 3 + 4";
    std::vector<EntryType> v2 = {NUMBER, OPERATOR, NUMBER, OPERATOR, NUMBER, OPERATOR, NUMBER};
    TEST(performTest(s2, v2));


    std::string s3 = "123,45 * -14 + (3)";
    std::vector<EntryType> v3 = {NUMBER, OPERATOR, NUMBER, OPERATOR, OPEN_BRACKET, NUMBER, CLOSED_BRACKET};
    TEST(performTest(s3, v3));

    std::string s4 = "(9.9 / 1.3)";
    std::vector<EntryType> v4 = {OPEN_BRACKET, NUMBER, OPERATOR, NUMBER, CLOSED_BRACKET};
    TEST(performTest(s4, v4));

    std::string s5 = "0.23 * ((-32.5 - 8) - 0)";
    std::vector<EntryType> v5 = {NUMBER, OPERATOR, OPEN_BRACKET, OPEN_BRACKET, NUMBER, OPERATOR, NUMBER, CLOSED_BRACKET, OPERATOR, NUMBER, CLOSED_BRACKET};
    TEST(performTest(s5, v5));

    return 0;
}
