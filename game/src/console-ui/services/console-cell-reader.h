#ifndef BATTLESHIP_SRC_CONSOLE_UI_SERVICES_CONSOLE_CELL_READER_H
#define BATTLESHIP_SRC_CONSOLE_UI_SERVICES_CONSOLE_CELL_READER_H

#include "icell-reader.h"
#include <string>

class ConsoleCellReader : public ICellReader
{
public:
    Cell readCell() const override;

private:
    const std::string INVALID_INPUT_ERROR_MSG =
        "Coordinates entered are invalid. "
        "Make sure your input is in this format '{RowLetterNumber} {ColumnNumber}', "
        "where {RowLetterNumber} is one of 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'I' "
        "and {ColumnNumber} is one of '1', '2', '3', '4', '5', '6', '7', '8', '9', '10'";
};

#endif
