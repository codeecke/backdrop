#include "./PositionUpdateEvent.h"

PositionUpdateEvent::PositionUpdateEvent(u_int motorId, int position) : motorId(motorId), payload(position)
{
}

String PositionUpdateEvent::toString()
{
    JsonDocument doc; // Nutzt die neue Empfehlung ohne veraltete Warnung
    String result;

    doc["motorId"] = this->motorId;
    doc["payload"] = this->payload;
    doc["eventName"] = this->eventName;

    serializeJson(doc, result);

    Serial.printf("Event to send: %s\n", result);

    return result;
}
void PositionUpdateEvent::send(AsyncWebSocket *ws)
{
    ws->textAll(this->toString());
}