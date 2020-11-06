#include "Evaluator.h"


void Evaluator::convertEntry(const ExpressionEntry& currentEntry)
{
    switch(currentEntry.type)
    {
        case EntryType::NUMBER:
            ReversedNotation.push(currentEntry);
            break;

        case EntryType::OPEN_BRACKET:
            entriesInnerStack.push(currentEntry);
            break;

        case EntryType::CLOSED_BRACKET:
            while (entriesInnerStack.size() && entriesInnerStack.top().type != EntryType::OPEN_BRACKET)
            {
                ReversedNotation.push(entriesInnerStack.top());
                entriesInnerStack.pop();
            }

            if (!entriesInnerStack.size())
            {
                error = ErrorType::BRACKETS_MESS;
                return;
            }
            else
            {
                entriesInnerStack.pop();
            }
            break;

        case EntryType::OPERATOR:
            while (entriesInnerStack.size() && entriesInnerStack.top().type == EntryType::OPERATOR &&
                   operatorsPriority.find(entriesInnerStack.top().dataAsChar) >= operatorsPriority.find(currentEntry.dataAsChar))
            {
                ReversedNotation.push(entriesInnerStack.top());
                entriesInnerStack.pop();
            }

            entriesInnerStack.push(currentEntry);
            break;
    }
}


float Evaluator::performOperation(float x, float y, char operation)
{
    switch (operation)
    {
        case '+':
            return x + y;

        case '-':
            return x - y;

        case '*':
            return x * y;

        case '/':
            if (y == 0.0)
            {
                error = ErrorType::DIVISION_BY_ZERO;
                return NAN;
            }
            return x / y;
    }
    return NAN;
}


Evaluator::Evaluator(Parser&& input)
{
    error = input.GetError();
    if (error)
    {
        return;
    }

    ExpressionEntry currentEntry;

    while (input.TryGetNextEntry(currentEntry))
    {
        convertEntry(currentEntry);
    }

    while (entriesInnerStack.size())
    {
        if (entriesInnerStack.top().type != EntryType::OPERATOR)
        {
            error = ErrorType::BRACKETS_MESS;
            return;
        }

        ReversedNotation.push(entriesInnerStack.top());
        entriesInnerStack.pop();
    }
}


float Evaluator::GetAnswer()
{
    while (ReversedNotation.size())
    {
        switch (ReversedNotation.front().type)
        {
            case EntryType::NUMBER:
                numsInnerStack.push(ReversedNotation.front().dataAsNumber);
                break;

            case EntryType::OPERATOR:
                if (numsInnerStack.size() < 2)
                {
                    error = ErrorType::BRACKETS_MESS;
                    return NAN;
                }

                float secondOperand = numsInnerStack.top();
                numsInnerStack.pop();
                float firstOperand = numsInnerStack.top();
                numsInnerStack.pop();

                float result = performOperation(firstOperand, secondOperand, ReversedNotation.front().dataAsChar);

                if (error)
                {
                    return NAN;
                }
                if (result > EVALUATION_BOUND || result < -EVALUATION_BOUND)
                {
                    error = ErrorType::NUM_OVERFLOW;
                    return NAN;
                }

                numsInnerStack.push(result);
        }

        ReversedNotation.pop();
    }

    if (numsInnerStack.size() != 1)
    {
        error = ErrorType::BRACKETS_MESS;
        return NAN;
    }

    return roundf(numsInnerStack.top() * 100.0) / 100.0;
}

