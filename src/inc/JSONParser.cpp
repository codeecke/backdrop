#include <ArduinoJson.h>
#include <iostream>
#include <stdexcept>
#include "JSONParser.h"

WebSocketCommand JSONParser::parseWebSocketCommand(String json)
{
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, json);
    if (error)
    {
        throw std::runtime_error("invalid json");
    }
    u_int motorId = doc["motorId"];
    String command = doc["command"];
    JsonVariant payload = doc["payload"];
    WebSocketCommand result(motorId, command, payload);
    return result;
}
