#include "maincontroller.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainController main(a);
    main.startGameInstance();
}
