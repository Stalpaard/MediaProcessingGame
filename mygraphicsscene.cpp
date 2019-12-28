#include "mygraphicsscene.h"

const int defaultAnimationMillisec = 15;
const int tileSize = 32;
const int xOffset = 6;
const int yOffset = 1;
const int xTileTextOffset = 10;
const int yTileTextOffset = 20;
const int xEntityTextOffset = 8;
const int yEntityTextOffset = 4;

MyGraphicsScene::MyGraphicsScene(QString& location, std::shared_ptr<ModelWorld> model) : data_model{model}, pathfindingResult{nullptr}, pathfinding_on{true}, animationMilliSec{defaultAnimationMillisec}, moveCounter{0}, movingDirection{Direction::UP}

{
    world_data = std::make_shared<QImage>(location);
    //Convert world data to RGB space in order to use non-grayscale colors
    *world_data = world_data->convertToFormat(QImage::Format_RGB16,Qt::ColorOnly);
    original_world_data = *world_data;
    camera_center = std::make_pair(0,0);
    animationLoop();
}

void MyGraphicsScene::drawEntities(QImage &source, int centerX, int centerY, int range){
    QPainter painter;

    int xDistance, yDistance, xRangeCheck, yRangeCheck, xDraw, yDraw;
    MyProtagonist* protagonist = data_model->getMyProtagonist();
    QImage protagonist_representation = *(protagonist->getRepresentation());

    //Get 2D representation of the world in range of the protagonist ('window' into the data)
    std::vector<std::vector<std::shared_ptr<MyTile>>> areaOfInterest = data_model->make2DRepresentationAroundPointWithRange(centerX,centerY,range+1);

    painter.begin(&source);
    //Tell QPainter to paint on top of the provided source file
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    QFont font;
    font.setPixelSize(15);
    font.setFamily("Courier");
    painter.setFont(font);

    xDistance = protagonist->getXPos()-std::get<0>(camera_center);
    yDistance = protagonist->getYPos()-std::get<1>(camera_center);
    xDraw = (range*tileSize)+xOffset+(tileSize*xDistance);
    yDraw = (range*tileSize)+yOffset+(tileSize*yDistance);
    //Range check needed in order to move camera when protagonist is near the edge of the visible screen in order to see adjacent enemies
    xRangeCheck = std::abs(xDistance);
    yRangeCheck = std::abs(yDistance);


    if(protagonist->isWalking()){
        //Draw protagonist between start and end tile according to the move counter
        moveCounter++;
        if(moveCounter >= 31){
            moveCounter=0;
            emit moveCompleted();
        }
        else{
            switch(movingDirection){
            case Direction::UP :
                yDraw = yDraw + moveCounter-32;
                break;
            case Direction::DOWN :
                yDraw = yDraw - moveCounter+32;
                break;
            case Direction::LEFT :
                xDraw = xDraw - moveCounter+32;
                protagonist_representation = protagonist_representation.mirrored(true,false);
                break;
            case Direction::RIGHT :
                xDraw = xDraw + moveCounter-32;
                break;

            }
        }
        if(xRangeCheck == range || xRangeCheck == range+1){
            if(xDistance > 0) updateCameraCenter(range,0);
            else updateCameraCenter(-range,0);
        }
        else if(yRangeCheck == range || yRangeCheck == range+1){
            if(yDistance > 0) updateCameraCenter(0,range);
            else updateCameraCenter(0,-range);
        }
    }
    painter.drawImage(xDraw,yDraw,protagonist_representation);

    //Draw representations of occupants occupying the tiles in the area of interest
    for(std::vector<std::shared_ptr<MyTile>> row : areaOfInterest){
        for(std::shared_ptr<MyTile> column : row){
            xDistance = column->getXPos()-centerX;
            yDistance = column->getYPos()-centerY;
            painter.setPen(Qt::white);
            if(column->isOccupied()){
                std::shared_ptr<Entity> occupant = column->getOccupant();
                float occupant_value = occupant->getValue();
                std::shared_ptr<QImage> representation = occupant->getRepresentation();
                painter.drawImage(xOffset+(tileSize*xDistance)+(range*tileSize),yOffset+(tileSize*yDistance)+(range*tileSize),*representation);

                if(!(occupant->isDefeated())){
                    if(occupant_value > 0) painter.setPen(Qt::red);
                    else painter.setPen(Qt::white);
                    painter.drawText(xEntityTextOffset+(tileSize*xDistance)+(range*tileSize),yEntityTextOffset+(tileSize*yDistance)+(range*tileSize),QString::number(std::abs(static_cast<int>(occupant->getValue()))));
                }
            }
            if(column->getPoisonLevel() > 0){
                painter.setPen(Qt::green);
                painter.drawText(xTileTextOffset+(tileSize*xDistance)+(range*tileSize),yTileTextOffset+(tileSize*yDistance)+(range*tileSize),QString::number(std::abs(static_cast<int>(column->getPoisonLevel()))));
            }
        }
    }

    painter.end();
}

