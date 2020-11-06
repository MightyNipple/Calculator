#pragma once


#include <string>
#include <vector>

#include "ErrorHandler.h"

enum EntryType
{
    NUMBER = 0,
    OPEN_BRACKET,
    CLOSED_BRACKET,
    OPERATOR
};


struct ExpressionEntry
{
    EntryType type;

    union
    {
        float dataAsNumber;
        char dataAsChar;
    };

    ExpressionEntry(float number) :
        type(EntryType::NUMBER),
        dataAsNumber(number)
    {}

    ExpressionEntry(char symbol) :
        dataAsChar(symbol)
    {
        switch (symbol)
        {
            case '(':
                type = EntryType::OPEN_BRACKET;
                break;
            case ')':
                type = EntryType::CLOSED_BRACKET;
                break;
            default:
                type = EntryType::OPERATOR;
                break;
        }
    }

    ExpressionEntry(){};
};

class Parser
{
private:
    Parser() = delete;

    const int MAX_ALLOWED_NUM_SIZE = 8;
    const std::string allowedSymbols = "+-/*()";

    std::vector<ExpressionEntry> Entries;
    int currentEntry = 0;

    ErrorType error = ErrorType::NO_ERROR;

    bool tryParseAndInsertNumber(const std::string& source);

public:
    explicit Parser(const std::string& input);

    ErrorType GetError() const
    {
        return error;
    }

    bool TryGetNextEntry(ExpressionEntry& output);
};
