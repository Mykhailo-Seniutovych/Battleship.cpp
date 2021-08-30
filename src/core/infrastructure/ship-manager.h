#ifndef BATTLESHIP_CORE_INFRASTRUCTURE_SHIPMAMAGER_H
#define BATTLESHIP_CORE_INFRASTRUCTURE_SHIPMAMAGER_H

#include <vector>
#include "../models/shoot-response.h"
#include "../models/ship.h"
#include "../interfaces/iobservable.h"
#include "../interfaces/iship-manager.h"
#include "../models/map-update-data.h"

class ShipManager : public IShipManager
{

public:
    ShipManager();

    ShootResponse receiveShot(const Cell &t_cell) override;
    void initializeShips(
        const Ship &t_carrier,
        const Ship &t_battleship,
        const Ship &t_cruiser,
        const Ship &t_submarine,
        const Ship &t_destroyer) override;
    void subscribe(IObserver<MapUpdateData> *observer) override;
    void unsubscribe(IObserver<MapUpdateData> *observer) override;

private:
    Ship m_carrier;
    Ship m_battleship;
    Ship m_cruiser;
    Ship m_submarine;
    Ship m_destroyer;
    std::vector<IObserver<MapUpdateData> *> m_observers = {};

    bool isGameOver() const;
    ShootResponse getSuccessfulShotResponse(const Ship &ship) const;
    void notifyMapUpdate(const MapUpdateData &data) const;
};

#endif
