#include <string>
#include <ios>
#include <vector>
#include <cstdint>
#include <unordered_set>
#include <string>
#include <exception>
#include <iostream>
#include <algorithm>

#include "console-ship-arrangement.h"
#include "constants.h"
#include "validation-exception.h"

using namespace std;

static const std::string BATTLESHIP_SYMBOL = "4 ";

static const std::string CRUISER1_SYMBOL = "3 ";
static const std::string CRUISER2_SYMBOL = "3`";

static const std::string DESTROYER1_SYMBOL = "2 ";
static const std::string DESTROYER2_SYMBOL = "2`";
static const std::string DESTROYER3_SYMBOL = "2'";

static const std::string SUBMARINE1_SYMBOL = "1 ";
static const std::string SUBMARINE2_SYMBOL = "1`";
static const std::string SUBMARINE4_SYMBOL = "1'";
static const std::string SUBMARINE3_SYMBOL = "1~";

static void editMapsOnUnix()
{
#ifdef __unix
    std::string cmd = "/bin/nano " + Constants::MAP_FILE_NAME;
    system(cmd.c_str());
#endif
}

static void rightTrimString(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
}

Ships ConsoleShipArrangement::getShipsArrangement() const
{
    editMapsOnUnix();

    ifstream inputFileStream;
    inputFileStream.open(Constants::MAP_FILE_NAME);
    if (!inputFileStream.is_open())
    {
        throw ios_base::failure("Could not open file " + Constants::MAP_FILE_NAME);
    }

    skipCommentSection(inputFileStream);
    skipUntilSecondMapRow(inputFileStream);

    ShipCells shipCells;
    uint8_t rowIndex = 0;
    while (!inputFileStream.eof() && rowIndex < Constants::MAP_SIZE)
    {
        string line;
        getline(inputFileStream, line);
        rightTrimString(line);
        parseLine(shipCells, line, rowIndex);
        rowIndex++;
    }

    auto ships = createShipsFromCells(shipCells);
    return ships;
};

void ConsoleShipArrangement::skipCommentSection(ifstream &t_inputFileStream) const
{
    while (!t_inputFileStream.eof())
    {
        char currentChar;
        t_inputFileStream >> currentChar;
        if (currentChar == '*')
        {
            t_inputFileStream >> currentChar;
            if (currentChar == '/')
            {
                break;
            }
        }
    }
}

void ConsoleShipArrangement::skipUntilSecondMapRow(ifstream &t_inputFileStream) const
{
    while (!t_inputFileStream.eof())
    {
        string line;
        getline(t_inputFileStream, line);
        auto isWhitespace = line.find_first_not_of(' ') == line.npos;
        auto isEmpty = line == "";
        if (!isEmpty && !isWhitespace)
        {
            break;
        }
    }
}

void ConsoleShipArrangement::parseLine(
    ShipCells &t_shipCells, const std::string &t_line, uint8_t t_rowIndex) const
{
    auto charCountInOneMapRow = Constants::MAP_SIZE * 2 + 4;
    if (t_line.size() != charCountInOneMapRow)
    {
        throw ValidationException(
            "Map file has incorrect format. "
            "If you corrupted the file and don't know how to restore it to the correct format, reinstall the game.");
    }

    for (uint8_t verIndex = 3; verIndex < charCountInOneMapRow - 1; verIndex += 2)
    {
        auto symbol = t_line.substr(verIndex, 2);
        uint8_t colIndex = (verIndex - 2) / 2;
        if (symbol == BATTLESHIP_SYMBOL)
        {
            t_shipCells.battleshipCells.push_back(Cell(t_rowIndex, colIndex));
        }

        if (symbol == CRUISER1_SYMBOL)
        {
            t_shipCells.cruiser1Cells.push_back(Cell(t_rowIndex, colIndex));
        }
        if (symbol == CRUISER2_SYMBOL)
        {
            t_shipCells.cruiser2Cells.push_back(Cell(t_rowIndex, colIndex));
        }

        if (symbol == DESTROYER1_SYMBOL)
        {
            t_shipCells.destroyer1Cells.push_back(Cell(t_rowIndex, colIndex));
        }
        if (symbol == DESTROYER2_SYMBOL)
        {
            t_shipCells.destroyer2Cells.push_back(Cell(t_rowIndex, colIndex));
        }
        if (symbol == DESTROYER3_SYMBOL)
        {
            t_shipCells.destroyer3Cells.push_back(Cell(t_rowIndex, colIndex));
        }

        if (symbol == SUBMARINE1_SYMBOL)
        {
            t_shipCells.submarine1Cells.push_back(Cell(t_rowIndex, colIndex));
        }
        if (symbol == SUBMARINE2_SYMBOL)
        {
            t_shipCells.submarine2Cells.push_back(Cell(t_rowIndex, colIndex));
        }
        if (symbol == SUBMARINE3_SYMBOL)
        {
            t_shipCells.submarine3Cells.push_back(Cell(t_rowIndex, colIndex));
        }
        if (symbol == SUBMARINE4_SYMBOL)
        {
            t_shipCells.submarine4Cells.push_back(Cell(t_rowIndex, colIndex));
        }
    }
}

Ships ConsoleShipArrangement::createShipsFromCells(const ShipCells &t_shipCells) const
{
    Ships ships{
        .battleship = createShipFromCells(t_shipCells.battleshipCells),
        .cruiser1 = createShipFromCells(t_shipCells.cruiser1Cells),
        .cruiser2 = createShipFromCells(t_shipCells.cruiser2Cells),
        .destroyer1 = createShipFromCells(t_shipCells.destroyer1Cells),
        .destroyer2 = createShipFromCells(t_shipCells.destroyer2Cells),
        .destroyer3 = createShipFromCells(t_shipCells.destroyer3Cells),
        .submarine1 = createShipFromCells(t_shipCells.submarine1Cells),
        .submarine2 = createShipFromCells(t_shipCells.submarine2Cells),
        .submarine3 = createShipFromCells(t_shipCells.submarine3Cells),
        .submarine4 = createShipFromCells(t_shipCells.submarine4Cells),
    };
    return ships;
}

Ship ConsoleShipArrangement::createShipFromCells(const std::vector<Cell> &t_cells) const
{
    Ship ship;
    if (t_cells.size() > 1)
    {
        auto position =
            t_cells[0].horCoord == t_cells[1].horCoord
                ? Position::Horizontal
                : Position::Vertical;

        auto axisCoord = position == Position::Horizontal
                             ? t_cells[0].horCoord
                             : t_cells[0].verCoord;

        unordered_set<uint8_t> coordinates = {};
        for (const auto &cell : t_cells)
        {
            auto cellAxisCoord = position == Position::Horizontal ? cell.horCoord : cell.verCoord;
            if (cellAxisCoord != axisCoord)
            {
                throw ValidationException(
                    "Ship cells must be in sequential order, "
                    "and ship must be either in horizontal or vertical position, not both.");
            }
            coordinates.insert(position == Position::Horizontal ? cell.verCoord : cell.horCoord);
        }
        ship = Ship(position, axisCoord, coordinates);
    }
    else if (t_cells.size() == 1)
    {
        ship = Ship(Position::Horizontal, t_cells[0].horCoord, {t_cells[0].verCoord});
    }
    else
    {
        throw ValidationException("Ship length cannot be 0");
    }
    return ship;
}
