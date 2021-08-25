#include "ship-manager.h"
#include "../interfaces/iobserver.h"

ShipManager::ShipManager() {
}

void ShipManager::initializeShips(
    Ship t_carrier, 
    Ship t_battleship, 
    Ship t_cruiser, 
    Ship t_submarine, 
    Ship t_destroyer
) {
    // TODO: Validate length is correct
    m_carrier = t_carrier;
    m_battleship = t_battleship;
    m_cruiser = t_cruiser;
    m_submarine = t_submarine;
    m_destroyer = t_destroyer;
}

void ShipManager::subscribe(IObserver<MapUpdateData>* observer){
    observers.push_back(observer);
}

void ShipManager::unsubscribe(IObserver<MapUpdateData>* observer){
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

ShootResponse ShipManager::receiveShot(Cell cell) {
    ShootResponse response (CellState::Miss);

    if (m_carrier.tryReceiveShot(cell)) {
        response = getSuccessfulShotResponse(m_carrier);
    } else if (m_battleship.tryReceiveShot(cell)) {
        response = getSuccessfulShotResponse(m_battleship);
    } else if (m_cruiser.tryReceiveShot(cell)) {
        response = getSuccessfulShotResponse(m_cruiser);
    } else if (m_submarine.tryReceiveShot(cell)) {
        response = getSuccessfulShotResponse(m_submarine);
    } else if (m_destroyer.tryReceiveShot(cell)) {
        response = getSuccessfulShotResponse(m_destroyer);
    };

    auto updateData = MapUpdateData(cell, response.cellState, response.sunkShipCoordinates);
    notifyMapUpdate(updateData);

    return response;
}

ShootResponse ShipManager::getSuccessfulShotResponse(Ship ship) {
    ShootResponse response (CellState::ShipDamaged);
    if (isGameOver()) {
        response = ShootResponse(CellState::GameOver, ship.getCoordinates());
    } else if (ship.isShipSunk()) {
        response = ShootResponse(CellState::ShipSunk, ship.getCoordinates());
    }
    return response;
}

void ShipManager::notifyMapUpdate(const MapUpdateData& data) {
    for (auto observer : observers) {
        observer->update(data);
    }
}

bool ShipManager::isGameOver() {
    return m_carrier.isShipSunk() 
        && m_battleship.isShipSunk() 
        && m_cruiser.isShipSunk() 
        && m_submarine.isShipSunk() 
        && m_destroyer.isShipSunk();
}