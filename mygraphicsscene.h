#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <string>
#include "QGraphicsPixmapItem"
#include <memory>
#include "modelworld.h"

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ~MyGraphicsScene() override = default;
    MyGraphicsScene(std::string location, std::shared_ptr<ModelWorld> model);
    QImage getWorldData() const {return *(world_data.get());}

private:
    std::shared_ptr<QImage> world_data;
    QImage original_world_data;
    std::shared_ptr<ModelWorld> data_model;

    void drawEntities(QImage& source, int protagonistX, int protagonistY, int fieldOfView);
    QImage calculateScaled(int protagonistX, int protagonistY, int fieldOfView);
signals:
    void updateFitScene();

public slots:
    void updateImageData();
    void poisonLevelChanged(std::vector<std::tuple<int,int>>, float level);
};

#endif // MYGRAPHICSSCENE_H
