#include "./MoveCommand.h"

MoveCommand::MoveCommand()
{
    Serial.println("Up command found");
}

bool MoveCommand::fromJson(JsonVariant json, MoveCommandPayload &payload)
{
    if (!json["motorId"].is<u_int>() || !json["direction"].is<String>())
    {
        Serial.println("Fehlende Werte in der Payload vom MoveCommand");
        return false;
    }
    payload.direction = json["direction"].as<String>();
    payload.motorId = json["motorId"].as<u_int>();
    return true;
}

void MoveCommand::execute(AsyncWebSocketClient *clientConnection, JsonVariant payload)
{
    MoveCommandPayload payloadData;
    if (!fromJson(payload, payloadData))
        return;

    u_int motorId = payloadData.motorId;
    if (!check_motor_id(motorId))
    {
        Serial.println("Invalid MotorID in MoveCommand");
        return;
    }
    Serial.println("Move command executed");
    Serial.printf("Move Motor %d %swards\n", payloadData.motorId, payloadData.direction);

    int target = payloadData.direction == "up" ? -1e6 : 1e6;

    stepper[0]->setAcceleration(1e6);
    stepper[0]->setSpeedInHz(1e4);
    stepper[0]->move(target);

    MotorConfigurationCommand client;
    client.broadcast(ws);
}