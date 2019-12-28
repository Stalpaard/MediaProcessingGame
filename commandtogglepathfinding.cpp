#include "commandtogglepathfinding.h"

CommandTogglePathfinding::CommandTogglePathfinding() : Command(nullptr)
{
    commandString = "toggle_pathfinding";
}

CommandTogglePathfinding::~CommandTogglePathfinding() = default;

void CommandTogglePathfinding::operator() ()
{
    emit togglePathfinding();
}
