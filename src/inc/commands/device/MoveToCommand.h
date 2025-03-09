#ifndef MOVE_TO_COMMAND_H
#define MOVE_TO_COMMAND_H

#include <Arduino.h>
#include "./AbstractCommand.h"
#include "../../motor/Motor.h"
#include "../../commands/client/MotorConfigurationCommand.h"
#include "../../network/WebSocketServer.h"

struct MoveToCommandPayload
{
    int position;
    u_int motorId;
};

class MoveToCommand : public AbstractCommand
{
public:
    MoveToCommand();
    bool fromJson(JsonVariant json, MoveToCommandPayload &payload);
    void execute(AsyncWebSocketClient *clientConnection, JsonVariant payload);
};

#endif