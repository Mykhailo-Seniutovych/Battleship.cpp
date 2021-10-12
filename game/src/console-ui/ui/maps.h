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
        const ShipCoordinates &t_myBattleship,
        const ShipCoordinates &t_myCruiser1,
        const ShipCoordinates &t_myCruiser2,
        const ShipCoordinates &t_myDestroyer1,
        const ShipCoordinates &t_myDestroyer2,
        const ShipCoordinates &t_myDestroyer3,
        const ShipCoordinates &t_mySubmarine1,
        const ShipCoordinates &t_mySubmarine2,
        const ShipCoordinates &t_mySubmarine3,
        const ShipCoordinates &t_mySubmarine4) override;

    void updateMyMap(const MapUpdateData &t_updateData) override;
    void updateEnemyMap(const MapUpdateData &t_updateData) override;

    void printMyShotCell(const Cell &t_cell) const override;
    void printMaps() const override;

private:
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
    void printColNumber(uint8_t rowNum) const;
    void printCell(const MapCellState &cellState) const;
};

#endif
