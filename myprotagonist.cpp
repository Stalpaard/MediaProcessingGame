#include "myprotagonist.h"

MyProtagonist::MyProtagonist(std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations) :
    Entity{0,0,0,idle_animations,death_animations,walking_animations}, health{100}, energy{100}
{
}

QString MyProtagonist::getTextRepresentation()
{
    return "<span style=\"color:red; font-family: monospace;  white-space: pre; font-weight: bold;\">HUH</span>";
}
