#ifndef COMMANDREGISTRY_H
#define COMMANDREGISTRY_H

#include <Arduino.h>
#include <vector>
#include "JSONParser.h"

class AbstractCommand; // ✅ Vorwärtsdeklaration, um zirkuläre Abhängigkeiten zu vermeiden

class CommandRegistry
{
private:
    std::vector<AbstractCommand *> commands;
    JSONParser parser;

public:
    CommandRegistry(JSONParser &parser);
    void registerCommand(AbstractCommand *command);
    void execute(String command, AsyncWebSocketClient *client);
};

extern CommandRegistry commandRegistry;

#endif // COMMANDREGISTRY_H
