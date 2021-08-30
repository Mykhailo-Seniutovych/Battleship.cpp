#include <memory>
using namespace std;

#include "../core/infrastructure/ship-manager.h"
#include "../core/infrastructure/battle-manager.h"
#include "../core/services/battle-communication.h"
#include "services/console-initial-ship-arrangement.h"
#include "services/console-map-state-observer.h"
#include "ui/maps.h"

int main()
{
    auto shipManager = make_shared<ShipManager>();
    auto shipArrangement = make_shared<ConsoleInitialShipArrangement>();
    auto battleComunication = make_shared<BattleCommunication>();
    auto battleManager = BattleManager(shipArrangement, shipManager, battleComunication);

    auto consoleMaps = make_shared<Maps>();
    auto observer = make_shared<ConsoleMapStateObserver>(consoleMaps);
    shipManager.get()->subscribe(observer);
    battleManager.playBattle();

    return 0;
}
