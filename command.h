#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <QString>
#include <QObject>
#include "direction.h"


class Command : public QObject
{
    Q_OBJECT

public:
    Command(QObject *parent);
    virtual ~Command() = default;
    virtual void operator() () = 0;
    QString getCommandString() const;

protected:
    QString commandString;

signals:
    void movementKeyPressed(Direction direction);
    void moveCompleted();

};

#endif // COMMAND_H
