#include "graphicalview.h"

#include <QGraphicsView>

GraphicalView::GraphicalView(QGraphicsScene* scene)
{
    setScene(scene);
    setViewportUpdateMode(ViewportUpdateMode::SmartViewportUpdate);
}



void GraphicalView::keyPressEvent(QKeyEvent* keyEvent){
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

void GraphicalView::updateImage(){
    fitInView(sceneRect(),Qt::KeepAspectRatio);
    //update();
}
