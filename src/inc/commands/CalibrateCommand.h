#ifndef CalibrateCommand_h
#define CalibrateCommand_h

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "AbstractCommand.h"
#include "../Motor.h"

class CalibrateCommand : public AbstractCommand
{
private:
    Motor *motor;

public:
    CalibrateCommand(Motor *motor);
    u_int getMotorId();
    String getName();
    void execute(AsyncWebSocketClient *clientConnection, JsonVariant payload);
};

#endif
