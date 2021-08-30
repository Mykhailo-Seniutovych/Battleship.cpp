#ifndef BATTLESHIP_CORE_INFRASTRUCTURE_ISHIPMANAGER_H
#define BATTLESHIP_CORE_INFRASTRUCTURE_ISHIPMANAGER_H

#include "iobservable.h"
#include "../models/map-update-data.h"
#include "../models/shoot-response.h"

class IShipManager: IObservable<MapUpdateData> {
public:
    virtual ShootResponse receiveShot(const Cell &t_cell) = 0;
    virtual void initializeShips(
        const Ship &t_carrier, 
        const Ship &t_battleship, 
        const Ship &t_cruiser, 
        const Ship &t_submarine, 
        const Ship &t_destroyer) = 0;
    virtual void subscribe(IObserver<MapUpdateData> *observer) override = 0;
    virtual void unsubscribe(IObserver<MapUpdateData> *observer) override = 0;
};

#endif
