#ifndef BATTLESHIP_CORE_MODELS_CELLSTATE_H
#define BATTLESHIP_CORE_MODELS_CELLSTATE_H

enum class CellState
{
    Miss,
    ShipDamaged,
    ShipSunk,
    GameOver
};

#endif