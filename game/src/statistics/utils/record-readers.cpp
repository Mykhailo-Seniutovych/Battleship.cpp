#include <string>
#include "record-readers.h"
#include "player.h"

using namespace std;

RecordReaders::playerReaderFunc RecordReaders::playerReader()
{
    return [](sqlite3_stmt *t_statement)
    {
        auto player = Player();
        player.nickname = string(reinterpret_cast<const char*>(sqlite3_column_text(t_statement, 0)));
        player.gamesWon = sqlite3_column_int(t_statement, 1);
        player.gamesLost = sqlite3_column_int(t_statement, 2);
        return player;
    };
}