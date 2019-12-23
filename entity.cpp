#include "entity.h"
#include <iostream>

const int deathMaxIndex = 14;
const int idleMaxIndex = 17;
const int walkingMaxIndex = 23;

Entity::Entity(int xPosition, int yPosition, float strength, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> idle_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> death_animations, std::shared_ptr<std::vector<std::shared_ptr<QImage>>> walking_animations):
    Tile{xPosition, yPosition, strength}, representation_index{0}, state{EntityState::IDLE}, stopAnimation{false}
{
    this->idle_animations = idle_animations;
    this->walking_animations = walking_animations;
    this->death_animations = death_animations;
    current_animations = idle_animations;
}

void Entity::setDefeated(bool newvalue){
    if (newvalue){
        state = EntityState::DEFEATED;
        current_animations = death_animations;
        deathAction();
    }
    else{
        state = EntityState::IDLE;
        current_animations = idle_animations;
    }
    representation_index = 0;
}

void Entity::setWalking(bool newvalue){
    if(newvalue){
        state = EntityState::WALKING;
        current_animations = walking_animations;
    }
    else{
        state = EntityState::IDLE;
        current_animations = idle_animations;
    }
    representation_index = 0;
}

std::shared_ptr<QImage> Entity::getRepresentation(){
    if(!stopAnimation){
        if(representation_index >= current_animations->size()){
            if(!(state == EntityState::DEFEATED)) representation_index = 0;
            else{
                representation_index = representation_index-1;
                stopAnimation = true;
            }
        }
    }
    std::shared_ptr<QImage> returnvalue = current_animations->at(representation_index);
    if(!stopAnimation) representation_index++;
    return returnvalue;
}
