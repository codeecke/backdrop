#include "./MotorRunningEvent.h"

MotorRunningEvent::MotorRunningEvent(u_int motorId, MotorRunningEventPayload payload) : motorId(motorId), payload(payload)
{
}

String MotorRunningEvent::toString()
{
    JsonDocument doc; // Nutzt die neue Empfehlung ohne veraltete Warnung
    String result;

    doc["motorId"] = this->motorId;
    doc["eventName"] = this->eventName;

    JsonObject payloadObj = doc["payload"].to<JsonObject>(); // Neuer Syntax für verschachtelte Objekte
    payloadObj["direction"] = this->payload.direction;
    payloadObj["running"] = this->payload.running;

    serializeJson(doc, result);

    Serial.printf("Event to send: %s\n", result);

    return result;
}
void MotorRunningEvent::send(AsyncWebSocket *ws)
{
    Serial.println(this->toString());
    ws->textAll(this->toString());
}