#ifndef BATTLESHIP_CORE_MODELS_SHOOTRESPONSE_H 
#define BATTLESHIP_CORE_MODELS_SHOOTRESPONSE_H 

#include "ship-coordinates.h"
#include "cell-state.h"

struct ShootResponse {
    CellState cellState;
    ShipCoordinates sunkShipCoordinates;

    ShootResponse(CellState t_cellState);
    ShootResponse(CellState t_cellState, ShipCoordinates t_sunkShip);
};

#endif