#include <Arduino.h>
#include "driver/pcnt.h"
#include "esp_attr.h"
#include "esp_task_wdt.h"
#include <atomic>

struct MotorPinConfig
{
    unsigned int encoderA;
    unsigned int encoderB;
    unsigned int button;
    unsigned int relais1;
    unsigned int relais2;
};

struct MotorInterruptConfig
{
    volatile int *counter;
    volatile int *direction;
    volatile int *target;
    void (*handler)();
};

struct MotorConfig
{
    MotorPinConfig pins;
    MotorInterruptConfig interrupt;
};

class Motor
{
private:
    MotorPinConfig pins;
    MotorInterruptConfig interrupt;

public:
    Motor(MotorConfig config)
    {
        this->pins = config.pins;
        this->interrupt = config.interrupt;
    }

    int getCounterValue()
    {
        if (!this->interrupt.counter)
        {
            Serial.println("counter is not defined");
            abort();
        }
        return *this->interrupt.counter;
    }

    int getTarget()
    {
        if (!this->interrupt.target)
        {
            Serial.println("target is not defined");
            abort();
        }
        return *this->interrupt.target;
    }

    void setTarget(int value)
    {
        noInterrupts();
        if (!this->interrupt.target)
        {
            Serial.println("target is not defined");
            abort();
        }
        *this->interrupt.target = value;
        interrupts();
    }

    int getDirection()
    {
        if (!this->interrupt.direction)
        {
            Serial.println("direction is not defined");
            abort();
        }
        return *this->interrupt.direction;
    }

    void setDirection(int value)
    {
        noInterrupts();
        if (!this->interrupt.direction)
        {
            Serial.println("direction is not defined");
            abort();
        }
        *this->interrupt.direction = value;
        interrupts();
    }

    void setup()
    {
        pinMode(this->pins.encoderA, INPUT_PULLDOWN);
        pinMode(this->pins.encoderB, INPUT_PULLDOWN);
        pinMode(this->pins.button, INPUT_PULLDOWN);
        pinMode(this->pins.relais1, OUTPUT);
        pinMode(this->pins.relais2, OUTPUT);

        digitalWrite(this->pins.relais1, LOW);
        digitalWrite(this->pins.relais2, LOW);

        attachInterrupt(digitalPinToInterrupt(this->pins.encoderA), this->interrupt.handler, RISING);

        esp_task_wdt_init(5, true); // Timeout auf 5 Sekunden setzen
        esp_task_wdt_add(NULL);     // Haupttask dem Watchdog hinzufügen
    }

    void loop()
    {
        int counter, direction, target;
        esp_task_wdt_reset();
        static unsigned long lastPrintTime = 0;
        counter = this->getCounterValue();
        direction = this->getDirection();
        target = this->getTarget();

        // debug
        //*this->interrupt.counter += *this->interrupt.direction;
    }

    void stop()
    {
        digitalWrite(this->pins.relais1, LOW);
        Serial.println("Relais1 auf LOW");
        digitalWrite(this->pins.relais2, LOW);
        Serial.println("Relais2 auf LOW");

        Serial.println("Beide Relais sind auf LOW, nun wird Direction auf 0 gesetzt");
        this->setDirection(0);
        Serial.println("Direction auf 0");
        delay(100);
    }

    void down()
    {
        digitalWrite(this->pins.relais1, HIGH);
        Serial.println("Relais1 auf HIGH");
        this->setDirection(-1);
    }

    void up()
    {
        digitalWrite(this->pins.relais2, HIGH);
        Serial.println("Relais2 auf HIGH");
        this->setDirection(1);
    }

    void goToTarget(int target)
    {
        this->stop();
        this->setTarget(target);

        int currentValue = this->getCounterValue();
        if (target > 32767)
            target = 32767;
        if (target < 0)
            target = 0;

        Serial.printf("Aktueller Wert: %d, Zielwert: %d\n", currentValue, target);

        if (currentValue < target)
        {
            this->down();
        }
        else if (currentValue > target)
        {
            this->up();
        }
    }
};

volatile int motor1Counter = 0;
volatile int motor1Direction = 0;
volatile int motor1Target = 0;

void motor1ISR()
{
    if (motor1Direction == 0)
        return;
    motor1Counter += motor1Direction;
    /*
    if ((motor1Direction == -1 && motor1Counter <= motor1Target) || (motor1Direction == 1 && motor1Counter >= motor1Target))
    {
        digitalWrite(33, LOW);
        digitalWrite(25, LOW);
    }
    */
}

Motor motor1({.pins = {
                  .encoderA = 34,
                  .encoderB = 32,
                  .button = 35,
                  .relais1 = 33,
                  .relais2 = 25,
              },
              .interrupt = {.counter = &motor1Counter, .direction = &motor1Direction, .target = &motor1Target, .handler = &motor1ISR}});
