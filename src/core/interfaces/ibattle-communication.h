#ifndef BATTLESHIP_SRC_CORE_INTERFACES_IBATTLE_COMMUNICATION_H
#define BATTLESHIP_SRC_CORE_INTERFACES_IBATTLE_COMMUNICATION_H

#include "../models/cell.h"

class IBattleComunication
{
public:
    virtual Cell getNextShotTarget() const = 0;
    virtual void sendShotTo(const Cell &cell) = 0;
};

#endif
