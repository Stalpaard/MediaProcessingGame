#include "textedit.h"
#include <QCompleter>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QtDebug>
#include <QApplication>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QScrollBar>
#include <iostream>


TextEdit::TextEdit(QWidget *parent, std::vector<std::shared_ptr<Command>> *commands)
: QTextEdit(parent), commands(commands), c(nullptr)
{
}

TextEdit::~TextEdit()
{
}

void TextEdit::setCompleter(QCompleter *completer)
{
    if (c)
        QObject::disconnect(c, nullptr, this, nullptr);

    c = completer; //private instance of qcompleter

    if (!c)
        return;

    c->setWidget(this);
    c->setCompletionMode(QCompleter::PopupCompletion);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    QObject::connect(c, QOverload<const QString &>::of(&QCompleter::activated),
                     this, &TextEdit::insertCompletion);
}

QCompleter *TextEdit::completer() const
{
    return c;
}

// Complete the word in the textedit.
void TextEdit::insertCompletion(const QString& completion)
{
    if (c->widget() != this)
        return;
    QTextCursor tc = textCursor();
    int extra = completion.length() - c->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}

// Return the text under the cursor.
QString TextEdit::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}


// Reimplement focusInEvent()
void TextEdit::focusInEvent(QFocusEvent *e)
{
    if (c)
        c->setWidget(this);
    QTextEdit::focusInEvent(e);
}

void TextEdit::keyPressEvent(QKeyEvent *e)
{
    if (c && c->popup()->isVisible())
    {
        //ignore keys when the popup is visible
       switch (e->key())
       {
       case Qt::Key_Enter:
       case Qt::Key_Return:
       case Qt::Key_Escape:
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            e->ignore();
            return;
       default:
           break;
       }
    }
    else
    {
        switch (e->key())
        {
        case Qt::Key_Enter:
        case Qt::Key_Return:
             {
                e->ignore();
                QString temp = QTextEdit::toPlainText();        // Extract written text
                for (auto &c : *commands) // access by reference to avoid copying
                {
                    if(0 == QString::compare(c->getCommandString(), temp, Qt::CaseInsensitive))
                    {
                      c->operator()();
                    }
                }
                QTextEdit::clear();                             // Clear submitted text
                //QTextEdit::moveCursor(QTextCursor::Start);    // Reset cursor position
            }
             return;
        default:
            break;
        }
    }
    QTextEdit::keyPressEvent(e);
    QString completionPrefix = textUnderCursor();

    if (completionPrefix != c->completionPrefix())
    {
        c->setCompletionPrefix(completionPrefix);
        c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(c->popup()->sizeHintForColumn(0) + c->popup()->verticalScrollBar()->sizeHint().width());
    c->complete(cr);
}

QStringList TextEdit::getAllCommands() const
{
    QStringList words;
    for (auto &c : *commands) words << c->getCommandString();
    return words;
}

