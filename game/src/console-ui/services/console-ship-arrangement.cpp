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

static const std::string CARRIER_SYMBOL = "5 ";
static const std::string BATTLESHIP_SYMBOL = "4 ";
static const std::string CRUISER_SYMBOL = "3 ";
static const std::string SUBMARINE_SYMBOL = "3`";
static const std::string DESTROYER_SYMBOL = "2 ";

static void editMapsOnUnix()
{
#ifdef __unix
    std::string cmd = "/bin/nano " + Constants::MAP_FILE_NAME;
    system(cmd.c_str());
#endif
}

static void rightTrimString(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
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
    auto charCountInOneMapRow = Constants::MAP_SIZE * 2 + 3;
    if (t_line.size() != charCountInOneMapRow)
    {
        throw ValidationException(
            "Map file has incorrect format. "
            "If you corrupted the file and don't know how to restore it to the correct format, reinstall the game.");
    }

    for (uint8_t verIndex = 2; verIndex < charCountInOneMapRow - 1; verIndex += 2)
    {
        auto symbol = t_line.substr(verIndex, 2);
        uint8_t colIndex = (verIndex - 2) / 2;
        if (symbol == CARRIER_SYMBOL)
        {
            t_shipCells.carrierCells.push_back(Cell(t_rowIndex, colIndex));
        }
        if (symbol == BATTLESHIP_SYMBOL)
        {
            t_shipCells.battleshipCells.push_back(Cell(t_rowIndex, colIndex));
        }
        if (symbol == CRUISER_SYMBOL)
        {
            t_shipCells.cruiserCells.push_back(Cell(t_rowIndex, colIndex));
        }
        if (symbol == SUBMARINE_SYMBOL)
        {
            t_shipCells.submarineCells.push_back(Cell(t_rowIndex, colIndex));
        }
        if (symbol == DESTROYER_SYMBOL)
        {
            t_shipCells.destroyerCells.push_back(Cell(t_rowIndex, colIndex));
        }
    }
}

Ships ConsoleShipArrangement::createShipsFromCells(const ShipCells &t_shipCells) const
{
    Ships ships{
        .carrier = createShipFromCells(t_shipCells.carrierCells),
        .battleship = createShipFromCells(t_shipCells.battleshipCells),
        .cruiser = createShipFromCells(t_shipCells.cruiserCells),
        .submarine = createShipFromCells(t_shipCells.submarineCells),
        .destroyer = createShipFromCells(t_shipCells.destroyerCells)};
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
