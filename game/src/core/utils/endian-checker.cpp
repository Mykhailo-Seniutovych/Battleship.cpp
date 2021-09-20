#include "endian-checker.h"
#include <cstdint>

bool EndianChecker::isCurrentSystemBigEndian()
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1; 
}