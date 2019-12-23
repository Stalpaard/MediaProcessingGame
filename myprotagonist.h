#ifndef MYPROTAGONIST_H
#define MYPROTAGONIST_H

#include "entity.h"

class MyProtagonist : public Entity //Entity
{
    Q_OBJECT
public:
    MyProtagonist(std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations);
    void setXPos(int newPos) {xPos = newPos; emit posChanged(xPos, yPos);}
    void setYPos(int newPos) {yPos = newPos; emit posChanged(xPos, yPos);}
    void setPos(int newX, int newY) {if (xPos != newX || yPos != newY) {xPos = newX; yPos = newY; emit posChanged(xPos, yPos);}}
    float getHealth() const {return health;}
    void setHealth(float value) {health = value; emit healthChanged(static_cast<int>(health));}

    float getEnergy() const {return energy;}
    void setEnergy(float value) {energy = value; emit energyChanged(static_cast<int>(energy));}
    virtual void deathAction() override{} //maybe end game here
private:
    QImage* representation;
signals:
    void posChanged(int x, int y);
    void healthChanged(int h);
    void energyChanged(int e);
private:
    float health; //100.0f by construction
    float energy; //100.0f by construction
};

#endif // MYPROTAGONIST_H
