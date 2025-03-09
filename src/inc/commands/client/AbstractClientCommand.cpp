#include "./AbstractClientCommand.h"

AbstractClientCommand::AbstractClientCommand(/* args */)
{
}

void AbstractClientCommand::send(AsyncWebSocketClient &client)
{

    JsonDocument doc = this->toJson();
    String json;
    serializeJson(doc, json);

    client.text(json);
};

void AbstractClientCommand::broadcast(AsyncWebSocket &server)
{

    JsonDocument doc = this->toJson();
    String json;
    serializeJson(doc, json);

    server.textAll(json);
}