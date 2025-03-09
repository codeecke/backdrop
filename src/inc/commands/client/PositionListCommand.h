#ifndef POSITION_LIST_CLIENT_COMMAND_H
#define POSITION_LIST_CLIENT_COMMAND_H

#include "./AbstractClientCommand.h"
#include "../../sd/positions.h"

class PositionListCommand : public AbstractClientCommand
{
private:
    /* data */
public:
    PositionListCommand(/* args */);
    JsonDocument toJson();
};

#endif