QImage MyGraphicsScene::calculateScaled(int centerX, int centerY, int range){
    //Return scaled image of the world (in order to fit images of entities unto tiles)
    QImage newImage = world_data->copy(QRect(QPoint(centerX-range,centerY-range),QPoint(centerX+range,centerY+range)));
    return newImage.scaled(newImage.width()*tileSize,newImage.height()*tileSize, Qt::AspectRatioMode::KeepAspectRatio,Qt::FastTransformation);
}

//PRIVATE SLOTS

void MyGraphicsScene::animationLoop(){
    //Generate new frame using up-to-date parameters
    clear();
    int range = data_model->getFieldOfView();

    QImage scaled_copy = calculateScaled(std::get<0>(camera_center), std::get<1>(camera_center), range);
    if(sceneRect() != scaled_copy.rect()){
        setSceneRect(scaled_copy.rect());
        emit updateFitScene();
    }
    drawEntities(scaled_copy, std::get<0>(camera_center), std::get<1>(camera_center), range);
    addItem(new QGraphicsPixmapItem(QPixmap::fromImage(scaled_copy)));
    QTimer::singleShot(animationMilliSec, this, SLOT(animationLoop()));
}

//PUBLIC SLOTS

void MyGraphicsScene::updateMovingDirection(Direction d){
    movingDirection = d;
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
    camera_center = std::make_pair(newCameraX,newCameraY);
}

void MyGraphicsScene::updateAnimationSpeed(int newvalue){
    animationMilliSec = newvalue;
}


void MyGraphicsScene::newPathfindingResult(std::shared_ptr<std::vector<std::pair<int,int>>> result){
    bool temp_pathfinding_on = pathfinding_on;
    showPathfinding(false);
    pathfindingResult = result;
    showPathfinding(temp_pathfinding_on);
}

void MyGraphicsScene::showPathfinding(bool t_f){
    if(pathfindingResult != nullptr){
        pathfinding_on = t_f;
        if(pathfinding_on){
            for(auto& pair : *pathfindingResult){
                world_data->setPixelColor(std::get<0>(pair),std::get<1>(pair),QColor(255,0,0));
            }
        }
        else{
            for(auto& pair : *pathfindingResult){
                world_data->setPixelColor(std::get<0>(pair),std::get<1>(pair),original_world_data.pixelColor(std::get<0>(pair),std::get<1>(pair)));
            }
        }
    }
}

void MyGraphicsScene::poisonLevelChanged(std::vector<std::pair<int,int>>& pairs, float level){
    //Color poisoned tiles according to their level
    for (auto &pair : pairs){
            int greenLevel = static_cast<int>(level);
            if(greenLevel > 255) greenLevel = 255;
            else if(greenLevel < 0) greenLevel = 0;
            if(level > 0) world_data->setPixelColor(std::get<0>(pair),std::get<1>(pair),QColor(0,greenLevel,0));
            else world_data->setPixelColor(std::get<0>(pair),std::get<1>(pair),original_world_data.pixelColor(std::get<0>(pair),std::get<1>(pair)));
    }
}



