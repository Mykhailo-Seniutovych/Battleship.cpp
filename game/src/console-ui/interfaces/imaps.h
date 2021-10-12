#ifndef BATTLESHIP_SRC_CONSOLE_UI_INTERFACES_IMAPS_H
#define BATTLESHIP_SRC_CONSOLE_UI_INTERFACES_IMAPS_H

#include "ship-coordinates.h"
#include "map-update-data.h"

class IMaps
{
public:
    virtual void initMaps(
        const ShipCoordinates &t_myBattleship,
        const ShipCoordinates &t_myCruiser1,
        const ShipCoordinates &t_myCruiser2,
        const ShipCoordinates &t_myDestroyer1,
        const ShipCoordinates &t_myDestroyer2,
        const ShipCoordinates &t_myDestroyer3,
        const ShipCoordinates &t_mySubmarine1,
        const ShipCoordinates &t_mySubmarine2,
        const ShipCoordinates &t_mySubmarine3,
        const ShipCoordinates &t_mySubmarine4) = 0;

    virtual void updateMyMap(const MapUpdateData &t_updateData) = 0;
    virtual void updateEnemyMap(const MapUpdateData &t_updateData) = 0;

    virtual void printMyShotCell(const Cell &t_cell) const = 0;
    virtual void printMaps() const = 0;
};

#endif
