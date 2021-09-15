#include <algorithm>
#include <iostream>
#include <string>
#include "validation-exception.h"
#include "ship-manager.h"
#include "constants.h"

using namespace std;

void ShipManager::initializeShips(const Ships &t_ships)
{
    unordered_set<Cell, Cell::HashFunction> takenCells = {};

    validateShip(t_ships.carrier, takenCells, Constants::CARRIER_LENGTH);
    validateShip(t_ships.battleship, takenCells, Constants::BATTLESHIP_LENGTH);
    validateShip(t_ships.cruiser, takenCells, Constants::CRUISER_LENGTH);
    validateShip(t_ships.submarine, takenCells, Constants::SUBMARINE_LENGTH);
    validateShip(t_ships.destroyer, takenCells, Constants::DESTROYER_LENGTH);

    m_carrier = t_ships.carrier;
    m_battleship = t_ships.battleship;
    m_cruiser = t_ships.cruiser;
    m_submarine = t_ships.submarine;
    m_destroyer = t_ships.destroyer;
}

void ShipManager::validateShip(
    const Ship &t_ship,
    std::unordered_set<Cell, Cell::HashFunction> &t_takenCells,
    uint8_t t_shipSize)
{
    auto coordinates = t_ship.getCoordinates();
    if (coordinates.cellsCoordinates.size() != t_shipSize)
    {
        std::string msg = "Ship that must have " +
                          to_string(t_shipSize) +
                          " cells, has " +
                          to_string(coordinates.cellsCoordinates.size()) + " cells.";
        throw ValidationException(msg);
    }

    uint8_t previousCoord;
    auto isPreviousCoordSet = false;
    for (auto coord : coordinates.cellsCoordinates)
    {
        if (coord > Constants::MAP_SIZE - 1)
        {
            throw ValidationException("Ship cell is outside of map boundaries.");
        }
        
        if (isPreviousCoordSet && coord != previousCoord + 1)
        {
            throw ValidationException("Ship cells of a ship are not in a sequential order.");
        }

        auto cell = coordinates.position == Position::Horizontal
                        ? Cell(coordinates.axisCoordinate, coord)
                        : Cell(coord, coordinates.axisCoordinate);

        if (t_takenCells.count(cell))
        {
            throw ValidationException("Ship cell overlaps with other ship cells.");
        }

        t_takenCells.insert(cell);
        previousCoord = coord;
        isPreviousCoordSet = true;
    }
}

ShootResponse ShipManager::receiveShot(const Cell &t_cell)
{
    ShootResponse response(CellState::Miss);

    if (m_carrier.tryReceiveShot(t_cell))
    {
        response = getSuccessfulShotResponse(m_carrier);
    }
    else if (m_battleship.tryReceiveShot(t_cell))
    {
        response = getSuccessfulShotResponse(m_battleship);
    }
    else if (m_cruiser.tryReceiveShot(t_cell))
    {
        response = getSuccessfulShotResponse(m_cruiser);
    }
    else if (m_submarine.tryReceiveShot(t_cell))
    {
        response = getSuccessfulShotResponse(m_submarine);
    }
    else if (m_destroyer.tryReceiveShot(t_cell))
    {
        response = getSuccessfulShotResponse(m_destroyer);
    }

    return response;
}

ShootResponse ShipManager::getSuccessfulShotResponse(const Ship &t_ship) const
{
    ShootResponse response(CellState::ShipDamaged);
    if (isGameOver())
    {
        response = ShootResponse(CellState::GameOver, t_ship.getCoordinates());
    }
    else if (t_ship.isShipSunk())
    {
        response = ShootResponse(CellState::ShipSunk, t_ship.getCoordinates());
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