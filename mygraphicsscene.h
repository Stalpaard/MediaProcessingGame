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
    QImage getScaled() const {return *(scaled.get());}
    QImage getWorldData() const {return *(world_data.get());}

private:
    std::shared_ptr<QImage> world_data;
    std::shared_ptr<QImage> scaled;
    std::shared_ptr<ModelWorld> data_model;

    std::shared_ptr<QImage> protagonist_image;
    std::shared_ptr<QImage> enemy_image;
    std::shared_ptr<QImage> penemy_image;
    std::shared_ptr<QImage> xenemy_image;
    std::shared_ptr<QImage> healthpack_image;
    std::shared_ptr<QImage> gravestone_image;

    void drawEntities(QImage& source);
    void checkForPoison();

signals:
    void imageDataUpdated();

public slots:
    void updateImageData();
    void poisonLevelChanged(std::vector<std::tuple<int,int>>, float level);
};

#endif // MYGRAPHICSSCENE_H
