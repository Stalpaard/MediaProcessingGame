#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QString>

#include "textedit.h"
#include "modelworld.h"

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
class QComboBox;
class QCompleter;
class QLabel;
class QLineEdit;
class QProgressBar;
QT_END_NAMESPACE
class TextEdit;

class TextView : public QWidget
{
     Q_OBJECT
public:
    TextView(QWidget *parent = nullptr,  std::vector<std::shared_ptr<Command>> *commands = nullptr, std::shared_ptr<ModelWorld> model =  nullptr);
    void fitLabel();

private:
    QCompleter *completer;
    TextEdit *completingTextEdit;
    QLabel *label;
    QFont font;
    QVBoxLayout *layout;
    QString print;
    bool displayPathfinding;
    std::shared_ptr<ModelWorld> data_model;
    std::tuple<int,int> camera_center;
    std::tuple<int,int> printSize;
    std::shared_ptr<std::vector<std::pair<int,int>>> path;

    bool checkIfPath(int Xpos, int Ypos);

public slots:
    void updateCameraCenter(int dx, int dy);
    void printEntities();
    void newPathfindingResult(std::shared_ptr<std::vector<std::pair<int,int>>> result);
    void showPathfinding(bool newvalue);

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // TEXTVIEW_H
