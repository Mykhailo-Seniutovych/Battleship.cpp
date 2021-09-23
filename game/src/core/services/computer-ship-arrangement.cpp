#include <random>
#include <iostream>
#include <algorithm>

#include "utils/bool-random-generator.h"
#include "utils/int-random-generator.h"

#include "computer-ship-arrangement.h"
#include "constants.h"

using namespace std;

Ships ComputerShipArrangement::getShipsArrangement() const
{
    Ships ships;
    vector<Ship> existingShips = {};
    
    ships.carrier = getRandomlyPlacedShip(existingShips, Constants::CARRIER_LENGTH);
    existingShips.push_back(ships.carrier);

    ships.battleship = getRandomlyPlacedShip(existingShips, Constants::BATTLESHIP_LENGTH);
    existingShips.push_back(ships.battleship);

    ships.cruiser = getRandomlyPlacedShip(existingShips, Constants::CRUISER_LENGTH);
    existingShips.push_back(ships.cruiser);

    ships.submarine = getRandomlyPlacedShip(existingShips, Constants::SUBMARINE_LENGTH);
    existingShips.push_back(ships.submarine);

    ships.destroyer = getRandomlyPlacedShip(existingShips, Constants::DESTROYER_LENGTH);
    existingShips.push_back(ships.destroyer);

    return ships;
}

Ship ComputerShipArrangement::getRandomlyPlacedShip(
    const vector<Ship> &t_existingShips, uint8_t t_newShipLength) const
{
    BoolRandomGenerator randomBool;
    auto position = randomBool.getRandomBool() ? Position::Horizontal : Position::Vertical;
    auto availableCellsForShipBeginning = getAvailableCells(
        t_newShipLength, position, t_existingShips);
    IntRandomGenerator<int32_t> randomInt(0, availableCellsForShipBeginning.size() - 1);
    auto index = randomInt.getRandomInt();

    auto newShipBeginning = availableCellsForShipBeginning.at(index);

    unordered_set<uint8_t> newShipCoordinates = {};
    Ship newShip;
    if (position == Position::Horizontal)
    {
        for (uint8_t colIndex = 0; colIndex < t_newShipLength; colIndex++)
        {
            newShipCoordinates.insert(newShipBeginning.verCoord + colIndex);
        }
        newShip = Ship(position, newShipBeginning.horCoord, newShipCoordinates);
    }
    else
    {
        for (uint8_t rowIndex = 0; rowIndex < t_newShipLength; rowIndex++)
        {
            newShipCoordinates.insert(newShipBeginning.horCoord + rowIndex);
        }
        newShip = Ship(position, newShipBeginning.verCoord, newShipCoordinates);
    }

    return newShip;
}

vector<Cell> ComputerShipArrangement::getAvailableCells(
    uint8_t t_newShipLength,
    Position t_newShipPosition,
    const vector<Ship> &t_existingShips) const
{
    auto availableCells = getAllBeginningCells(t_newShipLength, t_newShipPosition);
    if (t_newShipPosition == Position::Horizontal)
    {
        removeUnavailableCellsFromLeft(availableCells, t_existingShips, t_newShipLength);
    }
    else
    {
        removeUnavailableCellsFromTop(availableCells, t_existingShips, t_newShipLength);
    }

    vector<Cell> result = {};
    result.insert(result.end(), availableCells.begin(), availableCells.end());
    return result;
}

unordered_set<Cell, Cell::HashFunction> ComputerShipArrangement::getAllBeginningCells(
    uint8_t t_newShipLength, Position t_newShipPosition) const
{
    auto maxRowIndex = t_newShipPosition == Position::Horizontal
                           ? Constants::MAP_SIZE
                           : Constants::MAP_SIZE - t_newShipLength + 1;
    auto maxColIndex = t_newShipPosition == Position::Horizontal
                           ? Constants::MAP_SIZE - t_newShipLength + 1
                           : Constants::MAP_SIZE;
    unordered_set<Cell, Cell::HashFunction> availableCells = {};
    for (uint8_t row = 0; row < maxRowIndex; row++)
    {
        for (uint8_t col = 0; col < maxColIndex; col++)
        {
            availableCells.insert(Cell(row, col));
        }
    }
    return availableCells;
}

void ComputerShipArrangement::removeUnavailableCellsFromLeft(
    unordered_set<Cell, Cell::HashFunction> &t_availableCells,
    const vector<Ship> &t_existingShips,
    uint8_t t_newShipLength) const
{
    for (auto existingShip : t_existingShips)
    {
        auto shipCells = existingShip.getShipCells();
        for (auto cell : shipCells)
        {
            for (uint8_t index = 0; index < t_newShipLength; index++)
            {
                t_availableCells.erase(Cell(cell.horCoord, cell.verCoord - index));
            }
        }
    }
}

void ComputerShipArrangement::removeUnavailableCellsFromTop(
    unordered_set<Cell, Cell::HashFunction> &t_availableCells,
    const vector<Ship> &t_existingShips,
    uint8_t t_newShipLength) const
{
    for (auto existingShip : t_existingShips)
    {
        auto shipCells = existingShip.getShipCells();
        for (auto cell : shipCells)
        {
            for (uint8_t index = 0; index < t_newShipLength; index++)
            {
                t_availableCells.erase(Cell(cell.horCoord - index, cell.verCoord));
            }
        }
    }
}
