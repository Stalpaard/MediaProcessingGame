#include "commandpandown.h"

CommandPanDown::CommandPanDown() : Command(nullptr)
{
    commandString = "pan_down";
}

CommandPanDown::~CommandPanDown() = default;

void CommandPanDown::operator() ()
{
    emit updateCameraCenter(0,1);
}
