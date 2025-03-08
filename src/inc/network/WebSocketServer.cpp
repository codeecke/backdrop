#include "./WebSocketServer.h"

AsyncWebSocket ws("/ws");

void onWebSocketMessage(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_DATA)
    {
        String json = String((char *)data, len);

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, json);
        if (error)
        {
            throw std::runtime_error("invalid json");
        }
        u_int motorId = doc["motorId"];
        String commandName = doc["command"];
        JsonVariant payload = doc["payload"];

        std::unique_ptr<AbstractCommand> command = CommandFactory::getInstance().createCommand(std::string(commandName.c_str()));

        if (command == nullptr)
        {
            Serial.printf("Command not found: %s\n", commandName.c_str());
            return;
        }
        Serial.printf("Command found: %s\n", commandName.c_str());
        command->execute(client, payload);
        return;
    }
    if (type == WS_EVT_CONNECT)
    {

        if (client->status() == WS_CONNECTED)
        {
            Serial.println("Client verbunden");
        }
        else
        {
            Serial.println("Client nicht verbunden");
        }
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Serial.println("Client getrennt");
    }
}

AsyncWebSocket *websocket_setup()
{
    ws.onEvent(onWebSocketMessage);
    return &ws;
}