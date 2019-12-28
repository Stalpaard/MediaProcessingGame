#include "modelworld.h"

const int poisonRange {1};
const int default_fieldOfView = 5;
const int deathMaxIndex = 14;
const int idleMaxIndex = 17;
const int walkingMaxIndex = 23;

ModelWorld::ModelWorld(int nrOfEnemies, int nrOfHealthpacks, QString location) : game_ended{false}
{ 
    remainingEnemies = nrOfEnemies;
    emit remainingEnemiesChanged(nrOfEnemies);
    nrOfXenemies = qrand() % (nrOfEnemies/2);
    nrOfEnemies = nrOfEnemies - nrOfXenemies;
    remainingEnemies = remainingEnemies + nrOfXenemies;

    world.createWorld(location,nrOfEnemies,nrOfHealthpacks);
    rows = world.getRows();
    columns = world.getCols();
    fieldOfView = default_fieldOfView;

    initializeAnimations();
    initializeCollections();
}

void ModelWorld::initializeAnimations(){
    protagonist_idle = std::make_shared<std::vector<std::shared_ptr<QImage>>>();
    enemy_idle = std::make_shared<std::vector<std::shared_ptr<QImage>>>();
    penemy_idle = std::make_shared<std::vector<std::shared_ptr<QImage>>>();
    xenemy_idle = std::make_shared<std::vector<std::shared_ptr<QImage>>>();
    zombie_idle = std::make_shared<std::vector<std::shared_ptr<QImage>>>();
    healthpack_idle = std::make_shared<std::vector<std::shared_ptr<QImage>>>();

    for(int i = 0; i <= idleMaxIndex; i++){
        protagonist_idle->push_back(std::make_shared<QImage>(QImage(":img/Animations/MyProtagonist/Idle/" + QString::number(i) + ".png")));
        enemy_idle->push_back(std::make_shared<QImage>(QImage(":img/Animations/MyEnemy/Idle/" + QString::number(i) + ".png")));
        penemy_idle->push_back(std::make_shared<QImage>(QImage(":img/Animations/MyPEnemy/Idle/" + QString::number(i) + ".png")));
        xenemy_idle->push_back(std::make_shared<QImage>(QImage(":img/Animations/MyXEnemy/Idle/" + QString::number(i) + ".png")));
        zombie_idle->push_back(std::make_shared<QImage>(QImage(":img/Animations/MyXEnemyZombie/Idle/" + QString::number(i) + ".png")));
        healthpack_idle->push_back(std::make_shared<QImage>(QImage(":img/Animations/Healthpack/Idle/" + QString::number(i) + ".png")));
    }

    protagonist_dying = std::make_shared<std::vector<std::shared_ptr<QImage>>>();
    enemy_dying = std::make_shared<std::vector<std::shared_ptr<QImage>>>();
    penemy_dying = std::make_shared<std::vector<std::shared_ptr<QImage>>>();
    xenemy_dying = std::make_shared<std::vector<std::shared_ptr<QImage>>>();
    zombie_dying = std::make_shared<std::vector<std::shared_ptr<QImage>>>();

    for(int i = 0; i <= deathMaxIndex; i++){

        protagonist_dying->push_back(std::make_shared<QImage>(QImage(":img/Animations_Dying_Update/MyProtagonist/Dying/" + QString::number(i) + ".png")));
        enemy_dying->push_back(std::make_shared<QImage>(QImage(":img/Animations_Dying_Update/MyEnemy/Dying/" + QString::number(i) + ".png")));
        penemy_dying->push_back(std::make_shared<QImage>(QImage(":img/Animations_Dying_Update/MyPEnemy/Dying/" + QString::number(i) + ".png")));
        xenemy_dying->push_back(std::make_shared<QImage>(QImage(":img/Animations_Dying_Update/MyXEnemy/Dying/" + QString::number(i) + ".png")));
        zombie_dying->push_back(std::make_shared<QImage>(QImage(":img/Animations_Dying_Update/MyXEnemyZombie/Dying/" + QString::number(i) + ".png")));
    }

    protagonist_walking = std::make_shared<std::vector<std::shared_ptr<QImage>>>();

    for(int i = 0; i <= walkingMaxIndex; i++){
        protagonist_walking->push_back(std::make_shared<QImage>(QImage(":img/Animations/MyProtagonist/Walking/" + QString::number(i) + ".png")));
    }
}

