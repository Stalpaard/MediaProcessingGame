#include "maincontroller.h"

MainController::MainController(QApplication& a) : app{a}
{
}

int MainController::startGameInstance(){
    std::cout << "start" << std::endl;
    QString worldFileName = QFileDialog::getOpenFileName(nullptr,"Select world file",QDir::currentPath(),"World Images (*.png)");

    if(worldFileName!=nullptr){
        QInputDialog amountOfEnemyPrompt;
        bool ok;
        int amountOfEnemies = QInputDialog::getInt(nullptr, "Input Enemies","Enter the desired amount of enemies:", 10, 2, 1000,1,&ok);
        if(ok){
            QInputDialog amountOfHealthpackPrompt;
            int amountOfHealthpacks = QInputDialog::getInt(nullptr, "Input Healthpacks","Enter the desired amount of healthpacks:", 10, 2, 1000,1,&ok);

            if(ok){
                std::shared_ptr<ModelWorld> model = std::make_shared<ModelWorld>(amountOfEnemies,amountOfHealthpacks,worldFileName);
                Strategy strategy(model);

                //2D View part
                MyGraphicsScene scene{worldFileName,model};
                GraphicalView view{&scene};

                //Pathfinding part
                model->setPathfindingAlgorithm(std::make_shared<aStarFast>(*(model->get2DRepresentation()),model->getColumns(),model->getRows()));

                //Text view part
                std::vector<std::shared_ptr<Command>> commands;
                commands.emplace_back(new CommandDown);
                commands.emplace_back(new CommandLeft);
                commands.emplace_back(new CommandPanDown);
                commands.emplace_back(new CommandPanLeft);
                commands.emplace_back(new CommandPanRight);
                commands.emplace_back(new CommandPanUp);
                commands.emplace_back(new CommandRight);
                commands.emplace_back(new CommandUp);
                commands.emplace_back(new CommandZoomIn);
                commands.emplace_back(new CommandZoomOut);
                TextView textView(nullptr, &commands, model);

                MainWindow w{nullptr, &view, &textView,amountOfEnemies,model->getColumns(),model->getRows()};

                //Connects for 2D View part
                    //Input
                QObject::connect(
                    &view, &GraphicalView::movementKeyPressed, //Send arrow key input to ModelWorld
                    model.get(), &ModelWorld::protagonistMoveRequested
                );
                QObject::connect(
                    &strategy, &Strategy::requestMove, //Send arrow key input to ModelWorld
                    model.get(), &ModelWorld::protagonistMoveRequested
                );

                    // MainWindow Updates
                QObject::connect(
                    model.get(), &ModelWorld::protagonistPositionChanged, //Update current position in Pathfinding page of StackedWidget
                    &w, &MainWindow::updateProtagonistPositionLabel
                );
                QObject::connect(
                    model.get(), &ModelWorld::protagonistHealthChanged, //Update healthbar in MainWindow
                    &w, &MainWindow::protagonistHealthUpdate
                );
                QObject::connect(
                    model.get(), &ModelWorld::protagonistEnergyChanged, //Update energybar in MainWindow
                    &w, &MainWindow::protagonistEnergyUpdate
                );
                QObject::connect(
                    model.get(), &ModelWorld::pathfindingAvailable, //Show pathfinding checkbox
                    &w, &MainWindow::pathfindingAvailable
                );
                QObject::connect(
                    model.get(), &ModelWorld::gameDefeat, //Show defeat screen
                    &w, &MainWindow::gameDefeat
                );
                QObject::connect(
                    model.get(), &ModelWorld::gameVictory, //Show victory screen
                    &w, &MainWindow::gameVictory
                );
                QObject::connect(
                    model.get(), &ModelWorld::remainingEnemiesChanged, //Update enemies counter in MainWindow
                    &w, &MainWindow::updateRemainingEnemies
                );
                    //ModelWorld updates
                QObject::connect(
                    &scene, &MyGraphicsScene::moveCompleted, //Re-enable protagonist arrow key input after walking animation has ended
                    model.get(), &ModelWorld::protagonistMoveCompleted
                );
                QObject::connect(
                    &view, &GraphicalView::zoom, //Update field-of-view in ModelWorld
                    model.get(), &ModelWorld::zoomRequested
                );
                QObject::connect(
                    &w, &MainWindow::runPathfinding, //Run pathfinding by pressing 'Run Algorithm' button
                    model.get(), &ModelWorld::pathfindingViewRequest
                );
                    //GraphicalView updates
                QObject::connect(
                    &scene, &MyGraphicsScene::updateFitScene, //Update view so whole scene fits in it
                    &view, &GraphicalView::fitScene
                );
                QObject::connect(
                    model.get(), &ModelWorld::endGame, //Disable input in GraphicalView
                    &view, &GraphicalView::gameEnd
                );
                    //MyGraphicsScene updates
                QObject::connect(
                    &view, &GraphicalView::pan,
                    &scene, &MyGraphicsScene::updateCameraCenter //Update camera center when ZSQD input
                );
                QObject::connect(
                    model.get(), &ModelWorld::poisonVisualChange, //Show poison visuals
                    &scene, &MyGraphicsScene::poisonLevelChanged
                );
                QObject::connect(
                    model.get(), &ModelWorld::newPathfindingResult, //Update pathfinding result pointer in MyGraphicsScene
                    &scene, &MyGraphicsScene::newPathfindingResult
                );
                QObject::connect(
                    &w, &MainWindow::changeAnimationSpeed,
                    &scene, &MyGraphicsScene::updateAnimationSpeed //Change animationspeed of 2D View using the slider
                );
                QObject::connect(
                    &w, &MainWindow::showPathfinding,
                    &scene, &MyGraphicsScene::showPathfinding //Enable/Disable pathfinding in view using CheckBox
                );
                QObject::connect(
                    model.get(), &ModelWorld::protagonistMovingDirection, //Update camera center when protagonist moves
                    &scene, &MyGraphicsScene::updateMovingDirection
                );
                    //MainController updates
                QObject::connect(
                    &w, &MainWindow::actionQuit,
                    this, &MainController::quitApp
                );
                QObject::connect(
                    &w, &MainWindow::openNewWorld,
                    this, &MainController::openNewWorld
                );

                //Connects for Strategy
                QObject::connect(
                    model.get(), &ModelWorld::endGame,
                    &strategy, &Strategy::gameEnd
                );
                QObject::connect(
                    &scene, &MyGraphicsScene::moveCompleted,
                    &strategy, &Strategy::nextMove
                );
                QObject::connect(
                    &w, &MainWindow::enableStrategy,
                    &strategy, &Strategy::enableStrategy
                );
                // Connects for the text view part
                for (auto &c : commands)
                {
                    QObject::connect(
                        c.get(), &Command::movementKeyPressed,
                        model.get(), &ModelWorld::protagonistMoveRequested);
                    QObject::connect(
                        c.get(), &Command::moveCompleted,
                        model.get(), &ModelWorld::protagonistMoveCompleted);
                    QObject::connect(
                        c.get(), &Command::zoom,
                        model.get(), &ModelWorld::zoomRequested);
                    QObject::connect(
                        c.get(), &Command::zoom,
                        &textView, &TextView::printEntities);
                    QObject::connect(
                        c.get(), &Command::updateCameraCenter,
                        &textView, &TextView::updateCameraCenter);
                }
                QObject::connect(
                    model.get(), &ModelWorld::changeCameraCenter,
                    &textView, &TextView::updateCameraCenter);
                QObject::connect(
                    model.get(), &ModelWorld::updateView,
                    &textView, &TextView::printEntities);
                QObject::connect(
                    model.get(), &ModelWorld::poisonVisualChange,
                    &textView, &TextView::printEntities);

                w.setWindowTitle("The Most Epic Game Ever");
                w.show();

                return app.exec();

            }
            else return 0;
        }
        else return 0;
    }
    else return 0;
}

void MainController::quitApp(){
    app.exit(0);
}

void MainController::openNewWorld(){
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    app.exit(0);
}
