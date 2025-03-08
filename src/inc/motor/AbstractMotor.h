#ifndef ABSTRACT_MOTOR_H
#define ABSTRACT_MOTOR_H

class AbstractMotor
{
public:
    virtual void moveUp();
    virtual void moveDown();
    virtual void stop();
};

#endif