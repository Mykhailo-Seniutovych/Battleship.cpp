#include <memory>
#include <iostream>
#include <iomanip>
#include <ios>
#include <functional>
#include "sqlite3.h"
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
#include "exception"
#include "sql-exception.h"

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

void showStatistics()
{
    try
    {
        const uint32_t count = 10;

        auto databaseService = make_unique<DatabaseService<Player>>();
        databaseService.get()->ensureDbCreated();
        auto statisticsService = StatisticsService(move(databaseService));
        auto players = statisticsService.getTopBestPlayers(count);

        cout << left
             << setw(20) << "Nickname"
             << setw(11) << "Games Won"
             << setw(12) << "Games Lost"
             << setw(6) << "Score"
             << endl;
        for (auto player : players)
        {
            cout << left
                 << setw(20) << player.nickname
                 << setw(11) << player.gamesWon
                 << setw(12) << player.gamesLost
                 << setw(6) << player.getScore()
                 << endl;
        };
        cout << endl;
    }
    catch (const exception &ex)
    {
        cout << "Unexpected error happened: " << ex.what() << endl;
    }
}

int main()
{
    showStatistics();
    //playGame();
    return 0;
}
