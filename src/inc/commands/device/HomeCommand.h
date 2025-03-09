#ifndef HOME_COMMAND_H
#define HOME_COMMAND_H

#include <Arduino.h>
#include "./AbstractCommand.h"
#include "../../motor/Motor.h"

class HomeCommand : public AbstractCommand
{
public:
    HomeCommand();
    void execute();
};

#endif