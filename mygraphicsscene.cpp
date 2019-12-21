#include "mygraphicsscene.h"
#include <iostream>


MyGraphicsScene::MyGraphicsScene(std::string location)
{
    world_data = std::unique_ptr<QImage>(new QImage(location.c_str()));
    addItem(new QGraphicsPixmapItem(QPixmap::fromImage(*(world_data.get()))));
}

void MyGraphicsScene::updateImageData(){
    //change QImage data according to changed conditions and generate new pixmap item
    emit imageDataUpdated();
}
