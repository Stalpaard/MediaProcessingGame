#ifndef COMMANDPANRIGHT_H
#define COMMANDPANRIGHT_H

#include "command.h"

class CommandPanRight : public Command
{
    Q_OBJECT

public:
    CommandPanRight();
    ~CommandPanRight();
    void operator() ();

};

#endif // COMMANDPANRIGHT_H
