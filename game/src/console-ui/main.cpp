#include <memory>
#include <cstdint>
#include <string>
#include <exception>
#include <iostream>

#include "ship-manager.h"
#include "battle-manager.h"
#include "statistics-service.h"
#include "database-service.h"
#include "computer-battle-communication.h"
#include "services/console-ship-arrangement.h"
#include "computer-ship-arrangement.h"
#include "services/console-map-observer.h"
#include "services/statistics-observer.h"
#include "services/console-cell-reader.h"
#include "ui/maps.h"
#include "database-service.h"
#include "ui/statistics-ui.h"

using namespace std;

void playGame()
{
    auto battleManager = BattleManager(
        make_unique<ConsoleShipArrangement>(),
        make_unique<ShipManager>(),
        make_unique<ComputerBattleCommunication>(
            make_unique<ShipManager>(), 
            make_unique<ComputerShipArrangement>()),
        make_unique<ConsoleCellReader>());

    auto mapObserver = make_unique<ConsoleMapObserver>(make_unique<Maps>());
    battleManager.subscribe(move(mapObserver));

    auto databaseService = make_unique<DatabaseService<Player>>();
    databaseService.get()->ensureDbCreated();

    auto statisticsObserver = make_unique<StatisticsObserver>(
        make_unique<StatisticsService>(move(databaseService)), "Super Bro"); // TODO: read nickname from file
    battleManager.subscribe(move(statisticsObserver));

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
    try
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
    }
    catch (const exception &ex)
    {
        auto msg = ex.what();
        cout << "Unexpected error happened: " << ex.what() << endl;
    }

    return 0;
}
