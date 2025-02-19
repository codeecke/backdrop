#ifndef WEB_SOCKET_COMMAND_H
#define WEB_SOCKET_COMMAND_H

#include <Arduino.h>
#include <ArduinoJson.h>

class WebSocketCommand
{
private:
  u_int motorId;
  String command;
  JsonVariant payload;

public:
  WebSocketCommand(u_int motorId, String command, JsonVariant payload = JsonVariant());
  u_int getMotorId();
  String getCommand();
  JsonVariant getPayload();
};

#endif