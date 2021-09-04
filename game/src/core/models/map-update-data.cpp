#include "map-update-data.h"

MapUpdateData::MapUpdateData(const Cell &t_cell, const CellState &t_cellState)
    : cell(t_cell), cellState(t_cellState) {}

MapUpdateData::MapUpdateData(
    const Cell &t_cell,
    const CellState &t_cellState,
    const ShipCoordinates &t_sunkShipCoordinates)
    : cell(t_cell), cellState(t_cellState), sunkShipCoordinates(t_sunkShipCoordinates) {}
