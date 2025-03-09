#include "./MotorConfigurationCommand.h"

MotorConfigurationCommand::MotorConfigurationCommand() {}

JsonDocument MotorConfigurationCommand::toJson()
{
    JsonDocument doc;

    doc["command"] = "motorConfiguration";
    JsonArray payload = doc["payload"].to<JsonArray>();

    for (const auto &motor : motorConfig)
    {
        if (!motor.active)
            continue;
        JsonObject obj = payload.add<JsonObject>();

        int pin = stepper[motor.id]->getDirectionPin();
        delay(100);

        obj["motorId"] = motor.id;
        obj["name"] = motor.name;
        obj["isRunning"] = stepper[motor.id]->isRunning();
        obj["direction"] = digitalRead(pin) ? "up" : "down";
        obj["colorCode"] = motor.colorCode;
    }

    return doc;
}