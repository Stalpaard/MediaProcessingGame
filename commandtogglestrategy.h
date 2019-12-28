#ifndef COMMANDTOGGLESTRATEGY_H
#define COMMANDTOGGLESTRATEGY_H

#include "command.h"

class CommandToggleStrategy : public Command
{
    Q_OBJECT

public:
    CommandToggleStrategy();
    ~CommandToggleStrategy();
    void operator() ();

};
#endif // COMMANDTOGGLESTRATEGY_H
