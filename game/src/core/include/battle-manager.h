#ifndef BATTLESHIP_SRC_CORE_INCLUDE_BATTLE_MANAGER_H
#define BATTLESHIP_SRC_CORE_INCLUDE_BATTLE_MANAGER_H

#include <array>
#include <memory>
#include <vector>

#include "ship.h"
#include "iship-arrangement.h"
#include "iship-manager.h"
#include "ibattle-communication.h"
#include "icell-reader.h"

class BattleManager
{
public:
    BattleManager(
        std::unique_ptr<IShipArrangement> t_shipArrangement,
        std::unique_ptr<IShipManager> t_shipManager,
        std::unique_ptr<IBattleComunication> t_battleCommunication,
        std::unique_ptr<ICellReader> t_cellReader);
    void playBattle() const;

    void subscribe(std::unique_ptr<IBattleObserver> t_observer);
    void unsubscribe(std::unique_ptr<IBattleObserver> t_observer);

private:
    std::unique_ptr<IShipArrangement> m_shipArrangement;
    std::unique_ptr<IShipManager> m_shipManager;
    std::unique_ptr<IBattleComunication> m_battleCommunication;
    std::unique_ptr<ICellReader> m_cellReader;

    std::vector<std::unique_ptr<IBattleObserver>> m_observers = {};

    void notifyShipsInitialized(const Ships &t_ships) const;
    void notifyMyMapUpdated(const Cell &t_cell, const ShootResponse &t_shootResponse) const;
    void notifyEnemyMapUpdated(const Cell &t_cell, const ShootResponse &t_shootResponse) const;
    void notifyGameOver(bool t_currenPlayerWon) const;
};

#endif
