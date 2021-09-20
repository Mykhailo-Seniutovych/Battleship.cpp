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

using namespace std;

void playGame()
{
    cout << "Establishing connection with another player..." << endl;

    auto battleManager = BattleManager(
        //make_unique<ConsoleShipArrangement>(),
        make_unique<ComputerShipArrangement>(),
        make_unique<ShipManager>(),
        // make_unique<ComputerBattleCommunicationFactory>(
        //    make_unique<ShipManager>(),
        //    make_unique<ComputerShipArrangement>()),
        make_unique<NetworkBattleCommunicationFactory>(
            make_unique<TcpClient>(),
            make_unique<Mapper>()),
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

// void testMapper1()
// {
//     auto mapper = Mapper();
//     auto res = mapper.mapToGameStartParams(
//         "{\"isError\": false, \"error\": \"aha no error\", \"message\": {\"initiateFirstShot\": true }}");

//     auto cellWrapper = MessageWrapper<Cell>{
//         .isError = false,
//         .error = "ololol",
//         .message = Cell(3, 4)};

//     auto msg = mapper.mapFromCell(cellWrapper);
//     auto entity = mapper.mapToCell(msg);
// }

// void testMapper2()
// {
//     auto mapper = Mapper();

//     auto shootResponse = ShootResponse();
//     shootResponse.cellState = CellState::GameOver;
//     shootResponse.sunkShipCoordinates = ShipCoordinates();
//     shootResponse.sunkShipCoordinates.position = Position::Vertical;
//     shootResponse.sunkShipCoordinates.axisCoordinate = 7;
//     shootResponse.sunkShipCoordinates.cellsCoordinates = {1, 2, 3, 4};

//     auto wrapper = MessageWrapper<ShootResponse>{
//         .isError = false,
//         .error = "ololol",
//         .message = shootResponse};

//     auto msg = mapper.mapFromShootResponse(wrapper);
//     auto entity = mapper.mapToShootResponse(msg);

//     for (auto t : entity.message.sunkShipCoordinates.cellsCoordinates)
//     {
//         cout << unsigned(t) << endl;
//     }
// }

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
        cerr << "Unexpected error happened: " << ex.what() << endl;
    }

    return 0;
}
