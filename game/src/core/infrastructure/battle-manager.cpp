#include <memory>
#include "battle-manager.h"
#include "shoot-response.h"

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
    unique_ptr<IShipManager> t_shipManager,
    std::unique_ptr<IBattleComunication> t_battleCommunication)

    : m_initialShipArrangement(move(t_initialShipArrangement)),
      m_shipManager(move(t_shipManager)),
      m_battleCommunication(move(t_battleCommunication))
{
}
