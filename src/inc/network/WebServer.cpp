#include "./WebServer.h"

AsyncWebServer server(80);

void handlePublicFiles(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", "Hello World");
}
void webserver_setup(AsyncWebSocket *ws)
{
    if (ws == nullptr)
    {
        Serial.println("❌ WebSocket-Handler ist NULL!");
        return;
    }

    Serial.println("✅ Webserver wird gestartet...");
    server.addHandler(ws);

    server.on("/*", HTTP_GET, handlePublicFiles);

    server.begin();
    Serial.println("✅ Webserver erfolgreich gestartet!");

    Serial.println("🚀 Warte auf eingehende Verbindungen...");

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        Serial.println("🔌 Neue HTTP-Anfrage empfangen!");
        request->send(200, "text/plain", "ESP32 Webserver läuft!"); });
}
