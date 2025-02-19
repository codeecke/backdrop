#include "Motor.h"
#include "AccelStepper.h"

#define MAX_SPEED 6000.0 // erfolgreiches max. 6000

Motor::Motor(int pulsePin, int dirPin, int enablePin, u_int id)
    : motor(AccelStepper::DRIVER, pulsePin, dirPin), id(id)
{
    motor.setEnablePin(enablePin);
    motor.setPinsInverted(true, false, true);
    motor.setMaxSpeed(MAX_SPEED);
    motor.setAcceleration(MAX_SPEED);
}

u_int Motor::getId()
{
    return this->id;
}

void Motor::reset()
{
    // this->motor.setAcceleration(0);
    this->motor.setAcceleration(999999);
    this->motor.setMaxSpeed(MAX_SPEED);
}

void Motor::up()
{
    this->enable();
    this->calibdationMode = true;
    this->speed = -MAX_SPEED;
    this->dispatchStartedEvent();
}

void Motor::down()
{
    this->enable();
    this->calibdationMode = true;
    this->speed = MAX_SPEED;
    this->dispatchStartedEvent();
}

void Motor::stop()
{
    this->calibdationMode = false;
    this->disable();
    this->motor.stop();
    this->motor.move(0);
    this->speed = 0;
}

void Motor::calibrate()
{
    this->setCurrentPositon(0);
}

void Motor::moveTo(long position)
{
    this->motor.setAcceleration(999999);
    this->calibdationMode = false;
    this->enable();
    this->motor.moveTo(position);
}

void Motor::enable()
{
    Serial.println("Motor::enable()");
    if (!this->disabled)
        return;
    Serial.println("enable!");
    this->motor.enableOutputs();
    this->disabled = false;
}

void Motor::disable()
{
    if (this->disabled)
        return;
    Serial.println("disable!");
    this->motor.disableOutputs();
    this->disabled = true;

    this->dispatchStoppedEvent();
    this->dispatchPositionUpdateEvent();
}

void Motor::dispatchStartedEvent()
{
    MotorRunnningEventPayload payload = {
        motorId : this->id,
        speed : this->speed,
        direction : this->speed > 0 ? "down" : "up"
    };
    this->dispatchEvent("started", &payload);
}

void Motor::dispatchStoppedEvent()
{
    MotorRunnningEventPayload payload = {
        motorId : this->id,
        speed : 0,
        direction : this->speed > 0 ? "down" : "up"
    };
    this->dispatchEvent("stopped", &payload);
}

void Motor::dispatchPositionUpdateEvent()
{
    this->lastEmittedPosition = this->motor.currentPosition();
    PositionUpdateEventPayload positionPayload;
    positionPayload.motorId = this->id;
    positionPayload.position = this->motor.currentPosition();

    this->lastPositionTime = millis();
    this->dispatchEvent("positionUpdate", &positionPayload);
}

void Motor::run()
{

    if (millis() - this->lastPositionTime > 100 && this->motor.currentPosition() != this->lastEmittedPosition)
    {

        this->dispatchPositionUpdateEvent();
    }

    if (this->calibdationMode)
    {

        this->motor.setSpeed(this->speed);
        this->motor.runSpeed();
    }
    else
    {
        this->motor.run();
    }

    if (this->motor.distanceToGo() == 0 && this->speed == 0)
    {
        this->disable();
    }
}

long Motor::currentPosition()
{
    return this->motor.currentPosition();
}

void Motor::setCurrentPositon(long position)
{
    this->motor.setCurrentPosition(position);
    this->dispatchPositionUpdateEvent();
}

Motor motor1(12, 14, 27, 1);
Motor motor2(21, 22, 23, 2);
