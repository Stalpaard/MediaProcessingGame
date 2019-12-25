QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    commandpandown.cpp \
    commandpanleft.cpp \
    commandpanright.cpp \
    commandpanup.cpp \
    commandzoomin.cpp \
    commandzoomout.cpp \
    entity.cpp \
    graphicalview.cpp \
    main.cpp \
    maincontroller.cpp \
    mainwindow.cpp \
    modelworld.cpp \
    myenemy.cpp \
    mygraphicsscene.cpp \
    myhealthpack.cpp \
    mypenemy.cpp \
    myprotagonist.cpp \
    mytile.cpp \
    myxenemy.cpp \
    textedit.cpp \
    textview.cpp \
    command.cpp \
    commanddown.cpp \
    commandleft.cpp \
    commandright.cpp \
    aStar.cpp   \
    commandup.cpp



HEADERS += \
    Node.h \
    commandpandown.h \
    commandpanleft.h \
    commandpanright.h \
    commandpanup.h \
    commandzoomin.h \
    commandzoomout.h \
    direction.h \
    entity.h \
    entitystate.h \
    graphicalview.h \
    maincontroller.h \
    mainwindow.h \
    Node.h \
    modelworld.h \
    myenemy.h \
    mygraphicsscene.h \
    myhealthpack.h \
    mypenemy.h \
    myprotagonist.h \
    mytile.h \
    myxenemy.h \
    world.h \
    world_global.h \
    textedit.h \
    textview.h \
    command.h \
    commanddown.h \
    commandleft.h \
    commandright.h \
    aStar.h \
    commandup.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/./ -lworld

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

DISTFILES += \
    worldmap.png \
    protagonist.png \
    enemy.png \
    Penemy.png \
    Xenemy.png \
    healthpack.png \
    gravestone.png \
    worldmap4.png \
    maze1.png \
    maze2.png \
    maze3.png \
    zombie.png


unix:!macx: LIBS += -L$$PWD/../Media_Processing_Final/world_v3/ -lworld

INCLUDEPATH += $$PWD/../Media_Processing_Final/world_v3
DEPENDPATH += $$PWD/../Media_Processing_Final/world_v3

RESOURCES += \
    worldmap.qrc
