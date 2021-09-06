#include <memory>
#include <algorithm>
#include "battle-manager.h"
#include "shoot-response.h"

using namespace std;

void BattleManager::playBattle() const
{
    auto shipsOnMap = m_initialShipArrangement.get()->getInitialShipArrangement();
    m_shipManager.get()->initializeShips(shipsOnMap);
    notifyShipsInitialized(shipsOnMap);

    auto isGameOver = false;
    do
    {
        auto targetCell = m_battleCommunication.get()->getNextShotTarget();
        auto currentPlayerResponse = m_shipManager.get()->receiveShot(targetCell);
        notifyMyMapUpdated(targetCell, currentPlayerResponse);
        m_battleCommunication.get()->notifyShotResponse(currentPlayerResponse);

        auto cellToShoot = m_cellReader.get()->readCell();
        auto enemyResponse = m_battleCommunication.get()->sendShotTo(cellToShoot);
        notifyEnemyMapUpdated(cellToShoot, enemyResponse);

        isGameOver = currentPlayerResponse.cellState == CellState::GameOver ||
                     enemyResponse.cellState == CellState::GameOver;
    } while (!isGameOver);
}

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

void BattleManager::subscribe(unique_ptr<IMapStateObserver> t_observer)
{
    m_observers.push_back(move(t_observer));
}

void BattleManager::unsubscribe(unique_ptr<IMapStateObserver> t_observer)
{
    m_observers.erase(
        remove(m_observers.begin(), m_observers.end(), t_observer),
        m_observers.end());
}

void BattleManager::notifyShipsInitialized(const Ships &ships) const
{
    for (auto const &observer : m_observers)
    {
        observer->notifyShipsInitialized(ships);
    }
}

void BattleManager::notifyMyMapUpdated(const Cell &cell, const ShootResponse &shootResponse) const
{
    auto mapUpdateData = MapUpdateData(
        cell,
        shootResponse.cellState,
        shootResponse.sunkShipCoordinates);
    for (auto const &observer : m_observers)
    {
        observer->notifyMyMapUpdated(mapUpdateData);
    }
}

void BattleManager::notifyEnemyMapUpdated(const Cell &cell, const ShootResponse &shootResponse) const
{
        auto mapUpdateData = MapUpdateData(
        cell,
        shootResponse.cellState,
        shootResponse.sunkShipCoordinates);
    for (auto const &observer : m_observers)
    {
        observer->notifyEnemyMapUpdated(mapUpdateData);
    }
}
