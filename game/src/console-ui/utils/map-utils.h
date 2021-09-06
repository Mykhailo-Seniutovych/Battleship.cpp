#ifndef BATTLESHIP_SRC_CONSOLE_UI_UTILS_MAP_UTILS_H
#define BATTLESHIP_SRC_CONSOLE_UI_UTILS_MAP_UTILS_H

#include "cstdint"

namespace map_utils
{
    char convertRowNumberToRowLetter(uint8_t rowNum);
    uint8_t convertRowLetterToRowNumber(char rowLetter);
}

#endif
