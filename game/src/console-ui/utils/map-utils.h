#ifndef BATTLESHIP_SRC_CONSOLE_UI_UTILS_MAP_UTILS_H
#define BATTLESHIP_SRC_CONSOLE_UI_UTILS_MAP_UTILS_H

#include "cstdint"

namespace map_utils
{
    char convertColNumberToColLetter(uint8_t t_rowNum);
    int8_t convertRowLetterToRowNumber(char t_rowLetter);
}

#endif
