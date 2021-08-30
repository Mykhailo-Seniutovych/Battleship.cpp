#ifndef BATTLESHIP_SRC_CORE_MODELS_SHIPS_H
#define BATTLESHIP_SRC_CORE_MODELS_SHIPS_H

#include "./ship.h"

struct Ships
{
    Ship carrier;
    Ship battleship;
    Ship cruiser;
    Ship submarine;
    Ship destroyer;
};

#endif
