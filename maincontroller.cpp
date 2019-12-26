#include "maincontroller.h"

MainController::MainController(QApplication& a) : app{a}
{
}

int MainController::startGameInstance(){
    std::cout << "start" << std::endl;
    QString worldFileName = QFileDialog::getOpenFileName(0,"Select world file",QDir::currentPath(),"World Images (*.png)");
    newWorldRequested = false;

    if(worldFileName!=nullptr){
        QInputDialog amountOfEnemyPrompt;
        bool ok;
        int amountOfEnemies = QInputDialog::getInt(0, "Input Enemies","Enter the desired amount of enemies:", 10, 2, 1000,1,&ok);
        if(ok){
            QInputDialog amountOfHealthpackPrompt;
            int amountOfHealthpacks = QInputDialog::getInt(0, "Input Healthpacks","Enter the desired amount of healthpacks:", 10, 2, 1000,1,&ok);

            if(ok){
                std::shared_ptr<ModelWorld> model = std::make_shared<ModelWorld>(amountOfEnemies,amountOfHealthpacks,worldFileName);
                //2D view part
                MyGraphicsScene scene{worldFileName,model};
                GraphicalView view{&scene};

                // text view part
                std::vector<std::shared_ptr<Command>> *commands = new std::vector<std::shared_ptr<Command>>;
                commands->emplace_back(new CommandDown);
                commands->emplace_back(new CommandLeft);
                commands->emplace_back(new CommandPanDown);
                commands->emplace_back(new CommandPanLeft);
                commands->emplace_back(new CommandPanRight);
                commands->emplace_back(new CommandPanUp);
                commands->emplace_back(new CommandRight);
                commands->emplace_back(new CommandUp);
                commands->emplace_back(new CommandZoomIn);
                commands->emplace_back(new CommandZoomOut);
                TextView *textView = new TextView(nullptr, commands, model);

                // a star part

                MainWindow w{nullptr, &view, textView,amountOfEnemies,model->getColumns(),model->getRows()};
                QObject::connect(
                    &view, &GraphicalView::movementKeyPressed,
                    model.get(), &ModelWorld::protagonistMoveRequested
                );


                QObject::connect(
                    &scene, &MyGraphicsScene::updateFitScene,
                    &view, &GraphicalView::fitScene
                );
                QObject::connect(
                    &scene, &MyGraphicsScene::moveCompleted,
                    model.get(), &ModelWorld::protagonistMoveCompleted
                );
                QObject::connect(
                    model.get(), &ModelWorld::changeCameraCenter,
                    &scene, &MyGraphicsScene::updateCameraCenter
                );
                QObject::connect(
                    model.get(), &ModelWorld::protagonistPositionChanged,
                    &w, &MainWindow::updateProtagonistPositionLabel
                );
                QObject::connect(
                    model.get(), &ModelWorld::poisonVisualChange,
                    &scene, &MyGraphicsScene::poisonLevelChanged
                );
                QObject::connect(
                    model.get(), &ModelWorld::protagonistHealthChanged,
                    &w, &MainWindow::protagonistHealthUpdate
                );
                QObject::connect(
                    model.get(), &ModelWorld::protagonistEnergyChanged,
                    &w, &MainWindow::protagonistEnergyUpdate
                );
                QObject::connect(
                    model.get(), &ModelWorld::gameDefeat,
                    &w, &MainWindow::gameDefeat
                );
                QObject::connect(
                    model.get(), &ModelWorld::gameVictory,
                    &w, &MainWindow::gameVictory
                );
                QObject::connect(
                    model.get(), &ModelWorld::endGame,
                    &view, &GraphicalView::gameEnd
                );
                QObject::connect(
                    model.get(), &ModelWorld::remainingEnemiesChanged,
                    &w, &MainWindow::updateRemainingEnemies
                );
                QObject::connect(
                    &view, &GraphicalView::zoom,
                    model.get(), &ModelWorld::zoomRequested
                );
                QObject::connect(
                    &view, &GraphicalView::pan,
                    &scene, &MyGraphicsScene::updateCameraCenter
                );
                QObject::connect(
                    &w, &MainWindow::changeAnimationSpeed,
                    &scene, &MyGraphicsScene::updateAnimationSpeed
                );
                QObject::connect(
                    &w, &MainWindow::actionQuit,
                    this, &MainController::quitApp
                );
                QObject::connect(
                    &w, &MainWindow::runPathfinding,
                    model.get(), &ModelWorld::runPathfinding
                );
                QObject::connect(
                    &w, &MainWindow::openNewWorld,
                    this, &MainController::openNewWorld
                );

                // Connects for the text view part
                for (auto &c : *commands)
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
                            textView, &TextView::printEntities);
                        QObject::connect(
                            c.get(), &Command::updateCameraCenter,
                            textView, &TextView::updateCameraCenter);
                    }
                QObject::connect(
                    model.get(), &ModelWorld::changeCameraCenter,
                    textView, &TextView::updateCameraCenter);
                QObject::connect(
                    model.get(), &ModelWorld::updateView,
                    textView, &TextView::printEntities);
                QObject::connect(
                    model.get(), &ModelWorld::poisonVisualChange,
                    textView, &TextView::printEntities);

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
