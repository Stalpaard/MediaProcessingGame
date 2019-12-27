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

    std::vector<std::pair<int,int>> currentPath;
    std::vector<std::vector<std::shared_ptr<MyTile>>>* representation_2D;

    MyProtagonist* protagonist;
    void followPath(std::shared_ptr<std::vector<std::pair<int, int>>> path);
    void calculateBestPath();
    GridLocation protagonist_loc, destination_loc;
    std::shared_ptr<std::vector<std::pair<int,int>>> bestPath, altBestPath, pathToBeFollowed;

    int moveIndex;
    bool strategyEnabled;
public slots:
    void gameEnd();
    void enableStrategy(bool enabled);
    void nextMove();
signals:
    void requestMove(Direction d);
};

#endif // STRATEGY_H
