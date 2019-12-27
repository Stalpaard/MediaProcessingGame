#ifndef MODELWORLD_H
#define MODELWORLD_H

#include "world.h"
#include "direction.h"
#include "aStarFast.h"
#include "mytile.h"
#include "myenemy.h"
#include "myhealthpack.h"
#include "myprotagonist.h"
#include "mypenemy.h"
#include "myxenemy.h"



class ModelWorld : public QObject
{
    Q_OBJECT

public:
    ModelWorld(int nrOfEnemies, int nrOfHealthpacks, QString location);
    std::vector<std::shared_ptr<MyEnemy>> getMyEnemies() const{return myEnemies;}
    std::vector<std::shared_ptr<MyPEnemy>> getMyPEnemies() const{return myPEnemies;}
    std::vector<std::shared_ptr<MyHealthpack>> getMyHealthPacks() const{return myHealthPacks;}
    MyProtagonist* getMyProtagonist() const{return myProtagonist.get();}
    std::vector<std::vector<std::shared_ptr<MyTile>>> get2DRepresentation(){return representation_2D;}

    int getFieldOfView() const{return fieldOfView;}
    void setFieldOfView(int newvalue){if(newvalue > 0 && newvalue < rows) fieldOfView = newvalue;}

    int getRows() const{return rows;}
    int getColumns() const{return columns;}

    std::vector<std::vector<std::shared_ptr<MyTile>>>make2DRepresentationAroundPointWithRange(int x, int y, int range);


private:
    void createWorld(QString filename, int nrOfEnemies, int nrOfHealthpacks);
    void initializeCollections();
    void initializeAnimations();
    void moveProtagonist(Direction direction);
    void addOccupantToTile(std::shared_ptr<Tile> newEnemy);

    std::pair<int,int> generateNewEnemyPosition();

    World world;
    int rows, columns, fieldOfView;
    int nrOfXenemies, remainingEnemies;

    std::shared_ptr<std::vector<std::pair<int,int>>> algoResult;
    std::shared_ptr<MyProtagonist> myProtagonist;
    std::vector<std::vector<std::shared_ptr<MyTile>>> representation_2D;

    std::vector<std::shared_ptr<MyTile>> myTiles;
    std::vector<std::shared_ptr<MyEnemy>> myEnemies;
    std::vector<std::shared_ptr<MyPEnemy>> myPEnemies;
    std::vector<std::shared_ptr<MyXEnemy>> myXEnemies;
    std::vector<std::shared_ptr<MyHealthpack>> myHealthPacks;

    std::shared_ptr<QImage> protagonist_image, enemy_image, penemy_image, xenemy_image, healthpack_image, gravestone_image, zombie_image;

    std::shared_ptr<std::vector<std::shared_ptr<QImage>>> protagonist_idle, protagonist_walking, protagonist_dying, enemy_idle, enemy_dying, penemy_idle, penemy_dying,
    xenemy_idle, xenemy_dying, zombie_idle, zombie_dying, healthpack_idle;

public slots:
    void protagonistMoveRequested(Direction direction);
    void protagonistMoveCompleted();

    void zoomRequested(bool in_out);
    void runPathfinding(int destX, int destY);
private slots:
    void respawnEnemy(int x, int y);
    void poisonTile(float value, int x, int y);

    void broadcastHealthChange(int h);
    void broadcastEnergyChange(int e);
    void broadcastPositionChange(int x, int y);
signals:
    void remainingEnemiesChanged(int remainingAmount);
    void protagonistHealthChanged(int h);
    void protagonistEnergyChanged(int e);
    void protagonistPositionChanged(int x, int y);
    void protagonistMovingDirection(Direction d);
    void gameDefeat();
    void gameVictory();
    void endGame();

    void newPathfindingResult(std::shared_ptr<std::vector<std::pair<int,int>>> result);
    void pathfindingAvailable();

    void changeCameraCenter(int x, int y);
    void updateView();
    void poisonVisualChange(std::vector<std::pair<int,int>>& area, float level);

};




#endif // MODELWORLD_H
