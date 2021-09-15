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
        std::vector<Cell> carrierCells;
        std::vector<Cell> battleshipCells;
        std::vector<Cell> cruiserCells;
        std::vector<Cell> submarineCells;
        std::vector<Cell> destroyerCells;
    };

    const std::string MAP_FILE_NAME = "map.txt";
    const std::string CARRIER_SYMBOL = "5 ";
    const std::string BATTLESHIP_SYMBOL = "4 ";
    const std::string CRUISER_SYMBOL = "3 ";
    const std::string SUBMARINE_SYMBOL = "3`";
    const std::string DESTROYER_SYMBOL = "2 ";

    void skipCommentSection(std::ifstream &t_inputFileStream) const;
    void skipUntilSecondMapRow(std::ifstream &t_inputFileStream) const;
    void parseLine(ShipCells &t_shipCells, const std::string &t_line, uint8_t t_rowIndex) const;
    Ships createShipsFromCells(const ShipCells &t_shipCells) const;
    Ship createShipFromCells(const std::vector<Cell> &t_cells) const;
};

#endif
