#include "statistics-service.h"
#include <algorithm>
#include <filesystem>

#include "queries.h"
#include "utils/record-readers.h"

using namespace std;
using namespace std::filesystem;

StatisticsService::StatisticsService(std::unique_ptr<IDatabaseService<Player>> t_databaseService)
    : m_databaseService(move(t_databaseService)) {}

void StatisticsService::updatePlayerStats(const std::string &nickname, bool isGameWon) const
{
    auto playerRecord = m_databaseService->readSingle(
        Queries::SELECT_PLAYER,
        RecordReaders::playerReader(),
        Queries::selectPlayerBinder(nickname.c_str()));

    if (playerRecord.isFoundInDb)
    {
        playerRecord.entity.gamesWon += isGameWon ? 1 : 0;
        playerRecord.entity.gamesLost += isGameWon ? 0 : 1;

        m_databaseService->executeCommand(
            Queries::UPDATE_PLAYER_STATS,
            Queries::updatePlayerStatsBinder(
                playerRecord.entity.nickname.c_str(),
                playerRecord.entity.gamesWon,
                playerRecord.entity.gamesLost));
    }
    else
    {
        auto gamesWon = isGameWon ? 1 : 0;
        auto gamesLost = isGameWon ? 0 : 1;
        m_databaseService->executeCommand(
            Queries::INSERT_PLAYER,
            Queries::insertPlayerBinder(nickname.c_str(), gamesWon, gamesLost));
    }
}

vector<Player> StatisticsService::getTopBestPlayers(uint32_t t_count) const
{
    auto players = m_databaseService->readCollection(
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
    auto players = m_databaseService->readCollection(
        Queries::SELECT_PLAYERS, RecordReaders::playerReader());

    sort(players.begin(), players.end());

    if (players.size() > t_count)
    {
        players.resize(t_count);
    }
    return players;
};
