#include "graphicalview.h"
#include <iostream>

#include <QGraphicsView>

GraphicalView::GraphicalView(QGraphicsScene* scene)
{
    setScene(scene);
    setViewportUpdateMode(ViewportUpdateMode::SmartViewportUpdate);
    gameEnded = false;
}

void GraphicalView::wheelEvent(QWheelEvent *event){
    if(event->angleDelta().y() > 0) emit zoom(true);
    else emit zoom(false);
}

void GraphicalView::keyPressEvent(QKeyEvent* keyEvent){
    if(!(gameEnded)){
        switch(keyEvent->key()){
        case Qt::Key_Up:
            emit movementKeyPressed(Direction::UP);
            break;
        case Qt::Key_Down:
            emit movementKeyPressed(Direction::DOWN);
            break;
        case Qt::Key_Left:
            emit movementKeyPressed(Direction::LEFT);
            break;
        case Qt::Key_Right:
            emit movementKeyPressed(Direction::RIGHT);
            break;
        }
    }
}

void GraphicalView::fitScene(){
    fitInView(sceneRect(),Qt::KeepAspectRatio);
}

void GraphicalView::gameEnd(){
    gameEnded = true;
}

