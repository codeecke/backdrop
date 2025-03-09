#ifndef ABSTRACT_COMMAND_H
#define ABSTRACT_COMMAND_H

#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

class AbstractCommand
{
public:
    virtual ~AbstractCommand() = default;
    virtual void execute(AsyncWebSocketClient *clientConnection, JsonVariant payload) = 0;
};

#endif
