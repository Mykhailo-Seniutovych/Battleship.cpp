#ifndef BATTLESHIP_CORE_MODELS_MAPUPDATEDATA_H 
#define BATTLESHIP_CORE_MODELS_MAPUPDATEDATA_H 

#include "ship.h"
#include "cell-state.h"
#include "ship-coordinates.h"

struct MapUpdateData {
    Cell cell;
    CellState cellState;
    ShipCoordinates sunkShipCoordinates;

    MapUpdateData(Cell t_cell, CellState t_cellState);
    MapUpdateData(Cell t_cell, CellState t_cellState, ShipCoordinates t_sunkShipCoordinates);
};

#endif