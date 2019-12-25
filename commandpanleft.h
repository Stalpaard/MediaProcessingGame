#ifndef COMMANDPANLEFT_H
#define COMMANDPANLEFT_H

#include "command.h"

class CommandPanLeft : public Command
{
    Q_OBJECT

public:
    CommandPanLeft();
    ~CommandPanLeft();
    void operator() ();

};

#endif // COMMANDPANLEFT_H
