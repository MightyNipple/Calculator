#pragma once

#include <stack>
#include <queue>
#include <cmath>

#include "Parser.h"


/*
 *   Implemented, as described here:
 *    https://ru.wikipedia.org/wiki/%D0%9E%D0%B1%D1%80%D0%B0%D1%82%D0%BD%D0%B0%D1%8F_%D0%BF%D0%BE%D0%BB%D1%8C%D1%81%D0%BA%D0%B0%D1%8F_%D0%B7%D0%B0%D0%BF%D0%B8%D1%81%D1%8C
 */
class Evaluator
{
private:
    Evaluator() = delete;

    const float EVALUATION_BOUND = 10000000.0f;
    const std::string operatorsPriority = "+-*/";

    std::queue<ExpressionEntry> ReversedNotation;
    ErrorType error = ErrorType::NO_ERROR;

    std::stack<ExpressionEntry> entriesInnerStack;
    std::stack<float> numsInnerStack;

    void convertEntry(const ExpressionEntry& currentEntry);
    float performOperation(float x, float y, char operation);

public:
    explicit Evaluator(Parser&& input);

    float GetAnswer();

    ErrorType GetError() const
    {
        return error;
    }
};
