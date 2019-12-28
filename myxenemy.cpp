#include "myxenemy.h"

MyXEnemy::MyXEnemy(int xPosition, int yPosition, float strength, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations) :
    Entity{xPosition,yPosition,strength,idle_animations,death_animations,walking_animations}, respawned{false}
{

}

void MyXEnemy::deathAction(){
    if(!respawned){
        respawned = true;
        setDefeated(false);
        emit respawn(getXPos(),getYPos());
    }
    else emit dead();
}
QString MyXEnemy::getTextRepresentation()
{
    QString value;
    if (respawned == true && state == EntityState::IDLE)
    {
        if(int(this->getValue()) < 10) value.append("0");
        value.append(QString::fromStdString(std::to_string(int(this->getValue()))));

        QString text = "<span style=\"color:olivedrab; font-family: monospace;  white-space: pre; font-weight: 900;\">Z</span>";
        text.append("<span style=\"color:black; font-family: monospace;  white-space: pre; font-weight: 100;\">");
        text.append(value);
        text.append("</span>");
        return text;
    }
    if(state == EntityState::DEFEATED )
    {
        return "<span style=\"color:black; font-family: monospace;  white-space: pre;\"> x </span>";
    }

    else
    {
        if(int(this->getValue()) < 10) value.append("0");
        value.append(QString::fromStdString(std::to_string(int(this->getValue()))));

        QString text = "<span style=\"color:orange; font-family: monospace;  white-space: pre; font-weight: 900;\">X</span>";
        text.append("<span style=\"color:black; font-family: monospace;  white-space: pre; font-weight: 100;\">");
        text.append(value);
        text.append("</span>");
        return text;
    }
}
