#ifndef MYTILE_H
#define MYTILE_H

#include "world.h"
#include "myenemy.h"

class MyTile : public Tile
{
public:
    MyTile(int xPosition, int yPosition, float tileWeight);
    bool isOccupied() const{return occupied;}
    float getInitValue() const{return init_value;}
    void setOccupied(bool newvalue){occupied = newvalue;}
    std::shared_ptr<Entity> getOccupant() const{return occupant;}
    void setOccupant(std::shared_ptr<Entity> newOccupant);
    float getPoisonLevel() const{return poisonLevel;}
    void setPoisonLevel(float newvalue){poisonLevel = newvalue;}
private:
    bool occupied;
    float init_value;
    float poisonLevel;
    std::shared_ptr<Entity> occupant;
};

#endif // MYTILE_H
