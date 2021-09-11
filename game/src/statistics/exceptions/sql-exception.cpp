#include "sql-exception.h"

SqlException::SqlException(const char *t_message) : m_message(t_message) {}
const char *SqlException::what() const noexcept
{
    return m_message;
}