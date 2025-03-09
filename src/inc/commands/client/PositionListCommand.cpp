#include "./PositionListCommand.h"

PositionListCommand::PositionListCommand() {}

JsonDocument PositionListCommand::toJson()
{
    JsonDocument doc;

    doc["command"] = "positionList";
    JsonArray payload = doc["payload"].to<JsonArray>();

    for (const auto &pos : positions)
    {
        JsonObject obj = payload.add<JsonObject>();

        obj["motorId"] = pos.motorId;
        obj["name"] = pos.name;
        obj["position"] = pos.position;
    }

    return doc;
}