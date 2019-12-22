#ifndef MYPENEMY_H
#define MYPENEMY_H

#include "myenemy.h"
#include <iostream>

class MyPEnemy : public MyEnemy
{
    Q_OBJECT
public:
    MyPEnemy(int xPosition, int yPosition, float strength, QImage* representation);
    ~MyPEnemy() override = default;
    float getPoisonLevel() const;
    void setPoisonLevel(float value);
    virtual void deathAction() override{std::cout << "Enemy at x=" << xPos << " y=" << yPos << " was a PEnemy!" << std::endl; poison();}


public slots:
    bool poison();

signals:
    void poisonLevelUpdated(float value, int x, int y);

private:
    float poisonLevel;
};

#endif // MYPENEMY_H
