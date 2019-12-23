#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, GraphicalView *graphicalView)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->graphicalView = graphicalView;
    ui->setupUi(this);
    game_ended = false;
    ui->viewWidget->insertWidget(1,graphicalView);
    ui->viewWidget->setCurrentIndex(1);
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
    if(!(game_ended)) ui->viewWidget->setCurrentIndex(1);
}

void MainWindow::on_actiontextView_triggered()
{
    ui->viewWidget->setCurrentIndex(2);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   if(ui->viewWidget->currentIndex() == 1){
       graphicalView->fitInView(graphicalView->sceneRect(), Qt::KeepAspectRatio);
   }
}

void MainWindow::on_actionZoomIn_triggered()
{
    emit zoom(true);
}

void MainWindow::on_actionZoomOut_triggered()
{
    emit zoom(false);
}


//PUBLIC SLOTS

void MainWindow::protagonistHealthUpdate(int h){
    std::cout << "yesboi" << std::endl;
   ui->healthBar->setValue(h);
}

void MainWindow::protagonistEnergyUpdate(int e){
   ui->energyBar->setValue(e);
}

void MainWindow::gameEnd(){
    std::cout << "ended" << std::endl;
    game_ended = true;
    ui->viewWidget->setCurrentIndex(0);
}


