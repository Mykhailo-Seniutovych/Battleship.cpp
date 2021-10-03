#include "statistics-observer.h"
#include <memory>
using namespace std;

StatisticsObserver::StatisticsObserver(
    std::unique_ptr<IStatisticsService> t_statisticsService,
    const string& t_currentPlayerNickname)
    : m_statisticsService(move(t_statisticsService)),
      m_currentPlayerNickname(t_currentPlayerNickname)
{
}

void StatisticsObserver::notifyShipsInitialized(const Ships &t_ships) const {}
void StatisticsObserver::notifyMyMapUpdated(const MapUpdateData &t_updateData) const {}
void StatisticsObserver::notifyEnemyMapUpdated(const MapUpdateData &t_updateData) const {}

void StatisticsObserver::notifyGameOver(bool t_currentPlayerWon) const
{
    m_statisticsService->updatePlayerStats(m_currentPlayerNickname, t_currentPlayerWon);
}