#include "mygraphicsscene.h"

const int defaultAnimationMillisec = 15;

MyGraphicsScene::MyGraphicsScene(QString location, std::shared_ptr<ModelWorld> model) : animationMilliSec{defaultAnimationMillisec}, moveCounter{0}, movingDirection{Direction::UP}
{
    world_data = std::make_shared<QImage>(location);
    *world_data = world_data->convertToFormat(QImage::Format_RGB16,Qt::ColorOnly);
    original_world_data = *world_data;
    data_model = model;
    camera_center = std::make_tuple(0,0);
    updateImageData();
}

QImage MyGraphicsScene::calculateScaled(int centerX, int centerY, int range){
    QImage newImage = world_data->copy(QRect(QPoint(centerX-range,centerY-range),QPoint(centerX+range,centerY+range)));
    return newImage.scaled(newImage.width()*32,newImage.height()*32, Qt::AspectRatioMode::KeepAspectRatio);
}

void MyGraphicsScene::updateImageData(){
    //change QImage data according to changed conditions and generate new pixmap item
    clear();
    int range = data_model->getFieldOfView();

    if(camera_center != target_camera_center && !(data_model->getMyProtagonist()->isWalking())) camera_center = target_camera_center;

    QImage scaled_copy = calculateScaled(std::get<0>(camera_center), std::get<1>(camera_center), range);
    if(sceneRect() != scaled_copy.rect()){
        setSceneRect(scaled_copy.rect());
        emit updateFitScene();
    }
    drawEntities(scaled_copy, std::get<0>(camera_center), std::get<1>(camera_center), range);
    addItem(new QGraphicsPixmapItem(QPixmap::fromImage(scaled_copy)));
    QTimer::singleShot(animationMilliSec, this, SLOT(updateImageData()));
}

void MyGraphicsScene::startAnimationLoop(){
    updateImageData();

}

void MyGraphicsScene::drawEntities(QImage &source, int centerX, int centerY, int range){
    QPainter painter;

    int xDistance, yDistance;
    MyProtagonist* protagonist = data_model->getMyProtagonist();

    //Get 2D representation of the world in range of the protagonist ('window' into the data)
    std::vector<std::vector<std::shared_ptr<MyTile>>> areaOfInterest = data_model->make2DRepresentationAroundPointWithRange(centerX,centerY,range+1);

    painter.begin(&source);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    QFont font;
    font.setPixelSize(15);
    font.setFamily("Courier");
    painter.setFont(font);

    xDistance = protagonist->getXPos()-std::get<0>(target_camera_center);
    yDistance = protagonist->getYPos()-std::get<1>(target_camera_center);
    if(!(xDistance > range || yDistance > range)){
        if(camera_center != target_camera_center){
                moveCounter++;
                if(moveCounter >= 32){
                    moveCounter=0;
                    camera_center = target_camera_center;
                    emit moveCompleted();
                }
                else{
                    switch(movingDirection){
                    case Direction::UP :
                        painter.drawImage((range*32)+6+(32*xDistance),(range*32)+1+moveCounter+(32*yDistance),*(protagonist->getRepresentation()));
                        break;
                    case Direction::DOWN :
                        painter.drawImage((range*32)+6+(32*xDistance),(range*32)+1-moveCounter+(32*yDistance),*(protagonist->getRepresentation()));
                        break;
                    case Direction::LEFT :
                        painter.drawImage((range*32)+6-moveCounter+(32*xDistance),(range*32)+1+(32*yDistance),*(protagonist->getRepresentation()));
                        break;
                    case Direction::RIGHT :
                        painter.drawImage((range*32)+6+moveCounter+(32*xDistance),(range*32)+1+(32*yDistance),*(data_model->getMyProtagonist()->getRepresentation()));
                        break;
                    }
                }
        }
        else painter.drawImage((range*32)+6+(32*xDistance),(range*32)+1+(32*yDistance),*(data_model->getMyProtagonist()->getRepresentation()));
    }




    for(std::vector<std::shared_ptr<MyTile>> row : areaOfInterest){
        for(std::shared_ptr<MyTile> column : row){
            xDistance = column->getXPos()-centerX;
            yDistance = column->getYPos()-centerY;
            if(column->isOccupied()){
                std::shared_ptr<Entity> occupant = column->getOccupant();
                float occupant_value = occupant->getValue();
                std::shared_ptr<QImage> representation = occupant->getRepresentation();
                painter.drawImage(6+(32*xDistance)+(range*32),1+(32*yDistance)+(range*32),*representation);

                if(!(occupant->isDefeated())){
                    if(occupant_value > 0) painter.setPen(Qt::red);
                    else painter.setPen(Qt::white);
                    painter.drawText(8+(32*xDistance)+(range*32),4+(32*yDistance)+(range*32),QString::number(std::abs(static_cast<int>(occupant->getValue()))));
                }
            }
            if(column->getPoisonLevel() > 0){
                painter.setPen(Qt::green);
                painter.drawText(10+(32*xDistance)+(range*32),20+(32*yDistance)+(range*32),QString::number(std::abs(static_cast<int>(column->getPoisonLevel()))));
            }
        }
    }

    painter.end();
}

void MyGraphicsScene::updateCameraCenter(int dx, int dy){
    int currentcameraX = std::get<0>(camera_center);
    int currentcameraY = std::get<1>(camera_center);
    int newCameraX = currentcameraX+dx;
    int newCameraY = currentcameraY+dy;
    if(newCameraX > data_model->getColumns()) newCameraX = data_model->getColumns();
    else if(newCameraX < 0) newCameraX = 0;
    if(newCameraY > data_model->getRows()) newCameraY = data_model->getRows();
    else if(newCameraY < 0 ) newCameraY = 0;

    target_camera_center = std::make_tuple(newCameraX,newCameraY);

    if(newCameraX != currentcameraX){
        if(currentcameraX-newCameraX > 0){
            movingDirection = Direction::LEFT;
        }
        else movingDirection = Direction::RIGHT;
    }
    else if(newCameraY != currentcameraY){
        if(currentcameraY-newCameraY > 0){
            movingDirection = Direction::DOWN;
        }
        else movingDirection = Direction::UP;
    }
}

void MyGraphicsScene::poisonLevelChanged(std::vector<std::tuple<int,int>>& tuples, float level){
    for (auto &tuple : tuples){
            int greenLevel = static_cast<int>(level);
            if(greenLevel > 255) greenLevel = 255;
            else if(greenLevel < 0) greenLevel = 0;
            if(level > 0) world_data->setPixelColor(std::get<0>(tuple),std::get<1>(tuple),QColor(0,greenLevel,0));
            else world_data->setPixelColor(std::get<0>(tuple),std::get<1>(tuple),original_world_data.pixelColor(std::get<0>(tuple),std::get<1>(tuple)));
    }
}

void MyGraphicsScene::updateAnimationSpeed(int newvalue){
    animationMilliSec = newvalue;
}
