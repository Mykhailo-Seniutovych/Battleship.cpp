#ifndef BATTLESHIP_CORE_MODELS_SHIPCOORDINATES_H
#define BATTLESHIP_CORE_MODELS_SHIPCOORDINATES_H

#include <unordered_set>
#include "position.h"
#include "cell.h"

struct ShipCoordinates
{
    Position position;
    uint8_t axisCoordinate;
    std::unordered_set<uint8_t> cellsCoordinates = {};

    ShipCoordinates();
    ShipCoordinates(
        const Position &t_position,
        const uint8_t &t_axisCoordinate,
        const std::unordered_set<uint8_t> &t_cellsCoordinates);
};

#endif