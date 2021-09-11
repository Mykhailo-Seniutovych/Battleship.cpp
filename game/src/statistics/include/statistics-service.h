#ifndef BATTLESHIP_SRC_STATISTICS_INCLUDE_STATISTICS_SERVICE_H
#define BATTLESHIP_SRC_STATISTICS_INCLUDE_STATISTICS_SERVICE_H

#include <memory>
#include <string>
#include "istatistics-service.h"
#include "idatabase-service.h"

class StatisticsService : public IStatisticsService
{
public:
    StatisticsService(std::unique_ptr<IDatabaseService<Player>> t_databaseService);

    void updatePlayerStats(const std::string &nickname, bool isGameWon) const override;
    std::vector<Player> getTopBestPlayers(uint32_t t_count) const override;
    std::vector<Player> getTopWorstPlayers(uint32_t t_count) const override;

private:
    std::unique_ptr<IDatabaseService<Player>> m_databaseService;
};

#endif
