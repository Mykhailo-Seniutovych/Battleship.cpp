#include "ship-manager.h"
#include <iostream>
#include <algorithm>

void ShipManager::initializeShips(const Ships &ships)
{

    m_carrier = ships.carrier;
    m_battleship = ships.battleship;
    m_cruiser = ships.cruiser;
    m_submarine = ships.submarine;
    m_destroyer = ships.destroyer;
}

ShootResponse ShipManager::receiveShot(const Cell &cell)
{
    ShootResponse response(CellState::Miss);

    if (m_carrier.tryReceiveShot(cell))
    {
        response = getSuccessfulShotResponse(m_carrier);
    }
    else if (m_battleship.tryReceiveShot(cell))
    {
        response = getSuccessfulShotResponse(m_battleship);
    }
    else if (m_cruiser.tryReceiveShot(cell))
    {
        response = getSuccessfulShotResponse(m_cruiser);
    }
    else if (m_submarine.tryReceiveShot(cell))
    {
        response = getSuccessfulShotResponse(m_submarine);
    }
    else if (m_destroyer.tryReceiveShot(cell))
    {
        response = getSuccessfulShotResponse(m_destroyer);
    }

    auto updateData =
        MapUpdateData(cell, response.cellState, response.sunkShipCoordinates);

    return response;
}

ShootResponse ShipManager::getSuccessfulShotResponse(const Ship &ship) const
{
    ShootResponse response(CellState::ShipDamaged);
    if (isGameOver())
    {
        response = ShootResponse(CellState::GameOver, ship.getCoordinates());
    }
    else if (ship.isShipSunk())
    {
        response = ShootResponse(CellState::ShipSunk, ship.getCoordinates());
    }
    return response;
}

bool ShipManager::isGameOver() const
{
    return m_carrier.isShipSunk() &&
           m_battleship.isShipSunk() &&
           m_cruiser.isShipSunk() &&
           m_submarine.isShipSunk() &&
           m_destroyer.isShipSunk();
}