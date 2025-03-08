#include "./wifi.h"

void wifi_setup()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n✅ Verbunden!");
    Serial.print("🌍 ESP32-IP: ");
    Serial.println(WiFi.localIP());
}