#ifndef BATTLESHIP_CORE_INFRASTRUCTURE_SHIPMAMAGER_H
#define BATTLESHIP_CORE_INFRASTRUCTURE_SHIPMAMAGER_H

#include <vector>
#include "../models/shoot-response.h"
#include "../models/ship.h"
#include "../interfaces/iobservable.h"
#include "../interfaces/iship-manager.h"
#include "../models/map-update-data.h"

class ShipManager: public IShipManager {

public:
    ShipManager();

    ShootResponse receiveShot(Cell cell) override;
    void initializeShips(Ship t_carrier, Ship t_battleship, Ship t_cruiser, Ship t_submarine, Ship t_destroyer) override;
    void subscribe(IObserver<MapUpdateData> *observer) override;
    void unsubscribe(IObserver<MapUpdateData> *observer) override;

private:
    Ship m_carrier;
    Ship m_battleship;
    Ship m_cruiser;
    Ship m_submarine;
    Ship m_destroyer;
    std::vector<IObserver<MapUpdateData>*> observers = {};

    bool isGameOver();
    ShootResponse getSuccessfulShotResponse(Ship ship);
    void notifyMapUpdate(const MapUpdateData& data);
};

#endif
