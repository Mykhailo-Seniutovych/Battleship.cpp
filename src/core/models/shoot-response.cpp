#include "shoot-response.h"

ShootResponse::ShootResponse(CellState t_cellState)
    : cellState(t_cellState) {}

ShootResponse::ShootResponse(CellState t_cellState, ShipCoordinates t_sunkShipCoordinates)
    : cellState(t_cellState), sunkShipCoordinates(t_sunkShipCoordinates) {}