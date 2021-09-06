#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>
#include "computer-battle-communication.h"
#include "constants.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

ComputerBattleCommunication::ComputerBattleCommunication()
{
    initShips();
    initShootTargets();
}

void ComputerBattleCommunication::initShips()
{
    // TODO: Replace with randomly created ships
    m_carrier = Ship(Position::Horizontal, 1, {1, 2, 3, 4, 5, 6});
    m_battleship = Ship(Position::Vertical, 7, {1, 2, 3, 5});
    m_cruiser = Ship(Position::Horizontal, 8, {3, 4, 5});
    m_submarine = Ship(Position::Vertical, 9, {7, 8, 9});
    m_destroyer = Ship(Position::Vertical, 2, {4, 5});
}

void ComputerBattleCommunication::initShootTargets()
{
    for (auto row = 0; row < Constants::MAP_SIZE; row++)
    {
        for (auto col = 0; col < Constants::MAP_SIZE; col++)
        {
            m_cellsToShoot.push_back(Cell(row, col));
        }
    }

    random_device rd;
    auto engine = default_random_engine(rd());
    shuffle(m_cellsToShoot.begin(), m_cellsToShoot.end(), engine);
}

Cell ComputerBattleCommunication::getNextShotTarget() const
{
    sleep_for(2s);

    auto cell = m_cellsToShoot.back();
    m_shotCells.insert(cell);

    m_cellsToShoot.pop_back();
    return cell;
}

void ComputerBattleCommunication::notifyShotResponse(ShootResponse shootResponse)
{
}

// TODO: Similar methods exist in BattleManager, need to provide common implementation 
ShootResponse ComputerBattleCommunication::sendShotTo(const Cell &cell)
{
    ShootResponse response(CellState::Miss);

    if (m_carrier.tryReceiveShot(cell))
    {
        response = getSuccessfulShotResponse(m_carrier);
    }
    else if (m_battleship.tryReceiveShot(cell))
    {
        response = getSuccessfulShotResponse(m_battleship);
    }
    else if (m_cruiser.tryReceiveShot(cell))
    {
        response = getSuccessfulShotResponse(m_cruiser);
    }
    else if (m_submarine.tryReceiveShot(cell))
    {
        response = getSuccessfulShotResponse(m_submarine);
    }
    else if (m_destroyer.tryReceiveShot(cell))
    {
        response = getSuccessfulShotResponse(m_destroyer);
    }

    return response;
}

ShootResponse ComputerBattleCommunication::getSuccessfulShotResponse(const Ship &ship) const
{
    ShootResponse response(CellState::ShipDamaged);
    if (isGameOver())
    {
        response = ShootResponse(CellState::GameOver, ship.getCoordinates());
    }
    else if (ship.isShipSunk())
    {
        response = ShootResponse(CellState::ShipSunk, ship.getCoordinates());
    }
    return response;
}

bool ComputerBattleCommunication::isGameOver() const
{
    return m_carrier.isShipSunk() &&
           m_battleship.isShipSunk() &&
           m_cruiser.isShipSunk() &&
           m_submarine.isShipSunk() &&
           m_destroyer.isShipSunk();
}
