#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>
#include <memory>
#include "computer-battle-communication.h"
#include "constants.h"
#include "ships.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

ComputerBattleCommunication::ComputerBattleCommunication(
    unique_ptr<IShipManager> t_computerShipManager)
    : m_computerShipManager(move(t_computerShipManager))
{
    initShips();
    initShootTargets();
}

void ComputerBattleCommunication::initShips()
{
    // TODO: Replace with randomly created ships
    auto ships = Ships {
        .carrier = Ship(Position::Horizontal, 1, { 1, 2, 3, 4, 5 }),
        .battleship = Ship(Position::Vertical, 7, { 1, 2, 3, 4 }),
        .cruiser = Ship(Position::Horizontal, 8, { 3, 4, 5 }),
        .submarine = Ship(Position::Vertical, 9, { 7, 8, 9 }),
        .destroyer = Ship(Position::Vertical, 2, { 4, 5 }),
    };
    m_computerShipManager.get()->initializeShips(ships);
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

void ComputerBattleCommunication::notifyShotResponse(const ShootResponse& shootResponse)
{
}

ShootResponse ComputerBattleCommunication::sendShotTo(const Cell &cell)
{
    auto response = m_computerShipManager.get()->receiveShot(cell);
    return response;
}
