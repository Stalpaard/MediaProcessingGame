#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, GraphicalView *graphicalView, TextView *textView)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), panBool{false}, game_ended{false}
{
    setWindowTitle(tr("Our Game"));
    this->graphicalView = graphicalView;
    ui->setupUi(this);
    ui->viewWidget->insertWidget(2,graphicalView);
    ui->viewWidget->setCurrentIndex(2);
    ui->animationSlider->setValue(15);
    ui->sliderLabel->setText("Animation speed (" + QString::number(15) + " ms/frame)");
    ui->viewWidget->insertWidget(3, textView);

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
        ui->viewWidget->setCurrentIndex(2);
        setEnabled2DViewWidgets(true);
    }
}

void MainWindow::on_actiontextView_triggered()
{
    if(!(game_ended)){
        ui->viewWidget->setCurrentIndex(3);
        setEnabled2DViewWidgets(false);
    }
}

void MainWindow::on_animationSlider_valueChanged(int value)
{
    ui->sliderLabel->setText("Animation speed (" + QString::number(value) + " ms/frame)");
    emit changeAnimationSpeed(value);
}


void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   if(ui->viewWidget->currentIndex() == 2){
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

void MainWindow::gameDefeat(){
    game_ended = true;
    ui->viewWidget->setCurrentIndex(0);
}

void MainWindow::gameVictory(){
    game_ended = true;
    ui->viewWidget->setCurrentIndex(1);
}


void MainWindow::panLoop(){
    if(panBool){
        switch(panDir){
            case Direction::LEFT:
                emit pan(-1,0);
                break;
            case Direction::RIGHT:
                emit pan(1,0);
                break;
            case Direction::UP:
                emit pan(0,-1);
                break;
            case Direction::DOWN:
                emit pan(0,1);
                break;
        }
        QTimer::singleShot(100, this, SLOT(panLoop()));
    }
}


void MainWindow::on_RightPanKey_pressed()
{
    panBool = true;
    panDir = Direction::RIGHT;
    panLoop();
}

void MainWindow::on_RightPanKey_released()
{
    panBool = false;
}

void MainWindow::on_LeftPanKey_pressed()
{
    panBool = true;
    panDir = Direction::LEFT;
    panLoop();
}

void MainWindow::on_LeftPanKey_released()
{
    panBool = false;
}

void MainWindow::on_UpPanKey_pressed()
{
    panBool = true;
    panDir = Direction::UP;
    panLoop();
}

void MainWindow::on_UpPanKey_released()
{
    panBool = false;
}

void MainWindow::on_DownPanKey_pressed()
{
    panBool = true;
    panDir = Direction::DOWN;
    panLoop();
}

void MainWindow::on_DownPanKey_released()
{
    panBool = false;
}
