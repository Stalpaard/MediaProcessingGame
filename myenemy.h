#ifndef MYENEMY_H
#define MYENEMY_H

#include "world.h"

class MyEnemy :  public QObject, public Tile
{
    Q_OBJECT
public:
    MyEnemy(int xPosition, int yPosition, float strength, QImage* representation);
    ~MyEnemy() override = default;
    bool getDefeated() const {return defeated;}
    QImage* getRepresentation() const {return image_representation;}
    void setDefeated(bool newvalue);
    void setRepresentation(QImage* newvalue) {image_representation = newvalue;}
    virtual void deathAction(){emit dead();}

signals:
    void dead();
private:
    bool defeated;
    QImage* image_representation;
};

#endif // MYENEMY_H
