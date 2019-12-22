#include "myxenemy.h"

MyXEnemy::MyXEnemy(int xPosition, int yPosition, float strength, QImage* representation) : MyEnemy{xPosition,yPosition,strength,representation}, respawned{false}
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
