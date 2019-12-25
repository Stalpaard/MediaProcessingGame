#ifndef COMMANDRIGHT_H
#define COMMANDRIGHT_H

#include "command.h"

class CommandRight : public Command
{
    Q_OBJECT

public:
    CommandRight();
    ~CommandRight();
    void operator() ();

};

#endif // COMMANDRIGHT_H
