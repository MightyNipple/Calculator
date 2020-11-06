#include <iostream>
#include <utility>

#include "Evaluator.h"

void PrintError(ErrorType error)
{
    std::cout << "Ошибка: \"" << GetErrorDescription(error) << "\"" << std::endl;
}


int main()
{
    std::cout << "Пожалуйста, введите выражение:" << std::endl;

    std::string s;
    std::getline(std::cin, s);

    Parser parser(s);
    if (parser.GetError())
    {
        PrintError(parser.GetError());
        return -1;
    }

    Evaluator evaluator(std::move(parser));
    if (evaluator.GetError())
    {
        PrintError(evaluator.GetError());
        return -1;
    }

    float answer = evaluator.GetAnswer();
    if (evaluator.GetError())
    {
        PrintError(evaluator.GetError());
        return -1;
    }

    std::cout << "Значение выражения равно " <<  answer << std::endl;
    return 0;
}
