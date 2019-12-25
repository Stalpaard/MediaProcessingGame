#include "myenemy.h"
#include <iostream>

MyEnemy::MyEnemy(int xPosition, int yPosition, float strength, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations):
    Entity{xPosition,yPosition,strength,idle_animations,death_animations,walking_animations}
{
}

QString MyEnemy::getTextRepresentation()
{
    if(state == EntityState::DEFEATED) return "<span style=\"color:black; font-family: monospace;  white-space: pre;\"> x </span>";
    else
    {
        QString value;
        if(int(this->getValue()) < 10) value.append("0");
        value.append(QString::fromStdString(std::to_string(int(this->getValue()))));

        QString text = "<span style=\"color:red; font-family: monospace;  white-space: pre; font-weight: 900;\">E</span>";
        text.append("<span style=\"color:black; font-family: monospace;  white-space: pre; font-weight: 100;\">");
        text.append(value);
        text.append("</span>");
        return text;
    }
}


