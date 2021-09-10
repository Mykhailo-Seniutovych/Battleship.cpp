#ifndef BATTLESHIP_SRC_STATISTICS_UTILS_QUERIES_H
#define BATTLESHIP_SRC_STATISTICS_UTILS_QUERIES_H
#include <functional>
#include <cstdint>
#include "sqlite3.h"

struct Queries
{
    typedef std::function<const void(sqlite3_stmt *)> paramsBinderFunc;

    static const char *CREATE_PLAYER_TABLE;
    static const char *SELECT_PLAYERS;

    static const char *SELECT_PLAYER;
    static paramsBinderFunc selectPlayerBinder(const char *nickname);

    static const char *INSERT_PLAYER;
    static paramsBinderFunc insertPlayerBinder(const char *nickname, uint32_t gamesWon, uint32_t gamesLost);

    static const char *UPDATE_PLAYER_STATS;
    static paramsBinderFunc updatePlayerStatsBinder(const char *nickname, uint32_t gamesWon, uint32_t gamesLost);
};

#endif
