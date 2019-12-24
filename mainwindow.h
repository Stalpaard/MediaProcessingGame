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
    MainWindow(QWidget *parent = nullptr, GraphicalView* graphicalView = nullptr, TextView* textView = nullptr);
    ~MainWindow() override;

private slots:
    void on_actionOpen_world_triggered();

    void on_actionQuit_triggered();

    void on_actiongraphicalView_triggered();

    void on_actiontextView_triggered();

    void on_animationSlider_valueChanged(int value);

    void on_RightPanKey_pressed();



    void on_RightPanKey_released();

    void on_LeftPanKey_pressed();

    void on_LeftPanKey_released();

    void on_UpPanKey_pressed();

    void on_UpPanKey_released();

    void on_DownPanKey_pressed();

    void on_DownPanKey_released();

public slots:
    void protagonistHealthUpdate(int h);
    void protagonistEnergyUpdate(int e);
    void gameDefeat();
    void gameVictory();
    void panLoop();

signals:
    void zoom(bool in_out);
    void pan(int dx, int dy);
    void changeAnimationSpeed(int value);

private:

    bool panBool;
    Direction panDir;
    void setEnabled2DViewWidgets(bool newvalue);
    virtual void resizeEvent(QResizeEvent*) override;

    Ui::MainWindow *ui;
    bool game_ended;

    GraphicalView* graphicalView;
    TextView* textView;
#endif // MAINWINDOW_H
};
