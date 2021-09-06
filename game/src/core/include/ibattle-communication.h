#ifndef BATTLESHIP_SRC_CORE_INCLUDE_IBATTLE_COMMUNICATION_H
#define BATTLESHIP_SRC_CORE_INCLUDE_IBATTLE_COMMUNICATION_H

#include "cell.h"
#include "shoot-response.h"

class IBattleComunication
{
public:
    virtual Cell getNextShotTarget() const = 0;
    virtual void notifyShotResponse(ShootResponse shootResponse) = 0;
    virtual ShootResponse sendShotTo(const Cell &cell) = 0;
};

#endif
