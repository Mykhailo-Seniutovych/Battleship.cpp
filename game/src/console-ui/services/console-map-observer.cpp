#include <iostream>
#include "console-map-observer.h"
using namespace std;

ConsoleMapObserver::ConsoleMapObserver(std::unique_ptr<IMaps> t_maps)
    : m_maps(std::move(t_maps)){};

void ConsoleMapObserver::notifyShipsInitialized(const Ships &ships) const
{
    cout << "Connection established successfully." << endl
         << endl;
    m_maps.get()->initMaps(
        ships.carrier.getCoordinates(),
        ships.battleship.getCoordinates(),
        ships.cruiser.getCoordinates(),
        ships.submarine.getCoordinates(),
        ships.destroyer.getCoordinates());
    m_maps.get()->printMaps();
}

void ConsoleMapObserver::notifyMyMapUpdated(const MapUpdateData &updateData) const
{
    m_maps.get()->printMyShotCell(updateData.cell);
    m_maps.get()->updateMyMap(updateData);
    m_maps.get()->printMaps();
}

void ConsoleMapObserver::notifyEnemyMapUpdated(const MapUpdateData &updateData) const
{
    m_maps.get()->updateEnemyMap(updateData);
    m_maps.get()->printMaps();
}

void ConsoleMapObserver::notifyGameOver(bool t_currentPlayerWon) const
{
    auto message = t_currentPlayerWon
                       ? "  Game Over. Congradulations, you won!"
                       : "  Game Over. You lost :(";
    auto separator = "-----------------------------------------";

    cout << separator << endl
         << endl;
    cout << message << endl;
    cout << endl
         << separator << endl;
}
