#ifndef BATTLESHIP_SRC_CONSOLE_UI_SERVICES_CONSOLE_CELL_READER_H
#define BATTLESHIP_SRC_CONSOLE_UI_SERVICES_CONSOLE_CELL_READER_H

#include "icell-reader.h"

class ConsoleCellReader: public ICellReader
{
public:
    Cell readCell() const override;
};

#endif
