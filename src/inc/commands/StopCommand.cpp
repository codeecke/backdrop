#include "../Motor.h"
#include "AbstractCommand.h"
#include "StopCommand.h"

StopCommand::StopCommand(Motor *motor) : motor(motor) {}

u_int StopCommand::getMotorId()
{
    return this->motor->getId();
};

String StopCommand::getName()
{
    return "stop";
};

void StopCommand::execute(AsyncWebSocketClient *clientConnection, JsonVariant payload)
{
    this->motor->stop();
};