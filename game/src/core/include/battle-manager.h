#ifndef BATTLESHIP_SRC_CORE_INCLUDE_BATTLE_MANAGER_H
#define BATTLESHIP_SRC_CORE_INCLUDE_BATTLE_MANAGER_H

#include <array>
#include <memory>

#include "ship.h"
#include "iinitial-ship-arrangement.h"
#include "iship-manager.h"
#include "ibattle-communication.h"

class BattleManager
{
public:
    BattleManager(
        std::unique_ptr<IInitialShipArrangement> t_initialShipArrangement,
        std::unique_ptr<IShipManager> t_shipManager,
        std::unique_ptr<IBattleComunication> t_battleCommunication);
    void playBattle() const;

private:
    std::unique_ptr<IInitialShipArrangement> m_initialShipArrangement;
    std::unique_ptr<IShipManager> m_shipManager;
    std::unique_ptr<IBattleComunication> m_battleCommunication;
};

#endif
