#ifndef BATTLESHIP_SRC_CORE_INCLUDE_CONSTANTS_H
#define BATTLESHIP_SRC_CORE_INCLUDE_CONSTANTS_H

#include <stdint.h>

class Constants
{
public:
    static const uint8_t SHIPS_COUNT = 5;
    static const uint8_t MAP_SIZE = 10;

    static const uint8_t CARRIER_LENGTH = 5;
    static const uint8_t BATTLESHIP_LENGTH = 4;
    static const uint8_t CRUISER_LENGTH = 3;
    static const uint8_t SUBMARINE_LENGTH = 3;
    static const uint8_t DESTROYER_LENGTH = 2;
};

#endif
