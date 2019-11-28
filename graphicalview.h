#ifndef GRAPHICALVIEW_H
#define GRAPHICALVIEW_H

#include <QGraphicsView>
#include <QKeyEvent>
#include "modelworld.h"

class GraphicalView : public QGraphicsView
{
    Q_OBJECT
private:
    void keyPressEvent(QKeyEvent *event) override;
public:
    GraphicalView(std::shared_ptr<QGraphicsScene> scene);
signals:
    void movementKeyPressed(ModelWorld::Direction direction);
};

#endif // GRAPHICALVIEW_H
