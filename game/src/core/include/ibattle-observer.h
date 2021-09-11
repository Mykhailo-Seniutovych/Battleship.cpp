#ifndef BATTLESHIP_SRC_CORE_INCLUDE_IBATTLE_OBSERVER_H
#define BATTLESHIP_SRC_CORE_INCLUDE_IBATTLE_OBSERVER_H

#include "ships.h"
#include "map-update-data.h"

class IBattleObserver
{
public:
    virtual void notifyShipsInitialized(const Ships &t_ships) const = 0;
    virtual void notifyMyMapUpdated(const MapUpdateData &t_updateData) const = 0;
    virtual void notifyEnemyMapUpdated(const MapUpdateData &t_updateData) const = 0;
    virtual void notifyGameOver(bool t_currentPlayerWon) const = 0;
};

#endif
