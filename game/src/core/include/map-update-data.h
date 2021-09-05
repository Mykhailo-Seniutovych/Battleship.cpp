#ifndef BATTLESHIP_SRC_CORE_INCLUDE_MAP_UPDATE_DATA_H
#define BATTLESHIP_SRC_CORE_INCLUDE_MAP_UPDATE_DATA_H

#include "ship.h"
#include "cell-state.h"
#include "ship-coordinates.h"

struct MapUpdateData
{
    Cell cell;
    CellState cellState;
    ShipCoordinates sunkShipCoordinates;

    MapUpdateData(const Cell &t_cell, const CellState &t_cellState);
    MapUpdateData(const Cell &t_cell, const CellState &t_cellState, const ShipCoordinates &t_sunkShipCoordinates);
};

#endif
