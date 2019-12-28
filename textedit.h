#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>
#include <memory>

#include "command.h"

QT_BEGIN_NAMESPACE
class QCompleter;
QT_END_NAMESPACE

class TextEdit : public QTextEdit
{
    Q_OBJECT

public:
    TextEdit(QWidget *parent = nullptr, std::vector<std::shared_ptr<Command>> *commands = nullptr);
    ~TextEdit() override;

    void setCompleter(QCompleter *c);
    QCompleter *completer() const;
    QStringList getAllCommands() const;

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void focusInEvent(QFocusEvent *e) override;

private slots:
    void insertCompletion(const QString &completion);

private:
    QString textUnderCursor() const;
    std::vector<std::shared_ptr<Command>> *commands;

private:
    QCompleter *c; //instance of completer
};

#endif // TEXTEDIT_H
