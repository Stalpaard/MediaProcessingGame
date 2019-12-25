#ifndef COMMANDUP_H
#define COMMANDUP_H

#include "command.h"

class CommandUp : public Command
{
    Q_OBJECT

public:
    CommandUp();
    ~CommandUp();
    void operator() ();

};

#endif // COMMANDUP_H
