#include "commandzoomin.h"

CommandZoomIn::CommandZoomIn() : Command(nullptr)
{
    commandString = "zoom_in";
}

CommandZoomIn::~CommandZoomIn() = default;

void CommandZoomIn::operator() ()
{
    for(int i=0; i<5; i++) emit zoom(true);
}
