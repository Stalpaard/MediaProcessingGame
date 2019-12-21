#include "myenemy.h"
#include <iostream>
MyEnemy::MyEnemy(int xPosition, int yPosition, float strength):
  Tile{xPosition, yPosition, strength}, defeated{false}
{
}
