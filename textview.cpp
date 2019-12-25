#include "textview.h"
#include <QtWidgets>

TextView::TextView(QWidget *parent, std::vector<std::shared_ptr<Command>> *commands, std::shared_ptr<ModelWorld> model)
    : QWidget(parent), completer(nullptr), data_model(model), camera_center(std::make_tuple(0,0)), printSize(std::make_tuple(0,0))
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
    layout = new QVBoxLayout;
    font=QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setPointSize(6);
    label->setFont(font);
    label->setTextFormat(Qt::RichText); //for fixed text size
    printEntities();

    label->setFrameStyle(QFrame::Box);
    label->setStyleSheet("background-color: rgb(255, 255, 255);");

    // Layout:
    layout->addWidget(label);
    layout->addWidget(completingTextEdit);
    label->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    this->setLayout(layout);
}

void TextView::printEntities()
{
    int protagonistX = data_model->getMyProtagonist()->getXPos();
    int protagonistY = data_model->getMyProtagonist()->getYPos();
    std::get<0>(printSize) = 0;
    print = "";
    //int xDistance, yDistance;

    QFont font=QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setPointSize(6);

    //Get 2D representation of the world in range of the protagonist ('window' into the data)
    std::vector<std::vector<std::shared_ptr<MyTile>>> areaOfInterest = data_model->make2DRepresentationAroundPointWithRange(std::get<0>(camera_center),std::get<1>(camera_center),data_model->getFieldOfView());


//    painter.begin(&source);
//    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
//    painter.drawImage((range*32)+6,(range*32)+1,*(data_model->getMyProtagonist()->getRepresentation()));

    for(std::vector<std::shared_ptr<MyTile>> row : areaOfInterest)
    {
        std::get<0>(printSize)++;
        std::get<1>(printSize) = 0;
        for(std::shared_ptr<MyTile> column : row)
        {
            print.append("<span style=\"color:grey; font-family: monospace; white-space: pre;\">+---</span>");
            std::get<1>(printSize)++;
        }
        print.append("<span style=\"color:grey; font-family: monospace;  white-space: pre;\">+<br></span>");
        for(std::shared_ptr<MyTile> column : row)
        {
            print.append("<span style=\"color:grey; font-family: monospace;  white-space: pre;\">|</span>");
//            xDistance = column->getXPos()-centerX;
//            yDistance = column->getYPos()-centerY;
            if (column->getXPos() == protagonistX && column->getYPos() == protagonistY)
                print.append("<span style=\"color:blue; font-family: monospace;  white-space: pre; font-weight: bold;\">YOU</span>");
            else if(column->isOccupied())
                print.append("<span style=\"color:red; font-family: monospace;  white-space: pre; font-weight: bold;\"> X </span>");
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
    int nColumns = std::get<1>(printSize);
    while(nColumns > 0)
    {
        print.append("<span style=\"color:grey; font-family: monospace;  white-space: pre;\">+---</span>");
        nColumns--;
    }
    print.append("<span style=\"color:grey; font-family: monospace;  white-space: pre;\">+<br></span>");
    fitLabel();
    label->setText(print);
}

void TextView::fitLabel()
{
    QRect availablerect = label->contentsRect();
    QString oneLine = print.mid(0, print.indexOf("<br>")); //only first line
    QRect textrect   = QFontMetrics(font).boundingRect(oneLine);
    int height = textrect.height()*std::get<0>(printSize);

    float factorh = 18*availablerect.width() / float(textrect.width());
    float factorw = float(0.43)*availablerect.height() / float(height);
    float factor = std::min(factorh, factorw);

    if (factor < float(0.95) || factor > float(1.05))
    {
        float fontSize = float(font.pointSizeF())*factor;
        if(fontSize < 1) fontSize = 1;
        std::cout << "fontsize = " << fontSize << std::endl;
        font.setPointSize(int(fontSize));
        label->setFont(font);
    }
}

void TextView::updateCameraCenter(int dx, int dy)
{
    int currentcameraX = std::get<0>(camera_center);
    int currentcameraY = std::get<1>(camera_center);
    int newCameraX = currentcameraX+dx;
    int newCameraY = currentcameraY+dy;

    if(newCameraX > data_model->getColumns()) newCameraX = data_model->getColumns();
    else if(newCameraX < 0) newCameraX = 0;
    if(newCameraY > data_model->getRows()) newCameraY = data_model->getRows();
    else if(newCameraY < 0 ) newCameraY = 0;

    camera_center = std::make_tuple(newCameraX,newCameraY);
    printEntities();
}

