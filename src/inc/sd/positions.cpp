#include "./positions.h"

#include <vector>

std::vector<Position> positions;

void load_positions()
{
    JsonDocument config;
    if (!load_json_file("/config/positions.json", config))
    {
        return;
    }

    positions.clear();
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

        Position position;
        position.motorId = obj["motorID"].as<u_int>();
        position.name = obj["name"].as<String>();
        position.position = obj["position"].as<float>();

        positions.push_back(position);
    }
}

void convert_positions_to_json(JsonDocument &doc)
{
    JsonArray array = doc.to<JsonArray>(); // Erstelle ein JSON-Array im Dokument

    for (const auto &pos : positions)
    {
        JsonObject obj = array.add<JsonObject>(); // Neues Objekt im Array hinzufügen
        obj["motorID"] = pos.motorId;
        obj["name"] = pos.name;
        obj["position"] = pos.position;
    }
}

bool save_positions()
{
    JsonDocument doc;

    convert_positions_to_json(doc);
    return save_json_file("/config/positions.json", doc);
}