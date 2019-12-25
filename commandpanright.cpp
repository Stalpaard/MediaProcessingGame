#include "commandpanright.h"

CommandPanRight::CommandPanRight() : Command(nullptr)
{
    commandString = "pan_right";
}

CommandPanRight::~CommandPanRight() = default;

void CommandPanRight::operator() ()
{
    emit updateCameraCenter(1,0);
}
