#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "graphicalview.h"
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, GraphicalView* graphicalView = nullptr);
    ~MainWindow() override;

private slots:
    void on_actionOpen_world_triggered();

    void on_actionQuit_triggered();

    void on_actiongraphicalView_triggered();

    void on_actionZoomIn_triggered();
    void on_actionZoomOut_triggered();

    void on_actiontextView_triggered();

public slots:
    void protagonistHealthUpdate(int h);
    void protagonistEnergyUpdate(int e);
    void gameEnd();

signals:
    void zoom(bool in_out);

private:

    virtual void resizeEvent(QResizeEvent*) override;

    Ui::MainWindow *ui;
    bool game_ended;

    GraphicalView* graphicalView;
#endif // MAINWINDOW_H
};
