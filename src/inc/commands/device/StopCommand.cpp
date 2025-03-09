#include "./StopCommand.h"

StopCommand::StopCommand()
{
    Serial.println("Stop command found");
}

bool StopCommand::fromJson(JsonVariant json, StopCommandPayload &payload)
{
    if (!json["motorId"].is<u_int>())
    {
        Serial.println("MotorID is missing in StopCommand");
        return false;
    }
    payload.motorId = json["motorId"].as<u_int>();
    return true;
}

void StopCommand::execute(AsyncWebSocketClient *clientConnection, JsonVariant payload)
{
    StopCommandPayload payloadData;
    if (!fromJson(payload, payloadData))
        return;

    u_int motorId = payloadData.motorId;
    if (!check_motor_id(motorId))
    {
        Serial.println("Invalid MotorID in StopCommand");
        return;
    }

    Serial.println("Stop command executed");
    stepper[motorId]->forceStop();
    MotorConfigurationCommand client;
    client.broadcast(ws);
    Serial.printf("Current Position: %d\n", stepper[motorId]->getCurrentPosition());
}