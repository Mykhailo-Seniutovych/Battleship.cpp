#ifndef BATTLESHIP_SRC_CORE_INCLUDE_MAPPER_H
#define BATTLESHIP_SRC_CORE_INCLUDE_MAPPER_H

#include <vector>
#include <unordered_set>
#include "imapper.h"
#include "json.hpp"
#include "functional"
#include "game-start-params.h"

class Mapper : public IMapper
{
public:
    MessageWrapper<GameStartParams> mapToGameStartParams(const std::string &t_message) const override
    {
        std::function<GameStartParams(nlohmann::json &)> mapper = [](nlohmann::json &json)
        {
            GameStartParams params;
            params.initiateFirstShot = json["initiateFirstShot"];
            return params;
        };

        return mapToMessage(t_message, mapper);
    }

    MessageWrapper<Cell> mapToCell(const std::string &t_message) const override
    {
        std::function<Cell(nlohmann::json &)> mapper = [](nlohmann::json &json)
        {
            Cell cell;
            cell.horCoord = json["horCoord"];
            cell.verCoord = json["verCoord"];
            return cell;
        };

        return mapToMessage(t_message, mapper);
    }

    MessageWrapper<ShootResponse> mapToShootResponse(const std::string &t_message) const override
    {
        std::function<ShootResponse(nlohmann::json &)> mapper = [](nlohmann::json &json)
        {
            ShootResponse response;
            response.cellState = json["cellState"];
            if (json.count("sunkShipCoordinates"))
            {
                response.sunkShipCoordinates.axisCoordinate = json["sunkShipCoordinates"]["axisCoordinate"];

                std::vector<uint8_t> coordinates = json["sunkShipCoordinates"]["cellsCoordinates"];
                response.sunkShipCoordinates.cellsCoordinates =
                    std::unordered_set<uint8_t>(coordinates.begin(), coordinates.end());

                response.sunkShipCoordinates.position = json["sunkShipCoordinates"]["position"];
            }
            return response;
        };

        return mapToMessage(t_message, mapper);
    };

    std::string mapFromIncomingConnection(const IncomingConnection &t_incomingConnection) const override
    {
        nlohmann::json json;
        json["playerNickname"] = t_incomingConnection.playerNickname;
        json["opponentNickname"] = t_incomingConnection.opponentNickname;
        json["passcode"] = t_incomingConnection.passcode;
        return json.dump();
    }

    std::string mapFromCell(const MessageWrapper<Cell> &t_messageWrapper) const override
    {
        std::function<nlohmann::json(const Cell &)> mapper = [](const Cell &entity)
        {
            nlohmann::json json;
            json["horCoord"] = entity.horCoord;
            json["verCoord"] = entity.verCoord;
            return json;
        };

        return mapFromEntity(t_messageWrapper, mapper);
    }

    std::string mapFromShootResponse(const MessageWrapper<ShootResponse> &t_messageWrapper) const override
    {
        std::function<nlohmann::json(const ShootResponse &)> mapper = [](const ShootResponse &entity)
        {
            nlohmann::json json;
            json["cellState"] = entity.cellState;
            json["sunkShipCoordinates"]["axisCoordinate"] = entity.sunkShipCoordinates.axisCoordinate;
            json["sunkShipCoordinates"]["position"] = entity.sunkShipCoordinates.position;
            json["sunkShipCoordinates"]["cellsCoordinates"] = entity.sunkShipCoordinates.cellsCoordinates;
            return json;
        };

        return mapFromEntity(t_messageWrapper, mapper);
    }

private:
    template <typename T>
    MessageWrapper<T> mapToMessage(
        const std::string &t_message,
        std::function<T(nlohmann::json &)> t_msgMapper) const
    {
        nlohmann::json json = nlohmann::json::parse(t_message);

        MessageWrapper<T> result;
        result.isError = json["isError"];
        
        if (!json["error"].is_null())
        {
            result.error = json["error"];
        }

        if (json.count("message"))
        {
            result.message = t_msgMapper(json["message"]);
        }

        return result;
    };

    template <typename T>
    std::string mapFromEntity(
        const MessageWrapper<T> t_messageWrapper,
        std::function<nlohmann::json(const T &)> t_msgMapper) const
    {
        nlohmann::json json;
        json["isError"] = t_messageWrapper.isError;
        json["error"] = t_messageWrapper.error;
        json["message"] = t_msgMapper(t_messageWrapper.message);

        auto serialized = json.dump();
        return serialized;
    };
};
#endif
