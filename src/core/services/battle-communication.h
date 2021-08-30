#ifndef BATTLESHIP_SRC_CORE_SERVICES_BATTLE_COMMUNICATION_H
#define BATTLESHIP_SRC_CORE_SERVICES_BATTLE_COMMUNICATION_H

#include "../interfaces/ibattle-communication.h"

class BattleCommunication : public IBattleComunication
{
public:
    Cell getNextShotTarget() const override;
    void sendShotTo(const Cell &cell) override;
};

#endif
