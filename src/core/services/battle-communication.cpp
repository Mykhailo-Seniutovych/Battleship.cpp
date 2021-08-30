#include <iostream>
using namespace std;

#include "battle-communication.h"

static int shotCounter = 0; // delete after real implementation is done

Cell BattleCommunication::getNextShotTarget() const
{
    // TODO: replace with TCP implementation
    cout << "Enter coordinates to receive next shot (e.g. \"1 10\")" << endl;
    string newTarget;
    getline(cin, newTarget);

    auto row = static_cast<uint8_t>(stoi(newTarget.substr(0, newTarget.find(" ")))) - 1;
    auto col = static_cast<uint8_t>(stoi(newTarget.substr(newTarget.find(" ") + 1)) - 1);

    return Cell(row, col);
}

void BattleCommunication::sendShotTo(const Cell &cell)
{
    // TODO: implement
}
