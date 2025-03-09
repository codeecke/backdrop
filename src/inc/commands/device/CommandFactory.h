#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include <Arduino.h>
#include <string>
#include <unordered_map>
#include <memory>
#include "./AbstractCommand.h"

using CommandCreator = std::function<std::unique_ptr<AbstractCommand>()>;

class CommandFactory
{
private:
    std::unordered_map<std::string, CommandCreator> commands;

public:
    static CommandFactory &getInstance();
    void setupCommands();
    void registerCommand(const std::string &name, CommandCreator command);
    std::unique_ptr<AbstractCommand> createCommand(const std::string &name);
};

#endif