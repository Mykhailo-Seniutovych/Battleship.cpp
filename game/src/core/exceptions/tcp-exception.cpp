#include "tcp-exception.h"

using namespace std;

TcpException::TcpException(const string &t_message) : m_message(t_message) {}
const char *TcpException::what() const noexcept
{
    return m_message.c_str();
}