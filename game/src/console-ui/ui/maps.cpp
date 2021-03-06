
#include <iostream>
#include "maps.h"
#include "ship-coordinates.h"
#include "map-update-data.h"
#include "utils/map-utils.h"
#include "constants.h"

using namespace std;
using namespace map_utils;

#ifdef __unix
static const std::string INVISIBLE_CELL = "- ";
static const std::string MISSED_SHOT_CELL = "\U00002737 ";
static const std::string MY_SHIP_CELL = "\U0001F229";
static const std::string SHIP_DAMAGED = "\U00002716 ";
static const std::string SHIP_SUNK_CELL = "\U000025A0 ";
static const std::string MAPS_SEPARATOR = "  |  ";
// UNICODE characters are not supported on Windows Console, that's why we have to use ASCHII for Windows
#elif defined _WIN32
static const std::string INVISIBLE_CELL = "- ";
static const std::string MISSED_SHOT_CELL = "* ";
static const std::string MY_SHIP_CELL = "()";
static const std::string SHIP_DAMAGED = "X ";
static const std::string SHIP_SUNK_CELL = "X*";
static const std::string MAPS_SEPARATOR = "  |  ";
#endif

void Maps::initMaps(
    const ShipCoordinates &t_myBattleship,
    const ShipCoordinates &t_myCruiser1,
    const ShipCoordinates &t_myCruiser2,
    const ShipCoordinates &t_myDestroyer1,
    const ShipCoordinates &t_myDestroyer2,
    const ShipCoordinates &t_myDestroyer3,
    const ShipCoordinates &t_mySubmarine1,
    const ShipCoordinates &t_mySubmarine2,
    const ShipCoordinates &t_mySubmarine3,
    const ShipCoordinates &t_mySubmarine4)
{
    for (uint8_t row = 0; row < Constants::MAP_SIZE; row++)
    {
        for (uint8_t col = 0; col < Constants::MAP_SIZE; col++)
        {
            m_myMap[row][col] = MapCellState::Invisible;
            m_enemyMap[row][col] = MapCellState::Invisible;
        }
    }

    initShipOnMyMap(t_myBattleship);
    initShipOnMyMap(t_myCruiser1);
    initShipOnMyMap(t_myCruiser2);
    initShipOnMyMap(t_myDestroyer1);
    initShipOnMyMap(t_myDestroyer2);
    initShipOnMyMap(t_myDestroyer3);
    initShipOnMyMap(t_mySubmarine1);
    initShipOnMyMap(t_mySubmarine2);
    initShipOnMyMap(t_mySubmarine3);
    initShipOnMyMap(t_mySubmarine4);
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
         << unsigned(t_cell.horCoord) + 1
         << " "
         << convertColNumberToColLetter(unsigned(t_cell.verCoord) + 1)
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
            cout << "   ";
        }
        else if (row == 0)
        {
            printColNumber(col);
        }
        else if (col == 0)
        {
            auto isRowNumberOneCharLong = row < 10;
            if (isRowNumberOneCharLong)
            {
                cout << " ";
            }
            cout << unsigned(row) << " ";
        }
        else
        {
            printCell(t_map[row - 1][col - 1]);
        }
    }
}

void Maps::printColNumber(uint8_t rowNum) const
{
    char rowLetter = convertColNumberToColLetter(rowNum);
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
