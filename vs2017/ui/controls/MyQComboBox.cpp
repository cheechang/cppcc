#include "MyQComboBox.h"
#include <QMouseEvent>
namespace ui{
    MyQComboBox::MyQComboBox(QWidget* parent):QComboBox(parent)
    {
    }

    MyQComboBox::~MyQComboBox(void)
    {
    }

    void MyQComboBox::mouseMoveEvent( QMouseEvent *event )
    {
        event->accept();
    }

}

