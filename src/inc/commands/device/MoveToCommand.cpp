#include "./MoveToCommand.h"

MoveToCommand::MoveToCommand()
{
    Serial.println("Up command found");
}

bool MoveToCommand::fromJson(JsonVariant json, MoveToCommandPayload &payload)
{
    if (!json["motorId"].is<u_int>() || !json["position"].is<int>())
    {
        Serial.println("Fehlende Werte in der Payload vom MoveToCommand");
        return false;
    }
    payload.position = json["position"].as<int>();
    payload.motorId = json["motorId"].as<u_int>();
    return true;
}

void MoveToCommand::execute(AsyncWebSocketClient *clientConnection, JsonVariant payload)
{
    MoveToCommandPayload payloadData;
    if (!fromJson(payload, payloadData))
        return;

    u_int motorId = payloadData.motorId;
    if (!check_motor_id(motorId))
    {
        Serial.println("Invalid MotorID in MoveToCommand");
        return;
    }
    Serial.println("Move command executed");
    Serial.printf("Move Motor %d to position %d\n", payloadData.motorId, payloadData.position);

    stepper[0]->setAcceleration(1e4);
    stepper[0]->setSpeedInHz(5e4);
    stepper[0]->moveTo(payloadData.position);

    MotorConfigurationCommand client;
    client.broadcast(ws);
}