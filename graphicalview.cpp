#include "graphicalview.h"

GraphicalView::GraphicalView(QGraphicsScene* scene)
{
    setScene(scene);
    setViewportUpdateMode(ViewportUpdateMode::SmartViewportUpdate);
}

void GraphicalView::wheelEvent(QWheelEvent *event){
    if(event->angleDelta().y() > 0) emit zoom(true);
    else emit zoom(false);
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
        case Qt::Key_Z :
            emit pan(0,-1);
            break;
        case Qt::Key_Q :
            emit pan(-1,0);
            break;
        case Qt::Key_S :
            emit pan(0,1);
            break;
        case Qt::Key_D :
            emit pan(1,0);
            break;

    }
}

void GraphicalView::fitScene(){
    fitInView(sceneRect(),Qt::KeepAspectRatio);
}

void GraphicalView::resizeEvent(QResizeEvent *event)
{
    (void)event; //to silence warning
    fitScene();
}
