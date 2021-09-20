#ifndef BATTLESHIP_SRC_CORE_INCLUDE_IMAPPER_H
#define BATTLESHIP_SRC_CORE_INCLUDE_IMAPPER_H

#include <string>
#include "message-wrapper.h"
#include "game-start-params.h"
#include "cell.h"
#include "shoot-response.h"
#include "incoming-connection.h"

class IMapper
{
public:
    virtual MessageWrapper<GameStartParams> mapToGameStartParams(const std::string &t_message) const = 0;
    virtual MessageWrapper<Cell> mapToCell(const std::string &t_message) const = 0;
    virtual MessageWrapper<ShootResponse> mapToShootResponse(const std::string &t_message) const = 0;

    virtual std::string mapFromIncomingConnection(const IncomingConnection &t_incomingConnection) const = 0;
    virtual std::string mapFromCell(const MessageWrapper<Cell> &t_messageWrapper) const = 0;
    virtual std::string mapFromShootResponse(const MessageWrapper<ShootResponse> &t_messageWrapper) const = 0;
};

#endif
