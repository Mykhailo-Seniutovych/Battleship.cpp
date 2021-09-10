#ifndef BATTLESHIP_SRC_CORE_INCLUDE_COMPUTER_BATTLE_COMMUNICATION_H
#define BATTLESHIP_SRC_CORE_INCLUDE_COMPUTER_BATTLE_COMMUNICATION_H

#include <unordered_set>
#include <vector>
#include <memory>;
#include "ibattle-communication.h"
#include "ship.h"
#include "shoot-response.h"
#include "iship-manager.h"

class ComputerBattleCommunication : public IBattleComunication
{
public:
    ComputerBattleCommunication(std::unique_ptr<IShipManager> t_computerShipManager);
    
    Cell getNextShotTarget() const override;
    ShootResponse sendShotTo(const Cell &cell) override;
    void notifyShotResponse(const ShootResponse& shootResponse) override;

private:
    std::unique_ptr<IShipManager> m_computerShipManager;
    mutable std::unordered_set<Cell, Cell::HashFunction> m_shotCells = {};
    mutable std::vector<Cell> m_cellsToShoot;

    void initShips();
    void initShootTargets();
};

#endif