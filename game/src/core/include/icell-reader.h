#ifndef BATTLESHIP_SRC_CORE_INCLUDE_ICELL_READER_H
#define BATTLESHIP_SRC_CORE_INCLUDE_ICELL_READER_H

#include "cell.h"

class ICellReader
{
public:
    virtual Cell readCell() const = 0;
};

#endif
