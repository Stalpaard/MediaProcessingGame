#include "commandpanleft.h"

CommandPanLeft::CommandPanLeft() : Command(nullptr)
{
    commandString = "pan_left";
}

CommandPanLeft::~CommandPanLeft() = default;

void CommandPanLeft::operator() ()
{
    emit updateCameraCenter(-1,0);
}
