#include "../Motor.h"
#include "AbstractCommand.h"
#include "CalibrateCommand.h"

CalibrateCommand::CalibrateCommand(Motor *motor) : motor(motor) {}

u_int CalibrateCommand::getMotorId()
{
    return this->motor->getId();
};

String CalibrateCommand::getName()
{
    return "calibrate";
};

void CalibrateCommand::execute(AsyncWebSocketClient *clientConnection, JsonVariant payload)
{
    this->motor->calibrate();
};