#ifndef BATTLESHIP_SRC_CORE_INCLUDE_INCOMING_CONNECTION_H
#define BATTLESHIP_SRC_CORE_INCLUDE_INCOMING_CONNECTION_H

#include <string>


struct IncomingConnection
{
    std::string playerNickname;
    std::string opponentNickname;

    // TODO: Provide better storage of a passcode than directly in source code, that is publicly available on GitHub.
    std::string passcode = "cG!GA{{Y2G;A'C`[,&nPoYTf6yg&FFPkj!`EqoLB0r{lvxKdOE";
};

#endif
