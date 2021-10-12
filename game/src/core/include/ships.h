#ifndef BATTLESHIP_SRC_CORE_INCLUDE_SHIPS_H
#define BATTLESHIP_SRC_CORE_INCLUDE_SHIPS_H

#include "./ship.h"

struct Ships
{
    Ship battleship;

    Ship cruiser1;
    Ship cruiser2;

    Ship destroyer1;
    Ship destroyer2;
    Ship destroyer3;
    
    Ship submarine1;
    Ship submarine2;
    Ship submarine3;
    Ship submarine4;
};

#endif
