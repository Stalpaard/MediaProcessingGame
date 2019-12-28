#ifndef STRATEGY_H
#define STRATEGY_H

#include "modelworld.h"

class Strategy : public QObject
{
    Q_OBJECT
public:
    Strategy(std::shared_ptr<ModelWorld> model);
private:
    std::shared_ptr<ModelWorld> model;
    std::shared_ptr<std::vector<std::pair<int,int>>> currentPath, bestPath, altBestPath, pathToBeFollowed;

    std::vector<std::vector<std::shared_ptr<MyTile>>>* representation_2D;
    std::vector<std::vector<MyTile>>* original_representation_2D;

    MyProtagonist* protagonist;
    int protagonist_loc, destination_loc;
    int moveIndex;
    bool strategyEnabled, gameEnded;

    void followPath(std::shared_ptr<std::vector<std::pair<int, int>>> path);
    void calculateBestPath();
    float calculateRequiredEnergyToEntity(int protagonist_loc, std::shared_ptr<Entity> entity);

public slots:
    void gameEnd();
    void enableStrategy(bool enabled);
    void toggleStrategy();
    void nextMove();

signals:
    void requestMove(Direction d);
    void noPossibleSolution(QString reason);
    void newPathfindingResult(std::shared_ptr<std::vector<std::pair<int,int>>> result);
    void pathfindingAvailable();
};

#endif // STRATEGY_H
