#include "ErrorHandler.h"


std::string GetErrorDescription(ErrorType error)
{
    switch(error)
    {
        case TWO_NUMS_IN_ROW:
            return "Выражение содержит два числа через пробел";

        case TOO_MANY_DOTS:
            return "Выражение содержит число с двумя точками";

        case NUM_OVERFLOW:
            return "Выражение содержит слишком большие числа";

        case WRONG_CHAR:
            return "Выражение содержит недопустимые символы";

        case BRACKETS_MESS:
            return "Скобки в выражении расставлены неверно";

        case DIVISION_BY_ZERO:
            return "В выражении содержится деление на ноль";
    }
    return "Ошибки нет";
}
