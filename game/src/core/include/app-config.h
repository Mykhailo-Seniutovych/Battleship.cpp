#ifndef BATTLESHIP_SRC_CORE_INCLUDE_APP_CONFIG_H
#define BATTLESHIP_SRC_CORE_INCLUDE_APP_CONFIG_H

#include "iapp-config.h"

class AppConfig : public IAppConfig
{
public:
    void initialize();
    
    std::string getServerAddres() const override;
    uint32_t getServerPort() const override;
    std::string getNickname() const override;
    std::string getAuthPasscode() const override;

    void setNickname(const std::string &t_nickname) override;
private:
    std::string m_serverAddres;
    uint32_t m_serverPort;
    std::string m_nickname;

};

#endif
