#ifndef MYXENEMY_H
#define MYXENEMY_H

#include "myenemy.h"


class MyXEnemy : public MyEnemy
{
    Q_OBJECT
public:
    MyXEnemy(int xPosition, int yPosition, float strength, QImage* representation);
    ~MyXEnemy() override = default;
    virtual void deathAction() override;
private:
    bool respawned;

signals:
    void respawn(int Xpos, int Ypos);
};

#endif // MYXENEMY_H
