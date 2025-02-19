#ifndef MOTOR_RUNNING_EVENT_H
#define MOTOR_RUNNING_EVENT_H

#include <Arduino.h>
#include <AsyncWebSocket.h>
#include <ArduinoJson.h>

struct MotorRunningEventPayload
{
    boolean running;
    String direction;
};

class MotorRunningEvent
{
public:
    String eventName = "motorRunning";
    u_int motorId;
    MotorRunningEventPayload payload;

    MotorRunningEvent(u_int motorId, MotorRunningEventPayload payload);

    String toString();
    void send(AsyncWebSocket *ws);
};

#endif