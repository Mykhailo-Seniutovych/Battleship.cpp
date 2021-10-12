#ifndef BATTLESHIP_SRC_CONSOLE_UI_SERVICES_CONSOLE_SHIP_ARRANGEMENT_H
#define BATTLESHIP_SRC_CONSOLE_UI_SERVICES_CONSOLE_SHIP_ARRANGEMENT_H

#include <fstream>
#include <string>
#include <ship.h>
#include <vector>
#include <cstdint>
#include "cell.h"
#include "iship-arrangement.h"

class ConsoleShipArrangement : public IShipArrangement
{
public:
    Ships getShipsArrangement() const override;

private:
    struct ShipCells
    {
        std::vector<Cell> battleshipCells;
        
        std::vector<Cell> cruiser1Cells;
        std::vector<Cell> cruiser2Cells;

        std::vector<Cell> destroyer1Cells;
        std::vector<Cell> destroyer2Cells;
        std::vector<Cell> destroyer3Cells;

        std::vector<Cell> submarine1Cells;
        std::vector<Cell> submarine2Cells;
        std::vector<Cell> submarine3Cells;
        std::vector<Cell> submarine4Cells;

    };

    void skipCommentSection(std::ifstream &t_inputFileStream) const;
    void skipUntilSecondMapRow(std::ifstream &t_inputFileStream) const;
    void parseLine(ShipCells &t_shipCells, const std::string &t_line, uint8_t t_rowIndex) const;
    Ships createShipsFromCells(const ShipCells &t_shipCells) const;
    Ship createShipFromCells(const std::vector<Cell> &t_cells) const;
};

#endif
