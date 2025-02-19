#include "MoveCommand.h"

MoveCommand::MoveCommand(Motor *motor) : motor(motor) {};

u_int MoveCommand::getMotorId()
{
    return this->motor->getId();
};
String MoveCommand::getName()
{
    return "move";
};
void MoveCommand::execute(AsyncWebSocketClient *clientConnection, JsonVariant payload)
{
    String direction = payload;
    Serial.printf("MoveCommand::execute() / payload: %s\r\n", direction);
    Serial.printf("Address of motor in MoveCommand: %p\n", &(this->motor));
    if (direction == "up")
    {
        Serial.println("Move up");
        this->motor->up();
    }
    else if (direction == "down")
    {
        Serial.println("Move down");
        this->motor->down();
    }
}
