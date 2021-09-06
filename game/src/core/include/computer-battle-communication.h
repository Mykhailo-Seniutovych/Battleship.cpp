#ifndef BATTLESHIP_SRC_CORE_INCLUDE_COMPUTER_BATTLE_COMMUNICATION_H
#define BATTLESHIP_SRC_CORE_INCLUDE_COMPUTER_BATTLE_COMMUNICATION_H

#include <unordered_set>
#include <vector>
#include "ibattle-communication.h"
#include "ship.h"
#include "shoot-response.h"

class ComputerBattleCommunication : public IBattleComunication
{
public:
    ComputerBattleCommunication();
    
    Cell getNextShotTarget() const override;
    ShootResponse sendShotTo(const Cell &cell) override;
    void notifyShotResponse(ShootResponse shootResponse) override;

private:
    Ship m_carrier;
    Ship m_battleship;
    Ship m_cruiser;
    Ship m_submarine;
    Ship m_destroyer;
    mutable std::unordered_set<Cell, Cell::HashFunction> m_shotCells = {};
    mutable std::vector<Cell> m_cellsToShoot;

    void initShips();
    void initShootTargets();
    ShootResponse getSuccessfulShotResponse(const Ship &ship) const;
    bool isGameOver() const;
};

#endif
