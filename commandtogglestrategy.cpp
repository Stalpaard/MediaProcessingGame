#include "commandtogglestrategy.h"

CommandToggleStrategy::CommandToggleStrategy() : Command(nullptr)
{
    commandString = "toggle_strategy";
}

CommandToggleStrategy::~CommandToggleStrategy() = default;

void CommandToggleStrategy::operator() ()
{
    emit toggleStrategy();
}
