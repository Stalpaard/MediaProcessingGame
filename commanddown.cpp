#include "commanddown.h"

CommandDown::CommandDown() : Command(nullptr)
{
    commandString = "down";
}

CommandDown::~CommandDown() = default;

void CommandDown::operator() ()
{
    emit movementKeyPressed(Direction::DOWN);
    emit moveCompleted();
}
