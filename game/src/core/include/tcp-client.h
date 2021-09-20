#ifndef BATTLESHIP_SRC_CORE_INCLUDE_TCP_CLIENT_H
#define BATTLESHIP_SRC_CORE_INCLUDE_TCP_CLIENT_H

#include <string>
#include <cstdint>
#include "itcp-client.h"

class TcpClient : public ITcpClient
{
public:
    void establishConnection(const std::string &t_connectionInfo) override;
    std::string readNextMessage() override;
    void sendMessage(const std::string &t_message) override;
    void closeConnection() override;

private:
    int32_t m_socketDescriptor;
    bool m_isSocketEstablished = false;

    int32_t readMessageLength();
    std::string readMessageContent(int32_t t_messageLength);

    void sendMessageLength(int32_t t_length);
    void sendMessageContent(const std::string &message);
    void throwError();
};
#endif
