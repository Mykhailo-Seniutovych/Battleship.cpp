#include "ship-coordinates.h"

ShipCoordinates::ShipCoordinates() = default;

ShipCoordinates::ShipCoordinates(
    const Position &t_position,
    const uint8_t &t_axisCoordinate,
    const std::unordered_set<uint8_t> &t_cellsCoordinates)
    : position(t_position),
      axisCoordinate(t_axisCoordinate),
      cellsCoordinates(t_cellsCoordinates) {}
