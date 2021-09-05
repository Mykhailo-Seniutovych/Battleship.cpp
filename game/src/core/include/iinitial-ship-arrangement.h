#ifndef BATTLESHIP_SRC_CORE_INTERFACES_IINITIAL_SHIP_ARRANGEMENT_H
#define BATTLESHIP_SRC_CORE_INTERFACES_IINITIAL_SHIP_ARRANGEMENT_H

#include <array>

#include "ships.h"
#include "constants.h"

class IInitialShipArrangement
{
public:
    virtual Ships getInitialShipArrangement() const = 0;
};

#endif
