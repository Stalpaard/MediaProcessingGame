#include "mypenemy.h"
#include <ctime>
#include <QTimer>
#include <iostream>


MyPEnemy::MyPEnemy(int xPosition, int yPosition, float strength): MyEnemy(xPosition, yPosition, strength), poisonLevel{strength}
{
  qsrand(time(nullptr));
}

bool MyPEnemy::poison()
{
  if (poisonLevel > 0.0f)
    {
      emit poisonLevelUpdated(poisonLevel, xPos,yPos);
      int t = 2;
      std::cout << "starting timer for " << t << " seconds" << " with poisonLevel = " << poisonLevel << std::endl;
      poisonLevel -= 10.0f;
      QTimer::singleShot(t*1000, this, SLOT(poison()));
      return true;
    }
  else
    {
      poisonLevel = 0.0f;
      emit poisonLevelUpdated(poisonLevel, xPos, yPos);
      emit dead();
    }
  return false;
}

float MyPEnemy::getPoisonLevel() const
{
  return poisonLevel;
}

void PEnemy::setPoisonLevel(float newvalue)
{
  poisonLevel = newvalue;
}
