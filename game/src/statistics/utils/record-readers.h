#ifndef BATTLESHIP_SRC_STATISTICS_UTILS_RECORD_READERS_H
#define BATTLESHIP_SRC_STATISTICS_UTILS_RECORD_READERS_H

#include <functional>
#include "player.h"
#include "sqlite3.h"

class RecordReaders
{
public:
    typedef std::function<const Player(sqlite3_stmt *)> playerReaderFunc;

    static playerReaderFunc playerReader();
};

#endif
