#include "mainwindow.h"
#include "world.h"
#include "world_global.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    World epicweerelt;
    epicweerelt.createWorld(":/img/worldmap.png",1,1);
    w.show();


    return a.exec();
}
