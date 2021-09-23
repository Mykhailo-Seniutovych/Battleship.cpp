#include "map-utils.h"
#include "cstdint"
#include "exceptions/invalid-input-exception.h"

char map_utils::convertRowNumberToRowLetter(uint8_t t_result)
{
    char result;
    switch (t_result)
    {
    case 1:
        result = 'A';
        break;
    case 2:
        result = 'B';
        break;
    case 3:
        result = 'C';
        break;
    case 4:
        result = 'D';
        break;
    case 5:
        result = 'E';
        break;
    case 6:
        result = 'F';
        break;
    case 7:
        result = 'G';
        break;
    case 8:
        result = 'H';
        break;
    case 9:
        result = 'I';
        break;
    case 10:
        result = 'J';
        break;
    default:
        result = -1;
    };

    return result;
};

int8_t map_utils::convertRowLetterToRowNumber(char t_rowLetter)
{
    char result;
    if (t_rowLetter == 'A' || t_rowLetter == 'a')
    {
        result = 1;
    }
    else if (t_rowLetter == 'B' || t_rowLetter == 'b')
    {
        result = 2;
    }
    else if (t_rowLetter == 'C' || t_rowLetter == 'c')
    {
        result = 3;
    }
    else if (t_rowLetter == 'D' || t_rowLetter == 'd')
    {
        result = 4;
    }
    else if (t_rowLetter == 'E' || t_rowLetter == 'e')
    {
        result = 5;
    }
    else if (t_rowLetter == 'F' || t_rowLetter == 'f')
    {
        result = 6;
    }
    else if (t_rowLetter == 'G' || t_rowLetter == 'g')
    {
        result = 7;
    }
    else if (t_rowLetter == 'H' || t_rowLetter == 'h')
    {
        result = 8;
    }
    else if (t_rowLetter == 'I' || t_rowLetter == 'i')
    {
        result = 9;
    }
    else if (t_rowLetter == 'J' || t_rowLetter == 'j')
    {
        result = 10;
    }
    else
    {
        result = -1;
    }

    return result;
};