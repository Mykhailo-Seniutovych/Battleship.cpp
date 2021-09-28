#ifndef BATTLESHIP_SRC_CONSOLE_UI_UI_MAPS_H
#define BATTLESHIP_SRC_CONSOLE_UI_UI_MAPS_H

#include <string>
#include "ship-coordinates.h"
#include "map-update-data.h"
#include "interfaces/imaps.h"
#include "constants.h"

enum class MapCellState
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

    void updateMyMap(const MapUpdateData &t_updateData) override;
    void updateEnemyMap(const MapUpdateData &t_updateData) override;

    void printMyShotCell(const Cell &t_cell) const override;
    void printMaps() const override;

private:
#ifdef __unix
    const std::string INVISIBLE_CELL = "- ";
    const std::string MISSED_SHOT_CELL = "\U00002737 ";
    const std::string MY_SHIP_CELL = "\U0001F229";
    const std::string SHIP_DAMAGED = "\U00002716 ";
    const std::string SHIP_SUNK_CELL = "\U0001F147 ";
    const std::string MAPS_SEPARATOR = "  |  ";
// UNICODE characters are not supported on Windows Console, that's why we have to use ASCHII for Windows
#elif defined _WIN32
    const std::string INVISIBLE_CELL = "- ";
    const std::string MISSED_SHOT_CELL = "* ";
    const std::string MY_SHIP_CELL = "()";
    const std::string SHIP_DAMAGED = "X ";
    const std::string SHIP_SUNK_CELL = "X*";
    const std::string MAPS_SEPARATOR = "  |  ";
#endif

    MapCellState m_myMap[Constants::MAP_SIZE][Constants::MAP_SIZE];
    MapCellState m_enemyMap[Constants::MAP_SIZE][Constants::MAP_SIZE];

    void updateMap(
        MapCellState (&t_map)[Constants::MAP_SIZE][Constants::MAP_SIZE],
        const MapUpdateData &t_updateData);
    void addSunkShip(
        MapCellState (&t_map)[Constants::MAP_SIZE][Constants::MAP_SIZE],
        const ShipCoordinates &t_sunkShipCoord);
    MapCellState convertToMapState(CellState cellState) const;
    void initShipOnMyMap(const ShipCoordinates &ship);
    void printMapsSeparator() const;
    void printMapRow(uint8_t row, const MapCellState (&t_map)[Constants::MAP_SIZE][Constants::MAP_SIZE]) const;
    void printRowNumber(uint8_t rowNum) const;
    void printCell(const MapCellState &cellState) const;
};

#endif
