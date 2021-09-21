#ifndef BATTLESHIP_SRC_CORE_INCLUDE_COMMUNICATION_EXCEPTION_H
#define BATTLESHIP_SRC_CORE_INCLUDE_COMMUNICATION_EXCEPTION_H

#include <exception>
#include <string>

class CommunicationException : public std::exception
{
public:
    CommunicationException(const std::string &t_message);
    const char *what() const noexcept override;

private:
    std::string m_message;
};

#endif
