#include <fstream>
#include <exception>
#include <iomanip>
#include "invalid-config-exception.h"
#include "app-config.h"
#include "json.hpp"

using namespace std;

void AppConfig::initialize()
{
    try
    {
        ifstream fileStream(CONFIG_FILENAME);
        nlohmann::json json;
        fileStream >> json;

        m_nickname = json[NICKNAME_KEY];
        m_serverAddres = json[SERVER_ADDRESS_KEY];
        m_serverPort = json[SERVER_PORT_KEY];
    }
    catch (const exception &ex)
    {
        auto message =
            "Could not read and process '" + CONFIG_FILENAME +
            "', message: '" + ex.what() + "'. Make sure config file exists and has valid values.";
        throw InvalidConfigException(message);
    }
}

string AppConfig::getNickname() const
{
    return m_nickname;
}

string AppConfig::getServerAddres() const
{
    return m_serverAddres;
}

uint32_t AppConfig::getServerPort() const
{
    return m_serverPort;
}

std::string AppConfig::getAuthPasscode() const
{
    // TODO: Provide better storage of a passcode than directly in source code, that is publicly available on GitHub.
    return "cG!GA{{Y2G;A'C`[,&nPoYTf6yg&FFPkj!`EqoLB0r{lvxKdOE";
}

void AppConfig::setNickname(const string &t_nickname)
{
    nlohmann::json json;
    json[NICKNAME_KEY] = t_nickname;
    json[SERVER_ADDRESS_KEY] = m_serverAddres;
    json[SERVER_PORT_KEY] = m_serverPort;

    std::ofstream fileStream(CONFIG_FILENAME);
    fileStream << setw(4) << json << std::endl;
}