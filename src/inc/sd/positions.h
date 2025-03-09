#ifndef POSITION_H
#define POSITION_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <vector>
#include "./base.h"

#define CS_PIN 5

struct Position
{
    u_int motorID;
    float position;
    String name;
};

extern std::vector<Position> positions;

void load_positions();
bool save_positions();
#endif