#include "Parser.h"


bool Parser::tryParseAndInsertNumber(const std::string& source)
{
    if (Entries.size() && Entries.back().type == EntryType::NUMBER)
    {
        error = ErrorType::TWO_NUMS_IN_ROW;
        return false;
    }

    float number = std::stof(source);
    if ((Entries.size() >= 1 && Entries.back().type == EntryType::OPERATOR && Entries.back().dataAsChar == '-') &&
        (Entries.size() == 1 || (Entries[Entries.size() - 2].type == EntryType::OPERATOR ||
                                 Entries[Entries.size() - 2].type == EntryType::OPEN_BRACKET)))
    {
        number = -number;
        Entries.pop_back();
    }
    
    Entries.push_back(ExpressionEntry(number));
    return true;
}


Parser::Parser(const std::string& input)
{
    std::string currentNum;
    bool isDotOccured = false;

    for (const char c : input)
    {
        if ('0' <= c && c <= '9')
        {
            if (!isDotOccured && currentNum.size() == MAX_ALLOWED_NUM_SIZE)
            {
                error = ErrorType::NUM_OVERFLOW;
                return;
            }

            currentNum.push_back(c);
        }
        else if (c == '.' || c == ',')
        {
            if (!isDotOccured)
            {
                currentNum.push_back('.');
                isDotOccured = true;
            }
            else
            {
                error = ErrorType::TOO_MANY_DOTS;
                return;
            }
        }
        else
        {
            if (currentNum.size())
            {
                if (!tryParseAndInsertNumber(currentNum))
                {
                    return;
                }

                currentNum.erase();
                isDotOccured = false;
            }

            if (allowedSymbols.find(c) != std::string::npos)
            {
                Entries.push_back(ExpressionEntry(c));
            }
            else if (c != ' ')
            {
                error = ErrorType::WRONG_CHAR;
                return;
            }
        }
    }

    if (currentNum.size())
    {
        tryParseAndInsertNumber(currentNum);
    }
}


bool Parser::TryGetNextEntry(ExpressionEntry& output)
{
    if (currentEntry < Entries.size())
    {
        output = Entries[currentEntry++];
        return true;
    }
    return false;
}

