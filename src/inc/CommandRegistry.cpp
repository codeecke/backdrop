#include "./commands/StopCommand.h"

#include "CommandRegistry.h"
#include "commands/AbstractCommand.h"

CommandRegistry::CommandRegistry(JSONParser &parser) : parser(parser) {};

void CommandRegistry::registerCommand(AbstractCommand *command)
{
    this->commands.push_back(command);
}

void CommandRegistry::execute(String json, AsyncWebSocketClient *client)
{
    WebSocketCommand commandToExecute = this->parser.parseWebSocketCommand(json);
    auto it = std::find_if(this->commands.begin(), this->commands.end(), [&](AbstractCommand *command)
                           { return command->getName() == commandToExecute.getCommand() && command->getMotorId() == commandToExecute.getMotorId(); });

    if (it != commands.end())
    {
        Serial.printf("FOUND! Motor: %d / Command: %s\r\n", (*it)->getMotorId(), (*it)->getName());
        JsonVariant payload = commandToExecute.getPayload();
        (*it)->execute(client, payload);
    }
    else
    {
        Serial.printf("NOT FOUND!\n");
    }
}

JSONParser parser;
CommandRegistry commandRegistry(parser);
