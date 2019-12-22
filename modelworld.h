#ifndef MODELWORLD_H
#define MODELWORLD_H

#include "world.h"
#include "QObject"
#include "QGraphicsPixmapItem"
#include "direction.h"
#include "mytile.h"
#include "myenemy.h"
#include "myhealthpack.h"
#include "mypenemy.h"
#include <string>



class ModelWorld : public QObject
{
    Q_OBJECT

public:
    ModelWorld(unsigned int nrOfEnemies, unsigned int nrOfHealthpacks);
    std::vector<std::shared_ptr<Tile>> getTiles() const{return tiles;}
    std::vector<std::shared_ptr<Enemy>> getEnemies() const{return enemies;}
    std::vector<std::shared_ptr<MyEnemy>> getMyEnemies() const{return myEnemies;}
    std::vector<std::shared_ptr<MyPEnemy>> getMyPEnemies() const{return myPEnemies;}
    std::vector<std::shared_ptr<Tile>> getHealthPacks() const{return healthPacks;}
    std::vector<std::shared_ptr<MyHealthpack>> getMyHealthPacks() const{return myHealthPacks;}
    std::shared_ptr<Protagonist> getProtagonist() const{return protagonist;}
    std::vector<std::vector<std::shared_ptr<MyTile>>> get2DRepresentation() const{return representation_2D;}


private:
    void createWorld(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks);
    void initializeCollections();
    void moveProtagonist(Direction direction);
    void addOccupantToTile(std::shared_ptr<Tile> newEnemy);

    World world;
    int rows;
    int columns;


    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<MyTile>> myTiles;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<MyEnemy>> myEnemies;
    std::vector<std::shared_ptr<MyPEnemy>> myPEnemies;
    std::vector<std::shared_ptr<Tile>> healthPacks;
    std::vector<std::shared_ptr<MyHealthpack>> myHealthPacks;


    std::shared_ptr<Protagonist> protagonist;

    std::vector<std::vector<std::shared_ptr<MyTile>>> representation_2D;

public slots:
    void protagonistMoveRequested(Direction direction);
    void poisonTile(float value, int x, int y);
signals:
    void updateView();
    void endGame();
    void poisonVisualChange(std::vector<std::tuple<int,int>>, float level);

};




#endif // MODELWORLD_H
