#include "myenemy.h"
#include <iostream>
MyEnemy::MyEnemy(int xPosition, int yPosition, float strength, QImage* representation):
  Tile{xPosition, yPosition, strength}, defeated{false}
{
    image_representation = representation;
}

void MyEnemy::setDefeated(bool newvalue){
    defeated = newvalue;
    if (defeated){
        deathAction();
    }
}
