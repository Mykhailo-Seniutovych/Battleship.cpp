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

void ConsoleMapStateObserver::notifyMapUpdated(const MapUpdateData &updateData) const
{
    m_maps.get()->updateMyMap(updateData);
    m_maps.get()->printMaps();
}

ConsoleMapStateObserver::ConsoleMapStateObserver(std::shared_ptr<IMaps> t_maps)
    : m_maps(t_maps){};
