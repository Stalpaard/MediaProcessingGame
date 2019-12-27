#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "QGraphicsPixmapItem"
#include <memory>
#include <QTimer>
#include <QPainter>
#include <math.h>
#include "modelworld.h"
#include "direction.h"

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ~MyGraphicsScene() override = default;
    MyGraphicsScene(QString& location, std::shared_ptr<ModelWorld> model);
    QImage getWorldData() const {return *(world_data.get());}
    void setAnimationMilliSec(int newvalue){animationMilliSec = newvalue;}

private:
    std::shared_ptr<QImage> world_data;
    QImage original_world_data;
    std::shared_ptr<ModelWorld> data_model;

    int animationMilliSec;

    void drawEntities(QImage& source, int centerX, int centerY, int range);
    void startAnimationLoop();
    QImage calculateScaled(int centerX, int centerY, int range);

    std::pair<int,int> camera_center;
    std::shared_ptr<std::vector<std::pair<int,int>>> pathfindingResult;

    int moveCounter;
    Direction movingDirection;
signals:
    void updateFitScene();
    void moveCompleted();

public slots:
    void updateMovingDirection(Direction d);
    void updateCameraCenter(int dx, int dy);
    void newPathfindingResult(std::shared_ptr<std::vector<std::pair<int,int>>> result);
    void showPathfinding(bool newvalue);
    void animationLoop();
    void updateAnimationSpeed(int newvalue);
    void poisonLevelChanged(std::vector<std::pair<int,int>>& area, float level);
};

#endif // MYGRAPHICSSCENE_H
