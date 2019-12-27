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
    bool keyevents_enabled;
public:
    GraphicalView(QGraphicsScene* scene);
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
signals:
    void movementKeyPressed(Direction direction);
    void zoom(bool in_out);
    void pan(int x, int y);

public slots:
    void fitScene();
    void toggleKeyEvents();
};

#endif // GRAPHICALVIEW_H
