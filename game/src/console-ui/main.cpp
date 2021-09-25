#include <memory>
#include <cstdint>
#include <string>
#include <exception>
#include <iostream>

#include "ship-manager.h"
#include "battle-manager.h"
#include "statistics-service.h"
#include "database-service.h"
#include "computer-battle-communication-factory.h"
#include "network-battle-communication-factory.h"
#include "network-battle-communication.h"
#include "tcp-client.h"
#include "services/console-ship-arrangement.h"
#include "computer-ship-arrangement.h"
#include "services/console-map-observer.h"
#include "services/statistics-observer.h"
#include "services/console-cell-reader.h"
#include "ui/maps.h"
#include "database-service.h"
#include "ui/statistics-ui.h"
#include "mapper.h"
#include "message-wrapper.h"
#include "app-config.h"
#include "validation-exception.h"
#include "models/play-mode.h"

using namespace std;

PlayMode readPlayMode()
{
    cout << "Do you want to play with the computer or another player "
            "(type 'c' for computer or 'p' for another player)?"
         << endl;
    string playMode;
    getline(cin, playMode);
    if (playMode != "c" && playMode != "p")
    {
        cout << "Option '" << playMode << "' is invalid." << endl;
        return readPlayMode();
    }

    return playMode == "c" ? PlayMode::Computer : PlayMode::AnotherPlayer;
}

string readOpponentNickname()
{
    cout << "Type the name of the player you wanna play with "
            "(if you don't care who to play with leave it empty and press Enter)"
         << endl;
    string opponentNickname;
    getline(cin, opponentNickname);

    return opponentNickname;
}

BattleManager createBattleManager(PlayMode t_playMode, shared_ptr<IAppConfig> t_appConfig)
{
    if (t_playMode == PlayMode::Computer)
    {
        return BattleManager(
            make_unique<ConsoleShipArrangement>(),
            make_unique<ShipManager>(),
            make_unique<ComputerBattleCommunicationFactory>(
                make_unique<ShipManager>(),
                make_unique<ConsoleShipArrangement>()),
            make_unique<ConsoleCellReader>());
    }
    else
    {
        auto opponentNickname = readOpponentNickname();

        return BattleManager(
            make_unique<ConsoleShipArrangement>(),
            make_unique<ShipManager>(),
            make_unique<NetworkBattleCommunicationFactory>(
                make_unique<TcpClient>(t_appConfig),
                make_unique<Mapper>(),
                t_appConfig,
                opponentNickname),
            make_unique<ConsoleCellReader>());
    }
}

void playGame()
{
    auto playMode = readPlayMode();

    auto appConfig = make_shared<AppConfig>();
    appConfig.get()->initialize();

    auto battleManager = createBattleManager(playMode, appConfig);

    auto mapObserver = make_unique<ConsoleMapObserver>(make_unique<Maps>());
    battleManager.subscribe(move(mapObserver));

    auto databaseService = make_unique<DatabaseService<Player>>();
    databaseService.get()->ensureDbCreated();

    auto statisticsObserver = make_unique<StatisticsObserver>(
        make_unique<StatisticsService>(move(databaseService)),
        appConfig.get()->getNickname());
    battleManager.subscribe(move(statisticsObserver));

    if (playMode == PlayMode::AnotherPlayer)
    {
        cout << "Establishing connection with another player..." << endl;
    }
    battleManager.playBattle();
}

void showStatistics(bool showBest)
{
    auto databaseService = make_unique<DatabaseService<Player>>();
    databaseService.get()->ensureDbCreated();
    StatisticsUi statisticsUi(
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
    try
    {
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
            }

            if (string(argv[index]) == "--set-nickname")
            {
                startGame = false;
                auto nicknameIndex = index + 1;
                if (nicknameIndex < argc)
                {
                    auto appConfig = make_shared<AppConfig>();
                    appConfig.get()->initialize();
                    appConfig.get()->setNickname(argv[nicknameIndex]);
                }
                else
                {
                    cout << "Provide value for nickname." << endl;
                }
            }

            if (string(argv[index]) == "--help")
            {
                startGame = false;
                cout << "Command line options:" << endl
                     << left << setw(35) << "--stats-best"
                     << "Display statistics of best players" << endl
                     << left << setw(35) << "--stats-worst"
                     << "Display statistics of worst players" << endl
                     << left << setw(35) << "--set-nickname {new nickname}"
                     << "Set a new nickname" << endl
                     << endl;
            }
        }

        if (startGame)
        {
            playGame();
        }
    }
    catch (const exception &ex)
    {
        cerr << "Unexpected error happened: " << ex.what() << endl;
    }

    if (startGame)
    {
        cout << "Press 'Enter' to exit" << endl;
        cin.get();
    }

    return 0;
}
