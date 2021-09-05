#include <memory>
#include <iostream>
using namespace std;

#include "ship-manager.h"
#include "battle-manager.h"
#include "battle-communication.h"
#include "services/console-initial-ship-arrangement.h"
#include "services/console-map-state-observer.h"
#include "ui/maps.h"

int main()
{
    auto shipManager = make_unique<ShipManager>();
    auto observer = make_unique<ConsoleMapStateObserver>(make_unique<Maps>());
    shipManager.get()->subscribe(move(observer));

    auto battleManager = BattleManager(
        make_unique<ConsoleInitialShipArrangement>(),
        move(shipManager),
        make_unique<BattleCommunication>());

    battleManager.playBattle();

    return 0;
}
