#ifndef BATTLESHIP_SRC_CORE_INCLUDE_COMPUTER_SHIP_ARRANGEMENT_H
#define BATTLESHIP_SRC_CORE_INCLUDE_COMPUTER_SHIP_ARRANGEMENT_H

#include <unordered_set>
#include <cstdint>
#include <vector>
#include "iship-arrangement.h"
#include "cell.h"
#include "position.h"

class ComputerShipArrangement : public IShipArrangement
{
public:
    Ships getShipsArrangement() const override;

private:
    Ship getRandomlyPlacedShip(const std::vector<Ship> &t_existingShips, uint8_t t_newShipLength) const;

    std::vector<Cell> getAvailableCells(
        uint8_t t_newShipLength,
        Position t_newShipPosition,
        const std::vector<Ship> &t_existingShips) const;

    std::unordered_set<Cell, Cell::HashFunction> getAllBeginningCells(
        uint8_t t_newShipLength, Position t_newShipPosition) const;

    void removeUnavailableCellsFromLeft(
        std::unordered_set<Cell, Cell::HashFunction> &t_availableCells,
        const std::vector<Ship> &t_existingShips,
        uint8_t t_newShipLength) const;

    void removeUnavailableCellsFromTop(
        std::unordered_set<Cell, Cell::HashFunction> &t_availableCells,
        const std::vector<Ship> &t_existingShips,
        uint8_t t_newShipLength) const;
};

#endif
