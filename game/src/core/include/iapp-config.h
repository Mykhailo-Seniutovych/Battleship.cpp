#ifndef BATTLESHIP_SRC_CORE_INCLUDE_IAPP_CONFIG_H
#define BATTLESHIP_SRC_CORE_INCLUDE_IAPP_CONFIG_H

#include <string>
#include <cstdint>

class IAppConfig
{
public:
    virtual std::string getServerAddres() const = 0;
    virtual uint32_t getServerPort() const = 0;
    virtual std::string getNickname() const = 0;
    virtual std::string getAuthPasscode() const = 0;
};

#endif
