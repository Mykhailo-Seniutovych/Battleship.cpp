#ifndef BATTLESHIP_SRC_CORE_INCLUDE_TCP_CLIENT_H
#define BATTLESHIP_SRC_CORE_INCLUDE_TCP_CLIENT_H

#include <string>
#include <cstdint>
#include <memory>
#include "itcp-client.h"
#include "iapp-config.h"

class TcpClient : public ITcpClient
{
public:
    TcpClient(std::shared_ptr<IAppConfig> t_appConfig);

    void establishConnection(const std::string &t_incomingConnection) override;
    std::string readNextMessage() override;
    void sendMessage(const std::string &t_message) override;
    void shutdownConnection() override;

private:
    const std::string CONNECTION_LOST_MSG = "Network connection with another player was lost.";

    uint64_t m_socketDescriptor;
    bool m_isSocketEstablished = false;
    std::shared_ptr<IAppConfig> m_appConfig;

    int32_t readMessageLength();
    std::string readMessageContent(int32_t t_messageLength);

    void sendMessageLength(int32_t t_length);
    void sendMessageContent(const std::string &message);
    void throwConnectionLostError();
    void throwError();
};
#endif
