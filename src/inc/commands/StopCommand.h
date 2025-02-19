#ifndef StopCommand_h
#define StopCommand_h

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "AbstractCommand.h"
#include "../Motor.h"

struct StopCommandPayload
{
};

class StopCommand : public AbstractCommand
{
private:
    Motor *motor;

public:
    StopCommand(Motor *motor);
    u_int getMotorId();
    String getName();
    void execute(AsyncWebSocketClient *clientConnection, JsonVariant payload);
};

#endif
