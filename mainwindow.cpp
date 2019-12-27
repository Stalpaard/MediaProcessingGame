#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, GraphicalView *graphicalView, TextView *textView, int amountOfEnemies, int mapCols, int mapRows)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), game_ended{false}
{
    this->graphicalView = graphicalView;
    ui->setupUi(this);
    ui->viewWidget->insertWidget(3,graphicalView);
    ui->viewWidget->setCurrentIndex(3);
    ui->animationSlider->setValue(15);
    ui->sliderLabel->setText("Animation speed (" + QString::number(15) + " ms/frame)");
    ui->viewWidget->insertWidget(4, textView);
    updateRemainingEnemies(amountOfEnemies);
    ui->xSpinBox->setMaximum(mapCols-1);
    ui->ySpinBox->setMaximum(mapRows-1);
    ui->pathfindingCheckBox->setEnabled(false);
    ui->pathfindingCheckBox->setVisible(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_world_triggered()
{
    emit openNewWorld();
}

void MainWindow::on_actionQuit_triggered()
{
    emit actionQuit();
}

void MainWindow::on_actiongraphicalView_triggered()
{
    if(!(game_ended)){
        ui->viewWidget->setCurrentIndex(3);
        setEnabled2DViewWidgets(true);
    }
}

void MainWindow::on_actiontextView_triggered()
{
    if(!(game_ended)){
        ui->viewWidget->setCurrentIndex(4);
        setEnabled2DViewWidgets(false);
    }
}

void MainWindow::on_animationSlider_valueChanged(int value)
{
    ui->sliderLabel->setText("Animation speed (" + QString::number(value) + " ms/frame)");
    emit changeAnimationSpeed(value);
}

void MainWindow::on_actionPathFinding_triggered()
{
    if(!(game_ended)){
        ui->viewWidget->setCurrentIndex(2);
        setEnabled2DViewWidgets(false);
    }
}

void MainWindow::on_pathfindingCheckBox_stateChanged(int arg1)
{
    switch(arg1){
        case Qt::CheckState::Checked :
            emit showPathfinding(true);
            break;
        case Qt::CheckState::Unchecked :
            emit showPathfinding(false);
            break;
    }
}

void MainWindow::on_runAlgoButton_clicked()
{
    ui->runAlgoButton->setText("Running..");
    ui->runAlgoButton->setDisabled(true);
    emit runPathfinding(ui->xSpinBox->value(), ui->ySpinBox->value());
    ui->viewWidget->setCurrentIndex(3);
    setEnabled2DViewWidgets(true);
    std::cout << "button clicked" << std::endl;
}


void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   if(ui->viewWidget->currentIndex() == 2) graphicalView->fitInView(graphicalView->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::setEnabled2DViewWidgets(bool newvalue){
    ui->animationSlider->setEnabled(newvalue);
    ui->animationSlider->setVisible(newvalue);
    ui->sliderLabel->setVisible(newvalue);
    ui->helpLabel->setVisible(newvalue);
    ui->zoomHelpLabel->setVisible(newvalue);
    ui->panHelpLabel->setVisible(newvalue);
    ui->moveHelpLabel->setVisible(newvalue);
    ui->pathfindingCheckBox->setEnabled(newvalue);
    ui->pathfindingCheckBox->setVisible(newvalue);
}

//PUBLIC SLOTS

void MainWindow::protagonistHealthUpdate(int h){
    ui->healthBar->setValue(h);
}

void MainWindow::pathfindingAvailable(){
    ui->pathfindingCheckBox->setEnabled(true);
    ui->pathfindingCheckBox->setVisible(true);
    ui->pathfindingCheckBox->setCheckState(Qt::CheckState::Checked);
    ui->runAlgoButton->setText("Run Algorithm");
    ui->runAlgoButton->setDisabled(false);
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

void MainWindow::updateRemainingEnemies(int value) {
    ui->remainingEnemiesLabel->setText("Remaining enemies: " + QString::number(value));
}

void MainWindow::updateProtagonistPositionLabel(int x, int y){
    ui->positionLabel->setText("Current position: (" + QString::number(x) + "," + QString::number(y) + ")");
}


