#include <iostream>
#include <iomanip>
#include <exception>
#include <cstdint>
#include "statistics-ui.h"

using namespace std;

StatisticsUi::StatisticsUi(unique_ptr<IStatisticsService> t_statisticsService)
    : m_statisticsService(move(t_statisticsService))
{
}

void StatisticsUi::showBestPlayers() const
{
    auto players = m_statisticsService.get()->getTopBestPlayers(PLAYERS_COUNT);
    displayPlayers(players);
}

void StatisticsUi::showWorstPlayers() const
{
    auto players = m_statisticsService.get()->getTopWorstPlayers(PLAYERS_COUNT);
    displayPlayers(players);
}

void StatisticsUi::displayPlayers(const std::vector<Player> &players) const
{
    cout << left
         << setw(20) << "Nickname"
         << setw(11) << "Games Won"
         << setw(12) << "Games Lost"
         << setw(6) << "Score"
         << endl;
    for (auto player : players)
    {
        cout << left
             << setw(20) << player.nickname
             << setw(11) << player.gamesWon
             << setw(12) << player.gamesLost
             << setw(6) << player.getScore()
             << endl;
    };
    cout << endl;
}