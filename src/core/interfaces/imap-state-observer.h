#ifndef BATTLESHIP_SRC_CORE_INTERFACES_IMAP_STATE_OBSERVER_H
#define BATTLESHIP_SRC_CORE_INTERFACES_IMAP_STATE_OBSERVER_H

#include "../models/ships.h"
#include "../models/map-update-data.h"

class IMapStateObserver
{
public:
    virtual void notifyShipsInitialized(const Ships &t_ships) const  = 0;
    virtual void notifyMapUpdated(const MapUpdateData &t_updateData) const = 0;
};

#endif
