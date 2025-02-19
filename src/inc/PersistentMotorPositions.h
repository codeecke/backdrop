#ifndef PERSISTENT_MOTOR_POSITION_H
#define PERSISTENT_MOTOR_POSITION_H

#ifndef SD_CS
#define SD_CS 5
#endif

#include "./Motor.h"
#include "ArduinoJson.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

struct PersistentMotorPositionsPayload
{
    int motor1;
    int motor2;
};

class PersistentMotorPositions
{
private:
    int lastPositions[2] = {0, 0};
    Motor *motors[2];

public:
    PersistentMotorPositions(Motor **motors);
    void save();
    void load();
};
#endif