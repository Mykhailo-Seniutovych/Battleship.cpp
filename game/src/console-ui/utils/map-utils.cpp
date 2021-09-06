#include "map-utils.h"
#include "cstdint"

char map_utils::convertRowNumberToRowLetter(uint8_t rowNum)
{
    char rowLetter;
    switch (rowNum)
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
        break;
    };

    return rowLetter;
};

uint8_t map_utils::convertRowLetterToRowNumber(char rowLetter)
{
    char rowNum;
    switch (rowLetter)
    {
    case 'A':
        rowNum = 1;
        break;
    case 'B':
        rowNum = 2;
        break;
    case 'C':
        rowNum = 3;
        break;
    case 'D':
        rowNum = 4;
        break;
    case 'E':
        rowNum = 5;
        break;
    case 'F':
        rowNum = 6;
        break;
    case 'G':
        rowNum = 7;
        break;
    case 'H':
        rowNum = 8;
        break;
    case 'I':
        rowNum = 9;
        break;
    case 'J':
        rowNum = 10;
        break;
    default:
        break;
    };

    return rowNum;
};