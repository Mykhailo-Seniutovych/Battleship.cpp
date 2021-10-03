#include <cctype>
#include "map-utils.h"
#include "cstdint"
#include "exceptions/invalid-input-exception.h"
#include "constants.h"

static const uint8_t ASCHII_LETTER_OFFSET = 64;

char map_utils::convertRowNumberToRowLetter(uint8_t t_rowNum)
{
    auto letterCode = t_rowNum + ASCHII_LETTER_OFFSET;
    char result = -1;
    if (letterCode >= 'A' && letterCode < 'A' + Constants::MAP_SIZE)
    {
        result = letterCode;
    }
    return result;
};

int8_t map_utils::convertRowLetterToRowNumber(char t_rowLetter)
{
    int8_t result = -1;
    auto rowNumber = toupper(t_rowLetter) - ASCHII_LETTER_OFFSET;
    if (rowNumber > 0 && rowNumber < Constants::MAP_SIZE)
    {
        result = rowNumber;
    }
    return result;
};