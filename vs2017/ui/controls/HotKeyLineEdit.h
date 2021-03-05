#pragma once
#include <QLineEdit>
#include <QWidget>
namespace ui{
    class HotKeyLineEdit :    public QLineEdit
    {
    public:
        explicit HotKeyLineEdit(QWidget *parent = 0);
        ~HotKeyLineEdit(void);
    protected:
        virtual void keyPressEvent(QKeyEvent *event);
    };


}
