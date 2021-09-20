#include "network-battle-communication-factory.h"
#include "network-battle-communication.h"
#include "tcp-client.h"

using namespace std;

NetworkBattleCommunicationFactory::NetworkBattleCommunicationFactory(
    unique_ptr<ITcpClient> t_tcpClient, 
    unique_ptr<IMapper> t_mapper) : m_tcpClient(move(t_tcpClient)), m_mapper(move(t_mapper))
{
}

shared_ptr<IBattleComunication> NetworkBattleCommunicationFactory::createBattleCommunication()
{
    auto communication = make_shared<NetworkBattleCommunication>(move(m_tcpClient), move(m_mapper));
    communication.get()->establishNetworkConnection();
    return communication;
}
