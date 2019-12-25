#include "commandzoomout.h"

CommandZoomOut::CommandZoomOut() : Command(nullptr)
{
    commandString = "zoom_out";
}

CommandZoomOut::~CommandZoomOut() = default;

void CommandZoomOut::operator() ()
{
    for(int i=0; i<5; i++) emit zoom(false);
}
