#include "communication-exception.h"

using namespace std;

CommunicationException::CommunicationException(const string &t_message) : m_message(t_message) {}
const char *CommunicationException::what() const noexcept
{
    return m_message.c_str();
}