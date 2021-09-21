//#ifdef UNIX

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
        auto address = m_appConfig.get()->getServerAddres();
        auto port = m_appConfig.get()->getServerPort();

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

        sendMessage(t_incomingConnection);
        m_isSocketEstablished = true;
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
    char messageLengthBytes[sizeof(int32_t)];
    auto bytesReadCount = read(m_socketDescriptor, messageLengthBytes, sizeof(messageLengthBytes));
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
        reverse(messageLengthBytes, messageLengthBytes + sizeof(messageLengthBytes));
    }
    int32_t messageLength;
    memcpy(&messageLength, messageLengthBytes, sizeof(int32_t));
    return messageLength;
}

string TcpClient::readMessageContent(int32_t t_messageLength)
{
    char buffer[t_messageLength];
    auto bytesReadCount = read(m_socketDescriptor, buffer, t_messageLength);
    if (bytesReadCount == 0)
    {
        throwConnectionLostError();
    }
    if (bytesReadCount < 0)
    {
        throwError();
    }

    return string(buffer).substr(0, t_messageLength);
}

void TcpClient::sendMessageLength(int32_t t_length)
{
    char lengthBuffer[sizeof(int32_t)];
    memcpy(lengthBuffer, &t_length, sizeof(int32_t));

    if (!EndianChecker::isCurrentSystemBigEndian())
    {
        reverse(lengthBuffer, lengthBuffer + sizeof(lengthBuffer));
    }
    char messageLengthBytes[sizeof(int32_t)];
    auto bytesWrittenCount = send(m_socketDescriptor, lengthBuffer, sizeof(int32_t), 0);
    if (bytesWrittenCount < 0)
    {
        throwError();
    }
}

void TcpClient::sendMessageContent(const string &message)
{
    char buffer[message.length()];
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
    throw TcpException("Network connection with another player was lost.");
}

void TcpClient::shutdownConnection()
{
    if (m_isSocketEstablished)
    {
        shutdown(m_socketDescriptor, SHUT_RDWR);
    }
}

//#endif
