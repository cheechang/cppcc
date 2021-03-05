#pragma once
#include "QComboBox"
namespace ui{
    class MyQComboBox :    public QComboBox
    {
        Q_OBJECT
    public:
       explicit MyQComboBox(QWidget* parent);
        ~MyQComboBox(void);
    protected:
        void mouseMoveEvent(QMouseEvent *event);
    };

}

