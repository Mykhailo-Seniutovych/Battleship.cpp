#ifndef BATTLESHIP_SRC_STATISTICS_INCLUDE_PLAYER_H
#define BATTLESHIP_SRC_STATISTICS_INCLUDE_PLAYER_H
#include <cstdint>
#include <string>

struct Player
{
    std::string nickname;
    uint32_t gamesWon;
    uint32_t gamesLost;

    int32_t getScore() const;

    bool operator<(const Player &otherPlayer) const;
    bool operator>(const Player &otherPlayer) const;

};

#endif
