#ifndef BATTLESHIP_SRC_CORE_INCLUDE_TCP_EXCEPTION_H
#define BATTLESHIP_SRC_CORE_INCLUDE_TCP_EXCEPTION_H

#include <exception>
#include <string>

class TcpException : public std::exception
{
public:
    TcpException(const std::string &t_message);
    const char *what() const noexcept override;

private:
    std::string m_message;
};

#endif
