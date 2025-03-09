#include "./motor_config.h"

std::vector<MotorConfigItem> motorConfig;

void load_motor_config()
{

    JsonDocument config;
    if (!load_json_file("/config/motor.json", config))
    {
        return;
    }

    motorConfig.clear();
    for (size_t i = 0; i < config.size(); i++)
    {
        JsonObject obj = config[i].as<JsonObject>();
        if (obj.isNull())
        {
            Serial.print("⚠️ Fehler: Objekt an Index ");
            Serial.print(i);
            Serial.println(" ist NULL!");
            continue;
        }

        MotorConfigItem motor;
        motor.id = obj["id"];
        motor.name = obj["name"].as<String>();

        // Hex-Farbe als char-Array kopieren
        strlcpy(motor.colorCode, obj["colorCode"].as<const char *>(), sizeof(motor.colorCode));

        motor.rs285Addr = obj["rs285Addr"];
        motor.active = obj["active"];

        // PositionConfig
        motor.position.current = obj["position"]["current"];
        motor.position.min = obj["position"]["min"];
        motor.position.max = obj["position"]["max"];

        // SpeedConfig
        motor.speed.acceleration = obj["speed"]["acceleration"];
        motor.speed.maxRPM = obj["speed"]["maxRPM"];

        motor.stepsPerRotation = obj["stepsPerRotation"];
        motor.inverted = obj["inverted"];
        motor.lastCommand = obj["lastCommand"].isNull() ? "" : obj["lastCommand"].as<String>();

        // PinConfig
        motor.pins.step = obj["pins"]["step"].as<u_int>();
        motor.pins.dir = obj["pins"]["dir"].as<u_int>();
        motor.pins.enable = obj["pins"]["enable"].as<u_int>();

        // Motor zur Liste hinzufügen
        motorConfig.push_back(motor);
    }

    Serial.println("✅ motor.json erfolgreich geladen!");
}