void ModelWorld::initializeCollections(){
    //Initializing myTiles
    for(auto& tile : world.getTiles()){
        myTiles.push_back(std::make_shared<MyTile>(tile->getXPos(),tile->getYPos(),tile->getValue()));
    }

    //creating 2D representation
    std::vector<std::shared_ptr<MyTile>> row;
    std::vector<MyTile> original_row;

    for(int i = 0; i < rows ; i++){
        row.clear();
        for(int j = 0; j < columns; j++){
            int index = i*columns+j;
            row.push_back(myTiles.at(index));
            original_row.push_back(*(myTiles.at(index)));
        }
        representation_2D.push_back(row);
        original_representation_2D.push_back(original_row);
    }

    //Initializing healthpacks collections
    for(auto& healthPack : world.getHealthPacks()){
        int xPos = healthPack->getXPos();
        int yPos = healthPack->getYPos();
        std::shared_ptr<MyHealthpack> tempMyHealthPack = std::make_shared<MyHealthpack>(xPos, yPos, -healthPack->getValue(),healthpack_idle,healthpack_idle,healthpack_idle);
        tempMyHealthPack->setWalking(true);//TEMP
        representation_2D.at(yPos).at(xPos)->setOccupant(tempMyHealthPack);
        myEntities.push_back(tempMyHealthPack);
    }

    //Initialize Enemies and PEnemies

    for(auto& enemy : world.getEnemies()){
        int xPos = enemy->getXPos();
        int yPos = enemy->getYPos();
        QString type = typeid(*enemy).name();

        if(type.contains("PEnemy")){
            std::shared_ptr<MyPEnemy> newMyPEnemy = std::make_shared<MyPEnemy>(xPos,yPos,enemy->getValue(),penemy_idle,penemy_dying,protagonist_walking);
            QObject::connect(
                newMyPEnemy.get(), &MyPEnemy::poisonLevelUpdated,
                this, &ModelWorld::poisonTile
            );
            representation_2D.at(yPos).at(xPos)->setOccupant(newMyPEnemy);
            myEntities.push_back(newMyPEnemy);
        }
        else{
            std::shared_ptr<MyEnemy> tempMyEnemy = std::make_shared<MyEnemy>(xPos,yPos,enemy->getValue(),enemy_idle,enemy_dying,protagonist_walking);
            representation_2D.at(yPos).at(xPos)->setOccupant(tempMyEnemy);
            myEntities.push_back(tempMyEnemy);
        }
    }

    //Initializing protagonist
    myProtagonist = std::make_shared<MyProtagonist>(protagonist_idle,protagonist_dying,protagonist_walking);
    QObject::connect(
        myProtagonist.get(), &MyProtagonist::posChanged,
        this, &ModelWorld::broadcastPositionChange
    );
    QObject::connect(
        myProtagonist.get(), &MyProtagonist::healthChanged,
        this, &ModelWorld::broadcastHealthChange
    );
    QObject::connect(
        myProtagonist.get(), &MyProtagonist::energyChanged,
        this, &ModelWorld::broadcastEnergyChange
    );

    // Initialize XEnemies
    int currentXEnemies = 0;
    while(currentXEnemies < nrOfXenemies){
        std::pair<int,int> position = generateNewEnemyPosition();
        int xPos = std::get<0>(position);
        int yPos = std::get<1>(position);
        std::shared_ptr<MyTile> tile = representation_2D.at(yPos).at(xPos);
        std::shared_ptr<MyXEnemy> tempMyXenemy = std::make_shared<MyXEnemy>(xPos,yPos,qrand()%100,xenemy_idle,xenemy_dying,protagonist_walking);
        QObject::connect(
            tempMyXenemy.get(), &MyXEnemy::respawn,
            this, &ModelWorld::respawnEnemy
        );
        tile->setOccupant(tempMyXenemy);
        currentXEnemies++;
        myEntities.push_back(tempMyXenemy);
    }


}

