#include "commandpanup.h"

CommandPanUp::CommandPanUp() : Command(nullptr)
{
    commandString = "pan_up";
}

CommandPanUp::~CommandPanUp() = default;

void CommandPanUp::operator() ()
{
    emit updateCameraCenter(0,-1);
}
