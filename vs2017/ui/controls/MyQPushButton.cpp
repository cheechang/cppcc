#include "MyQPushButton.h"
#include <QMouseEvent>
namespace ui{
MyQPushButton::MyQPushButton(QWidget *parent):QPushButton(parent)
{	
}
MyQPushButton::~MyQPushButton()
{

}
void MyQPushButton::mouseMoveEvent(QMouseEvent *event){
	event->accept();
}
}
