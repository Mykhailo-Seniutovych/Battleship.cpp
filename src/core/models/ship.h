#ifndef BATTLESHIP_CORE_MODELS_SHIP_H 
#define BATTLESHIP_CORE_MODELS_SHIP_H 

#include <bits/stdc++.h>
#include "position.h"
#include "cell.h"
#include "ship-coordinates.h"

class Ship
{
public:
    Ship();
    Ship(Position t_position, uint8_t t_axisCoordinate, std::unordered_set<uint8_t> t_cellsCoordinates);

    bool tryReceiveShot(Cell cell);
    bool isShipSunk() const;
    ShipCoordinates getCoordinates() const;

private:
    Position m_position;
    uint8_t m_axisCoordinate;
    std::unordered_set<uint8_t> m_damagedCellsCoordinates = {};
    std::unordered_set<uint8_t> m_intactCellsCoordinates = {};

    bool tryMoveIntactCellToDamaged(uint8_t t_cellCoordinate);
};

#endif
