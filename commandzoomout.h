#ifndef COMMANDZOOMOUT_H
#define COMMANDZOOMOUT_H

#include "command.h"

class CommandZoomOut : public Command
{
    Q_OBJECT

public:
    CommandZoomOut();
    ~CommandZoomOut();
    void operator() ();

};

#endif // COMMANDZOOMOUT_H
