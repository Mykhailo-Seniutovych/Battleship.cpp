#include "queries.h"

const char *Queries::CREATE_PLAYER_TABLE =
    "create table if not exists Player (Nickname text primary key unique, GamesWon int, GamesLost int)";
const char *Queries::SELECT_PLAYERS = "select Nickname, GamesWon, GamesLost from Player";

const char *Queries::SELECT_PLAYER = "select Nickname, GamesWon, GamesLost from Player where Nickname = ?";
Queries::paramsBinderFunc Queries::selectPlayerBinder(const char *nickname)
{
    return [nickname](sqlite3_stmt *t_statement)
    {
        sqlite3_bind_text(t_statement, 1, nickname, -1, nullptr);
    };
}

const char *Queries::INSERT_PLAYER = "insert into Player (Nickname, GamesWon, GamesLost) values (?,?,?)";
Queries::paramsBinderFunc Queries::insertPlayerBinder(
    const char *nickname, uint32_t gamesWon, uint32_t gamesLost)
{
    return [nickname, gamesWon, gamesLost](sqlite3_stmt *t_statement)
    {
        sqlite3_bind_text(t_statement, 1, nickname, -1, nullptr);
        sqlite3_bind_int(t_statement, 2, gamesWon);
        sqlite3_bind_int(t_statement, 3, gamesLost);
    };
}

const char *Queries::UPDATE_PLAYER_STATS = "update Player set GamesWon = ?, GamesLost = ? where Nickname = ?";
Queries::paramsBinderFunc Queries::updatePlayerStatsBinder(
    const char *nickname, uint32_t gamesWon, uint32_t gamesLost)
{
    return [nickname, gamesWon, gamesLost](sqlite3_stmt *t_statement)
    {
        sqlite3_bind_int(t_statement, 1, gamesWon);
        sqlite3_bind_int(t_statement, 2, gamesLost);
        sqlite3_bind_text(t_statement, 3, nickname, -1, nullptr);
    };
}
