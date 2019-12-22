#include "mygraphicsscene.h"
#include <iostream>
#include <QPainter>


MyGraphicsScene::MyGraphicsScene(std::string location, std::shared_ptr<ModelWorld> model)
{
    world_data = std::make_shared<QImage>(location.c_str());
    protagonist_image = std::make_shared<QImage>(":img/protagonist.png");
    enemy_image = std::make_shared<QImage>(":img/enemy.png");
    penemy_image = std::make_shared<QImage>(":img/Penemy.png");
    xenemy_image = std::make_shared<QImage>(":img/Xenemy.png");
    gravestone_image = std::make_shared<QImage>(":img/gravestone.png");
    healthpack_image = std::make_shared<QImage>(":img/healthpack.png");
    data_model = model;
    scaled = std::make_shared<QImage>(world_data->scaled(world_data->width()*32, world_data->height()*32, Qt::AspectRatioMode::KeepAspectRatio));
    std::cout << "scaled width: " << scaled->width() << " scaled height: " << scaled->height() << std::endl;
    updateImageData();
}

void MyGraphicsScene::updateImageData(){
    //change QImage data according to changed conditions and generate new pixmap item
    clear();
    QImage scaled_copy = getScaled();
    drawEntities(scaled_copy);
    emit imageDataUpdated();
    addItem(new QGraphicsPixmapItem(QPixmap::fromImage(scaled_copy)));
}

void MyGraphicsScene::drawEntities(QImage &source){
    QImage* image;
    QPainter painter;

    painter.begin(&source);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    painter.drawImage(6+(32*data_model->getProtagonist()->getXPos()),1+(32*data_model->getProtagonist()->getYPos()),*(protagonist_image.get()));

    for (auto &enemy : data_model->getMyEnemies()) // access by reference to avoid copying
    {
        if(enemy->getDefeated()) image = gravestone_image.get();
        else image = enemy_image.get();
        painter.drawImage(6+(32*enemy->getXPos()),1+(32*enemy->getYPos()),*image);
    }
    for (auto &enemy : data_model->getMyPEnemies()) // access by reference to avoid copying
    {
        if(enemy->getDefeated()) image = gravestone_image.get();
        else image = penemy_image.get();
        painter.drawImage(6+(32*enemy->getXPos()),1+(32*enemy->getYPos()),*image);
    }
    for (auto &healthpack : data_model->getMyHealthPacks()) // access by reference to avoid copying
    {
        if(!(healthpack->getDefeated())){
            painter.drawImage(6+(32*healthpack->getXPos()),1+(32*healthpack->getYPos()),*(healthpack_image.get()));
        }
    }
    painter.end();
}

void MyGraphicsScene::poisonLevelChanged(std::vector<std::tuple<int,int>> tuples, float level){
    QImage world = getWorldData();
    if(level > 0){
        for (auto &tuple : tuples){
            world.setPixel(std::get<0>(tuple),std::get<1>(tuple),255);
        }
        scaled = std::make_shared<QImage>(world.scaled(world.width()*32, world.height()*32, Qt::AspectRatioMode::KeepAspectRatio));
    }
    else scaled = std::make_shared<QImage>(world_data->scaled(world_data->width()*32, world_data->height()*32, Qt::AspectRatioMode::KeepAspectRatio));
    updateImageData();
}
