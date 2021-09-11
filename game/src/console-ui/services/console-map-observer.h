#ifndef BATTLESHIP_SRC_CONSOLE_UI_SERVICES_CONSOLE_MAP_OBSERVER_H
#define BATTLESHIP_SRC_CONSOLE_UI_SERVICES_CONSOLE_MAP_OBSERVER_H

#include <memory>

#include "ibattle-observer.h"
#include "interfaces/imaps.h"

class ConsoleMapObserver : public IBattleObserver
{
public:
    ConsoleMapObserver(std::unique_ptr<IMaps> t_maps);
    void notifyShipsInitialized(const Ships &t_ships) const override;
    void notifyMyMapUpdated(const MapUpdateData &t_updateData) const override;
    void notifyEnemyMapUpdated(const MapUpdateData &t_updateData) const override;
    void notifyGameOver(bool t_currentPlayerWon) const override;
private:
    std::unique_ptr<IMaps> m_maps;
};

#endif
