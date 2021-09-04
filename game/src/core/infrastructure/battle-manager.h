#ifndef BATTLESHIP_SRC_CORE_INFRASTRUCTURE_BATTLE_MANAGER_H
#define BATTLESHIP_SRC_CORE_INFRASTRUCTURE_BATTLE_MANAGER_H

#include <array>
#include <memory>

#include "../models/ship.h"
#include "../utils/constants.h"
#include "../interfaces/iinitial-ship-arrangement.h"
#include "../interfaces/iship-manager.h"
#include "../interfaces/ibattle-communication.h"

class BattleManager
{
public:
    BattleManager(
        std::unique_ptr<IInitialShipArrangement> t_initialShipArrangement,
        std::shared_ptr<IShipManager> t_shipManager,
        std::shared_ptr<IBattleComunication> t_battleCommunication);
    void playBattle() const;

private:
    std::unique_ptr<IInitialShipArrangement> m_initialShipArrangement;
    std::shared_ptr<IShipManager> m_shipManager;
    std::shared_ptr<IBattleComunication> m_battleCommunication;
};

#endif
