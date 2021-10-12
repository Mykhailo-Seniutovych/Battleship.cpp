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
    Ship m_battleship;

    Ship m_cruiser1;
    Ship m_cruiser2;

    Ship m_destroyer1;
    Ship m_destroyer2;
    Ship m_destroyer3;

    Ship m_submarine1;
    Ship m_submarine2;
    Ship m_submarine3;
    Ship m_submarine4;

    bool isGameOver() const;

    ShootResponse getSuccessfulShotResponse(const Ship &t_ship) const;

    void validateShip(
        const Ship &t_ship,
        std::unordered_set<Cell, Cell::HashFunction> &t_takenCells,
        uint8_t t_shipSize) const;

    void insertOuterCellsTakenByShip(
        std::unordered_set<Cell, Cell::HashFunction> &t_takenCells,
        const Ship &t_ship) const;

    void insertValidCell(
        std::unordered_set<Cell, Cell::HashFunction> &t_takenCells,
        int8_t t_horCoord,
        int8_t t_verCoord) const;
};

#endif
