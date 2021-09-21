#ifndef BATTLESHIP_SRC_CORE_INCLUDE_NETWORK_BATTLE_COMMUNICATION_H
#define BATTLESHIP_SRC_CORE_INCLUDE_NETWORK_BATTLE_COMMUNICATION_H

#include <memory>
#include <iapp-config.h>
#include "ibattle-communication.h"
#include "itcp-client.h"
#include "imapper.h"

class NetworkBattleCommunication : public IBattleComunication
{
public:
    NetworkBattleCommunication(
        std::unique_ptr<ITcpClient> t_tcpClient,
        std::unique_ptr<IMapper> t_mapper,
        std::shared_ptr<IAppConfig> t_appConfig,
        const std::string &m_opponentName);
    ~NetworkBattleCommunication();

    void establishNetworkConnection() const;
    GameStartParams receiveGameStartParams() const override;
    Cell getNextShotTarget() const override;
    ShootResponse sendShotTo(const Cell &cell) override;
    void notifyShotResponse(const ShootResponse &shootResponse) override;

private:
    std::shared_ptr<IAppConfig> m_appConfig;
    std::unique_ptr<ITcpClient> m_tcpClient;
    std::unique_ptr<IMapper> m_mapper;

    std::string m_opponentName;
};

#endif
