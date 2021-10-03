#include "network-battle-communication-factory.h"
#include "network-battle-communication.h"
#include "tcp-client.h"

using namespace std;

NetworkBattleCommunicationFactory::NetworkBattleCommunicationFactory(
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

shared_ptr<IBattleComunication> NetworkBattleCommunicationFactory::createBattleCommunication()
{
    auto communication = make_shared<NetworkBattleCommunication>(
        move(m_tcpClient), move(m_mapper), m_appConfig, m_opponentName);
    communication->establishNetworkConnection();
    return communication;
}
