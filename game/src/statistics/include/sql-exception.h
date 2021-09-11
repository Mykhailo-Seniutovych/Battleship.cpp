#ifndef BATTLESHIP_SRC_STATISTICS_INCLUDE_SQL_EXCEPTION_H
#define BATTLESHIP_SRC_STATISTICS_INCLUDE_SQL_EXCEPTION_H
#include <exception>

class SqlException : public std::exception
{
public:
    SqlException(const char *message);
    const char *what() const noexcept override;

private:
    const char *m_message;
};

#endif
