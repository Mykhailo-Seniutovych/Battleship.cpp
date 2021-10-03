#include <fstream>
#include <exception>
#include <iomanip>
#include <filesystem>
#include "invalid-config-exception.h"
#include "app-config.h"
#include "json.hpp"

using namespace std;

static const std::string CONFIG_FILENAME = "app-config.json";
static const std::string NICKNAME_KEY = "nickname";
static const std::string SERVER_ADDRESS_KEY = "serverAddress";
static const std::string SERVER_PORT_KEY = "serverPort";

void AppConfig::initialize()
{
    if (!filesystem::exists(CONFIG_FILENAME))
    {
        auto message =
            CONFIG_FILENAME + " was not found. Make sure this file exists. " +
            "If you lost or deleted it accidentally, you can reintsall the game to restore it.";
        throw InvalidConfigException(message);
    }

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
            "Could not process '" + CONFIG_FILENAME +
            "', message: '" + ex.what() + "'. Make sure the file is in correct json format. " +
            "If you don't know how to change to the correct format, you can reintsall the game to restore it in the correct foramt.";
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