#ifndef COMMANDZOOMIN_H
#define COMMANDZOOMIN_H

#include "command.h"

class CommandZoomIn : public Command
{
    Q_OBJECT

public:
    CommandZoomIn();
    ~CommandZoomIn();
    void operator() ();

};

#endif // COMMANDZOOMIN_H
