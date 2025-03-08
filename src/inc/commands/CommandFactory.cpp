

#include "./CommandFactory.h"
#include "./MoveCommand.h"
#include "./StopCommand.h"

CommandFactory &CommandFactory::getInstance()
{
    static CommandFactory instance;

    return instance;
}

void CommandFactory::setupCommands()
{
    registerCommand("move", []()
                    { return std::unique_ptr<MoveCommand>(new MoveCommand()); });
    registerCommand("stop", []()
                    { return std::unique_ptr<StopCommand>(new StopCommand()); });
}

void CommandFactory::registerCommand(const std::string &name, CommandCreator command)
{
    this->commands[name] = command;
    Serial.printf("✅ Command registered: %s\n", name.c_str());
}

std::unique_ptr<AbstractCommand> CommandFactory::createCommand(const std::string &name)
{
    auto it = commands.find(name);
    if (it != commands.end())
    {
        return it->second();
    }
    return nullptr;
}