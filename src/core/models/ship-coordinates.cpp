#include "ship-coordinates.h"

ShipCoordinates::ShipCoordinates() {
}

ShipCoordinates::ShipCoordinates(
    Position t_position, uint8_t t_axisCoordinate, std::unordered_set<uint8_t> t_cellsCoordinates) :
        position(t_position), 
        axisCoordinate(t_axisCoordinate), 
        cellsCoordinates(t_cellsCoordinates) {
}