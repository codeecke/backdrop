#include "./init.h"

void sd_setup()
{
    if (!SD.begin(SD_CS_PIN, SPI, 1000000))
    {
        Serial.println("❌ Fehler: SD-Karte konnte nicht initialisiert werden!");
    }
    else
    {
        Serial.println("✅ SD-Karte erfolgreich initialisiert.");
    }
}