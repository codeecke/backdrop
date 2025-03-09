#ifndef MOTOR_H
#define MOTOR_H
#include "../sd/motor_config.h"
#include <Arduino.h>
#include <FastAccelStepper.h>

#define MOTOR_COUNT 2

extern FastAccelStepper *stepper[MOTOR_COUNT];

void motor_setup();
bool check_motor_id(int motorId);
#endif