std::pair<int,int> ModelWorld::generateNewEnemyPosition(){
    int limit = rows*columns;
    int count = 0;
    while(count <= limit){
        int newX = qrand()%columns;
        int newY = qrand()%rows;
        if(newX == myProtagonist->getXPos() && newY == myProtagonist->getYPos()) continue;
        std::shared_ptr<MyTile> tile = representation_2D.at(newY).at(newX);
        if(!(tile->isOccupied()) && tile->getValue() < std::numeric_limits<float>::infinity()){
            return std::make_pair(newX,newY);
        }
        count++;
    }
    std::cout << "No more tiles available" << std::endl;
    return std::make_pair(rows+1,columns+1);
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

std::shared_ptr<std::vector<std::pair<int,int>>> ModelWorld::runPathfinding(GridLocation start, GridLocation finish){
    pathfindingAlgorithm = std::make_shared<aStarFast>(*(get2DRepresentation()),columns,rows); //needed for reset
    pathfindingAlgorithm->a_star_search(start, finish);
    algoResult = std::make_shared<std::vector<std::pair<int,int>>>(pathfindingAlgorithm->reconstruct_path(start,finish,pathfindingAlgorithm->came_from));
    for(std::pair<int,int> p : *algoResult)
    {
        std::cout<<p.first<<"--"<<p.second<<std::endl;
    }
    return algoResult;
}

//SLOTS

void ModelWorld::pathfindingViewRequest(int destX, int destY){
    std::cout<<"PATHFINDING INITIATED!!!"<<std::endl;
    GridLocation start,finish;
    start.x=getMyProtagonist()->getXPos();
    start.y=getMyProtagonist()->getYPos();
    finish.x=destX;
    finish.y=destY;
    std::shared_ptr<std::vector<std::pair<int,int>>> path = runPathfinding(start,finish);
    emit newPathfindingResult(path);
    emit pathfindingAvailable();
}

void ModelWorld::respawnEnemy(int x, int y){
    std::shared_ptr<MyTile> tile = representation_2D.at(y).at(x);
    tile->setOccupied(false);
    tile->setValue(original_representation_2D.at(y).at(x).getValue());
    std::shared_ptr<Entity> enemy = tile->getOccupant();
    enemy->setIdleAnimations(zombie_idle);
    enemy->setDeathAnimations(zombie_dying);
    enemy->setDefeated(false);
    std::tuple<int,int> newPosition = generateNewEnemyPosition();
    int newX = std::get<0>(newPosition);
    int newY = std::get<1>(newPosition);
    if(newX < columns && newY < rows){
        enemy->setXPos(newX);
        enemy->setYPos(newY);
        representation_2D.at(newY).at(newX)->setOccupant(enemy);
    }
    else std::cout << "Not possible to respawn enemy" << std::endl;
}

void ModelWorld::zoomRequested(bool in_out){
    if(in_out) setFieldOfView(fieldOfView-1);
    else setFieldOfView(fieldOfView+1);
    emit updateView();
}

void ModelWorld::broadcastPositionChange(int x, int y){
    if(x > 0) emit protagonistMovingDirection(Direction::RIGHT);
    else if(x < 0) emit protagonistMovingDirection(Direction::LEFT);
    if(y > 0) emit protagonistMovingDirection(Direction::UP);
    else if(y < 0) emit protagonistMovingDirection(Direction::DOWN);
    emit protagonistPositionChanged(myProtagonist->getXPos(), myProtagonist->getYPos());
    emit changeCameraCenter(x,y);
}

void ModelWorld::broadcastHealthChange(int h){
    emit protagonistHealthChanged(h);
    if(h <= 0){
        if(!game_ended){
            emit gameDefeat("Protagonist dead");
            game_ended = true;
            emit endGame();
        }
    }
}

void ModelWorld::noPossibleSolution(QString reason){
    if(!game_ended){
        emit gameDefeat(reason);
        game_ended = true;
        emit endGame();
    }
}

void ModelWorld::broadcastEnergyChange(int e){
    emit protagonistEnergyChanged(e);
}

void ModelWorld::protagonistMoveRequested(Direction direction){
    if(!(myProtagonist->isWalking()) && !game_ended){
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
            float costOfMovement = std::abs(destinationTile->getValue()-original_representation_2D.at(currentY).at(currentX).getValue());
            if(currentEnergy > costOfMovement){
                myProtagonist->setWalking(true);
                myProtagonist->setEnergy(currentEnergy-costOfMovement);
                if(Xchanged) myProtagonist->setXPos(newX);
                else if(Ychanged) myProtagonist->setYPos(newY);
                std::cout << "Protagonist has new position: x = " << myProtagonist->getXPos() << " / y = " << myProtagonist->getYPos() << std::endl;

                if(destinationTile->isOccupied() && !(destinationTile->getOccupant()->isDefeated())){
                    std::shared_ptr<Entity> occupant = destinationTile->getOccupant();
                    float occupantStrength = occupant->getValue();
                    float newHealth = myProtagonist->getHealth() - occupantStrength;
                    if(newHealth > 0){
                        if(newHealth > 100) myProtagonist->setHealth(100);
                        else myProtagonist->setHealth(newHealth);
                        if(occupantStrength > 0){
                            destinationTile->setValue(std::numeric_limits<float>::infinity()); //defeated enemy creates impassable tile, healthpacks not however
                            myProtagonist->setEnergy(100.0f); //Defeating enemies restores energy
                            remainingEnemies--;
                            emit remainingEnemiesChanged(remainingEnemies);
                            if(remainingEnemies == 0 && !game_ended){
                                emit gameVictory();
                                game_ended = true;
                                emit endGame();
                            }
                        }
                        else destinationTile->setOccupied(false); //remove visualization
                        occupant->setDefeated(true);
                    }
                    else myProtagonist->setHealth(0);
                }
                std::cout << "Current health: " << myProtagonist->getHealth() << " Current energy: " << myProtagonist->getEnergy() << "\n" << std::endl;
            }
            else std::cout << "Insufficient energy for requested movement\n" << std::endl;
        }
    }
}

