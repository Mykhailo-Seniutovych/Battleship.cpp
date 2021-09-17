//#ifdef UNIX

#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "tcp-client.h"
#include "tcp-exception.h"

using namespace std;

void TcpClient::establishConnection(const std::string &connectionInfo)
{
    if (!m_isSocketEstablished)
    {
        // TODO: put these values into config
        const int port = 5000;
        const string address = "127.0.0.1";

        auto socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (socketDescriptor < 0)
        {
            throw TcpException(string(strerror(errno)));
        }

        sockaddr_in servAddr;
        servAddr.sin_family = AF_INET;
        servAddr.sin_port = htons(port);

        if (inet_pton(AF_INET, address.c_str(), &servAddr.sin_addr) <= 0)
        {
            close(socketDescriptor);
            throw TcpException(string(strerror(errno)));
        }

        auto connectResult = connect(
            socketDescriptor,
            reinterpret_cast<sockaddr *>(&servAddr),
            sizeof(servAddr));

        if (connectResult < 0)
        {
            close(socketDescriptor);
            throw TcpException(string(strerror(errno)));
        }

        m_socketDescriptor = socketDescriptor;

        sendMessage(connectionInfo);
        m_isSocketEstablished = true;
    }
}

string TcpClient::readNextMessage()
{
    char buffer[1024];
    auto bytesReadCount = read(m_socketDescriptor, buffer, sizeof(buffer));
    if (bytesReadCount < 0)
    {
        m_isSocketEstablished = false;
        close(m_socketDescriptor);
        throw TcpException(string(strerror(errno)));
    }
    auto message = string(buffer).substr(0, bytesReadCount);
    return message;
}

void TcpClient::sendMessage(const string &message)
{
    char buffer[1024];
    auto bytesWrittenCount = send(m_socketDescriptor, message.c_str(), message.length(), 0);
    if (bytesWrittenCount < 0)
    {
        m_isSocketEstablished = false;
        close(m_socketDescriptor);
        throw TcpException(string(strerror(errno)));
    }
}
//#endif
