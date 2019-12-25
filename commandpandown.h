#ifndef COMMANDPANDOWN_H
#define COMMANDPANDOWN_H

#include "command.h"

class CommandPanDown : public Command
{
    Q_OBJECT

public:
    CommandPanDown();
    ~CommandPanDown();
    void operator() ();

};

#endif // COMMANDPANDOWN_H
