#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <Arduino.h>
#include "./AbstractCommand.h"
#include "../../motor/Motor.h"
#include "../../commands/client/MotorConfigurationCommand.h"
#include "../../network/WebSocketServer.h"

struct MoveCommandPayload
{
    String direction;
    u_int motorId;
};

class MoveCommand : public AbstractCommand
{
public:
    MoveCommand();
    bool fromJson(JsonVariant json, MoveCommandPayload &payload);
    void execute(AsyncWebSocketClient *clientConnection, JsonVariant payload);
};

#endif