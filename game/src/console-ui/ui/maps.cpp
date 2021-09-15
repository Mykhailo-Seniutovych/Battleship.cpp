
#include <iostream>
#include "maps.h"
#include "ship-coordinates.h"
#include "map-update-data.h"
#include "utils/map-utils.h"
#include "constants.h"

using namespace std;
using namespace map_utils;

void Maps::initMaps(
    const ShipCoordinates &t_myCarrier,
    const ShipCoordinates &t_myBattleship,
    const ShipCoordinates &t_myCruiser,
    const ShipCoordinates &t_mySubmarine,
    const ShipCoordinates &t_myDestroyer)
{
    for (uint8_t row = 0; row < Constants::MAP_SIZE; row++)
    {
        for (uint8_t col = 0; col < Constants::MAP_SIZE; col++)
        {
            m_myMap[row][col] = MapCellState::Invisible;
            m_enemyMap[row][col] = MapCellState::Invisible;
        }
    }

    initShipOnMyMap(t_myCarrier);
    initShipOnMyMap(t_myBattleship);
    initShipOnMyMap(t_myCruiser);
    initShipOnMyMap(t_mySubmarine);
    initShipOnMyMap(t_myDestroyer);
}

void Maps::updateMyMap(const MapUpdateData &updateData)
{
    updateMap(m_myMap, updateData);
}

void Maps::updateEnemyMap(const MapUpdateData &updateData)
{
    updateMap(m_enemyMap, updateData);
}

void Maps::updateMap(
    MapCellState (&t_map)[Constants::MAP_SIZE][Constants::MAP_SIZE],
    const MapUpdateData &t_updateData)
{
    if (t_updateData.cellState == CellState::ShipSunk || t_updateData.cellState == CellState::GameOver)
    {
        addSunkShip(t_map, t_updateData.sunkShipCoordinates);
    }
    else
    {
        auto row = t_updateData.cell.horCoord;
        auto col = t_updateData.cell.verCoord;
        t_map[row][col] = convertToMapState(t_updateData.cellState);
    }
}

void Maps::addSunkShip(
    MapCellState (&t_map)[Constants::MAP_SIZE][Constants::MAP_SIZE],
    const ShipCoordinates &t_sunkShipCoord)
{
    if (t_sunkShipCoord.position == Position::Horizontal)
    {
        auto row = t_sunkShipCoord.axisCoordinate;
        for (auto col : t_sunkShipCoord.cellsCoordinates)
        {
            t_map[row][col] = MapCellState::SunkShip;
        }
    }
    else
    {
        auto col = t_sunkShipCoord.axisCoordinate;
        for (auto row : t_sunkShipCoord.cellsCoordinates)
        {
            t_map[row][col] = MapCellState::SunkShip;
        }
    }
}

void Maps::printMyShotCell(const Cell &t_cell) const
{
    cout << "Enemy shot at ("
         << convertRowNumberToRowLetter(unsigned(t_cell.horCoord) + 1)
         << " "
         << unsigned(t_cell.verCoord) + 1
         << ")"
         << endl;
}

void Maps::printMaps() const
{
    for (uint8_t row = 0; row <= Constants::MAP_SIZE; row++)
    {
        printMapRow(row, m_myMap);
        printMapsSeparator();
        printMapRow(row, m_enemyMap);
        cout << endl;
    }
    cout << endl;
}

MapCellState Maps::convertToMapState(CellState cellState) const
{
    MapCellState result;

    switch (cellState)
    {
    case CellState::Miss:
        result = MapCellState::MissedShot;
        break;
    case CellState::ShipDamaged:
        result = MapCellState::DamagedShip;
        break;
    case CellState::ShipSunk:
        result = MapCellState::SunkShip;
        break;
    case CellState::GameOver:
        result = MapCellState::SunkShip;
        break;
    default:
        break;
    }

    return result;
}

void Maps::initShipOnMyMap(const ShipCoordinates &ship)
{
    if (ship.position == Position::Horizontal)
    {
        auto row = ship.axisCoordinate;
        for (auto col : ship.cellsCoordinates)
        {
            m_myMap[row][col] = MapCellState::MyShip;
        }
    }
    else
    {
        auto col = ship.axisCoordinate;
        for (auto row : ship.cellsCoordinates)
        {
            m_myMap[row][col] = MapCellState::MyShip;
        }
    }
}

void Maps::printMapsSeparator() const
{
    cout << MAPS_SEPARATOR;
}

void Maps::printMapRow(uint8_t row, const MapCellState (&t_map)[Constants::MAP_SIZE][Constants::MAP_SIZE]) const
{
    for (uint8_t col = 0; col <= Constants::MAP_SIZE; col++)
    {
        if (row == 0 && col == 0)
        {
            cout << "  ";
        }
        else if (row == 0)
        {

            cout << unsigned(col);
            auto isColumnNumberOneCharLong = col < 10;
            if (isColumnNumberOneCharLong)
            {
                cout << " ";
            }
        }
        else if (col == 0)
        {
            printRowNumber(row);
        }
        else
        {
            printCell(t_map[row - 1][col - 1]);
        }
    }
}

void Maps::printRowNumber(uint8_t rowNum) const
{
    char rowLetter = convertRowNumberToRowLetter(rowNum);
    cout << rowLetter << " ";
}

void Maps::printCell(const MapCellState &cellState) const
{
    switch (cellState)
    {
    case MapCellState::Invisible:
        cout << INVISIBLE_CELL;
        break;
    case MapCellState::MyShip:
        cout << MY_SHIP_CELL;
        break;
    case MapCellState::MissedShot:
        cout << MISSED_SHOT_CELL;
        break;
    case MapCellState::DamagedShip:
        cout << SHIP_DAMAGED;
        break;
    case MapCellState::SunkShip:
        cout << SHIP_SUNK_CELL;
        break;
    default:
        break;
    }
}
