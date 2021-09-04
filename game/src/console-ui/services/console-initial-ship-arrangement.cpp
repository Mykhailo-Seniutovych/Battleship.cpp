#include "console-initial-ship-arrangement.h"

Ships ConsoleInitialShipArrangement::getInitialShipArrangement() const
{
    // TODO: replace mocked implementation with reading from file
    auto ships = Ships();
    ships.carrier = Ship(Position::Horizontal, 1, {1, 2, 3, 4, 5, 6});
    ships.battleship = Ship(Position::Vertical, 7, {1, 2, 3, 5});
    ships.cruiser = Ship(Position::Horizontal, 8, {3, 4, 5});
    ships.submarine = Ship(Position::Vertical, 9, {7, 8, 9});
    ships.destroyer = Ship(Position::Vertical, 2, {4, 5});
    return ships;
};
