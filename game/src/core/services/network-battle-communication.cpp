#include <iostream>
#include "network-battle-communication.h"
#include <string>

using namespace std;

NetworkBattleCommunication::NetworkBattleCommunication(
    unique_ptr<ITcpClient> t_tcpClient) : m_tcpClient(move(t_tcpClient))
{
}

NetworkBattleCommunication::~NetworkBattleCommunication()
{
    m_tcpClient.get()->closeConnection();
}

void NetworkBattleCommunication::establishNetworkConnection() const
{
    m_tcpClient.get()->establishConnection(
        "{ \"PlayerNickname\": \"Dawg\", \"OpponentNickname\": \"ZalBoy\", \"PassCode\": \"123\"}\0");
}

GameStartParams NetworkBattleCommunication::receiveGameStartParams() const
{
    auto message = m_tcpClient.get()->readNextMessage();
    cout << "established connection: " << message << endl;

    return GameStartParams{.initiateFirstShot = true};
}

Cell NetworkBattleCommunication::getNextShotTarget() const
{
    auto message = m_tcpClient.get()->readNextMessage();

    cout << "received target: " << message << endl;
    return Cell(1, 2);
}

void NetworkBattleCommunication::notifyShotResponse(const ShootResponse &shootResponse)
{
    m_tcpClient.get()->sendMessage("Dawg, you got me");
};

ShootResponse NetworkBattleCommunication::sendShotTo(const Cell &cell)
{
    auto message = "Dawg, I am shooting at " + to_string(cell.horCoord) + " " + to_string(cell.verCoord);
    m_tcpClient.get()->sendMessage(message);
    auto receivedMsg = m_tcpClient.get()->readNextMessage();
    cout << "received shoot response: " << receivedMsg << endl;

    return ShootResponse(CellState::Miss);
}
