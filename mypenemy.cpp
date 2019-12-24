#include "mypenemy.h"
#include <ctime>
#include <QTimer>
#include <iostream>


MyPEnemy::MyPEnemy(int xPosition, int yPosition, float strength, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations):
    Entity(xPosition, yPosition, strength, idle_animations,death_animations,walking_animations), poisonLevel{strength}
{
  qsrand(time(nullptr));
}

bool MyPEnemy::poison()
{
  if (poisonLevel > 0.0f)
    {
      emit poisonLevelUpdated(poisonLevel, xPos,yPos);
      int t = qrand()%5;
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
