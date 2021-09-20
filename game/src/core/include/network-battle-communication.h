#ifndef BATTLESHIP_SRC_CORE_INCLUDE_NETWORK_BATTLE_COMMUNICATION_H
#define BATTLESHIP_SRC_CORE_INCLUDE_NETWORK_BATTLE_COMMUNICATION_H

#include <memory>
#include "ibattle-communication.h"
#include "itcp-client.h"

class NetworkBattleCommunication : public IBattleComunication
{
public:
    NetworkBattleCommunication(std::unique_ptr<ITcpClient> t_tcpClient);
    ~NetworkBattleCommunication();

    void establishNetworkConnection() const;
    GameStartParams receiveGameStartParams() const override;
    Cell getNextShotTarget() const override;
    ShootResponse sendShotTo(const Cell &cell) override;
    void notifyShotResponse(const ShootResponse &shootResponse) override;

private:
    std::unique_ptr<ITcpClient> m_tcpClient;
};

#endif
