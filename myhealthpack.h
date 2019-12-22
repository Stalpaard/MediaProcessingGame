#ifndef MYHEALTHPACK_H
#define MYHEALTHPACK_H

#include "world.h"
#include "myenemy.h"

class MyHealthpack : public MyEnemy
{
public:
    MyHealthpack(int xPosition, int yPosition, float health, QImage* representation);
};

#endif // MYHEALTHPACK_H
