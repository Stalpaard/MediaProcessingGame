#include "modelworld.h"
#include "iostream"

const int poisonRange {1};
const int default_fieldOfView = 5;

ModelWorld::ModelWorld(unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, std::string location)
{ 
    nrOfXenemies = qrand() % nrOfEnemies;
    nrOfEnemies = nrOfEnemies - nrOfXenemies;
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
    for(auto& tile : world.getTiles()){
        myTiles.push_back(std::make_shared<MyTile>(tile->getXPos(),tile->getYPos(),tile->getValue()));
    }

    //creating 2D representation
    std::vector<std::shared_ptr<MyTile>> row;

    for(int i = 0; i < rows ; i++){
        row.clear();
        for(int j = 0; j < columns; j++){
            int index = i*columns+j;
            row.push_back(myTiles.at(index));
        }
        representation_2D.push_back(row);
    }

    //Initializing healthpacks collections
    for(auto& healthPack : world.getHealthPacks()){
        int xPos = healthPack->getXPos();
        int yPos = healthPack->getYPos();
        std::shared_ptr<MyHealthpack> tempMyHealthPack = std::make_shared<MyHealthpack>(xPos, yPos, -healthPack->getValue(),healthpack_image.get());
        representation_2D.at(yPos).at(xPos)->setOccupant(tempMyHealthPack);
        myHealthPacks.push_back(tempMyHealthPack);
    }

    //Initializing enemies collections (Penemy/enemy/Xenemy)

    for(auto& enemy : world.getEnemies()){
        int xPos = enemy->getXPos();
        int yPos = enemy->getYPos();
        std::string type = typeid(*(enemy.get())).name();

        if(type.find("PEnemy") != std::string::npos){
            std::shared_ptr<MyPEnemy> newMyPEnemy = std::make_shared<MyPEnemy>(xPos,yPos,enemy->getValue(),penemy_image.get());
            QObject::connect(
                newMyPEnemy.get(), &MyPEnemy::poisonLevelUpdated,
                this, &ModelWorld::poisonTile
            );
            representation_2D.at(yPos).at(xPos)->setOccupant(newMyPEnemy);
            myPEnemies.push_back(newMyPEnemy);
        }
        else{
            std::shared_ptr<MyEnemy> tempMyEnemy = std::make_shared<MyEnemy>(xPos,yPos,enemy->getValue(),enemy_image.get());
            representation_2D.at(yPos).at(xPos)->setOccupant(tempMyEnemy);
            myEnemies.push_back(tempMyEnemy);
        }
    }
    //Initializing protagonist
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

    while(myXEnemies.size() < nrOfXenemies){
        std::tuple<int,int> position = generateNewEnemyPosition();
        int xPos = std::get<0>(position);
        int yPos = std::get<1>(position);
        std::shared_ptr<MyTile> tile = representation_2D.at(yPos).at(xPos);
        std::shared_ptr<MyXEnemy> tempMyXenemy = std::make_shared<MyXEnemy>(xPos,yPos,qrand()%100,xenemy_image.get());
        QObject::connect(
            tempMyXenemy.get(), &MyXEnemy::respawn,
            this, &ModelWorld::respawnEnemy
        );
        tile->setOccupant(tempMyXenemy);
        myXEnemies.push_back(tempMyXenemy);
    }

}

std::tuple<int,int> ModelWorld::generateNewEnemyPosition(){ //kan ook nog met oude collectie geïmplementeerd worden..
    bool valid = false;
    while(!valid){
        int newX = qrand()%columns;
        int newY = qrand()%rows;
        if(newX == myProtagonist->getXPos() && newY == myProtagonist->getYPos()) continue;
        std::shared_ptr<MyTile> tile = representation_2D.at(newY).at(newX);
        if(!(tile->isOccupied()) && tile->getValue() != std::numeric_limits<float>::infinity()){
            valid = true;
            return std::make_tuple(newX,newY);
        }
    }
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

void ModelWorld::respawnEnemy(int x, int y){
    std::shared_ptr<MyTile> tile = representation_2D.at(y).at(x);
    tile->setOccupied(false);
    std::shared_ptr<MyEnemy> enemy = tile->getOccupant();
    enemy->setRepresentation(xenemy_image.get()); //zombie
    std::tuple<int,int> newPosition = generateNewEnemyPosition();
    int newX = std::get<0>(newPosition);
    int newY = std::get<1>(newPosition);
    enemy->setXPos(newX);
    enemy->setYPos(newY);
    representation_2D.at(newY).at(newX)->setOccupant(enemy);
}

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
        std::shared_ptr<MyTile> destinationTile = representation_2D.at(newY).at(newX);
        float costOfMovement = destinationTile->getValue();
        if(currentEnergy > costOfMovement){
            myProtagonist->setEnergy(currentEnergy-costOfMovement);
            if(Xchanged) myProtagonist->setXPos(newX);
            else if(Ychanged) myProtagonist->setYPos(newY);
            std::cout << "Protagonist has new position: x = " << myProtagonist->getXPos() << " / y = " << myProtagonist->getYPos() << std::endl;

            //if occupied, check damage/heal, if not defeated, change special tile image, if defeated, end game
            if(destinationTile->isOccupied() && !(destinationTile->getOccupant()->getDefeated())){
                std::shared_ptr<MyEnemy> occupant = destinationTile->getOccupant();
                float occupantStrength = occupant->getValue();
                float newHealth = myProtagonist->getHealth() - occupantStrength;
                if(newHealth > 0){
                    if(newHealth > 100) myProtagonist->setHealth(100);
                    else myProtagonist->setHealth(newHealth);
                    if(occupantStrength > 0){
                        destinationTile->setValue(std::numeric_limits<float>::infinity()); //defeated enemy creates impassable tile, healthpacks not however
                        occupant->setRepresentation(gravestone_image.get());
                        myProtagonist->setEnergy(100.0f); //Defeating enemies restores energy
                    }
                    else destinationTile->setOccupied(false);
                    occupant->setDefeated(true);
                }
                else myProtagonist->setHealth(0);
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
        else myProtagonist->setHealth(0);
        std::cout << "Protagonist took poison damage!" << std::endl;
    }
    //Set poison levels and pass tuples of (int,int) to views
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
