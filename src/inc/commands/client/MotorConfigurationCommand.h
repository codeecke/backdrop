#ifndef MOTOR_CONFIGURATION_CLIENT_COMMAND_H
#define MOTOR_CONFIGURATION_CLIENT_COMMAND_H

#include "./AbstractClientCommand.h"
#include "../../sd/motor_config.h"
#include "../../motor/Motor.h"

class MotorConfigurationCommand : public AbstractClientCommand
{
private:
    /* data */
public:
    MotorConfigurationCommand(/* args */);
    JsonDocument toJson();
};

#endif