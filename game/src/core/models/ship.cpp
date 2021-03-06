#include <vector>
#include "ship.h"
#include "position.h"
#include "cell.h"
using namespace std;

Ship::Ship() = default;

Ship::Ship(
    const Position &t_position, uint8_t t_axisCoordinate, const unordered_set<uint8_t> &t_cellsCoordinates)
    : m_position(t_position),
      m_axisCoordinate(t_axisCoordinate),
      m_intactCellsCoordinates(t_cellsCoordinates) {}

bool Ship::tryReceiveShot(const Cell &cell)
{
    bool shotReceived = false;
    if (m_position == Position::Horizontal && m_axisCoordinate == cell.horCoord)
    {
        shotReceived = tryMoveToDamagedCells(cell.verCoord);
    }
    else if (m_position == Position::Vertical && m_axisCoordinate == cell.verCoord)
    {
        shotReceived = tryMoveToDamagedCells(cell.horCoord);
    }

    return shotReceived;
}

ShipCoordinates Ship::getCoordinates() const
{
    unordered_set<uint8_t> cellsCoordinates = {};
    cellsCoordinates.insert(m_intactCellsCoordinates.begin(), m_intactCellsCoordinates.end());
    cellsCoordinates.insert(m_damagedCellsCoordinates.begin(), m_damagedCellsCoordinates.end());

    ShipCoordinates result(m_position, m_axisCoordinate, cellsCoordinates);
    return result;
}

unordered_set<Cell, Cell::HashFunction> Ship::getShipCells() const
{
    auto cells = unordered_set<Cell, Cell::HashFunction>();
    if (m_position == Position::Horizontal)
    {
        for (auto coord : m_intactCellsCoordinates)
        {
            cells.insert(Cell(m_axisCoordinate, coord));
        }
        for (auto coord : m_damagedCellsCoordinates)
        {
            cells.insert(Cell(m_axisCoordinate, coord));
        }
    }
    else
    {
        for (auto coord : m_intactCellsCoordinates)
        {
            cells.insert(Cell(coord, m_axisCoordinate));
        }
        for (auto coord : m_damagedCellsCoordinates)
        {
            cells.insert(Cell(coord, m_axisCoordinate));
        }
    }
    return cells;
}

bool Ship::tryMoveToDamagedCells(uint8_t t_cellCoordinate)
{
    if (m_damagedCellsCoordinates.count(t_cellCoordinate))
    {
        return true;
    }

    auto cellsErasedCount = m_intactCellsCoordinates.erase(t_cellCoordinate);
    auto wasCellRemoved = cellsErasedCount != 0;
    if (cellsErasedCount != 0)
    {
        m_damagedCellsCoordinates.insert(t_cellCoordinate);
    }
    return wasCellRemoved;
}

bool Ship::isShipSunk() const
{
    return m_intactCellsCoordinates.empty();
}