#include "myhealthpack.h"

MyHealthpack::MyHealthpack(int xPosition, int yPosition, float health, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations) :
    Entity{xPosition,yPosition,health, idle_animations,death_animations,walking_animations}
{

}
QString MyHealthpack::getTextRepresentation()
{
    if(state == EntityState::DEFEATED) return "<span style=\"color:red; font-family: monospace;  white-space: pre; font-weight: bold;\">   </span>";
    else return "<span style=\"color:green; font-family: monospace;  white-space: pre; font-weight: bold;\"> + </span>";
}
