#ifndef BATTLESHIP_SRC_CONSOLE_UI_INTERFACES_IMAPS_H
#define BATTLESHIP_SRC_CONSOLE_UI_INTERFACES_IMAPS_H

#include "ship-coordinates.h"
#include "map-update-data.h"

class IMaps
{
public:
    virtual void initMaps(
        const ShipCoordinates &t_myCarrier,
        const ShipCoordinates &t_myBattleship,
        const ShipCoordinates &t_myCruiser,
        const ShipCoordinates &t_mySubmarine,
        const ShipCoordinates &t_myDestroyer) = 0;

    virtual void updateMyMap(const MapUpdateData &t_updateData) = 0;
    virtual void updateEnemyMap(const MapUpdateData &t_updateData) = 0;

    virtual void printMyShotCell(const Cell &t_cell) const = 0;
    virtual void printMaps() const = 0;
};

#endif
