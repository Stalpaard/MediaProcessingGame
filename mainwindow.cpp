#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, GraphicalView *graphicalView, TextView *textView)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), game_ended{false}
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
        ui->helpLabel->setVisible(true);
        ui->zoomHelpLabel->setVisible(true);
        ui->panHelpLabel->setVisible(true);
        ui->moveHelpLabel->setVisible(true);
    }
    else{
        ui->animationSlider->setEnabled(false);
        ui->animationSlider->setVisible(false);
        ui->sliderLabel->setVisible(false);
        ui->helpLabel->setVisible(false);
        ui->zoomHelpLabel->setVisible(false);
        ui->panHelpLabel->setVisible(false);
        ui->moveHelpLabel->setVisible(false);
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
