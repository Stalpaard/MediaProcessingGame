#include "strategy.h"
#include <iostream>

Strategy::Strategy(std::shared_ptr<ModelWorld> model) : model{model}, strategyEnabled{false}, moveIndex{0}, pathToBeFollowed{nullptr}
{
    protagonist = model->getMyProtagonist();
    representation_2D = model->get2DRepresentation();
}

void Strategy::enableStrategy(bool newvalue){

    strategyEnabled = newvalue;
    if(strategyEnabled) calculateBestPath();
    else pathToBeFollowed = nullptr;
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
                for(int i = 1; i < currentPath->size(); i++){
                    std::pair<int,int> pair = currentPath->at(i);

                    float newvalue = representation_2D->at(pair.second).at(pair.first)->getValue();
                    required_energy = required_energy + newvalue;
                }
                if((required_energy < minimum_energy) || minimum_energy == 0){
                    minimum_energy = required_energy;
                    bestPath = currentPath;
                    nearestEntity = entity;
                }
            }
        }
    }
    if((protagonist->getEnergy()-minimum_energy) > 0 && minimum_energy != 0){
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
                    if(healing >= healthNeeded){
                        destination_loc.x = healthpack->getXPos();
                        destination_loc.y = healthpack->getYPos();
                        currentPath = model->runPathfinding(protagonist_loc,destination_loc);
                        for(int i = 1; i < currentPath->size(); i++){
                            std::pair<int,int> pair = currentPath->at(i);
                            required_energy = required_energy + representation_2D->at(std::get<1>(pair)).at(std::get<0>(pair))->getValue();
                        }
                        if(((required_energy < minimum_energy) || minimum_energy == 0) && (healing >= healthNeeded)){
                            minimum_energy = required_energy;
                            bestPath = currentPath;
                            nearestEntity = healthpack;
                        }
                        else if(required_energy < alt_minimum_energy || alt_minimum_energy <= 0){
                            std::cout << "new alt_minimum_energy " << required_energy << std::endl;
                            alt_minimum_energy = required_energy;
                            altBestPath = currentPath;
                            altNearestEntity = healthpack;
                        }
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
                emit noPossibleSolution();
                std::cout << "no possible solution, total healing: " << total_healing << ", health needed: " << healthNeeded << std::endl;
            }
        }

    }
    else{
        strategyEnabled = false;
        emit noPossibleSolution();
        std::cout << "no possible path to enemy (insufficient energy)" << std::endl;
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
    strategyEnabled = false;
}
