#include <memory>
#include <cstdint>
#include <string>

#include "ship-manager.h"
#include "battle-manager.h"
#include "statistics-service.h"
#include "database-service.h"
#include "computer-battle-communication.h"
#include "services/console-initial-ship-arrangement.h"
#include "services/console-map-state-observer.h"
#include "services/console-cell-reader.h"
#include "ui/maps.h"
#include "database-service.h"
#include "ui/statistics-ui.h"

using namespace std;

void playGame()
{
    auto battleManager = BattleManager(
        make_unique<ConsoleInitialShipArrangement>(),
        make_unique<ShipManager>(),
        make_unique<ComputerBattleCommunication>(make_unique<ShipManager>()),
        make_unique<ConsoleCellReader>());

    auto observer = make_unique<ConsoleMapStateObserver>(make_unique<Maps>());
    battleManager.subscribe(move(observer));

    battleManager.playBattle();
}

void showStatistics(bool showBest)
{
    auto databaseService = make_unique<DatabaseService<Player>>();
    databaseService.get()->ensureDbCreated();
    auto statisticsUi = StatisticsUi(
        make_unique<StatisticsService>(move(databaseService)));
    if (showBest)
    {
        statisticsUi.showBestPlayers();
    }
    else
    {
        statisticsUi.showWorstPlayers();
    }
}

int main(int argc, char *argv[])
{
    auto startGame = true;
    for (uint8_t index = 1; index < argc; index++)
    {
        if (string(argv[index]) == "--stats-best")
        {
            startGame = false;
            showStatistics(true);
            break;
        }

        if (string(argv[index]) == "--stats-worst")
        {
            startGame = false;
            showStatistics(false);
            break;
        };
    }

    if (startGame)
    {
        playGame();
    }

    return 0;
}
