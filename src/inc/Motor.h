#ifndef Motor_h
#define Motor_h

#include <AccelStepper.h>
#include "./EventDispatcher.h"

struct MotorRunnningEventPayload
{
    u_int motorId;
    float speed;
    String direction;
};

struct PositionUpdateEventPayload
{
    u_int motorId;
    long position;
};

class Motor : public EventDispatcher
{
private:
    AccelStepper motor;
    bool calibdationMode = false;
    float speed = 0;
    int lastDebug = 0;
    int lastPositionTime = 0;
    bool disabled = false;
    u_int id;
    long lastEmittedPosition = 0;

    void reset();

public:
    Motor(int pulsePin, int dirPin, int enablePin, u_int id);
    u_int getId();
    void up();
    void down();
    void stop();
    void calibrate();
    void moveTo(long position);
    long currentPosition();
    void run();
    void enable();
    void disable();
    void setCurrentPositon(long position);
    void dispatchStartedEvent();
    void dispatchStoppedEvent();
    void dispatchPositionUpdateEvent();
};

extern Motor motor1;
extern Motor motor2;

#endif
