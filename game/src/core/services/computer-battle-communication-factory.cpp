#include "computer-battle-communication-factory.h"
#include "computer-battle-communication.h"

using namespace std;

ComputerBattleCommunicationFactory::ComputerBattleCommunicationFactory(
    std::unique_ptr<IShipManager> t_computerShipManager,
    std::unique_ptr<IShipArrangement> t_computerShipArrangement)
    : m_computerShipManager(move(t_computerShipManager)), m_computerShipArrangement(move(t_computerShipArrangement))
{
}

shared_ptr<IBattleComunication> ComputerBattleCommunicationFactory::createBattleCommunication()
{
    return make_shared<ComputerBattleCommunication>(
        move(m_computerShipManager),
        move(m_computerShipArrangement));
}
