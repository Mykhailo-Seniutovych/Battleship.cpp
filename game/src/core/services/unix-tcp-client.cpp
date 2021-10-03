#ifdef __unix

#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <algorithm>
#include <string>
#include <fcntl.h>
#include "tcp-client.h"
#include "tcp-exception.h"
#include "utils/endian-checker.h"

using namespace std;

TcpClient::TcpClient(std::shared_ptr<IAppConfig> t_appConfig) : m_appConfig(t_appConfig) {}

void TcpClient::establishConnection(const std::string &t_incomingConnection)
{
    if (!m_isSocketEstablished)
    {
        auto socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (socketDescriptor < 0)
        {
            throwError();
        }
        auto address = m_appConfig->getServerAddres();
        auto port = m_appConfig->getServerPort();

        sockaddr_in servAddr;
        servAddr.sin_family = AF_INET;
        servAddr.sin_port = htons(port);

        if (inet_pton(AF_INET, address.c_str(), &servAddr.sin_addr) <= 0)
        {
            throwError();
        }

        auto connectResult = connect(
            socketDescriptor,
            reinterpret_cast<sockaddr *>(&servAddr),
            sizeof(servAddr));

        if (connectResult < 0)
        {
            throwError();
        }

        m_socketDescriptor = socketDescriptor;
        m_isSocketEstablished = true;

        sendMessage(t_incomingConnection);
    }
}

string TcpClient::readNextMessage()
{
    auto messageLength = readMessageLength();
    auto message = readMessageContent(messageLength);
    return message;
}

void TcpClient::sendMessage(const string &message)
{
    sendMessageLength(message.length());
    sendMessageContent(message);
}

int32_t TcpClient::readMessageLength()
{
    char buffer[sizeof(int32_t)];
    auto bytesReadCount = read(m_socketDescriptor, buffer, sizeof(buffer));
    if (bytesReadCount == 0)
    {
        throwConnectionLostError();
    }

    if (bytesReadCount < 0)
    {
        throwError();
    }

    if (!EndianChecker::isCurrentSystemBigEndian())
    {
        reverse(buffer, buffer + sizeof(buffer));
    }
    int32_t messageLength;
    memcpy(&messageLength, buffer, sizeof(int32_t));
    return messageLength;
}

string TcpClient::readMessageContent(int32_t t_messageLength)
{
    auto buffer = make_unique<char[]>(t_messageLength);
    auto bytesReadCount = read(m_socketDescriptor, buffer.get(), t_messageLength);
    if (bytesReadCount == 0)
    {
        throwConnectionLostError();
    }
    if (bytesReadCount < 0)
    {
        throwError();
    }

    return string(buffer.get()).substr(0, t_messageLength);
}

void TcpClient::sendMessageLength(int32_t t_length)
{
    char buffer[sizeof(int32_t)];
    memcpy(buffer, &t_length, sizeof(int32_t));

    if (!EndianChecker::isCurrentSystemBigEndian())
    {
        reverse(buffer, buffer + sizeof(buffer));
    }

    auto bytesWrittenCount = send(m_socketDescriptor, buffer, sizeof(int32_t), 0);
    if (bytesWrittenCount < 0)
    {
        throwError();
    }
}

void TcpClient::sendMessageContent(const string &message)
{
    auto bytesWrittenCount = send(m_socketDescriptor, message.c_str(), message.length(), 0);
    if (bytesWrittenCount < 0)
    {
        throwError();
    }
}

void TcpClient::throwError()
{
    close(m_socketDescriptor);
    m_isSocketEstablished = false;
    throw TcpException(string(strerror(errno)));
}

void TcpClient::throwConnectionLostError()
{
    close(m_socketDescriptor);
    m_isSocketEstablished = false;
    throw TcpException(CONNECTION_LOST_MSG);
}

void TcpClient::shutdownConnection()
{
    if (m_isSocketEstablished)
    {
        shutdown(m_socketDescriptor, SHUT_RDWR);
    }
}

#endif
