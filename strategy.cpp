#include "strategy.h"

Strategy::Strategy(std::shared_ptr<ModelWorld> model) : model{model}, pathToBeFollowed{nullptr}, moveIndex{0}, strategyEnabled{false}, gameEnded{false}
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

void Strategy::toggleStrategy()
{
    if(strategyEnabled) enableStrategy(false);
    else enableStrategy(true);
}

void Strategy::calculateBestPath(){
    float required_energy = 0;
    float minimum_energy = 0;

    bestPath = nullptr;
    std::shared_ptr<Entity> nearestEntity = nullptr;
    std::shared_ptr<Entity> altNearestEntity = nullptr;

    protagonist_loc = protagonist->getYPos()*model->getColumns()+protagonist->getXPos();
    //Check for path to nearest enemy
    for(auto& entity : *model->getMyEntities()){
        if(!(entity->isDefeated())){
            if(entity->getValue() > 0){
                required_energy = calculateRequiredEnergyToEntity(protagonist_loc,entity);
                if((required_energy < minimum_energy) || bestPath == nullptr){
                    minimum_energy = required_energy;
                    bestPath = currentPath;
                    nearestEntity = entity;
                }
            }
        }
    }
    if((protagonist->getEnergy()-minimum_energy) > 0 && bestPath != nullptr){
        //Check if the protagonist can defeat the nearest enemy
        int healthNeeded = nearestEntity->getValue() - protagonist->getHealth();
        if(healthNeeded < 0){
            //std::cout << "set path to nearest enemy at: " << nearestEntity->getXPos() << "," << nearestEntity->getYPos() << std::endl;
            followPath(bestPath);
        }

        else{
            //Search nearest suitable healthpack or go to the nearest healthpack if total available healing is sufficient, else no possible solution
            bestPath = nullptr;
            altBestPath = nullptr;
            minimum_energy = 0;
            int alt_minimum_energy = 0;
            int total_healing = 0;
            for(auto& entity : *model->getMyEntities()){
                if(!(entity->isDefeated()) && entity->getValue() < 0){
                    required_energy = calculateRequiredEnergyToEntity(protagonist_loc, entity);
                    int healing = std::abs(entity->getValue());
                    total_healing += healing;
                    if(((required_energy < minimum_energy) || bestPath == nullptr) && (healing >= healthNeeded)){
                        minimum_energy = required_energy;
                        bestPath = currentPath;
                        nearestEntity = entity;
                    }
                    else if(required_energy < alt_minimum_energy || altBestPath == nullptr){
                        //std::cout << "new alt_minimum_energy " << required_energy << std::endl;
                        alt_minimum_energy = required_energy;
                        altBestPath = currentPath;
                        altNearestEntity = entity;
                    }
                }
            }
            if(bestPath != nullptr && (protagonist->getEnergy() - minimum_energy) > 0){
                //std::cout << "set path to nearest suitable healthpack" << std::endl;
                followPath(bestPath);
            }
            else if(total_healing >= healthNeeded && (protagonist->getEnergy() - alt_minimum_energy) > 0 && altBestPath != nullptr) {
                //std::cout << "set path to nearest healthpack, total healing available still sufficient" << std::endl;
                followPath(altBestPath);

            }
            else{
                //std::cout << "alt minimum energy: " << alt_minimum_energy << std::endl;
                strategyEnabled = false;
                emit noPossibleSolution("no possible solution, available healing: " + QString::number(total_healing) + ", health needed to kill nearest enemy: " + QString::number(healthNeeded));
            }
        }

    }
    else{
        //Not enough energy to go to nearest enemy => no possible solution
        strategyEnabled = false;
        emit noPossibleSolution("no possible path to nearest enemy (insufficient energy)");
    }
}

float Strategy::calculateRequiredEnergyToEntity(int protagonist_loc, std::shared_ptr<Entity> entity){
    //Run pathfinding algorithm and make a sum of the required energies
    int destination_loc;
    float required_energy = 0;
    /*destination_loc.x = entity->getXPos();
    destination_loc.y = entity->getYPos();*/
    destination_loc = entity->getYPos()*model->getColumns()+entity->getXPos();
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
    return required_energy;
}

void Strategy::followPath(std::shared_ptr<std::vector<std::pair<int, int>>> path){
    //Assign pathToBeFollowed and let the views know that a path calculated by pathfinding is available
    pathToBeFollowed = path;
    emit pathfindingAvailable();
    emit newPathfindingResult(pathToBeFollowed); //needed to reimplement signals, otherwise every calculated path would be shown
    //If protagonist is idle, do next move
    if(!(protagonist->isWalking())) nextMove();
}

void Strategy::nextMove(){
    //Do the next move pointed to by moveIndex, if path complete, calculate next path
    if(strategyEnabled && pathToBeFollowed != nullptr){ //If strategy is enabled and there's a new path available/old path not yet completed, do a move
        //std::cout << "sending new move" << std::endl;
        if(moveIndex >= pathToBeFollowed->size()){
            //std::cout << "path complete, calculating next path" << std::endl;
            pathToBeFollowed = nullptr;
            moveIndex = 0;
            if(strategyEnabled) calculateBestPath();
        }
        else{
            std::pair<int,int> nextTile = pathToBeFollowed->at(moveIndex++);
            int dx = std::get<0>(nextTile)-protagonist->getXPos();
            int dy = std::get<1>(nextTile)-protagonist->getYPos();
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
