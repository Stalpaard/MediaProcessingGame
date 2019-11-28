#include "graphicalview.h"

#include <QGraphicsView>

GraphicalView::GraphicalView(std::shared_ptr<QGraphicsScene> scene)
{
    setScene(scene.get());
}



void GraphicalView::keyPressEvent(QKeyEvent* keyEvent){
    switch(keyEvent->key()){
    case Qt::Key_Up:
        emit movementKeyPressed(ModelWorld::Direction::UP);
        break;
    case Qt::Key_Down:
        emit movementKeyPressed(ModelWorld::Direction::DOWN);
        break;
    case Qt::Key_Left:
        emit movementKeyPressed(ModelWorld::Direction::LEFT);
        break;
    case Qt::Key_Right:
        emit movementKeyPressed(ModelWorld::Direction::RIGHT);
        break;
    }
}
