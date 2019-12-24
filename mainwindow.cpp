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
    ui->animationSlider->setValue(15);
    ui->sliderLabel->setText("Animation speed (" + QString::number(15) + " ms/frame)");
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
    if(!(game_ended)){
        ui->viewWidget->setCurrentIndex(1);
        setEnabled2DViewWidgets(true);
    }
}

void MainWindow::on_actiontextView_triggered()
{
    if(!(game_ended)){
        ui->viewWidget->setCurrentIndex(2);
        setEnabled2DViewWidgets(false);
    }
}

void MainWindow::on_animationSlider_valueChanged(int value)
{
    ui->sliderLabel->setText("Animation speed (" + QString::number(value) + " ms/frame)");
    emit changeAnimationSpeed(value);
}

void MainWindow::on_UpPanKey_clicked()
{
    emit pan(0,-1);
}

void MainWindow::on_LeftPanKey_clicked()
{
    emit pan(-1,0);
}

void MainWindow::on_RightPanKey_clicked()
{
    emit pan(1,0);
}

void MainWindow::on_DownPanKey_clicked()
{
    emit pan(0,1);
}


void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   if(ui->viewWidget->currentIndex() == 1){
       graphicalView->fitInView(graphicalView->sceneRect(), Qt::KeepAspectRatio);
   }
}

void MainWindow::setEnabled2DViewWidgets(bool newvalue){
    if(newvalue){
        ui->animationSlider->setEnabled(true);
        ui->animationSlider->setVisible(true);
        ui->sliderLabel->setVisible(true);
        ui->LeftPanKey->setEnabled(true);
        ui->RightPanKey->setEnabled(true);
        ui->UpPanKey->setEnabled(true);
        ui->DownPanKey->setEnabled(true);
        ui->LeftPanKey->setVisible(true);
        ui->RightPanKey->setVisible(true);
        ui->UpPanKey->setVisible(true);
        ui->DownPanKey->setVisible(true);
    }
    else{
        ui->animationSlider->setEnabled(false);
        ui->animationSlider->setVisible(false);
        ui->sliderLabel->setVisible(false);
        ui->LeftPanKey->setEnabled(false);
        ui->RightPanKey->setEnabled(false);
        ui->UpPanKey->setEnabled(false);
        ui->DownPanKey->setEnabled(false);
        ui->LeftPanKey->setVisible(false);
        ui->RightPanKey->setVisible(false);
        ui->UpPanKey->setVisible(false);
        ui->DownPanKey->setVisible(false);
    }
}




//PUBLIC SLOTS

void MainWindow::protagonistHealthUpdate(int h){
   ui->healthBar->setValue(h);
}

void MainWindow::protagonistEnergyUpdate(int e){
   ui->energyBar->setValue(e);
}

void MainWindow::gameEnd(){
    game_ended = true;
    ui->viewWidget->setCurrentIndex(0);
}






