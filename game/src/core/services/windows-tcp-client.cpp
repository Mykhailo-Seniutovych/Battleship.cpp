#ifdef _WIN32

#include <memory>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <string>
#include <iostream>
#include "tcp-exception.h"
#include "utils/endian-checker.h"
#include "tcp-client.h"

#pragma comment(lib, "ws2_32.lib")

using namespace std;

uint64_t g_currentServerSocketDescriptor;

static string getSocketErrorMessage(int t_errorCode);
static BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType);

TcpClient::TcpClient(std::shared_ptr<IAppConfig> t_appConfig) : m_appConfig(t_appConfig) {}

void TcpClient::establishConnection(const std::string &t_incomingConnection)
{
    if(!m_isSocketEstablished)
    {
        WSADATA wsaData;
        int startupResult;

        auto version = MAKEWORD(2, 2);
        startupResult = WSAStartup(version, &wsaData);
        if (startupResult != 0) {
            auto errorMsg = getSocketErrorMessage(startupResult);
            throw TcpException(errorMsg);
        }

        auto address = m_appConfig.get()->getServerAddres();
        auto port = m_appConfig.get()->getServerPort();

        sockaddr_in addrInfo;
        addrInfo.sin_family = AF_INET;
        addrInfo.sin_port = htons(port);
        inet_pton(AF_INET, address.c_str(), &addrInfo.sin_addr);

        SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock == INVALID_SOCKET)
        {
            WSACleanup();
            throwError();
        }

        auto connectResult = connect(sock, (sockaddr*)&addrInfo, sizeof(addrInfo));
        if (connectResult == SOCKET_ERROR)
        {
            closesocket(sock);
            WSACleanup();
            throwError();
        }

        g_currentServerSocketDescriptor = sock;
        m_socketDescriptor = sock;
        m_isSocketEstablished = true;

        SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE);

        sendMessage(t_incomingConnection);
    }
}

string TcpClient::readNextMessage()
{
    auto messageLength = readMessageLength();
    auto message = readMessageContent(messageLength);
    return message;
    return "";
}

void TcpClient::sendMessage(const string &message)
{
    sendMessageLength(message.length());
    sendMessageContent(message);
}

int32_t TcpClient::readMessageLength()
{
    char buffer[sizeof(int32_t)];
    auto bytesReadCount = recv(m_socketDescriptor, buffer, sizeof(buffer), 0);
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
    auto bytesReadCount = recv(m_socketDescriptor, buffer.get(), t_messageLength, 0);
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
    if (bytesWrittenCount == SOCKET_ERROR)
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
    auto errorCode = WSAGetLastError();
    if (m_isSocketEstablished) 
    {
        closesocket(m_socketDescriptor);
        WSACleanup();
        m_isSocketEstablished = false;
    }

    auto errorMsg = getSocketErrorMessage(errorCode);
    throw TcpException(errorMsg);
}

void TcpClient::throwConnectionLostError()
{
   if (m_isSocketEstablished)
   {
       closesocket(m_socketDescriptor);
       WSACleanup();
       m_isSocketEstablished = false;
   }

   throw TcpException(CONNECTION_LOST_MSG);
}


void TcpClient::shutdownConnection()
{
    auto shutdownResult = shutdown(m_socketDescriptor, SD_SEND);

    if (shutdownResult == SOCKET_ERROR) 
    {
        closesocket(m_socketDescriptor);
        WSACleanup();
    }
    else 
    {
        // need to call recv again to make sure the other side gracefully closed the socket
        uint32_t defaultBufferSize = 1024;
        auto buffer = make_unique<char[]>(defaultBufferSize);
        recv(m_socketDescriptor, buffer.get(), defaultBufferSize, 0);

        closesocket(m_socketDescriptor);
        WSACleanup();
    } 
}


static string getSocketErrorMessage(int t_errorCode)
{
    wchar_t* charErrMsg;
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, t_errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&charErrMsg, 0, NULL);

    wstring wstringErrMsg(charErrMsg);
    string errorMessage(wstringErrMsg.begin(), wstringErrMsg.end());
    return errorMessage;
}

// We need to close the socket when user click CTRL+C, closes the console window, etc.
BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
    closesocket(g_currentServerSocketDescriptor);
    WSACleanup();
    return false;
}

#endif
