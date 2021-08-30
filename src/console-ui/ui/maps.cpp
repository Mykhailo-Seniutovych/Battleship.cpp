
#include <iostream>
#include "maps.h"
#include "../../core/models/ship-coordinates.h"
#include "../../core/models/map-update-data.h"

using namespace std;

void Maps::initMaps(
    const ShipCoordinates &t_myCarrier,
    const ShipCoordinates &t_myBattleship,
    const ShipCoordinates &t_myCruiser,
    const ShipCoordinates &t_mySubmarine,
    const ShipCoordinates &t_myDestroyer)
{
    //TODO: validation
    for (uint8_t row = 0; row < MAP_SIZE; row++)
    {
        for (uint8_t col = 0; col < MAP_SIZE; col++)
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
    if (updateData.cellState == CellState::ShipSunk || updateData.cellState == CellState::GameOver)
    {
        if (updateData.sunkShipCoordinates.position == Position::Horizontal)
        {
            auto row = updateData.sunkShipCoordinates.axisCoordinate;
            for (auto col : updateData.sunkShipCoordinates.cellsCoordinates)
            {
                m_myMap[row][col] = MapCellState::SunkShip;
            }
        }
        else
        {
            auto col = updateData.sunkShipCoordinates.axisCoordinate;
            for (auto row : updateData.sunkShipCoordinates.cellsCoordinates)
            {
                m_myMap[row][col] = MapCellState::SunkShip;
            }
        }
    }
    else
    {
        auto row = updateData.cell.horCoord;
        auto col = updateData.cell.verCoord;
        m_myMap[row][col] = convertToMapState(updateData.cellState);
    }
}

void Maps::printMaps() const
{
    for (uint8_t row = 0; row <= MAP_SIZE; row++)
    {
        printMapRow(row, m_myMap);
        printMapsSeparator();
        printMapRow(row, m_enemyMap);
        cout << endl;
    }
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

void Maps::printMapRow(uint8_t row, const MapCellState (&t_map)[MAP_SIZE][MAP_SIZE]) const
{
    for (uint8_t col = 0; col <= MAP_SIZE; col++)
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
    switch (rowNum)
    {
    case 1:
        cout << "A ";
        break;
    case 2:
        cout << "B ";
        break;
    case 3:
        cout << "C ";
        break;
    case 4:
        cout << "D ";
        break;
    case 5:
        cout << "E ";
        break;
    case 6:
        cout << "F ";
        break;
    case 7:
        cout << "G ";
        break;
    case 8:
        cout << "H ";
        break;
    case 9:
        cout << "I ";
        break;
    case 10:
        cout << "J ";
        break;
    default:
        break;
    }
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
