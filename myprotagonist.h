#ifndef MYPROTAGONIST_H
#define MYPROTAGONIST_H

#include "entity.h"

class MyProtagonist : public Entity
{
    Q_OBJECT
public:
    MyProtagonist(std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations);
    ~MyProtagonist() override = default;

    void setXPos(int newPos) {int dx = newPos-xPos;xPos = newPos; emit posChanged(dx, 0);}
    void setYPos(int newPos) {int dy = newPos-yPos;yPos = newPos; emit posChanged(0, dy);}
    void setPos(int newX, int newY) {if (xPos != newX || yPos != newY) {
            int dx = newX-xPos;
            int dy = newY-yPos;
            xPos = newX; yPos = newY;
            emit posChanged(dx, dy);
        }}

    float getHealth() const {return health;}
    void setHealth(float newvalue) {health = newvalue; emit healthChanged(static_cast<int>(health));}

    float getEnergy() const {return energy;}
    void setEnergy(float newvalue) {energy = newvalue; emit energyChanged(static_cast<int>(energy));}

    virtual void deathAction() override{}
    QString getTextRepresentation() override;

private:
    QImage* representation;
    float health;
    float energy;
signals:
    void posChanged(int x, int y);
    void healthChanged(int h);
    void energyChanged(int e);
};

#endif // MYPROTAGONIST_H
