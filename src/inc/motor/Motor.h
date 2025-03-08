#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>
#include <FastAccelStepper.h>

struct Color
{
    u_char red;
    u_char green;
    u_char blue;
};

struct MotorConfigItem
{
    u_int id;
    Color color[7];
    char name[20];
};

extern FastAccelStepper *stepper[1];

void motor_setup();
bool check_motor_id(int motorId);
#endif