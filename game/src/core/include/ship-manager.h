#ifndef BATTLESHIP_SRC_CORE_INCLUDE_SHIP_MANAGER_H
#define BATTLESHIP_SRC_CORE_INCLUDE_SHIP_MANAGER_H

#include <vector>
#include <memory>

#include "shoot-response.h"
#include "ships.h"
#include "iship-manager.h"
#include "map-update-data.h"

class ShipManager : public IShipManager
{

public:
    ShootResponse receiveShot(const Cell &t_cell) override;
    void initializeShips(const Ships &t_ships) override;

private:
    Ship m_carrier;
    Ship m_battleship;
    Ship m_cruiser;
    Ship m_submarine;
    Ship m_destroyer;

    bool isGameOver() const;
    ShootResponse getSuccessfulShotResponse(const Ship &ship) const;
};

#endif
