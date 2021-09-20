#ifndef BATTLESHIP_SRC_CORE_INCLUDE_ITCP_CLIENT_H
#define BATTLESHIP_SRC_CORE_INCLUDE_ITCP_CLIENT_H

#include <string>

class ITcpClient
{
public:
    virtual void establishConnection(const std::string &connectionInfo) = 0;
    virtual std::string readNextMessage() = 0;
    virtual void sendMessage(const std::string &t_message) = 0;
    virtual void closeConnection() = 0;
};

#endif
