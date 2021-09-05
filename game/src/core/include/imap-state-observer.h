#ifndef BATTLESHIP_SRC_CORE_INCLUDE_IMAP_STATE_OBSERVER_H
#define BATTLESHIP_SRC_CORE_INCLUDE_IMAP_STATE_OBSERVER_H

#include "ships.h"
#include "map-update-data.h"

class IMapStateObserver
{
public:
    virtual void notifyShipsInitialized(const Ships &t_ships) const = 0;
    virtual void notifyMapUpdated(const MapUpdateData &t_updateData) const = 0;
};

#endif
