#include "mygraphicsscene.h"
#include <iostream>
#include <QPainter>

MyGraphicsScene::MyGraphicsScene(std::string location, std::shared_ptr<ModelWorld> model)
{
    world_data = std::make_shared<QImage>(location.c_str());
    *(world_data.get()) = world_data->convertToFormat(QImage::Format_RGB16,Qt::ColorOnly);
    original_world_data = *(world_data.get());
    data_model = model;
    updateImageData();
}

QImage MyGraphicsScene::calculateScaled(int protagonistX, int protagonistY, int fieldOfView){
    QImage newImage = world_data->copy(QRect(QPoint(protagonistX-fieldOfView,protagonistY-fieldOfView),QPoint(protagonistX+fieldOfView,protagonistY+fieldOfView)));
    return newImage.scaled(newImage.width()*32,newImage.height()*32, Qt::AspectRatioMode::KeepAspectRatio);
}

void MyGraphicsScene::updateImageData(){
    //change QImage data according to changed conditions and generate new pixmap item
    clear();
    Protagonist* protagonist = data_model->getProtagonist();
    int xPos = protagonist->getXPos();
    int yPos = protagonist->getYPos();
    int fieldOfView = data_model->getFieldOfView();
    QImage scaled_copy = calculateScaled(xPos, yPos, fieldOfView);
    setSceneRect(scaled_copy.rect());
    drawEntities(scaled_copy, xPos, yPos, fieldOfView);
    addItem(new QGraphicsPixmapItem(QPixmap::fromImage(scaled_copy)));
    emit updateFitScene();
}

void MyGraphicsScene::drawEntities(QImage &source, int protagonistX, int protagonistY, int fieldOfView){
    QPainter painter;

    int xDistance, yDistance;

    //Get 2D representation of the world in range of the protagonist ('window' into the data)
    std::vector<std::vector<std::shared_ptr<MyTile>>> areaOfInterest = data_model->get2DRepresentationAroundPointWithRange(protagonistX,protagonistY,fieldOfView+1);

    painter.begin(&source);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage((fieldOfView*32)+6,(fieldOfView*32)+1,*(data_model->getMyProtagonist()->getRepresentation()));

    for(std::vector<std::shared_ptr<MyTile>> row : areaOfInterest){
        for(std::shared_ptr<MyTile> column : row){
            if(column->isOccupied()){
                xDistance = column->getXPos()-protagonistX;
                yDistance = column->getYPos()-protagonistY;
                painter.drawImage(6+(32*xDistance)+(fieldOfView*32),1+(32*yDistance)+(fieldOfView*32),*(column->getOccupant()->getRepresentation()));
            }
        }
    }

    painter.end();
}


void MyGraphicsScene::poisonLevelChanged(std::vector<std::tuple<int,int>> tuples, float level){
    for (auto &tuple : tuples){

            if(level > 0) world_data->setPixel(std::get<0>(tuple),std::get<1>(tuple),255);
            else world_data->setPixel(std::get<0>(tuple),std::get<1>(tuple),original_world_data.pixelIndex(std::get<0>(tuple),std::get<1>(tuple)));
    }
    updateImageData();
}
