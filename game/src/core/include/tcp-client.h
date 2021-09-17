#ifndef BATTLESHIP_SRC_CORE_INCLUDE_TCP_CLIENT_H
#define BATTLESHIP_SRC_CORE_INCLUDE_TCP_CLIENT_H

#include "itcp-client.h"
#include <cstdint>

class TcpClient : public ITcpClient
{
public:
    void establishConnection(const std::string &connectionInfo) override;
    std::string readNextMessage() override;
    void sendMessage(const std::string &t_message) override;

private:
    int32_t m_socketDescriptor;
    bool m_isSocketEstablished = false;
};
#endif
