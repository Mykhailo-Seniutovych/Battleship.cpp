#ifndef BATTLESHIP_CORE_INFRASTRUCTURE_ISHIPMANAGER_H
#define BATTLESHIP_CORE_INFRASTRUCTURE_ISHIPMANAGER_H

#include "iobservable.h"
#include "../models/map-update-data.h"
#include "../models/shoot-response.h"

class IShipManager: IObservable<MapUpdateData> {
public:
    virtual ShootResponse receiveShot(Cell cell) = 0;
    virtual void initializeShips(
        Ship t_carrier, Ship t_battleship, Ship t_cruiser, Ship t_submarine, Ship t_destroyer) = 0;
    virtual void subscribe(IObserver<MapUpdateData> *observer) override = 0;
    virtual void unsubscribe(IObserver<MapUpdateData> *observer) override = 0;
};

#endif
