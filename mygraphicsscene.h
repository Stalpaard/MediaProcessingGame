#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "QGraphicsPixmapItem"
#include <memory>
#include <QTimer>
#include <QPainter>
#include "modelworld.h"

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ~MyGraphicsScene() override = default;
    MyGraphicsScene(QString location, std::shared_ptr<ModelWorld> model);
    QImage getWorldData() const {return *(world_data.get());}

private:
    std::shared_ptr<QImage> world_data;
    QImage original_world_data;
    std::shared_ptr<ModelWorld> data_model;

    void drawEntities(QImage& source, int centerX, int centerY, int range);
    void startAnimationLoop();
    QImage calculateScaled(int centerX, int centerY, int range);

    std::tuple<int,int> camera_center;
signals:
    void updateFitScene();

public slots:
    void updateCameraCenter(int x, int y);
    void updateImageData();
    void poisonLevelChanged(std::vector<std::tuple<int,int>>& area, float level);
};

#endif // MYGRAPHICSSCENE_H
