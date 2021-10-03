#include <iostream>
#include <string>
#include "network-battle-communication.h"
#include "communication-exception.h"

using namespace std;

NetworkBattleCommunication::NetworkBattleCommunication(
    unique_ptr<ITcpClient> t_tcpClient,
    unique_ptr<IMapper> t_mapper,
    shared_ptr<IAppConfig> t_appConfig,
    const std::string &t_opponentName)
    : m_tcpClient(move(t_tcpClient)),
      m_mapper(move(t_mapper)),
      m_appConfig(t_appConfig),
      m_opponentName(t_opponentName)
{
}

NetworkBattleCommunication::~NetworkBattleCommunication()
{
    m_tcpClient->shutdownConnection();
}

void NetworkBattleCommunication::establishNetworkConnection() const
{
    IncomingConnection incomingConnection{
        .playerNickname = m_appConfig->getNickname(),
        .opponentNickname = m_opponentName,
        .passcode = m_appConfig->getAuthPasscode()};

    auto message = m_mapper->mapFromIncomingConnection(incomingConnection);
    m_tcpClient->establishConnection(message);
}

GameStartParams NetworkBattleCommunication::receiveGameStartParams() const
{
    auto message = m_tcpClient->readNextMessage();
    auto msgWrapper = m_mapper->mapToGameStartParams(message);
    if (msgWrapper.isError)
    {
        throw CommunicationException(msgWrapper.error);
    }

    return msgWrapper.message;
}

Cell NetworkBattleCommunication::getNextShotTarget() const
{
    auto message = m_tcpClient->readNextMessage();
    auto msgWrapper = m_mapper->mapToCell(message);
    if (msgWrapper.isError)
    {
        throw CommunicationException(msgWrapper.error);
    }
    return msgWrapper.message;
}

void NetworkBattleCommunication::notifyShotResponse(const ShootResponse &shootResponse)
{
    MessageWrapper messageWrapper(shootResponse);
    auto message = m_mapper->mapFromShootResponse(messageWrapper);
    m_tcpClient->sendMessage(message);
};

ShootResponse NetworkBattleCommunication::sendShotTo(const Cell &cell)
{
    MessageWrapper messageWrapper(cell);
    auto message = m_mapper->mapFromCell(messageWrapper);
    m_tcpClient->sendMessage(message);

    auto shootResponseMessage = m_tcpClient->readNextMessage();
    auto shootResponse = m_mapper->mapToShootResponse(shootResponseMessage);
    if (shootResponse.isError)
    {
        throw CommunicationException(shootResponse.error);
    }

    return shootResponse.message;
}
