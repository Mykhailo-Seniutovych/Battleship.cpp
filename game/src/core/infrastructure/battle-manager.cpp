#include <memory>

#include "battle-manager.h"
#include "../models/shoot-response.h"
using namespace std;

void BattleManager::playBattle() const
{
    auto shipsOnMap = m_initialShipArrangement.get()->getInitialShipArrangement();
    m_shipManager.get()->initializeShips(shipsOnMap);

    auto isGameOver = false;
    do
    {
        auto targetCell = m_battleCommunication.get()->getNextShotTarget();
        auto response = m_shipManager.get()->receiveShot(targetCell);
        isGameOver = response.cellState == CellState::GameOver;
    } while (!isGameOver);
}

BattleManager::BattleManager(
    unique_ptr<IInitialShipArrangement> t_initialShipArrangement,
    shared_ptr<IShipManager> t_shipManager,
    std::shared_ptr<IBattleComunication> t_battleCommunication)

    : m_initialShipArrangement(std::move(t_initialShipArrangement)),
      m_shipManager(t_shipManager),
      m_battleCommunication(t_battleCommunication)
{
}
