#ifndef STOP_COMMAND_H
#define STOP_COMMAND_H

#include <Arduino.h>
#include "./AbstractCommand.h"
#include "../../motor/Motor.h"
#include "../../commands/client/MotorConfigurationCommand.h"
#include "../../network/WebSocketServer.h"

struct StopCommandPayload
{
    u_int motorId;
};

class StopCommand : public AbstractCommand
{
public:
    StopCommand();
    bool fromJson(JsonVariant json, StopCommandPayload &payload);
    void execute(AsyncWebSocketClient *clientConnection, JsonVariant payload);
};

#endif