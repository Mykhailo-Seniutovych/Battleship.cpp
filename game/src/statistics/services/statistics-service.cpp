#include "statistics-service.h"
#include <algorithm>

#include "../utils/queries.h"
#include "../utils/record-readers.h"

using namespace std;

StatisticsService::StatisticsService(std::unique_ptr<IDatabaseService<Player>> t_databaseService)
    : m_databaseService(move(t_databaseService)) {}

void StatisticsService::updatePlayerStats(std::string nickname, bool isGameWon) const
{
    auto player = m_databaseService.get()->readSingle(
        Queries::SELECT_PLAYER,
        RecordReaders::playerReader(),
        Queries::selectPlayerBinder(nickname.c_str()));

    player.gamesWon += isGameWon ? 1 : 0;
    player.gamesLost += isGameWon ? 0 : 1;

    m_databaseService.get()->executeCommand(
        Queries::UPDATE_PLAYER_STATS, 
        Queries::updatePlayerStatsBinder(player.nickname.c_str(), player.gamesWon, player.gamesLost));
}

vector<Player> StatisticsService::getTopBestPlayers(uint32_t t_count) const
{
    auto players = m_databaseService.get()->readCollection(
        Queries::SELECT_PLAYERS, RecordReaders::playerReader());

    sort(players.begin(), players.end(), std::greater<Player>());

    if (players.size() > t_count)
    {
        players.resize(t_count);
    }
    return players;
};

vector<Player> StatisticsService::getTopWorstPlayers(uint32_t t_count) const
{
    auto players = m_databaseService.get()->readCollection(
        Queries::SELECT_PLAYERS, RecordReaders::playerReader());

    sort(players.begin(), players.end());

    if (players.size() > t_count)
    {
        players.resize(t_count);
    }
    return players;
};
