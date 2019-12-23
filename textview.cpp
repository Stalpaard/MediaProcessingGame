#include "textview.h"
#include <QtWidgets>

TextView::TextView(QWidget *parent, std::vector<std::shared_ptr<Command>> *commands)
    : QWidget(parent), completer(nullptr)
{
    completingTextEdit = new TextEdit(parent, commands);
    completer = new QCompleter(this);
    completer->setModel(new QStringListModel(completingTextEdit->getAllCommands(), completer));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    completingTextEdit->setCompleter(completer);

    //setCentralWidget(completingTextEdit);
    completingTextEdit->resize(500, 100);
    //setWindowTitle(tr("Completer"));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(completingTextEdit);
    this->setLayout(layout);
}
