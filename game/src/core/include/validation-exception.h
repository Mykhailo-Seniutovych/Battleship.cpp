#ifndef BATTLESHIP_SRC_CORE_INCLUDE_VALIDATION_EXCEPTION_H
#define BATTLESHIP_SRC_CORE_INCLUDE_VALIDATION_EXCEPTION_H
#include <exception>
#include <string>

class ValidationException : public std::exception
{
public:
    ValidationException(const std::string &t_message);
    const char *what() const noexcept override;

private:
    std::string m_message;
};

#endif
