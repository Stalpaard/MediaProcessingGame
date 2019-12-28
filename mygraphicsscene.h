#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <memory>
#include <QTimer>
#include <QPainter>

#include "modelworld.h"
#include "direction.h"

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ~MyGraphicsScene() override = default;
    MyGraphicsScene(QString& location, std::shared_ptr<ModelWorld> model);

private:
    std::shared_ptr<QImage> world_data;
    std::shared_ptr<ModelWorld> data_model;
    std::shared_ptr<std::vector<std::pair<int,int>>> pathfindingResult;
    QImage original_world_data;
    bool pathfinding_on;
    int animationMilliSec, moveCounter;
    Direction movingDirection;
    std::pair<int,int> camera_center;

    void drawEntities(QImage& source, int centerX, int centerY, int range);
    QImage calculateScaled(int centerX, int centerY, int range);

signals:
    void updateFitScene();
    void moveCompleted();

public slots:
    void updateMovingDirection(Direction d);
    void updateCameraCenter(int dx, int dy);
    void newPathfindingResult(std::shared_ptr<std::vector<std::pair<int,int>>> result);
    void showPathfinding(bool newvalue);
    void updateAnimationSpeed(int newvalue);
    void poisonLevelChanged(std::vector<std::pair<int,int>>& area, float level);

private slots:
    void animationLoop();
};

#endif // MYGRAPHICSSCENE_H
