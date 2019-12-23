#ifndef COMMANDLEFT_H
#define COMMANDLEFT_H

#include "command.h"


class CommandLeft : public Command
{
    Q_OBJECT

public:
    CommandLeft();
    ~CommandLeft();
    void operator() ();

};

#endif // COMMANDLEFT_H
