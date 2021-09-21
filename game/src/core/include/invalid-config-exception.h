#ifndef BATTLESHIP_SRC_CORE_INCLUDE_INVALID_CONFIG_EXCEPTION_H
#define BATTLESHIP_SRC_CORE_INCLUDE_INVALID_CONFIG_EXCEPTION_H

#include <exception>
#include <string>

class InvalidConfigException : public std::exception
{
public:
    InvalidConfigException(const std::string &t_message);
    const char *what() const noexcept override;

private:
    std::string m_message;
};

#endif
