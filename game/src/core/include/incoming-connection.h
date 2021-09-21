#ifndef BATTLESHIP_SRC_CORE_INCLUDE_INCOMING_CONNECTION_H
#define BATTLESHIP_SRC_CORE_INCLUDE_INCOMING_CONNECTION_H

#include <string>


struct IncomingConnection
{
    std::string playerNickname;
    std::string opponentNickname;
    std::string passcode;
};

#endif
