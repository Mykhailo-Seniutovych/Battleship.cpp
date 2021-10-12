#include <iostream>
#include "console-map-observer.h"

using namespace std;

static void clearConsole()
{
#ifdef __unix
    printf("\033c");
#elif defined _WIN32
    system("cls");
#endif
}
ConsoleMapObserver::ConsoleMapObserver(std::unique_ptr<IMaps> t_maps)
    : m_maps(std::move(t_maps)){};

void ConsoleMapObserver::notifyShipsInitialized(const Ships &ships) const
{
    cout << "Connection established successfully." << endl
         << endl;
    m_maps->initMaps(
        ships.battleship.getCoordinates(),
        ships.cruiser1.getCoordinates(),
        ships.cruiser2.getCoordinates(),
        ships.destroyer1.getCoordinates(),
        ships.destroyer2.getCoordinates(),
        ships.destroyer3.getCoordinates(),
        ships.submarine1.getCoordinates(),
        ships.submarine2.getCoordinates(),
        ships.submarine3.getCoordinates(),
        ships.submarine4.getCoordinates());
    m_maps->printMaps();
}

void ConsoleMapObserver::notifyMyMapUpdated(const MapUpdateData &updateData) const
{
    clearConsole();

    m_maps->printMyShotCell(updateData.cell);
    m_maps->updateMyMap(updateData);
    m_maps->printMaps();
}

void ConsoleMapObserver::notifyEnemyMapUpdated(const MapUpdateData &updateData) const
{
    clearConsole();

    m_maps->updateEnemyMap(updateData);
    m_maps->printMaps();
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
