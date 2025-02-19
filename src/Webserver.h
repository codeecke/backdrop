#ifndef MY_WEBSERVER_H
#define MY_WEBSERVER_H

#include "freertos/FreeRTOS.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "./inc/Motor.h"
#include "./inc/CommandRegistry.h"

void ws_setup();
void ws_loop();

extern AsyncWebSocket ws;

#endif
