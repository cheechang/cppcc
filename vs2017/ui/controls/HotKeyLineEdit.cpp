#include "HotKeyLineEdit.h"
#include <QEvent>
#include <QKeyEvent>
#include <QRegExpValidator>
#include <QDebug>
namespace ui{
    HotKeyLineEdit::HotKeyLineEdit(QWidget* parnet):QLineEdit(parnet)
    {
         setAttribute(Qt::WA_InputMethodEnabled, false);
    }


    HotKeyLineEdit::~HotKeyLineEdit(void)
    {
    }

    void HotKeyLineEdit::keyPressEvent( QKeyEvent *event )
    {        QString text = "";
        QChar key = event->key();

        if (event->modifiers() == (Qt::AltModifier | Qt::ControlModifier) && (event->key() > 65 && event->key() < 90 ))
        {
            text.append("ctrl+alt+");
            text.append(key.toLower());
        }

        if (event->modifiers() == (Qt::AltModifier) && (event->key() > 65 && event->key() < 90 ))
        {
            text.append("alt+");
            text.append(key.toLower());
        }

        if (event->modifiers() == (Qt::ControlModifier) && (event->key() > 65 && event->key() < 90 ))
        {
            text.append("ctrl+");
            text.append(key.toLower());
        }

         this->setText(text);
         event->accept();
    }

}
