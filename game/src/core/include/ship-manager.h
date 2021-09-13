#ifndef BATTLESHIP_SRC_CORE_INCLUDE_SHIP_MANAGER_H
#define BATTLESHIP_SRC_CORE_INCLUDE_SHIP_MANAGER_H

#include <vector>
#include <memory>
#include <unordered_set>
#include <cstdint>

#include "shoot-response.h"
#include "ships.h"
#include "iship-manager.h"
#include "map-update-data.h"

class ShipManager : public IShipManager
{

public:
    ShootResponse receiveShot(const Cell &t_cell) override;
    void initializeShips(const Ships &t_ships) override;

private:
    const uint8_t CARRIER_LENGTH = 5;
    const uint8_t BATTLESHIP_LENGTH = 4;
    const uint8_t CRUISER_LENGTH = 3;
    const uint8_t SUBMARINE_LENGTH = 3;
    const uint8_t DESTROYER_LENGTH = 2;

    Ship m_carrier;
    Ship m_battleship;
    Ship m_cruiser;
    Ship m_submarine;
    Ship m_destroyer;

    bool isGameOver() const;
    ShootResponse getSuccessfulShotResponse(const Ship &t_ship) const;
    void validateShip(
        const Ship &t_ship,
        std::unordered_set<Cell, Cell::HashFunction> &t_takenCells,
        uint8_t t_shipSize);
};

#endif
