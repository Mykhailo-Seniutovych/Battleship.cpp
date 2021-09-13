#include "validation-exception.h"
using namespace std;

ValidationException::ValidationException(const string &t_message) : m_message(t_message) {}
const char *ValidationException::what() const noexcept
{
    return m_message.c_str();
}