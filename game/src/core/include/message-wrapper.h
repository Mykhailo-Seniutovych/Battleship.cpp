#ifndef BATTLESHIP_SRC_CORE_INCLUDE_MESSAGE_WRAPPER_H
#define BATTLESHIP_SRC_CORE_INCLUDE_MESSAGE_WRAPPER_H

#include <string>

template <typename T>
struct MessageWrapper
{
    bool isError;
    std::string error;
    T message;

    MessageWrapper() = default;
    
    MessageWrapper(T t_message) : isError(false), message(t_message)
    {
    }

    MessageWrapper(const std::string &t_error) : error(t_error)
    {
    }
};

#endif
