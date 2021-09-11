#ifndef BATTLESHIP_SRC_CONSOLE_UI_UI_STATISTICS_UI_H
#define BATTLESHIP_SRC_CONSOLE_UI_UI_STATISTICS_UI_H

#include <memory>
#include <cstdint>
#include <vector>
#include "interfaces/istatistics-ui.h"
#include "istatistics-service.h"
#include "player.h"

class StatisticsUi : public IStatisticsUi
{
public:
    StatisticsUi(std::unique_ptr<IStatisticsService> t_statisticsService);
    void showBestPlayers() const override;
    void showWorstPlayers() const override;

private:
    const uint32_t PLAYERS_COUNT = 10;
    std::unique_ptr<IStatisticsService> m_statisticsService;

    void displayPlayers(const std::vector<Player> &players) const;
};

#endif
