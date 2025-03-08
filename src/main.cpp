#include "./inc/commands/CommandFactory.h"
#include "./inc/network/wifi.h"
#include "./inc/network/WebServer.h"
#include "./inc/network/WebSocketServer.h"
#include "./inc/motor/Motor.h"

void setup()
{
    Serial.begin(115200);
    CommandFactory::getInstance().setupCommands();
    wifi_setup();
    AsyncWebSocket *ws = websocket_setup();
    webserver_setup(ws);
    motor_setup();
}

void loop() {}