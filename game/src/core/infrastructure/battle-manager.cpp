#include <memory>
#include <algorithm>
#include "battle-manager.h"
#include "shoot-response.h"

using namespace std;

BattleManager::BattleManager(
    unique_ptr<IInitialShipArrangement> t_initialShipArrangement,
    unique_ptr<IShipManager> t_shipManager,
    unique_ptr<IBattleComunication> t_battleCommunication,
    unique_ptr<ICellReader> t_cellReader)

    : m_initialShipArrangement(move(t_initialShipArrangement)),
      m_shipManager(move(t_shipManager)),
      m_battleCommunication(move(t_battleCommunication)),
      m_cellReader(move(t_cellReader))
{
}

void BattleManager::playBattle() const
{
    auto shipsOnMap = m_initialShipArrangement.get()->getInitialShipArrangement();
    m_shipManager.get()->initializeShips(shipsOnMap);
    notifyShipsInitialized(shipsOnMap);

    do
    {
        auto targetCell = m_battleCommunication.get()->getNextShotTarget();
        auto currentPlayerResponse = m_shipManager.get()->receiveShot(targetCell);
        notifyMyMapUpdated(targetCell, currentPlayerResponse);
        m_battleCommunication.get()->notifyShotResponse(currentPlayerResponse);

        auto currentPlayerLost = currentPlayerResponse.cellState == CellState::GameOver;
        if (currentPlayerLost)
        {
            notifyGameOver(false);
            break;
        }

        auto cellToShoot = m_cellReader.get()->readCell();
        auto enemyResponse = m_battleCommunication.get()->sendShotTo(cellToShoot);
        notifyEnemyMapUpdated(cellToShoot, enemyResponse);

        auto enemyLost = enemyResponse.cellState == CellState::GameOver;
        if (enemyLost)
        {
            notifyGameOver(true);
            break;
        }

    } while (true);
}

void BattleManager::subscribe(unique_ptr<IBattleObserver> t_observer)
{
    m_observers.push_back(move(t_observer));
}

void BattleManager::unsubscribe(unique_ptr<IBattleObserver> t_observer)
{
    m_observers.erase(
        remove(m_observers.begin(), m_observers.end(), t_observer),
        m_observers.end());
}

void BattleManager::notifyShipsInitialized(const Ships &t_ships) const
{
    for (auto const &observer : m_observers)
    {
        observer->notifyShipsInitialized(t_ships);
    }
}

void BattleManager::notifyMyMapUpdated(const Cell &t_cell, const ShootResponse &t_shootResponse) const
{
    auto mapUpdateData = MapUpdateData(
        t_cell,
        t_shootResponse.cellState,
        t_shootResponse.sunkShipCoordinates);
    for (auto const &observer : m_observers)
    {
        observer->notifyMyMapUpdated(mapUpdateData);
    }
}

void BattleManager::notifyEnemyMapUpdated(const Cell &t_cell, const ShootResponse &t_shootResponse) const
{
    auto mapUpdateData = MapUpdateData(
        t_cell,
        t_shootResponse.cellState,
        t_shootResponse.sunkShipCoordinates);
    for (auto const &observer : m_observers)
    {
        observer->notifyEnemyMapUpdated(mapUpdateData);
    }
}

void BattleManager::notifyGameOver(bool t_currenPlayerWon) const
{
    for (auto const &observer : m_observers)
    {
        observer->notifyGameOver(t_currenPlayerWon);
    }
}
