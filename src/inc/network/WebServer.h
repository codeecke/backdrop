#ifndef MY_WEBSERVER_H
#define MY_WEBSERVER_H
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>

extern AsyncWebServer server;
void webserver_setup(AsyncWebSocket *ws = nullptr);
#endif