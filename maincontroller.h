#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "mainwindow.h"
#include "world.h"
#include "world_global.h"
#include "modelworld.h"
#include "graphicalview.h"
#include "mygraphicsscene.h"
#include "commandup.h"
#include "commanddown.h"
#include "commandleft.h"
#include "commandright.h"
#include "command.h"
#include "commandzoomin.h"
#include "commandzoomout.h"
#include "commandpandown.h"
#include "commandpanleft.h"
#include "commandpanright.h"
#include "commandpanup.h"
#include "aStar.h"
#include "textview.h"

#include <QApplication>
#include <QGraphicsView>
#include <QProcess>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QInputDialog>
#include <QObject>
#include <QPixmap>
#include <QGraphicsItem>
#include <iostream>


class MainController : public QObject
{
public:
    MainController(QApplication& a);
    int startGameInstance();
private:
    QApplication& app;

    bool newWorldRequested;
public slots:
    void quitApp();
    void openNewWorld();
};

#endif // MAINCONTROLLER_H
