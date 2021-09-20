#include "network-battle-communication-factory.h"
#include "network-battle-communication.h"
#include "tcp-client.h"

using namespace std;

NetworkBattleCommunicationFactory::NetworkBattleCommunicationFactory(
    unique_ptr<ITcpClient> t_tcpClient) : m_tcpClient(move(t_tcpClient))
{
}

shared_ptr<IBattleComunication> NetworkBattleCommunicationFactory::createBattleCommunication()
{
    auto communication = make_shared<NetworkBattleCommunication>(move(m_tcpClient));
    communication.get()->establishNetworkConnection();
    return communication;
}
