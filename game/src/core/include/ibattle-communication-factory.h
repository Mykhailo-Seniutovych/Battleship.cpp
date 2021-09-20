#ifndef BATTLESHIP_SRC_CORE_INCLUDE_IBATTLE_COMMUNICATION_FACTORY_H
#define BATTLESHIP_SRC_CORE_INCLUDE_IBATTLE_COMMUNICATION_FACTORY_H

#include "ibattle-communication.h"
#include <memory>

class IBattleComunicationFactory
{
public:
    virtual std::shared_ptr<IBattleComunication> createBattleCommunication() = 0;
};

#endif
