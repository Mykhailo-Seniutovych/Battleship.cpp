#ifndef BATTLESHIP_SRC_CORE_INCLUDE_SHOOT_RESPONSE_H
#define BATTLESHIP_SRC_CORE_INCLUDE_SHOOT_RESPONSE_H

#include "ship-coordinates.h"
#include "cell-state.h"

struct ShootResponse
{
    CellState cellState;
    ShipCoordinates sunkShipCoordinates;

    ShootResponse() = default;
    ShootResponse(const CellState &t_cellState);
    ShootResponse(const CellState &t_cellState, const ShipCoordinates &t_sunkShip);
};

#endif
