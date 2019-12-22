#include "modelworld.h"
#include "iostream"

const int poisonRange {1};
const int default_fieldOfView = 5;

ModelWorld::ModelWorld(unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, std::string location)
{ 
    world.createWorld(location.c_str(),nrOfEnemies,nrOfHealthpacks);
    protagonist_image = std::make_shared<QImage>(":img/protagonist.png");
    enemy_image = std::make_shared<QImage>(":img/enemy.png");
    penemy_image = std::make_shared<QImage>(":img/Penemy.png");
    xenemy_image = std::make_shared<QImage>(":img/Xenemy.png");
    gravestone_image = std::make_shared<QImage>(":img/gravestone.png");
    healthpack_image = std::make_shared<QImage>(":img/healthpack.png");
    rows = world.getRows();
    columns = world.getCols();
    fieldOfView = default_fieldOfView;
    initializeCollections();

}

void ModelWorld::initializeCollections(){
    //Initializing tiles and mytiles collections
    std::vector<std::unique_ptr<Tile>> tempTiles = world.getTiles();
    for(unsigned long i = 0; i < tempTiles.size(); i++){
        std::shared_ptr<Tile> tempTile = std::move(tempTiles.at(i));
        myTiles.push_back(std::make_shared<MyTile>(tempTile->getXPos(),tempTile->getYPos(),tempTile->getValue()));
        tiles.push_back(std::move(tempTile));
    }
    //creating 2D representation
    std::vector<std::shared_ptr<MyTile>> row;
    for(int i = 0; i < rows ; i++){
        row.clear();
        for(int j = 0; j < columns; j++){
            int index = i*columns+j;
            row.push_back(myTiles.at(index));
        }
        representation_2D.push_back(std::move(row));
    }

    //Initializing healthpacks collections
    std::vector<std::unique_ptr<Tile>> tempHealthpacks = world.getHealthPacks();
    for(unsigned long i = 0; i < tempHealthpacks.size(); i++){
        std::shared_ptr<Tile> newHealthPack = std::move(tempHealthpacks.at(i));
        int xPos = newHealthPack->getXPos();
        int yPos = newHealthPack->getYPos();
        std::shared_ptr<MyHealthpack> tempMyHealthPack = std::make_shared<MyHealthpack>(xPos, yPos, -newHealthPack->getValue(),healthpack_image.get());
        representation_2D.at(yPos).at(xPos)->setOccupant(tempMyHealthPack);
        healthPacks.push_back(std::move(newHealthPack));
        myHealthPacks.push_back(tempMyHealthPack);
    }


    //Initializing enemies collections (Penemy/enemy)
    std::vector<std::unique_ptr<Enemy>> tempEnemies = world.getEnemies();
    for(unsigned long i = 0; i < tempEnemies.size(); i++){
        std::shared_ptr<Enemy> newEnemy = std::move(tempEnemies.at(i));
        int xPos = newEnemy->getXPos();
        int yPos = newEnemy->getYPos();
        std::string type = typeid(*(newEnemy.get())).name();

        if(type.find("PEnemy") != std::string::npos){
            std::cout << "PEnemy created at " << xPos <<","<<yPos<< std::endl;
            std::shared_ptr<MyPEnemy> newMyPEnemy = std::make_shared<MyPEnemy>(xPos,yPos,newEnemy->getValue(),penemy_image.get());
            QObject::connect(
                newMyPEnemy.get(), &MyPEnemy::poisonLevelUpdated,
                this, &ModelWorld::poisonTile
            );
            representation_2D.at(yPos).at(xPos)->setOccupant(newMyPEnemy);
            myPEnemies.push_back(newMyPEnemy);
        }
        else{
            std::shared_ptr<MyEnemy> tempMyEnemy = std::make_shared<MyEnemy>(xPos,yPos,newEnemy->getValue(),enemy_image.get());
            representation_2D.at(yPos).at(xPos)->setOccupant(tempMyEnemy);
            myEnemies.push_back(tempMyEnemy);
        }
        enemies.push_back(std::move(newEnemy));
    }

    //Initializing protagonist
    std::unique_ptr<Protagonist> world_protagonist = world.getProtagonist();
    protagonist = std::move(world_protagonist);
    myProtagonist = std::make_shared<MyProtagonist>(protagonist_image.get());
    QObject::connect(
        myProtagonist.get(), &MyProtagonist::posChanged,
        this, &ModelWorld::cameraCenterChangeRequested
    );
    QObject::connect(
        myProtagonist.get(), &MyProtagonist::healthChanged,
        this, &ModelWorld::broadcastHealthChange
    );
    QObject::connect(
        myProtagonist.get(), &MyProtagonist::energyChanged,
        this, &ModelWorld::broadcastEnergyChange
    );

}


std::vector<std::vector<std::shared_ptr<MyTile>>> ModelWorld::make2DRepresentationAroundPointWithRange(int xPos, int yPos, int range){
    std::vector<std::vector<std::shared_ptr<MyTile>>> result;

    int firstYpos = yPos - range;
    int lastYpos = yPos + range;
    int firstXpos = xPos - range;
    int lastXpos = xPos + range;

    if(firstYpos < 0) firstYpos = 0;
    if(lastYpos > rows) lastYpos = rows;
    if(firstXpos < 0) firstXpos = 0;
    if(lastXpos > columns) lastXpos = columns;

    auto firstY = representation_2D.begin() + firstYpos;
    auto lastY = representation_2D.begin() + lastYpos;

    std::vector<std::vector<std::shared_ptr<MyTile>>> ySlice(firstY,lastY);

    for(auto& row : ySlice){
        auto firstX = row.begin() + firstXpos;
        auto lastX = row.begin() + lastXpos;
        result.push_back(std::vector<std::shared_ptr<MyTile>>(firstX,lastX));
    }
    return result;
}


