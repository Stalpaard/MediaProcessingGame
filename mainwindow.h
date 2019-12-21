#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QGraphicsView>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, QGraphicsView* graphicalView = nullptr);
    ~MainWindow();
    void set2DGraphicsView(QGraphicsView newView);

private slots:
    void on_actionOpen_world_triggered();

    void on_actionQuit_triggered();

    void on_actiongraphicalView_triggered();

private:

    virtual void resizeEvent(QResizeEvent*) override;
    //std::vector<QWidget*> visualizations;

    Ui::MainWindow *ui;

    QGraphicsView* graphicalView;
#endif // MAINWINDOW_H
};
