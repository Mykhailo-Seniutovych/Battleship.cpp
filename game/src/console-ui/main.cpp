#include <memory>
#include <iostream>
using namespace std;

#include "ship-manager.h"
#include "battle-manager.h"
#include "computer-battle-communication.h"
#include "services/console-initial-ship-arrangement.h"
#include "services/console-map-state-observer.h"
#include "services/console-cell-reader.h"
#include "ui/maps.h"

int main()
{
    auto battleManager = BattleManager(
        make_unique<ConsoleInitialShipArrangement>(),
        make_unique<ShipManager>(),
        make_unique<ComputerBattleCommunication>(make_unique<ShipManager>()),
        make_unique<ConsoleCellReader>());

    auto observer = make_unique<ConsoleMapStateObserver>(make_unique<Maps>());
    battleManager.subscribe(move(observer));

    battleManager.playBattle();

    return 0;
}