//SLOTS
void ModelWorld::zoomRequested(bool in_out){
    if(in_out) setFieldOfView(fieldOfView-1);
    else setFieldOfView(fieldOfView+1);
    emit updateView();
}

void ModelWorld::cameraCenterChangeRequested(int x, int y){
    emit changeCameraCenter(x,y);
}

void ModelWorld::broadcastHealthChange(int h){
    emit protagonistHealthChanged(h);
    if(h <= 0) emit endGame();
}

void ModelWorld::broadcastEnergyChange(int e){
    emit protagonistEnergyChanged(e);
}

void ModelWorld::protagonistMoveRequested(Direction direction){
    int currentX = myProtagonist->getXPos();
    int currentY = myProtagonist->getYPos();
    int newX=currentX;
    int newY=currentY;
    bool Xchanged = false;
    bool Ychanged = false;

    switch(direction){
        case Direction::DOWN : //Down and up flipped due to flipped y-axis
        if(currentY + 1 < rows){
            newY = currentY + 1;
            Ychanged = true;
        }
        break;
    case Direction::UP :
        if(currentY - 1 >= 0){
            newY = currentY - 1;
            Ychanged = true;
        }
        break;
    case Direction::LEFT :
        if(currentX - 1 >= 0){
            newX = currentX - 1;
            Xchanged = true;
        }
        break;
    case Direction::RIGHT :
        if(currentX + 1 < columns){
            newX = currentX + 1;
            Xchanged = true;
        }
        break;
    }

    if(Xchanged || Ychanged){
        float currentEnergy = myProtagonist->getEnergy();
        MyTile* destinationTile = representation_2D.at(newY).at(newX).get();
        float costOfMovement = destinationTile->getValue();
        if(currentEnergy > costOfMovement){
            myProtagonist->setEnergy(currentEnergy-costOfMovement);
            if(Xchanged) myProtagonist->setXPos(newX);
            else if(Ychanged) myProtagonist->setYPos(newY);
            std::cout << "Protagonist has new position: x = " << myProtagonist->getXPos() << " / y = " << myProtagonist->getYPos() << std::endl;

            //if occupied, check damage/heal, if not defeated, change special tile image, if defeated, end game
            if(destinationTile->isOccupied() && !(destinationTile->getOccupant()->getDefeated())){
                MyEnemy* occupant = destinationTile->getOccupant();
                float occupantStrength = occupant->getValue();
                float newHealth = myProtagonist->getHealth() - occupantStrength;
                if(newHealth > 0){
                    if(newHealth > 100) myProtagonist->setHealth(100);
                    else myProtagonist->setHealth(newHealth);
                    occupant->setDefeated(true);

                    if(occupantStrength > 0){
                        destinationTile->setValue(std::numeric_limits<float>::infinity()); //defeated enemy creates impassable tile, healthpacks not however
                        occupant->setRepresentation(gravestone_image.get());
                        myProtagonist->setEnergy(100.0f); //Defeating enemies restores energy
                    }
                    else destinationTile->setOccupied(false);
                }
                else{
                    myProtagonist->setHealth(0);
                }
            }
            else{
                std::cout << "Tile not occupied!\n" << std::endl;
            }
            std::cout << "Current health: " << myProtagonist->getHealth() << " Current energy: " << myProtagonist->getEnergy() << "\n" << std::endl;

            emit updateView();
        }
        else {
            std::cout << "Insufficient energy for requested movement\n" << std::endl;
        }

    }

}

void ModelWorld::poisonTile(float value, int x, int y){
    //Protagonist operation first because first time no poison after defeating enemy
    float protagonistPoison = representation_2D.at(myProtagonist->getYPos()).at(myProtagonist->getXPos())->getPoisonLevel();
    if(protagonistPoison > 0){
        float newHealth = myProtagonist->getHealth()-protagonistPoison;
        if(newHealth > 0) myProtagonist->setHealth(myProtagonist->getHealth()-protagonistPoison);
        std::cout << "Protagonist took poison damage!" << std::endl;
    }
    //Set poison levels and pass tuples to views
    unsigned long startY = y-poisonRange;
    unsigned long startX = x-poisonRange;
    std::vector<std::tuple<int,int>> tuples;

    for(int i = 0; i <= 2*poisonRange; i++){
        for(int j = 0; j <= 2*poisonRange; j++){
            int tileX = startX+i;
            int tileY = startY+j;
            tuples.push_back(std::make_tuple(tileX,tileY));
            if(tileX > 0 && tileY > 0 && tileX < rows && tileY < columns){
                if(value < 0) representation_2D.at(tileY).at(tileX)->setPoisonLevel(0);
                else representation_2D.at(tileY).at(tileX)->setPoisonLevel(value);
            }
        }
    }
    emit poisonVisualChange(tuples, value);
}
