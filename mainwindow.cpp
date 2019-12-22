#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, QGraphicsView *graphicalView)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    this->graphicalView = graphicalView;
    //ui->viewWidget = this->graphicalView;
    ui->setupUi(this);
    setCentralWidget(graphicalView);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_world_triggered()
{

}

void MainWindow::on_actionQuit_triggered()
{

}

void MainWindow::on_actiongraphicalView_triggered()
{
    if(this->centralWidget() != graphicalView) setCentralWidget(graphicalView);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   graphicalView->fitInView(graphicalView->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_actionZoomIn_triggered()
{
    emit zoom(true);
}

void MainWindow::on_actionZoomOut_triggered()
{
    emit zoom(false);
}
