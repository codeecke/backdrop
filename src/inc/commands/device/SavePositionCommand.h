#ifndef SAVE_POSITION_COMMAND_H
#define SAVE_POSITION_COMMAND_H

#include <Arduino.h>
#include "./AbstractCommand.h"
#include "../../motor/Motor.h"
#include "../../sd/positions.h"
#include "../../network/WebSocketServer.h"
#include "../client/PositionListCommand.h"

struct SavePositionCommandPayload
{
    u_int motorId;
    String name;
};

class SavePositionCommand : public AbstractCommand
{
public:
    SavePositionCommand();
    bool fromJson(JsonVariant json, SavePositionCommandPayload &payload);
    void execute(AsyncWebSocketClient *clientConnection, JsonVariant payload);
};

#endif