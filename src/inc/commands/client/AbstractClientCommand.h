#ifndef ABSTRACT_CLIENT_COMMAND_H
#define ABSTRACT_CLIENT_COMMAND_H

#include <AsyncWebSocket.h>
#include <ArduinoJson.h>

class AbstractClientCommand
{
private:
    /* data */
public:
    AbstractClientCommand(/* args */);
    virtual JsonDocument toJson() = 0;
    void send(AsyncWebSocketClient &client);
    void broadcast(AsyncWebSocket &server);
};

#endif