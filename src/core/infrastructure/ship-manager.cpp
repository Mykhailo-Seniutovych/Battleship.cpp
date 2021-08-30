#include "ship-manager.h"

#include "../interfaces/iobserver.h"

ShipManager::ShipManager() {}

void ShipManager::initializeShips(
    const Ship &t_carrier,
    const Ship &t_battleship,
    const Ship &t_cruiser,
    const Ship &t_submarine,
    const Ship &t_destroyer)
{
    // TODO: Validate length is correct
    m_carrier = t_carrier;
    m_battleship = t_battleship;
    m_cruiser = t_cruiser;
    m_submarine = t_submarine;
    m_destroyer = t_destroyer;
}

void ShipManager::subscribe(IObserver<MapUpdateData> *observer)
{
    m_observers.push_back(observer);
}

void ShipManager::unsubscribe(IObserver<MapUpdateData> *observer)
{
    m_observers.erase(
        std::remove(m_observers.begin(), m_observers.end(), observer),
        m_observers.end());
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
    notifyMapUpdate(updateData);

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

void ShipManager::notifyMapUpdate(const MapUpdateData &data) const
{
    for (auto observer : m_observers)
    {
        observer->update(data);
    }
}

bool ShipManager::isGameOver() const
{
    return m_carrier.isShipSunk() &&
           m_battleship.isShipSunk() &&
           m_cruiser.isShipSunk() &&
           m_submarine.isShipSunk() &&
           m_destroyer.isShipSunk();
}