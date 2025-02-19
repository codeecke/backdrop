#include "./Webserver.h"

// Erstelle einen Webserver auf Port 80
AsyncWebServer server(80);

// WebSocket-Handler
AsyncWebSocket ws("/ws");

struct TUpdatePayload
{
    int motor;
    int position;
};

struct TUpdateEvent
{
    String eventName;
    TUpdatePayload payload;
};

void onWebSocketMessage(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_DATA)
    {
        String json = String((char *)data);
        commandRegistry.execute(json, client);
        return;
    }
    if (type == WS_EVT_CONNECT)
    {

        Serial.println("Client verbunden");

        JsonDocument doc;
        doc["eventName"] = "POSITION_INIT";

        // JSON-Struktur manuell erstellen
        doc["payload"]["motor"] = 1;                           // Beispielwert
        doc["payload"]["position"] = motor1.currentPosition(); // Beispielwert

        String jsonString;
        if (serializeJson(doc, jsonString) == 0)
        {
            Serial.println("Fehler beim Serialisieren des JSON");
            return;
        }

        if (client->status() == WS_CONNECTED)
        {
            // client->text(jsonString);
            Serial.println("JSON gesendet:");
            Serial.println(jsonString);
        }
        else
        {
            Serial.println("Client nicht verbunden");
        }
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        Serial.println("Client getrennt");
    }
}

void broadcastEvent(const TUpdateEvent &event)
{
    JsonDocument doc; // Größe je nach Bedarf anpassen
    doc["eventName"] = event.eventName;

    if (event.eventName == "POSITION_UPDATE")
    {
        doc["payload"]["motor"] = event.payload.motor;
        doc["payload"]["position"] = event.payload.position;
    }
    String jsonString;
    if (serializeJson(doc, jsonString) == 0)
    {
        Serial.println("Fehler beim Serialisieren des JSON");
        return;
    }
    // Serial.println(jsonString);
    ws.textAll(jsonString);
}

void handleFileStream(AsyncWebServerRequest *request)
{
    // Datei auf der SD-Karte öffnen
    File file = SD.open("/public/assets/index-GoixtU-n.css");

    if (!file)
    {
        // Wenn die Datei nicht gefunden wurde, sende 404
        request->send(404, "text/plain", "Datei nicht gefunden");
        return;
    }

    // Bestimme den MIME-Typ basierend auf der Datei
    String contentType = "text/css"; // Hier für eine CSS-Datei

    // Sende die Datei
    request->send(file, contentType);

    // Datei wird automatisch nach der Übertragung geschlossen
}

void handlePublicFiles(AsyncWebServerRequest *request)
{
    Serial.println("Anfrage empfangen");
    String path = request->url(); // Hole den Pfad von der Anfrage
    // Entferne den führenden Slash, um die Datei direkt im public-Ordner zu finden
    if (path == "/")
    {
        path = "/index.html"; // Beispiel, um eine Standarddatei wie index.html zu laden, falls keine Datei angegeben wird
    }

    Serial.print("Anfrage für Datei: ");
    Serial.println(path);

    // Überprüfe, ob der Pfad korrekt für den Zugriff auf den public-Ordner umgeschrieben wurde
    String fullPath = "/public" + path;
    Serial.print("Vollständiger Pfad: ");
    Serial.println(fullPath);

    // Öffne die Datei im 'public'-Ordner
    File file = SD.open(fullPath); // Zugriff auf den öffentlichen Ordner

    if (!file)
    {
        // Wenn die Datei nicht gefunden wurde, sende 404
        Serial.println("Fehler: Datei nicht gefunden");
        request->send(404, "text/plain", "Datei nicht gefunden");
        return;
    }

    // Bestimme den Dateityp basierend auf der Erweiterung
    String contentType = "text/plain"; // Standardwert

    if (path.endsWith(".html"))
    {
        contentType = "text/html";
    }
    else if (path.endsWith(".css"))
    {
        contentType = "text/css";
    }
    else if (path.endsWith(".js"))
    {
        contentType = "application/javascript";
    }
    else if (path.endsWith(".jpg"))
    {
        contentType = "image/jpeg";
    }
    else if (path.endsWith(".png"))
    {
        contentType = "image/png";
    }

    size_t fileSize = file.size();

    Serial.printf("Content-Type: %s\n", contentType);

    // Sende die Datei zurück an den Client
    // request->send(file, path, contentType);

    request->send(file, path, contentType);

    // file.close(); // Schließe die Datei nach dem Senden
}

void ws_setup()
{
    /*
    SPI.begin(18, 19, 23, 5); // Manuelle Zuweisung der SPI-Pins (SCK, MISO, MOSI, CS)
    if (!SD.begin(5))
    { // Initialisiere die SD-Karte
        Serial.println("SD-Karteninitialisierung fehlgeschlagen!");
        return;
    }
    Serial.println("SD-Karte initialisiert");
    */

    ws.onEvent(onWebSocketMessage);
    server.addHandler(&ws);
    // server.on("/*", HTTP_GET, handlePublicFiles);
    server.begin();
    Serial.println("WebSocket-Server gestartet!");
}

int lastMotor1Value = -9999999;

void ws_loop()
{
    static unsigned long lastPrintTime = 0;

    int newMotor1Value = motor1.currentPosition();
    unsigned long currentTime = millis();
    return;
    if (newMotor1Value != lastMotor1Value && currentTime - lastPrintTime >= 500)
    {
        TUpdateEvent event = {
            .eventName = "POSITION_UPDATE",
            .payload = {
                .motor = 1,
                .position = newMotor1Value}};

        broadcastEvent(event);
        lastMotor1Value = newMotor1Value;
        lastPrintTime = currentTime;
        // Serial.printf("New Motor1: %d\n", newMotor1Value);
    }
}
