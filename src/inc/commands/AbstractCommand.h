#ifndef AbstractCommand_h
#define AbstractCommand_h

#include <any>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <iostream>

class AbstractCommand
{
public:
    virtual u_int getMotorId();
    virtual String getName();
    virtual void execute(AsyncWebSocketClient *clientConnection, JsonVariant payload = JsonVariant());
};

#endif
