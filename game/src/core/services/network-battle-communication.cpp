#include <iostream>
#include "network-battle-communication.h"
#include <string>

using namespace std;

static int shotCounter = 0; // delete after real implementation is done

NetworkBattleCommunication::NetworkBattleCommunication(
    unique_ptr<ITcpClient> t_tcpClient) : m_tcpClient(move(t_tcpClient))
{
}

Cell NetworkBattleCommunication::getNextShotTarget() const
{
    // TODO: Add real implementation
    m_tcpClient.get()->establishConnection(
        "{ \"PlayerNickname\": \"ZalBoy\", \"OpponentNickname\": \"Dawg\", \"PassCode\": \"123\"}\0");
    auto message = m_tcpClient.get()->readNextMessage();

    cout << "received: " << message << endl;
    return Cell(1, 2);
}

void NetworkBattleCommunication::notifyShotResponse(const ShootResponse &shootResponse)
{
    auto message = m_tcpClient.get()->readNextMessage();
};

ShootResponse NetworkBattleCommunication::sendShotTo(const Cell &cell)
{
    auto message = "Dawg, I am shooting at " + to_string(cell.horCoord) + " " + to_string(cell.verCoord);
    m_tcpClient.get()->sendMessage(message);
    
    return ShootResponse(CellState::Miss);
}
