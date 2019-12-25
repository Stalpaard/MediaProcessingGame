#ifndef COMMANDDOWN_H
#define COMMANDDOWN_H

#include "command.h"

class CommandDown : public Command
{
    Q_OBJECT

public:
    CommandDown();
    ~CommandDown();
    void operator() ();

};

#endif // COMMANDDOWN_H
