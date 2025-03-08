#include <Arduino.h>
#include <FastAccelStepper.h>

FastAccelStepperEngine engine[1];
FastAccelStepper *stepper[1] = {nullptr};

void initial_stepper(int id, int stepPin, int dirPin, int enaPin)
{
    engine[id].init();
    stepper[id] = engine[id].stepperConnectToPin(12);
    if (!stepper[id])
    {
        Serial.println("❌ Fehler: Stepper-Objekt ist NULL! Befehl ignoriert.");
        return;
    }

    stepper[id]->setDirectionPin(dirPin);
    stepper[id]->setEnablePin(enaPin, true);
    stepper[id]->setAutoEnable(true);
    stepper[id]->setAcceleration(1e4);
    stepper[id]->setSpeedInHz(50000);
}

void motor_setup()
{
    initial_stepper(0, 12, 14, 27);
}

bool check_motor_id(int motorId)
{
    return motorId == 0;
}