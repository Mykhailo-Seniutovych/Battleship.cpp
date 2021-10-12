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

    ships.battleship = getRandomlyPlacedShip(existingShips, Constants::BATTLESHIP_LENGTH);
    existingShips.push_back(ships.battleship);


    ships.cruiser1 = getRandomlyPlacedShip(existingShips, Constants::CRUISER_LENGTH);
    existingShips.push_back(ships.cruiser1);

    ships.cruiser2 = getRandomlyPlacedShip(existingShips, Constants::CRUISER_LENGTH);
    existingShips.push_back(ships.cruiser2);


    ships.destroyer1 = getRandomlyPlacedShip(existingShips, Constants::DESTROYER_LENGTH);
    existingShips.push_back(ships.destroyer1);

    ships.destroyer2 = getRandomlyPlacedShip(existingShips, Constants::DESTROYER_LENGTH);
    existingShips.push_back(ships.destroyer2);

    ships.destroyer3 = getRandomlyPlacedShip(existingShips, Constants::DESTROYER_LENGTH);
    existingShips.push_back(ships.destroyer3);


    ships.submarine1 = getRandomlyPlacedShip(existingShips, Constants::SUBMARINE_LENGTH);
    existingShips.push_back(ships.submarine1);

    ships.submarine2 = getRandomlyPlacedShip(existingShips, Constants::SUBMARINE_LENGTH);
    existingShips.push_back(ships.submarine2);

    ships.submarine3 = getRandomlyPlacedShip(existingShips, Constants::SUBMARINE_LENGTH);
    existingShips.push_back(ships.submarine3);

    ships.submarine4 = getRandomlyPlacedShip(existingShips, Constants::SUBMARINE_LENGTH);
    existingShips.push_back(ships.submarine4);

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
        removeUnavailableCellsForHorizontal(availableCells, t_existingShips, t_newShipLength);
    }
    else
    {
        removeUnavailableCellsForVertical(availableCells, t_existingShips, t_newShipLength);
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

void ComputerShipArrangement::removeUnavailableCellsForHorizontal(
    unordered_set<Cell, Cell::HashFunction> &t_availableCells,
    const vector<Ship> &t_existingShips,
    uint8_t t_newShipLength) const
{
    for (auto existingShip : t_existingShips)
    {
        auto shipCells = existingShip.getShipCells();
        for (auto cell : shipCells)
        {
            for (int8_t index = -1; index <= t_newShipLength; index++)
            {
                eraseValidCell(t_availableCells, cell.horCoord - 1, cell.verCoord - index);
                eraseValidCell(t_availableCells, cell.horCoord, cell.verCoord - index);
                eraseValidCell(t_availableCells, cell.horCoord + 1, cell.verCoord - index);
            }
        }
    }
}

void ComputerShipArrangement::removeUnavailableCellsForVertical(
    unordered_set<Cell, Cell::HashFunction> &t_availableCells,
    const vector<Ship> &t_existingShips,
    uint8_t t_newShipLength) const
{
    for (auto existingShip : t_existingShips)
    {
        auto shipCells = existingShip.getShipCells();
        for (auto cell : shipCells)
        {

            for (int8_t index = -1; index <= t_newShipLength; index++)
            {
                eraseValidCell(t_availableCells, cell.horCoord - index, cell.verCoord - 1);
                eraseValidCell(t_availableCells, cell.horCoord - index, cell.verCoord);
                eraseValidCell(t_availableCells, cell.horCoord - index, cell.verCoord + 1);
            }
        }
    }
}

void ComputerShipArrangement::eraseValidCell(
    unordered_set<Cell, Cell::HashFunction> &t_availableCells,
    int8_t t_horCoord,
    int8_t t_verCoord) const
{
    auto isPointOnMap = (t_horCoord >= 0 && t_horCoord < Constants::MAP_SIZE) &&
                        (t_verCoord >= 0 && t_verCoord < Constants::MAP_SIZE);
    if (isPointOnMap)
    {
        t_availableCells.erase(Cell(t_horCoord, t_verCoord));
    }
}
