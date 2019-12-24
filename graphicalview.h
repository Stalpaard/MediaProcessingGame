#ifndef GRAPHICALVIEW_H
#define GRAPHICALVIEW_H

#include <QGraphicsView>
#include <QKeyEvent>
#include "direction.h"

class GraphicalView : public QGraphicsView
{
    Q_OBJECT
private:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    bool gameEnded;
public:
    GraphicalView(QGraphicsScene* scene);
signals:
    void movementKeyPressed(Direction direction);
    void zoom(bool in_out);

public slots:
    void fitScene();
    void gameEnd();
};

#endif // GRAPHICALVIEW_H
