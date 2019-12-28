#include "strategy.h"
#include <iostream>

Strategy::Strategy(std::shared_ptr<ModelWorld> model) : model{model}, strategyEnabled{false}, moveIndex{0}, pathToBeFollowed{nullptr}, gameEnded{false}
{
    protagonist = model->getMyProtagonist();
    representation_2D = model->get2DRepresentation();
    original_representation_2D = model->getOriginal2DRepresentation();
}

void Strategy::enableStrategy(bool newvalue){
    if(!(gameEnded)){
        strategyEnabled = newvalue;
        if(strategyEnabled) calculateBestPath();
        else pathToBeFollowed = nullptr;
    }
}

void Strategy::calculateBestPath(){
    float required_energy = 0;
    float minimum_energy = 0;

    bestPath = nullptr;
    std::shared_ptr<Entity> nearestEntity = nullptr;
    std::shared_ptr<Entity> altNearestEntity = nullptr;

    protagonist_loc.x = protagonist->getXPos();
    protagonist_loc.y = protagonist->getYPos();

    for(auto& entity : model->getMyEntities()){

        if(!(entity->isDefeated())){
            if(entity->getValue() > 0){
                required_energy = 0;
                destination_loc.x = entity->getXPos();
                destination_loc.y = entity->getYPos();
                currentPath = model->runPathfinding(protagonist_loc,destination_loc);
                for(int i = 0; i < currentPath->size()-1; i++){
                    std::pair<int,int> pair = currentPath->at(i);
                    std::pair<int,int> secondPair = currentPath->at(i+1);
                    float pairValue;
                    if(i <= 0) pairValue = original_representation_2D->at(pair.second).at(pair.first).getValue();
                    else pairValue = representation_2D->at(pair.second).at(pair.first)->getValue();
                    float energy_difference = std::abs(pairValue-representation_2D->at(secondPair.second).at(secondPair.first)->getValue());
                    required_energy = required_energy + energy_difference;
                }
                if((required_energy < minimum_energy) || bestPath == nullptr){
                    minimum_energy = required_energy;
                    bestPath = currentPath;
                    nearestEntity = entity;
                }
            }
        }
    }
    if((protagonist->getEnergy()-minimum_energy) > 0 && bestPath != nullptr){
        int healthNeeded = nearestEntity->getValue() - protagonist->getHealth();
        if(healthNeeded < 0){
            std::cout << "set path to nearest enemy at: " << nearestEntity->getXPos() << "," << nearestEntity->getYPos() << std::endl;
            followPath(bestPath);
        }

        else{
            bestPath = nullptr;
            altBestPath = nullptr;
            minimum_energy = 0;
            int alt_minimum_energy = 0;
            int total_healing = 0;
            for(auto& healthpack : model->getMyHealthPacks()){
                required_energy = 0;
                if(!(healthpack->isDefeated())){
                    int healing = std::abs(healthpack->getValue());
                    total_healing += healing;
                    destination_loc.x = healthpack->getXPos();
                    destination_loc.y = healthpack->getYPos();
                    currentPath = model->runPathfinding(protagonist_loc,destination_loc);
                    for(int i = 0; i < currentPath->size()-1; i++){
                        std::pair<int,int> pair = currentPath->at(i);
                        std::pair<int,int> secondPair = currentPath->at(i+1);
                        float pairValue;
                        if(i <= 0) pairValue = original_representation_2D->at(pair.second).at(pair.first).getValue();
                        else pairValue = representation_2D->at(pair.second).at(pair.first)->getValue();
                        float energy_difference = std::abs(pairValue-representation_2D->at(secondPair.second).at(secondPair.first)->getValue());
                        required_energy = required_energy + energy_difference;
                    }
                    if(((required_energy < minimum_energy) || bestPath == nullptr) && (healing >= healthNeeded)){
                        minimum_energy = required_energy;
                        bestPath = currentPath;
                        nearestEntity = healthpack;
                    }
                    else if(required_energy < alt_minimum_energy || altBestPath == nullptr){
                        std::cout << "new alt_minimum_energy " << required_energy << std::endl;
                        alt_minimum_energy = required_energy;
                        altBestPath = currentPath;
                        altNearestEntity = healthpack;
                    }
                }
            }
            if(bestPath != nullptr && (protagonist->getEnergy() - minimum_energy) > 0){
                std::cout << "set path to nearest suitable healthpack" << std::endl;
                followPath(bestPath);
            }
            else if(total_healing >= healthNeeded && (protagonist->getEnergy() - alt_minimum_energy) > 0 && altBestPath != nullptr) {
                std::cout << "set path to nearest healthpack, total healing available still sufficient" << std::endl;
                followPath(altBestPath);

            }
            else{
                std::cout << "alt minimum energy: " << alt_minimum_energy << std::endl;
                strategyEnabled = false;
                emit noPossibleSolution("no possible solution, available healing: " + QString::number(total_healing) + ", health needed to kill nearest enemy: " + QString::number(healthNeeded));
            }
        }

    }
    else{
        strategyEnabled = false;
        emit noPossibleSolution("no possible path to nearest enemy (insufficient energy)");
    }
}

void Strategy::followPath(std::shared_ptr<std::vector<std::pair<int, int>>> path){
    pathToBeFollowed = path;
    emit pathfindingAvailable();
    emit newPathfindingResult(pathToBeFollowed);
    if(!(protagonist->isWalking())) nextMove();
}

void Strategy::nextMove(){
    if(strategyEnabled && pathToBeFollowed != nullptr){ //If strategy is enabled and there's a new path available/old path not yet completed, do a move
        std::cout << "sending new move" << std::endl;
        if(moveIndex >= pathToBeFollowed->size()){
            std::cout << "path complete, calculating new path" << std::endl;
            pathToBeFollowed = nullptr;
            moveIndex = 0;
            if(strategyEnabled) calculateBestPath();
        }
        else{
            std::pair<int,int> nextTile = pathToBeFollowed->at(moveIndex++);
            int dx = std::get<0>(nextTile)-protagonist->getXPos();
            int dy = std::get<1>(nextTile)-protagonist->getYPos();
            std::cout << "dx: " << dx << " dy: " << dy << std::endl;
            if(dx > 0) requestMove(Direction::RIGHT);
            else if(dx < 0) requestMove(Direction::LEFT);
            if(dy > 0) requestMove(Direction::DOWN);
            else if(dy < 0) requestMove(Direction::UP);
            else if(dx == 0 && dy == 0) nextMove();
        }
    }
}

void Strategy::gameEnd(){
    gameEnded = true;
    strategyEnabled = false;
}
