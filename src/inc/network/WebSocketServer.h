#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H
#include <AsyncWebSocket.h>
#include <memory>
#include "../commands/device/CommandFactory.h"
#include "../commands/client/MotorConfigurationCommand.h"
#include "../commands/client/PositionListCommand.h"

AsyncWebSocket *websocket_setup();

extern AsyncWebSocket ws; // <- hier ist es definiert
#endif