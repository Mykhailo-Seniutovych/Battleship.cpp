#include "sql-exception.h"
using namespace std;

SqlException::SqlException(const string &t_message) : m_message(t_message) {}
const char *SqlException::what() const noexcept
{
    return m_message.c_str();
}