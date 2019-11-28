#ifndef MODELWORLD_H
#define MODELWORLD_H

#include "world.h"
#include "QObject"

class ModelWorld : public QObject
{
    Q_OBJECT

private:
    void createWorld(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks);
    void moveCollections();
    World world;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Tile>> healthPacks;
    std::shared_ptr<Protagonist> protagonist;

    std::vector<std::vector<std::shared_ptr<Tile>>> representation_2D;
    int rows;
    int columns;

public:
    enum Direction {UP, DOWN, LEFT, RIGHT};
    ModelWorld(unsigned int nrOfEnemies, unsigned int nrOfHealthpacks);
    std::vector<std::shared_ptr<Tile>> getTiles();
    std::vector<std::shared_ptr<Enemy>> getEnemies();
    std::vector<std::shared_ptr<Tile>> getHealthPacks();
    std::shared_ptr<Protagonist> getProtagonist();
public slots:
    void moveProtagonist(Direction direction);
    void printPosition(int x, int y);
signals:
    void updateView();

};

#endif // MODELWORLD_H
