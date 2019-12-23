#include "command.h"

Command::Command(QObject *parent) : QObject(parent)
{

}

QString Command::getCommandString() const
{
    return commandString;
}
