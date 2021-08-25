#include "map-update-data.h"

MapUpdateData::MapUpdateData(Cell t_cell, CellState t_cellState)
    : cell(t_cell), cellState(t_cellState) {}

MapUpdateData::MapUpdateData(Cell t_cell, CellState t_cellState, ShipCoordinates t_sunkShipCoordinates)
    : cell(t_cell), cellState(t_cellState), sunkShipCoordinates(t_sunkShipCoordinates) {}
