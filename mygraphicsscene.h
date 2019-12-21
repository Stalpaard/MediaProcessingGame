#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <string>
#include "QGraphicsPixmapItem"
#include <memory>

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ~MyGraphicsScene() override = default;
    MyGraphicsScene(std::string location);
private:
    std::unique_ptr<QImage> world_data;

signals:
    void imageDataUpdated();

public slots:
    void updateImageData();
};

#endif // MYGRAPHICSSCENE_H
