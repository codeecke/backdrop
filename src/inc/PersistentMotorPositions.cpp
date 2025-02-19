#include "./PersistentMotorPositions.h"

PersistentMotorPositions::PersistentMotorPositions(Motor **motors)
{
    this->motors[0] = motors[0];
    this->motors[1] = motors[1];
}

void PersistentMotorPositions::save()
{
    JsonDocument doc;

    doc["motor1"] = this->motors[0]->currentPosition();
    doc["motor2"] = this->motors[1]->currentPosition();

    String output;
    serializeJson(doc, output);

    SD.begin(SD_CS);
    if (!SD.begin(SD_CS))
    {
        Serial.println("Fehler: SD-Karte konnte nicht initialisiert werden.");
        return;
    }
    File file = SD.open("/positions.json", FILE_WRITE);
    file.println(output);
    file.close();
}
void PersistentMotorPositions::load()
{
    SD.begin(SD_CS);
    if (!SD.begin(SD_CS))
    {
        Serial.println("Fehler: SD-Karte konnte nicht initialisiert werden.");
        return;
    }
    File file = SD.open("/test.txt");
    String json = "";
    while (file.available())
    {
        json = json + file.read();
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, json);
    if (error)
    {
        throw std::runtime_error("invalid json");
    }
    this->motors[0]->setCurrentPositon((long)doc["motor1"]);
    this->motors[1]->setCurrentPositon((long)doc["motor2"]);
}