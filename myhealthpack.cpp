#include "myhealthpack.h"

MyHealthpack::MyHealthpack(int xPosition, int yPosition, float health, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations) :
    Entity{xPosition,yPosition,health, idle_animations,death_animations,walking_animations}
{

}
