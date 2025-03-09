#include "./SavePositionCommand.h"

SavePositionCommand::SavePositionCommand()
{
    Serial.println("SavePosition command found");
}

bool SavePositionCommand::fromJson(JsonVariant json, SavePositionCommandPayload &payload)
{
    if (!json["motorId"].is<u_int>() || !json["name"].is<String>())
    {
        Serial.println("Fehlende Werte in der Payload vom SavePositionCommand");
        return false;
    }
    payload.motorId = json["motorId"].as<u_int>();
    payload.name = json["name"].as<String>();
    return true;
}

void SavePositionCommand::execute(AsyncWebSocketClient *clientConnection, JsonVariant payload)
{
    SavePositionCommandPayload payloadData;
    if (!fromJson(payload, payloadData))
        return;

    u_int motorId = payloadData.motorId;
    String name = payloadData.name;

    if (!check_motor_id(motorId))
    {
        Serial.println("❌ Invalid MotorID in SavePositionCommand");
        return;
    }

    Position newPosition;
    newPosition.motorID = motorId;
    newPosition.name = name;
    newPosition.position = stepper[motorId]->getCurrentPosition();

    positions.push_back(newPosition);
    save_positions();

    Serial.println("✅ SavePosition command executed");
}