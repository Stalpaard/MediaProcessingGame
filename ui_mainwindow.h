/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_world;
    QAction *actionQuit;
    QAction *actiongraphicalView;
    QAction *actiontextView;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *mainLayout;
    QVBoxLayout *barLayout;
    QLabel *healthLabel;
    QProgressBar *healthBar;
    QLabel *energyLabel;
    QProgressBar *energyBar;
    QStackedWidget *viewWidget;
    QWidget *end;
    QFrame *frame;
    QLabel *label;
    QWidget *view1;
    QWidget *view2;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(870, 671);
        actionOpen_world = new QAction(MainWindow);
        actionOpen_world->setObjectName(QString::fromUtf8("actionOpen_world"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actiongraphicalView = new QAction(MainWindow);
        actiongraphicalView->setObjectName(QString::fromUtf8("actiongraphicalView"));
        actiontextView = new QAction(MainWindow);
        actiontextView->setObjectName(QString::fromUtf8("actiontextView"));
        actionZoomIn = new QAction(MainWindow);
        actionZoomIn->setObjectName(QString::fromUtf8("actionZoomIn"));
        actionZoomOut = new QAction(MainWindow);
        actionZoomOut->setObjectName(QString::fromUtf8("actionZoomOut"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        mainLayout = new QHBoxLayout();
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        barLayout = new QVBoxLayout();
        barLayout->setSpacing(0);
        barLayout->setObjectName(QString::fromUtf8("barLayout"));
        barLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        healthLabel = new QLabel(centralwidget);
        healthLabel->setObjectName(QString::fromUtf8("healthLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(healthLabel->sizePolicy().hasHeightForWidth());
        healthLabel->setSizePolicy(sizePolicy);

        barLayout->addWidget(healthLabel);

        healthBar = new QProgressBar(centralwidget);
        healthBar->setObjectName(QString::fromUtf8("healthBar"));
        sizePolicy.setHeightForWidth(healthBar->sizePolicy().hasHeightForWidth());
        healthBar->setSizePolicy(sizePolicy);
        healthBar->setValue(100);
        healthBar->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        barLayout->addWidget(healthBar);

        energyLabel = new QLabel(centralwidget);
        energyLabel->setObjectName(QString::fromUtf8("energyLabel"));
        sizePolicy.setHeightForWidth(energyLabel->sizePolicy().hasHeightForWidth());
        energyLabel->setSizePolicy(sizePolicy);

        barLayout->addWidget(energyLabel);

        energyBar = new QProgressBar(centralwidget);
        energyBar->setObjectName(QString::fromUtf8("energyBar"));
        sizePolicy.setHeightForWidth(energyBar->sizePolicy().hasHeightForWidth());
        energyBar->setSizePolicy(sizePolicy);
        energyBar->setValue(100);
        energyBar->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        barLayout->addWidget(energyBar);


        mainLayout->addLayout(barLayout);

        viewWidget = new QStackedWidget(centralwidget);
        viewWidget->setObjectName(QString::fromUtf8("viewWidget"));
        end = new QWidget();
        end->setObjectName(QString::fromUtf8("end"));
        frame = new QFrame(end);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(-1, -1, 751, 581));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(1);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(250, 140, 211, 71));
        QFont font;
        font.setPointSize(40);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        viewWidget->addWidget(end);
        view1 = new QWidget();
        view1->setObjectName(QString::fromUtf8("view1"));
        viewWidget->addWidget(view1);
        view2 = new QWidget();
        view2->setObjectName(QString::fromUtf8("view2"));
        viewWidget->addWidget(view2);

        mainLayout->addWidget(viewWidget);


        horizontalLayout->addLayout(mainLayout);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 870, 22));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionOpen_world);
        menuMenu->addAction(actionQuit);
        toolBar->addAction(actiongraphicalView);
        toolBar->addAction(actiontextView);
        toolBar->addAction(actionZoomIn);
        toolBar->addAction(actionZoomOut);

        retranslateUi(MainWindow);

        viewWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen_world->setText(QApplication::translate("MainWindow", "Open world...", nullptr));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        actiongraphicalView->setText(QApplication::translate("MainWindow", "graphicalView", nullptr));
        actiontextView->setText(QApplication::translate("MainWindow", "textView", nullptr));
        actionZoomIn->setText(QApplication::translate("MainWindow", "ZoomIn", nullptr));
        actionZoomOut->setText(QApplication::translate("MainWindow", "ZoomOut", nullptr));
        healthLabel->setText(QApplication::translate("MainWindow", "Health", nullptr));
        energyLabel->setText(QApplication::translate("MainWindow", "Energy", nullptr));
        label->setText(QApplication::translate("MainWindow", "DEFEAT", nullptr));
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
