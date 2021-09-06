#ifndef BATTLESHIP_SRC_CORE_INCLUDE_BATTLE_MANAGER_H
#define BATTLESHIP_SRC_CORE_INCLUDE_BATTLE_MANAGER_H

#include <array>
#include <memory>
#include <vector>

#include "ship.h"
#include "iinitial-ship-arrangement.h"
#include "iship-manager.h"
#include "ibattle-communication.h"
#include "icell-reader.h"

class BattleManager
{
public:
    BattleManager(
        std::unique_ptr<IInitialShipArrangement> t_initialShipArrangement,
        std::unique_ptr<IShipManager> t_shipManager,
        std::unique_ptr<IBattleComunication> t_battleCommunication,
        std::unique_ptr<ICellReader> t_cellReader);
    void playBattle() const;

    void subscribe(std::unique_ptr<IMapStateObserver> t_observer);
    void unsubscribe(std::unique_ptr<IMapStateObserver> t_observer);

private:
    std::unique_ptr<IInitialShipArrangement> m_initialShipArrangement;
    std::unique_ptr<IShipManager> m_shipManager;
    std::unique_ptr<IBattleComunication> m_battleCommunication;
    std::unique_ptr<ICellReader> m_cellReader;

    std::vector<std::unique_ptr<IMapStateObserver>> m_observers = {};

    void notifyShipsInitialized(const Ships &ships) const;
    void notifyMyMapUpdated(const Cell &cell, const ShootResponse &shootResponse) const;
    void notifyEnemyMapUpdated(const Cell &cell, const ShootResponse &shootResponse) const;
};

#endif
