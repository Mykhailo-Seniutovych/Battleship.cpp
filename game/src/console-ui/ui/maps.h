#ifndef BATTLESHIP_SRC_CONSOLE_UI_UI_MAPS_H
#define BATTLESHIP_SRC_CONSOLE_UI_UI_MAPS_H

#include <string>
#include "../../core/models/ship-coordinates.h"
#include "../../core/models/map-update-data.h"
#include "../interfaces/imaps.h"

enum MapCellState
{
    Invisible,
    MyShip,
    MissedShot,
    DamagedShip,
    SunkShip
};

class Maps : public IMaps
{
public:
    void initMaps(
        const ShipCoordinates &t_myCarrier,
        const ShipCoordinates &t_myBattleship,
        const ShipCoordinates &t_myCruiser,
        const ShipCoordinates &t_mySubmarine,
        const ShipCoordinates &t_myDestroyer) override;

    void updateMyMap(const MapUpdateData &updateData) override;
    void printMaps() const override;

private:
    static const uint8_t MAP_SIZE = 10;
    
    // UNICODE characters are not supported on Windows Console, that's why we have to use ASCHII for Windows
#ifdef _WIN32
    const std::string INVISIBLE_CELL = "- ";
    const std::string MISSED_SHOT_CELL = "* ";
    const std::string MY_SHIP_CELL = "||";
    const std::string SHIP_DAMAGED = "X ";
    const std::string SHIP_SUNK_CELL = "X*";
    const std::string MAPS_SEPARATOR = "  |  ";
#else 
    const std::string INVISIBLE_CELL = "- ";
    const std::string MISSED_SHOT_CELL = "* ";
    const std::string MY_SHIP_CELL = "\U0001F229";
    const std::string SHIP_DAMAGED = "X ";
    const std::string SHIP_SUNK_CELL = "\U0001F147 ";
    const std::string MAPS_SEPARATOR = "  |  ";
#endif


    MapCellState m_myMap[MAP_SIZE][MAP_SIZE];
    MapCellState m_enemyMap[MAP_SIZE][MAP_SIZE];

    MapCellState convertToMapState(CellState cellState) const;
    void initShipOnMyMap(const ShipCoordinates &ship);
    void printMapsSeparator() const;
    void printMapRow(uint8_t row, const MapCellState (&t_map)[MAP_SIZE][MAP_SIZE]) const;
    void printRowNumber(uint8_t rowNum) const;
    void printCell(const MapCellState &cellState) const;
};


#endif
