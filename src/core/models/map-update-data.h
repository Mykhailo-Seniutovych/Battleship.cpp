#ifndef BATTLESHIP_CORE_MODELS_MAPUPDATEDATA_H
#define BATTLESHIP_CORE_MODELS_MAPUPDATEDATA_H

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