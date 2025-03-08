#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H
#include <AsyncWebSocket.h>
#include <memory>
#include "../commands/CommandFactory.h"

AsyncWebSocket *websocket_setup();

extern AsyncWebSocket ws;
#endif