void ModelWorld::protagonistMoveCompleted(){
    myProtagonist->setWalking(false);
}

void ModelWorld::poisonTile(float value, int x, int y){
    if(!game_ended){
        //Protagonist operation first because first time no poison after defeating enemy
        float protagonistPoison = representation_2D.at(myProtagonist->getYPos()).at(myProtagonist->getXPos())->getPoisonLevel();
        if(protagonistPoison > 0){
            float newHealth = myProtagonist->getHealth()-protagonistPoison;

            if(newHealth > 0) myProtagonist->setHealth(myProtagonist->getHealth()-protagonistPoison);
            else myProtagonist->setHealth(0);
            std::cout << "Protagonist took " << protagonistPoison << " poison damage!" << std::endl;
        }

        //Set poison levels and pass pairs of (int,int) to views
        int startY = y-poisonRange;
        int startX = x-poisonRange;
        std::vector<std::pair<int,int>> pairs;

        for(int i = 0; i <= 2*poisonRange; i++){
            for(int j = 0; j <= 2*poisonRange; j++){
                int tileX = startX+i;
                int tileY = startY+j;
                if(tileX >= 0 && tileY >= 0 && tileX < rows && tileY < columns){
                    pairs.push_back(std::make_pair(tileX,tileY));
                    if(value < 0) representation_2D.at(tileY).at(tileX)->setPoisonLevel(0);
                    else representation_2D.at(tileY).at(tileX)->setPoisonLevel(value);
                }
            }
        }
        emit poisonVisualChange(pairs, value);
    }
}


