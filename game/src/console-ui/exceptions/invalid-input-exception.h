#ifndef BATTLESHIP_SRC_CONSOLE_UI_EXCEPTIONS_INVALID_INPUT_EXCEPTION_H
#define BATTLESHIP_SRC_CONSOLE_UI_EXCEPTIONS_INVALID_INPUT_EXCEPTION_H

#include <string>
#include <exception>

class InvalidInputException : public std::exception
{
public:
    InvalidInputException(const std::string &t_message);
    const char *what() const noexcept override;

private:
    std::string m_message;
};

#endif
