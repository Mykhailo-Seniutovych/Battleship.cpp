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
    m_tcpClient.get()->shutdownConnection();
}

void NetworkBattleCommunication::establishNetworkConnection() const
{
    auto incomingConnection = IncomingConnection{
        .playerNickname = m_appConfig.get()->getNickname(),
        .opponentNickname = m_opponentName,
        .passcode = m_appConfig.get()->getAuthPasscode()};

    auto message = m_mapper.get()->mapFromIncomingConnection(incomingConnection);
    m_tcpClient.get()->establishConnection(message);
}

GameStartParams NetworkBattleCommunication::receiveGameStartParams() const
{
    auto message = m_tcpClient.get()->readNextMessage();
    auto msgWrapper = m_mapper.get()->mapToGameStartParams(message);
    if (msgWrapper.isError)
    {
        throw CommunicationException(msgWrapper.error);
    }

    return msgWrapper.message;
}

Cell NetworkBattleCommunication::getNextShotTarget() const
{
    auto message = m_tcpClient.get()->readNextMessage();
    auto msgWrapper = m_mapper.get()->mapToCell(message);
    if (msgWrapper.isError)
    {
        throw CommunicationException(msgWrapper.error);
    }
    return msgWrapper.message;
}

void NetworkBattleCommunication::notifyShotResponse(const ShootResponse &shootResponse)
{
    auto messageWrapper = MessageWrapper(shootResponse);
    auto message = m_mapper.get()->mapFromShootResponse(messageWrapper);
    m_tcpClient.get()->sendMessage(message);
};

ShootResponse NetworkBattleCommunication::sendShotTo(const Cell &cell)
{
    auto messageWrapper = MessageWrapper(cell);
    auto message = m_mapper.get()->mapFromCell(messageWrapper);
    m_tcpClient.get()->sendMessage(message);

    auto shootResponseMessage = m_tcpClient.get()->readNextMessage();
    auto shootResponse = m_mapper.get()->mapToShootResponse(shootResponseMessage);
    if (shootResponse.isError)
    {
        throw CommunicationException(shootResponse.error);
    }

    return shootResponse.message;
}
