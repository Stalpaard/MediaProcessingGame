#ifndef COMMANDTOGGLEPATHFINDING_H
#define COMMANDTOGGLEPATHFINDING_H

#include "command.h"

class CommandTogglePathfinding : public Command
{
    Q_OBJECT

public:
    CommandTogglePathfinding();
    ~CommandTogglePathfinding();
    void operator() ();

};
#endif // COMMANDTOGGLEPATHFINDING_H
