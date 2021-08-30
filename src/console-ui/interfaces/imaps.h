#ifndef BATTLESHIP_SRC_CONSOLE_UI_INTERFACES_IMAPS_H
#define BATTLESHIP_SRC_CONSOLE_UI_INTERFACES_IMAPS_H

class IMaps
{
public:
    virtual void initMaps(
        const ShipCoordinates &t_myCarrier,
        const ShipCoordinates &t_myBattleship,
        const ShipCoordinates &t_myCruiser,
        const ShipCoordinates &t_mySubmarine,
        const ShipCoordinates &t_myDestroyer) = 0;
    virtual void updateMyMap(const MapUpdateData &updateData) = 0;
    virtual void printMaps() const = 0;
};

#endif
