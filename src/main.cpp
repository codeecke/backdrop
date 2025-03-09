#include "./inc/commands/CommandFactory.h"
#include "./inc/network/wifi.h"
#include "./inc/network/WebServer.h"
#include "./inc/network/WebSocketServer.h"
#include "./inc/motor/Motor.h"
#include "./inc/sd/motor_config.h"
#include "./inc/sd/positions.h"

#define CS_PIN 5

void setup()
{
    Serial.begin(115200);

    if (!SD.begin(CS_PIN, SPI, 1000000))
    {
        Serial.println("❌ Fehler: SD-Karte konnte nicht initialisiert werden!");
        return;
    }

    Serial.println("✅ SD-Karte erfolgreich initialisiert.");

    load_motor_config();
    load_positions();

    motor_setup();

    CommandFactory::getInstance().setupCommands();
    wifi_setup();
    AsyncWebSocket *ws = websocket_setup();
    if (ws == nullptr)
    {
        Serial.println("❌ WebSocket konnte nicht initialisiert werden!");
    }
    else
    {
        Serial.println("✅ WebSocket erfolgreich initialisiert!");
        webserver_setup(ws);
    }
}

void loop()
{
    ws.cleanupClients();
}
