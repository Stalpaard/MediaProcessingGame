#ifndef MYTILE_H
#define MYTILE_H

#include "entity.h"

class MyTile : public Tile
{
public:
    MyTile(int xPosition, int yPosition, float tileWeight);
    ~MyTile() override = default;

    bool isOccupied() const{return occupied;}
    void setOccupied(bool newvalue){occupied = newvalue;}
    std::shared_ptr<Entity> getOccupant() const{return occupant;}
    void setOccupant(std::shared_ptr<Entity> newOccupant);
    float getPoisonLevel() const{return poisonLevel;}

    void setPoisonLevel(float newvalue){poisonLevel = newvalue;}

private:
    bool occupied;
    float poisonLevel;
    std::shared_ptr<Entity> occupant;
};

#endif // MYTILE_H
