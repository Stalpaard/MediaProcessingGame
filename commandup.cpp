#include "commandup.h"

CommandUp::CommandUp() : Command(nullptr)
{
    commandString = "up";
}

CommandUp::~CommandUp() = default;

void CommandUp::operator() ()
{
    emit movementKeyPressed(Direction::UP);
}
