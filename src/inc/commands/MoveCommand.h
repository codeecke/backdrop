#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include "./AbstractCommand.h"
#include "../Motor.h"
#include <AsyncWebSocket.h>

struct MoveCommandPayload
{
    String direction;
};

class MoveCommand : public AbstractCommand
{
private:
    Motor *motor;

public:
    MoveCommand(Motor *motor);
    u_int getMotorId();
    String getName();
    void execute(AsyncWebSocketClient *clientConnection, JsonVariant payload);
};

#endif