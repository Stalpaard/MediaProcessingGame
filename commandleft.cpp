#include "commandleft.h"

CommandLeft::CommandLeft() : Command(nullptr)
{
    commandString = "left";
}

CommandLeft::~CommandLeft() = default;

void CommandLeft::operator() ()
{
    emit movementKeyPressed(Direction::LEFT);
}
