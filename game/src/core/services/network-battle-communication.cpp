#include <iostream>
#include "network-battle-communication.h"
#include <string>

using namespace std;

static int shotCounter = 0; // delete after real implementation is done

Cell NetworkBattleCommunication::getNextShotTarget() const
{
    // TODO: replace with TCP implementation
    cout << "Enter coordinates to receive next shot (e.g. \"1 10\")" << endl;
    string newTarget;
    getline(cin, newTarget);

    auto row = static_cast<uint8_t>(stoi(newTarget.substr(0, newTarget.find(" "))) - 1);
    auto col = static_cast<uint8_t>(stoi(newTarget.substr(newTarget.find(" ") + 1)) - 1);

    return Cell(row, col);
}

void NetworkBattleCommunication::notifyShotResponse(ShootResponse shootResponse)
{
     // TODO: implement
};

ShootResponse NetworkBattleCommunication::sendShotTo(const Cell &cell)
{
    // TODO: implement

    return ShootResponse(CellState::Miss);
}
