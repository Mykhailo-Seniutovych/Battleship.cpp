#ifndef BATTLESHIP_CORE_MODELS_POINT_H
#define BATTLESHIP_CORE_MODELS_POINT_H

#include <stdint.h>

struct Cell {
    uint8_t horCoord;
    uint8_t verCoord;

    Cell(uint8_t t_horCoord, uint8_t t_verCoord);
};

#endif