#include "invalid-input-exception.h"

InvalidInputException::InvalidInputException(const std::string &t_message) : m_message(t_message) {}
const char *InvalidInputException::what() const noexcept
{
    return m_message.c_str();
}