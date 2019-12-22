#ifndef MODELWORLD_H
#define MODELWORLD_H

#include "world.h"
#include "QObject"
#include "QGraphicsPixmapItem"
#include "direction.h"
#include "mytile.h"
#include "myenemy.h"
#include "myhealthpack.h"
#include "myprotagonist.h"
#include "mypenemy.h"
#include "myxenemy.h"
#include <string>



class ModelWorld : public QObject
{
    Q_OBJECT

public:
    ModelWorld(unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, std::string location);
    std::vector<std::shared_ptr<MyEnemy>> getMyEnemies() const{return myEnemies;}
    std::vector<std::shared_ptr<MyPEnemy>> getMyPEnemies() const{return myPEnemies;}
    std::vector<std::shared_ptr<MyHealthpack>> getMyHealthPacks() const{return myHealthPacks;}
    MyProtagonist* getMyProtagonist() const{return myProtagonist.get();}
    std::vector<std::vector<std::shared_ptr<MyTile>>> get2DRepresentation() const{return representation_2D;}

    int getFieldOfView() const{return fieldOfView;}
    void setFieldOfView(int newvalue){if(newvalue > 0 && newvalue < rows) fieldOfView = newvalue;}

    std::vector<std::vector<std::shared_ptr<MyTile>>>make2DRepresentationAroundPointWithRange(int x, int y, int range);


private:
    void createWorld(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks);
    void initializeCollections();
    void moveProtagonist(Direction direction);
    void addOccupantToTile(std::shared_ptr<Tile> newEnemy);

    std::tuple<int,int> generateNewEnemyPosition();

    World world;
    int rows;
    int columns;
    int nrOfXenemies;
    int fieldOfView;


    std::vector<std::shared_ptr<MyTile>> myTiles;
    std::vector<std::shared_ptr<MyEnemy>> myEnemies;
    std::vector<std::shared_ptr<MyPEnemy>> myPEnemies;
    std::vector<std::shared_ptr<MyXEnemy>> myXEnemies;
    std::vector<std::shared_ptr<MyHealthpack>> myHealthPacks;

    std::shared_ptr<QImage> protagonist_image;
    std::shared_ptr<QImage> enemy_image;
    std::shared_ptr<QImage> penemy_image;
    std::shared_ptr<QImage> xenemy_image;
    std::shared_ptr<QImage> healthpack_image;
    std::shared_ptr<QImage> gravestone_image;


    std::shared_ptr<MyProtagonist> myProtagonist;

    std::vector<std::vector<std::shared_ptr<MyTile>>> representation_2D;

public slots:
    void protagonistMoveRequested(Direction direction);
    void poisonTile(float value, int x, int y);
    void zoomRequested(bool in_out);
    void broadcastHealthChange(int h);
    void broadcastEnergyChange(int e);
    void cameraCenterChangeRequested(int x, int y);
    void respawnEnemy(int x, int y);
signals:
    void updateView();
    void protagonistHealthChanged(int h);
    void protagonistEnergyChanged(int e);
    void endGame();
    void changeCameraCenter(int x, int y);
    void poisonVisualChange(std::vector<std::tuple<int,int>>& area, float level);

};




#endif // MODELWORLD_H
