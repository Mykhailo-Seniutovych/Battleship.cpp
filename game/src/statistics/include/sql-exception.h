#ifndef BATTLESHIP_SRC_STATISTICS_INCLUDE_SQL_EXCEPTION_H
#define BATTLESHIP_SRC_STATISTICS_INCLUDE_SQL_EXCEPTION_H
#include <exception>
#include <string>

class SqlException : public std::exception
{
public:
    SqlException(const std::string &t_message);
    const char *what() const noexcept override;

private:
    std::string m_message;
};

#endif
