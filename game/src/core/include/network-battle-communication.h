#ifndef BATTLESHIP_SRC_CORE_INCLUDE_NETWORK_BATTLE_COMMUNICATION_H
#define BATTLESHIP_SRC_CORE_INCLUDE_NETWORK_BATTLE_COMMUNICATION_H

#include "ibattle-communication.h"

class NetworkBattleCommunication : public IBattleComunication
{
public:
    Cell getNextShotTarget() const override;
    ShootResponse sendShotTo(const Cell &cell) override;
    void notifyShotResponse(const ShootResponse &shootResponse) override;
};

#endif
