#ifndef BATTLESHIP_CORE_MODELS_SHIPCOORDINATES_H 
#define BATTLESHIP_CORE_MODELS_SHIPCOORDINATES_H 

#include <bits/stdc++.h>
#include "position.h"
#include "cell.h"

struct ShipCoordinates {
    Position position;
    uint8_t axisCoordinate;
    std::unordered_set<uint8_t> cellsCoordinates = {};

    ShipCoordinates();
    ShipCoordinates(
        Position t_position, uint8_t t_axisCoordinate, std::unordered_set<uint8_t> t_cellsCoordinates);
};

#endif