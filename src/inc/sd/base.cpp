#include <ArduinoJson.h>
#include <SD.h>

#define CS_PIN 5

bool load_json_file(String path, JsonDocument &json)
{

    File file = SD.open(path, "r");

    if (!file)
    {
        Serial.printf("❌ Fehler: %s nicht gefunden!\n", path);
        return false;
    }

    DeserializationError error = deserializeJson(json, file);
    file.close();

    if (error)
    {
        Serial.print("❌ Fehler beim Parsen der JSON-Datei: ");
        Serial.println(error.c_str());
        return false;
    }
    return true;
}

bool save_json_file(String path, JsonDocument &json)
{
    File file = SD.open(path, "w");

    if (!file)
    {
        Serial.printf("❌ Fehler: %s konnte nicht geöffnet werden!\n", path);
        return false;
    }

    serializeJsonPretty(json, file);
    file.close();
    return true;
}