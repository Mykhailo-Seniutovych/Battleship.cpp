#ifndef BATTLESHIP_SRC_CORE_INTERFACES_ISHIP_MANAGER_H
#define BATTLESHIP_SRC_CORE_INTERFACES_ISHIP_MANAGER_H

#include "../models/map-update-data.h"
#include "../models/shoot-response.h"
#include "../interfaces/imap-state-observer.h"

class IShipManager
{
public:
    virtual ShootResponse receiveShot(const Cell &t_cell) = 0;
    virtual void initializeShips(const Ships &t_ships) = 0;
    virtual void subscribe(std::shared_ptr<IMapStateObserver> t_observer) = 0;
    virtual void unsubscribe(std::shared_ptr<IMapStateObserver> t_observer) = 0;
};

#endif
