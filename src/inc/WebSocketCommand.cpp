#include "WebSocketCommand.h"

WebSocketCommand::WebSocketCommand(u_int motorId, String command, JsonVariant payload) : motorId(motorId), command(command), payload(payload)
{
}

u_int WebSocketCommand::getMotorId()
{
    return this->motorId;
}

String WebSocketCommand::getCommand()
{
    return this->command;
}

JsonVariant WebSocketCommand::getPayload()
{
    return this->payload;
}