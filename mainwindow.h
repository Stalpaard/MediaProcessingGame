#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include "graphicalview.h"
#include "textedit.h"
#include "textview.h"
#include "direction.h"
#include <QKeyEvent>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, GraphicalView* graphicalView = nullptr, TextView* textView = nullptr, int amountOfEnemies = 0, int mapCols = 0, int mapRows = 0);
    ~MainWindow() override;

private slots:
    void on_actionOpen_world_triggered();

    void on_actionQuit_triggered();

    void on_actiongraphicalView_triggered();

    void on_actiontextView_triggered();

    void on_animationSlider_valueChanged(int value);

    void on_actionPathFinding_triggered();

    void on_pushButton_clicked();

public slots:
    void protagonistHealthUpdate(int h);
    void protagonistEnergyUpdate(int e);
    void gameDefeat();
    void gameVictory();
    void updateRemainingEnemies(int remainingAmount);
    void updateProtagonistPositionLabel(int x, int y);

signals:
    void zoom(bool in_out);
    void changeAnimationSpeed(int value);
    void actionQuit();
    void openNewWorld();
    void runPathfinding(int destX, int destY);

private:
    void setEnabled2DViewWidgets(bool newvalue);
    virtual void resizeEvent(QResizeEvent*) override;

    Ui::MainWindow *ui;
    bool game_ended;

    GraphicalView* graphicalView;
    TextView* textView;
};

#endif // MAINWINDOW_H
