#include "map-utils.h"
#include "cstdint"
#include "exceptions/invalid-input-exception.h"

char map_utils::convertRowNumberToRowLetter(uint8_t t_rowNum)
{
    char rowLetter;
    switch (t_rowNum)
    {
    case 1:
        rowLetter = 'A';
        break;
    case 2:
        rowLetter = 'B';
        break;
    case 3:
        rowLetter = 'C';
        break;
    case 4:
        rowLetter = 'D';
        break;
    case 5:
        rowLetter = 'E';
        break;
    case 6:
        rowLetter = 'F';
        break;
    case 7:
        rowLetter = 'G';
        break;
    case 8:
        rowLetter = 'H';
        break;
    case 9:
        rowLetter = 'I';
        break;
    case 10:
        rowLetter = 'J';
        break;
    default:
        throw new InvalidInputException("Row number is invalid.");
    };

    return rowLetter;
};

uint8_t map_utils::convertRowLetterToRowNumber(char t_rowLetter)
{
    char rowNum;
    if (t_rowLetter == 'A' || t_rowLetter == 'a')
    {
        rowNum = 1;
    }
    else if (t_rowLetter == 'B' || t_rowLetter == 'b')
    {
        rowNum = 2;
    }
    else if (t_rowLetter == 'C' || t_rowLetter == 'c')
    {
        rowNum = 3;
    }
    else if (t_rowLetter == 'D' || t_rowLetter == 'd')
    {
        rowNum = 4;
    }
    else if (t_rowLetter == 'E' || t_rowLetter == 'e')
    {
        rowNum = 5;
    }
    else if (t_rowLetter == 'F' || t_rowLetter == 'f')
    {
        rowNum = 6;
    }
    else if (t_rowLetter == 'G' || t_rowLetter == 'G')
    {
        rowNum = 7;
    }
    else if (t_rowLetter == 'H' || t_rowLetter == 'h')
    {
        rowNum = 8;
    }
    else if (t_rowLetter == 'I' || t_rowLetter == 'i')
    {
        rowNum = 9;
    }
    else if (t_rowLetter == 'J' || t_rowLetter == 'j')
    {
        rowNum = 10;
    }
    else
    {
        throw InvalidInputException("Row letter is invalid.");
    }

    return rowNum;
};