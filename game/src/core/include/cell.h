#ifndef BATTLESHIP_CORE_MODELS_CELL_H
#define BATTLESHIP_CORE_MODELS_CELL_H

#include <stdint.h>
#include <cstddef>

struct Cell
{
    uint8_t horCoord;
    uint8_t verCoord;
    
    Cell() = default;
    Cell(uint8_t t_horCoord, uint8_t t_verCoord);

    bool operator==(const Cell &otherPoint) const;

    struct HashFunction
    {
        size_t operator()(const Cell &cell) const;
    };
};

#endif