#include "./HomeCommand.h"

HomeCommand::HomeCommand()
{
    Serial.println("Home command found");
}

void HomeCommand::execute()
{
    Serial.println("Home command executed");
    stepper[0]->setAcceleration(1e4);
    stepper[0]->setSpeedInHz(50000);
    stepper[0]->moveTo(0);
}