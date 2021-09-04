#include "shoot-response.h"

ShootResponse::ShootResponse(const CellState &t_cellState)
    : cellState(t_cellState) {}

ShootResponse::ShootResponse(const CellState &t_cellState, const ShipCoordinates &t_sunkShipCoordinates)
    : cellState(t_cellState), sunkShipCoordinates(t_sunkShipCoordinates) {}
