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
