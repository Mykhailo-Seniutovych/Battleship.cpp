#include "console-map-state-observer.h"

void ConsoleMapStateObserver::notifyShipsInitialized(const Ships &ships) const
{
    m_maps.get()->initMaps(
        ships.carrier.getCoordinates(),
        ships.battleship.getCoordinates(),
        ships.cruiser.getCoordinates(),
        ships.submarine.getCoordinates(),
        ships.destroyer.getCoordinates());
    m_maps.get()->printMaps();
}

void ConsoleMapStateObserver::notifyMyMapUpdated(const MapUpdateData &updateData) const
{
    m_maps.get()->printMyShotCell(updateData.cell);
    m_maps.get()->updateMyMap(updateData);
    m_maps.get()->printMaps();
}

void ConsoleMapStateObserver::notifyEnemyMapUpdated(const MapUpdateData &updateData) const
{
    m_maps.get()->updateEnemyMap(updateData);
    m_maps.get()->printMaps();
}

ConsoleMapStateObserver::ConsoleMapStateObserver(std::unique_ptr<IMaps> t_maps)
    : m_maps(std::move(t_maps)){};
