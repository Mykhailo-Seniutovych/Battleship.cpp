#ifndef BATTLESHIP_SRC_CORE_INCLUDE_NETWORK_BATTLE_COMMUNICATION_FACTORY_H
#define BATTLESHIP_SRC_CORE_INCLUDE_NETWORK_BATTLE_COMMUNICATION_FACTORY_H

#include "ibattle-communication-factory.h"
#include "itcp-client.h"
#include "tcp-client.h"
#include "imapper.h"

class NetworkBattleCommunicationFactory : public IBattleComunicationFactory
{
public:
    NetworkBattleCommunicationFactory(
        std::unique_ptr<ITcpClient> t_tcpClient, 
        std::unique_ptr<IMapper> t_mapper,
        std::shared_ptr<IAppConfig> t_appConfig,
        const std::string &t_opponentName);
    std::shared_ptr<IBattleComunication> createBattleCommunication() override;

private:
    std::unique_ptr<ITcpClient> m_tcpClient;
    std::unique_ptr<IMapper> m_mapper;
    std::shared_ptr<IAppConfig> m_appConfig;

    std::string m_opponentName;
};

#endif
