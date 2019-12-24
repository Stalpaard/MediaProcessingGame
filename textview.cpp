#include "textview.h"
#include <QtWidgets>

TextView::TextView(QWidget *parent, std::vector<std::shared_ptr<Command>> *commands, std::shared_ptr<ModelWorld> model)
    : QWidget(parent), completer(nullptr), data_model(model)
{  
    // Textedit:
    completingTextEdit = new TextEdit(parent, commands);
    completer = new QCompleter(this);
    completer->setModel(new QStringListModel(completingTextEdit->getAllCommands(), completer));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    completingTextEdit->setCompleter(completer);
    completingTextEdit->setMaximumHeight(25);
    completingTextEdit->setFrameStyle(QFrame::Box);



    // Label:
    label = new QLabel;
    QFont font=QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setPointSize(6);
    label->setFont(font);
    label->setTextFormat(Qt::RichText); //for fixed text size
    printEntities();
    label->setFrameStyle(QFrame::Box);
    label->setStyleSheet("background-color: rgb(255, 255, 255);");

    // Layout:
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(completingTextEdit);
    label->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    this->setLayout(layout);
}

void TextView::printEntities()
{

    //int xDistance, yDistance;
    QString print;
    int range = 30;

    QFont font=QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setPointSize(6);

//    //Get 2D representation of the world in range of the protagonist ('window' into the data)
    std::vector<std::vector<std::shared_ptr<MyTile>>> areaOfInterest = data_model->make2DRepresentationAroundPointWithRange(0,0,range);

//    painter.begin(&source);
//    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
//    painter.drawImage((range*32)+6,(range*32)+1,*(data_model->getMyProtagonist()->getRepresentation()));

    for(std::vector<std::shared_ptr<MyTile>> row : areaOfInterest)
    {
        for(int i = 0; i < range; i++) print.append("<span style=\"color:grey; font-family: monospace; white-space: pre;\">+---</span>");
        print.append("<span style=\"color:grey; font-family: monospace;  white-space: pre;\">+<br></span>");
        for(std::shared_ptr<MyTile> column : row)
        {
            print.append("<span style=\"color:grey; font-family: monospace;  white-space: pre;\">|</span>");
//            xDistance = column->getXPos()-centerX;
//            yDistance = column->getYPos()-centerY;
            if(column->isOccupied()) print.append("<span style=\"color:red; font-family: monospace;  white-space: pre;\"> X </span>");
            else print.append("<span style=\"color:grey; font-family: monospace;  white-space: pre;\">   </span>");

//                std::shared_ptr<Entity> occupant = column->getOccupant();
//                float occupant_value = occupant->getValue();
//                std::shared_ptr<QImage> representation = occupant->getRepresentation();
//                painter.drawImage(6+(32*xDistance)+(range*32),1+(32*yDistance)+(range*32),*representation);

//                if(!(occupant->isDefeated())){
//                    if(occupant_value > 0) painter.setPen(Qt::red);
//                    else painter.setPen(Qt::darkGreen);
//                    painter.drawText(10+(32*xDistance)+(range*32),1+(32*yDistance)+(range*32),QString::number(std::abs(static_cast<int>(occupant->getValue()))));
//                }
//            }
//            if(column->getPoisonLevel() > 0){
//                painter.setPen(Qt::green);
//                painter.drawText(10+(32*xDistance)+(range*32),20+(32*yDistance)+(range*32),QString::number(std::abs(static_cast<int>(column->getPoisonLevel()))));
//            }
        }
        print.append("<span style=\"color:grey; font-family: monospace;  white-space: pre;\">|<br></span>");
    }
    for(int i = 0; i < range; i++) print.append("<span style=\"color:grey; font-family: monospace;  white-space: pre;\">+---</span>");
    print.append("<span style=\"color:grey; font-family: monospace;  white-space: pre;\">+<br></span>");
    label->setText(print);
}
