#ifndef COMMANDPANUP_H
#define COMMANDPANUP_H

#include "command.h"

class CommandPanUp : public Command
{
    Q_OBJECT

public:
    CommandPanUp();
    ~CommandPanUp();
    void operator() ();

};

#endif // COMMANDPANUP_H
