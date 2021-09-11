#ifndef BATTLESHIP_SRC_STATISTICS_INCLUDE_ISTATISTICS_SERVICE_H
#define BATTLESHIP_SRC_STATISTICS_INCLUDE_ISTATISTICS_SERVICE_H

#include <vector>
#include <cstdint>
#include "player.h"

class IStatisticsService
{
public:
    virtual void updatePlayerStats(const std::string& nickname, bool isGameWon) const = 0;
    virtual std::vector<Player> getTopBestPlayers(uint32_t t_count) const = 0;
    virtual std::vector<Player> getTopWorstPlayers(uint32_t t_count) const = 0;
};

#endif
