#include "strategy.h"
#include <iostream>

Strategy::Strategy(std::shared_ptr<ModelWorld> model) : model{model}, gameEnded{false}, strategyEnabled{false}, moveIndex{0}, pathToBeFollowed{nullptr}
{
    protagonist = model->getMyProtagonist();
    representation_2D = model->get2DRepresentation();
}

void Strategy::enableStrategy(bool newvalue){

    strategyEnabled = newvalue;
    if(strategyEnabled) calculateBestPath();
}

void Strategy::calculateBestPath(){
    std::cout << "Calculating next best path" << std::endl;
    float required_energy;
    float minimum_energy = 0;

    bestPath = nullptr;
    std::shared_ptr<Entity> nearestEnemy = nullptr;

    protagonist_loc.x = protagonist->getXPos();
    protagonist_loc.y = protagonist->getYPos();

    for(auto& entity : model->getMyEntities()){
        //std::cout << "Calculating best path to next entity" << std::endl;
        if(!(entity->isDefeated())){
            if(entity->getValue() > 0){
                required_energy = 0;
                destination_loc.x = entity->getXPos();
                destination_loc.y = entity->getYPos();
                currentPath = model->runPathfinding(protagonist_loc,destination_loc);
                for(int i = 0; i < currentPath.size(); i++){
                    std::pair<int,int> pair = currentPath.at(i);
                    required_energy = required_energy + representation_2D->at(std::get<1>(pair)).at(std::get<0>(pair))->getValue();
                }
                //std::cout << "Required energy of path: " << required_energy << std::endl;
                if((required_energy < minimum_energy) || minimum_energy == 0){
                    minimum_energy = required_energy;
                    bestPath = std::make_shared<std::vector<std::pair<int,int>>>(currentPath);
                    nearestEnemy = entity;
                }
            }
        }
    }
    if((protagonist->getEnergy()-minimum_energy) > 0 && minimum_energy != 0){
        int healthNeeded = nearestEnemy->getValue() - protagonist->getHealth();
        if(healthNeeded < 0){
            std::cout << "set path to nearest enemy" << std::endl;
            followPath(bestPath);
        }

        else{
            bestPath = nullptr;
            minimum_energy = 0;
            for(auto& healthpack : model->getMyHealthPacks()){
                required_energy = 0;
                if(!(healthpack->isDefeated()) && std::abs(healthpack->getValue()) >= healthNeeded){
                    destination_loc.x = healthpack->getXPos();
                    destination_loc.y = healthpack->getYPos();
                    currentPath = model->runPathfinding(protagonist_loc,destination_loc);
                    for(int i = 0; i < currentPath.size(); i++){
                        std::pair<int,int> pair = currentPath.at(i);
                        required_energy = required_energy + representation_2D->at(std::get<1>(pair)).at(std::get<0>(pair))->getValue();
                    }
                    if((required_energy < minimum_energy) || minimum_energy == 0){
                        minimum_energy = required_energy;
                        bestPath = std::make_shared<std::vector<std::pair<int,int>>>(currentPath);
                        nearestEnemy = healthpack;
                    }
                }
            }
            if(minimum_energy != 0 && (protagonist->getEnergy() - minimum_energy) > 0){
                std::cout << "set path to nearest healthpack" << std::endl;
                followPath(bestPath);
            }
            else{
                gameEnded = true;
                std::cout << "no possible path to healthpack" << std::endl;
            }

            //search for suitable healthpack and follow path
        }

    }
    else{
        gameEnded = true;
        std::cout << "no possible path to enemy" << std::endl;
    }
}

void Strategy::followPath(std::shared_ptr<std::vector<std::pair<int, int>>> path){
    //Give all key inputs but wait for move completed in the meantime (autopilot)
    //Or sethealth and setenergy + teleport (instant)
    //if(!gameEnded) repeat; / + abort function
    pathToBeFollowed = path;
    if(!(protagonist->isWalking())) nextMove();
}

void Strategy::nextMove(){
    if(strategyEnabled && pathToBeFollowed != nullptr){
        std::cout << "sending new move" << std::endl;
        if(moveIndex >= pathToBeFollowed->size()){
            std::cout << "path complete, calculating new path" << std::endl;
            pathToBeFollowed = nullptr;
            moveIndex = 0;
            if(!gameEnded) calculateBestPath();
        }
        else{
            std::pair<int,int> nextTile = pathToBeFollowed->at(moveIndex++);
            int dx = std::get<0>(nextTile)-protagonist->getXPos();
            int dy = std::get<1>(nextTile)-protagonist->getYPos();
            if(dx > 0) requestMove(Direction::RIGHT);
            else if(dx < 0) requestMove(Direction::LEFT);
            if(dy > 0) requestMove(Direction::DOWN);
            else if(dy < 0) requestMove(Direction::UP);
        }
    }
}

void Strategy::gameEnd(){
    gameEnded = true;
}
