#include "mytile.h"

MyTile::MyTile(int xPosition, int yPosition, float tileWeight) : Tile(xPosition,yPosition,tileWeight)
{
    occupied = false;
    poisonLevel = 0;
}

void MyTile::setOccupant(std::shared_ptr<MyEnemy> newOccupant){
    occupant = newOccupant;
    if(newOccupant) occupied = true;
    else occupied = false;
}
