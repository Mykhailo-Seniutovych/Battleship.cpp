#include <string>
#include <ios>
#include <vector>
#include <cstdint>
#include <unordered_set>
#include "console-initial-ship-arrangement.h"
#include "constants.h"

using namespace std;

Ships ConsoleInitialShipArrangement::getInitialShipArrangement() const
{
    ifstream inputFileStream;
    inputFileStream.open(MAP_FILE_NAME);
    if (!inputFileStream.is_open())
    {
        throw ios_base::failure("Could not open file " + MAP_FILE_NAME);
    }

    skipCommentSection(inputFileStream);
    skipUntilSecondMapRow(inputFileStream);

    auto shipCells = ShipCells();
    uint8_t rowIndex = 0;
    while (!inputFileStream.eof())
    {
        string line;
        getline(inputFileStream, line);
        parseLine(shipCells, line, rowIndex);
        rowIndex++;
    }

    auto ships = createShipsFromCells(shipCells);
    return ships;
};

void ConsoleInitialShipArrangement::skipCommentSection(ifstream &inputFileStream) const
{
    while (!inputFileStream.eof())
    {
        char currentChar;
        inputFileStream >> currentChar;
        if (currentChar == '*')
        {
            inputFileStream >> currentChar;
            if (currentChar == '/')
            {
                break;
            }
        }
    }
}

void ConsoleInitialShipArrangement::skipUntilSecondMapRow(ifstream &inputFileStream) const
{
    while (!inputFileStream.eof())
    {
        string line;
        getline(inputFileStream, line);
        auto isWhitespace = line.find_first_not_of(' ') == line.npos;
        auto isEmpty = line == "";
        if (!isEmpty && !isWhitespace)
        {
            break;
        }
    }
}

void ConsoleInitialShipArrangement::parseLine(
    ShipCells &shipCells, const std::string &line, uint8_t rowIndex) const
{
    auto charCountInOneMapRow = Constants::MAP_SIZE * 2 + 2;
    for (uint8_t verIndex = 2; verIndex < charCountInOneMapRow; verIndex += 2)
    {
        auto symbol = line.substr(verIndex, 2);
        uint8_t colIndex = (verIndex - 2) / 2;
        if (symbol == CARRIER_SYMBOL)
        {
            shipCells.carrierCells.push_back(Cell(rowIndex, colIndex));
        }
        if (symbol == BATTLESHIP_SYMBOL)
        {
            shipCells.battleshipCells.push_back(Cell(rowIndex, colIndex));
        }
        if (symbol == CRUISER_SYMBOL)
        {
            shipCells.cruiserCells.push_back(Cell(rowIndex, colIndex));
        }
        if (symbol == SUBMARINE_SYMBOL)
        {
            shipCells.submarineCells.push_back(Cell(rowIndex, colIndex));
        }
        if (symbol == DESTROYER_SYMBOL)
        {
            shipCells.destroyerCells.push_back(Cell(rowIndex, colIndex));
        }
    }
}

Ships ConsoleInitialShipArrangement::createShipsFromCells(const ShipCells &shipCells) const
{
    auto ships = Ships{
        .carrier = createShipFromCells(shipCells.carrierCells),
        .battleship = createShipFromCells(shipCells.battleshipCells),
        .cruiser = createShipFromCells(shipCells.cruiserCells),
        .submarine = createShipFromCells(shipCells.submarineCells),
        .destroyer = createShipFromCells(shipCells.destroyerCells)};
    return ships;
}

Ship ConsoleInitialShipArrangement::createShipFromCells(const std::vector<Cell> &cells) const
{
    auto position =
        cells[0].horCoord == cells[1].horCoord
            ? Position::Horizontal
            : Position::Vertical;

    auto axisCoord = position == Position::Horizontal
                         ? cells[0].horCoord
                         : cells[0].verCoord;
    unordered_set<uint8_t> coordinates = {};
    for (const auto &cell : cells)
    {
        coordinates.insert(position == Position::Horizontal ? cell.verCoord : cell.horCoord);
    }
    return Ship(position, axisCoord, coordinates);
}
