#include "commandright.h"

CommandRight::CommandRight() : Command(nullptr)
{
    commandString = "right";
}

CommandRight::~CommandRight() = default;

void CommandRight::operator() ()
{
    emit movementKeyPressed(Direction::RIGHT);
    emit moveCompleted();
}
