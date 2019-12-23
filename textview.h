#ifndef TEXTVIEW_H
#define TEXTVIEW_H

#include <QMainWindow>
#include "textedit.h"
#include <QVBoxLayout>

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
    TextView(QWidget *parent = nullptr,  std::vector<std::shared_ptr<Command>> *commands = nullptr);

private:
    QCompleter *completer;
    TextEdit *completingTextEdit;
};

#endif // TEXTVIEW_H
