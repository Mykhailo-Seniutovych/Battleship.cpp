#include "invalid-config-exception.h"
using namespace std;

InvalidConfigException::InvalidConfigException(const string &t_message) : m_message(t_message) {}
const char *InvalidConfigException::what() const noexcept
{
    return m_message.c_str();
}