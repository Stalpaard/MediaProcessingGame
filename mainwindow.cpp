#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, GraphicalView *graphicalView, TextView *textView)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowTitle(tr("Our Game"));
    this->graphicalView = graphicalView;
    ui->setupUi(this);
    game_ended = false;
    ui->viewWidget->insertWidget(1,graphicalView);
    ui->viewWidget->setCurrentIndex(1);

    ui->viewWidget->insertWidget(2, textView);

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

void MainWindow::on_actionpanLeft_triggered()
{
    emit pan(-1,0);
}

void MainWindow::on_actionpanTop_triggered()
{
    emit pan(0,-1);
}

void MainWindow::on_actionpanBottom_triggered()
{
    emit pan(0,1);
}

void MainWindow::on_actionpanRight_triggered()
{
    emit pan(1,0);
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





