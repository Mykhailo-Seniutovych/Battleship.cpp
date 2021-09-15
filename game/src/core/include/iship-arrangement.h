#ifndef BATTLESHIP_SRC_CORE_INCLUDE_ISHIP_ARRANGEMENT_H
#define BATTLESHIP_SRC_CORE_INCLUDE_ISHIP_ARRANGEMENT_H

#include <array>

#include "ships.h"
#include "constants.h"

class IShipArrangement
{
public:
    virtual Ships getShipsArrangement() const = 0;
};

#endif
