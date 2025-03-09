#include "./Motor.h"

FastAccelStepperEngine engine[MOTOR_COUNT];
FastAccelStepper *stepper[MOTOR_COUNT] = {};

void initial_stepper(int id, int stepPin, int dirPin, int enaPin)
{
    Serial.printf("🤘 Initialisiere Motor %d: Step=%d, Dir=%d, Enable=%d\n", id, stepPin, dirPin, enaPin);

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

    Serial.print("📏 Anzahl Motoren in motorConfig: ");
    Serial.println(motorConfig.size()); // Prüfen, ob die Liste überhaupt gefüllt ist

    if (motorConfig.empty())
    {
        Serial.println("⚠️ motorConfig ist leer! JSON wurde nicht korrekt geladen.");
        return;
    }

    for (const auto &motor : motorConfig)
    {
        if (!motor.active)
            continue;
        initial_stepper(
            motor.id,
            motor.pins.step,
            motor.pins.dir,
            motor.pins.enable);
    }

    // initial_stepper(0, 12, 14, 27);
}

bool check_motor_id(int motorId)
{
    return motorId == 0;
}