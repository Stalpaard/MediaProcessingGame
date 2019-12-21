#ifndef MYENEMY_H
#define MYENEMY_H

#include "world.h"

class MyEnemy :  public QObject, public Tile
{
    Q_OBJECT
public:
    MyEnemy(int xPosition, int yPosition, float strength);
    ~MyEnemy() override = default;
    bool getDefeated() const {return defeated;}
    void setDefeated(bool newvalue) {defeated = newvalue; if (defeated) deathAction();}
    virtual void deathAction(){emit dead();}

signals:
    void dead();
private:
    bool defeated;
};

#endif // MYENEMY_H
