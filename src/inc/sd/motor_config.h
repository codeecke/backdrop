#ifndef MOTOR_CONFIG_H
#define MOTOR_CONFIG_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include <vector>
#include "./base.h"

struct PositionConfig
{
    float current;
    float min;
    float max;
};

struct SpeedConfig
{
    float acceleration;
    float maxRPM;
};

struct PinConfig
{
    u_int step;
    u_int dir;
    u_int enable;
};

struct MotorConfigItem
{
    u_int id;
    String name;
    char colorCode[8];
    u_int rs285Addr;
    bool active;
    PositionConfig position;
    SpeedConfig speed;
    PinConfig pins;
    u_int stepsPerRotation;
    bool inverted;
    String lastCommand;
};

extern std::vector<MotorConfigItem> motorConfig;

void load_motor_config();
#endif