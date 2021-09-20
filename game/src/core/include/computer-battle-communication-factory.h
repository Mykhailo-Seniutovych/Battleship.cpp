#ifndef BATTLESHIP_SRC_CORE_INCLUDE_COMPUTER_BATTLE_COMMUNICATION_FACTORY_H
#define BATTLESHIP_SRC_CORE_INCLUDE_COMPUTER_BATTLE_COMMUNICATION_FACTORY_H

#include "ibattle-communication-factory.h"
#include "iship-manager.h"
#include "iship-arrangement.h"

class ComputerBattleCommunicationFactory : public IBattleComunicationFactory
{
public:
    ComputerBattleCommunicationFactory(
        std::unique_ptr<IShipManager> t_computerShipManager,
        std::unique_ptr<IShipArrangement> t_computerShipArrangement);
    std::shared_ptr<IBattleComunication> createBattleCommunication() override;

private:
    std::unique_ptr<IShipManager> m_computerShipManager;
    std::unique_ptr<IShipArrangement> m_computerShipArrangement;
};


#endif
