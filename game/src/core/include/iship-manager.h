#ifndef BATTLESHIP_SRC_CORE_INCLUDE_ISHIP_MANAGER_H
#define BATTLESHIP_SRC_CORE_INCLUDE_ISHIP_MANAGER_H

#include "map-update-data.h"
#include "shoot-response.h"
#include "imap-state-observer.h"

class IShipManager
{
public:
    virtual ShootResponse receiveShot(const Cell &t_cell) = 0;
    virtual void initializeShips(const Ships &t_ships) = 0;
    virtual void subscribe(std::unique_ptr<IMapStateObserver> t_observer) = 0;
    virtual void unsubscribe(std::unique_ptr<IMapStateObserver> t_observer) = 0;
};

#endif
