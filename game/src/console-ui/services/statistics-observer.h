#ifndef BATTLESHIP_SRC_CONSOLE_UI_SERVICES_STATISTICS_OBSERVER_H
#define BATTLESHIP_SRC_CONSOLE_UI_SERVICES_STATISTICS_OBSERVER_H

#include <memory>
#include <string>

#include "ibattle-observer.h"
#include "istatistics-service.h"

class StatisticsObserver : public IBattleObserver
{
public:
    StatisticsObserver(
        std::unique_ptr<IStatisticsService> t_statisticsService, 
        const std::string &t_currentPlayerNickname);
    void notifyShipsInitialized(const Ships &t_ships) const override;
    void notifyMyMapUpdated(const MapUpdateData &t_updateData) const override;
    void notifyEnemyMapUpdated(const MapUpdateData &t_updateData) const override;
    void notifyGameOver(bool t_currentPlayerWon) const override;

private:
    std::unique_ptr<IStatisticsService> m_statisticsService;
    std::string m_currentPlayerNickname;
};

#endif
