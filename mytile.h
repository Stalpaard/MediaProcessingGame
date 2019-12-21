#ifndef MYTILE_H
#define MYTILE_H

#include "world.h"
#include "myenemy.h"

class MyTile : public Tile
{
public:
    MyTile(int xPosition, int yPosition, float tileWeight);
    bool isOccupied() const{return occupied;}
    void setOccupied(bool newvalue){occupied = newvalue;}
    std::shared_ptr<MyEnemy> getOccupant(){return occupant;}
    void setOccupant(std::shared_ptr<MyEnemy> newOccupant);
    float getPoisonLevel() const{return poisonLevel;}
    void setPoisonLevel(float newvalue){poisonLevel = newvalue;}
private:
    bool occupied;
    float poisonLevel;
    std::shared_ptr<MyEnemy> occupant;
};

#endif // MYTILE_H
