#include "modelworld.h"
#include "iostream"

ModelWorld::ModelWorld(unsigned int nrOfEnemies, unsigned int nrOfHealthpacks)
{ 
    world.createWorld(":img/worldmap.png",nrOfEnemies,nrOfHealthpacks);
    moveCollections();

    QObject::connect(protagonist.get(), &Protagonist::posChanged, this, &ModelWorld::printPosition);

    std::vector<std::shared_ptr<Tile>> row;

    for(int i = 0; i < rows ; i++){
        row.clear();
        for(int j = 0; j < columns; j++){
            int index = i*columns+j;
            row.push_back(tiles.at(index));
        }
        representation_2D.push_back(row);
    }

}

void ModelWorld::moveCollections(){
    std::vector<std::unique_ptr<Tile>> world_tiles = world.getTiles();
    for(unsigned long i = 0; i < world_tiles.size(); i++){
        tiles.push_back(std::move(world_tiles.at(i)));
    }

    std::vector<std::unique_ptr<Tile>> world_healthpacks = world.getHealthPacks();
    for(unsigned long i = 0; i < world_healthpacks.size(); i++){
        healthPacks.push_back(std::move(world_healthpacks.at(i)));
    }

    std::vector<std::unique_ptr<Enemy>> world_enemies = world.getEnemies();
    for(unsigned long i = 0; i < world_enemies.size(); i++){
        enemies.push_back(std::move(world_enemies.at(i)));
    }



    std::unique_ptr<Protagonist> world_protagonist = world.getProtagonist();
    protagonist = std::move(world_protagonist);

    rows = world.getRows();
    columns = world.getCols();
}

void ModelWorld::moveProtagonist(Direction direction){

    int oldX = protagonist->getXPos();
    int oldY = protagonist->getYPos();
    switch (direction){
    case UP:
        if(oldY + 1 < rows){
            protagonist->setYPos(oldY+1);
        }
        break;

    case DOWN:
        if(oldY-1 >= 0){
            protagonist->setYPos(oldY-1);
        }
        break;

    case LEFT:
        if(oldX-1 >= 0){
            protagonist->setXPos(oldX-1);
        }
        break;

    case RIGHT:
        if(oldX+1 < columns){
            protagonist->setXPos(oldX+1);
        }
        break;

    }

}

void ModelWorld::printPosition(int x, int y){
    std::cout << "Protagonist has new position: x = " << x << " / y = " << y << std::endl;
}
