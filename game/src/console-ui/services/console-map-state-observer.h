#ifndef BATTLESHIP_SRC_CONSOLE_UI_SERVICES_CONSOLE_MAP_STATE_OBSERVER_H
#define BATTLESHIP_SRC_CONSOLE_UI_SERVICES_CONSOLE_MAP_STATE_OBSERVER_H

#include <memory>

#include "imap-state-observer.h"
#include "interfaces/imaps.h"

class ConsoleMapStateObserver : public IMapStateObserver
{
public:
    ConsoleMapStateObserver(std::unique_ptr<IMaps> t_maps);
    void notifyShipsInitialized(const Ships &t_ships) const override;
    void notifyMapUpdated(const MapUpdateData &t_updateData) const override;

private:
    std::unique_ptr<IMaps> m_maps;
};

#endif
