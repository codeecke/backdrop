#ifndef POSITION_UPDATE_EVENT_H
#define POSITION_UPDATE_EVENT_H

#include <Arduino.h>

#include <AsyncWebSocket.h>
#include <ArduinoJson.h>

class PositionUpdateEvent
{
private:
public:
    u_int motorId;
    String eventName = "positionUpdate";
    int payload;

    PositionUpdateEvent(u_int motorId, int position);
    String toString();
    void send(AsyncWebSocket *ws);
};

#endif