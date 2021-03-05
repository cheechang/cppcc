#include "MyQToolButton.h"
#include <QMouseEvent>
namespace ui{
MyQToolButton::MyQToolButton(QWidget *parent):QToolButton(parent)
{	
}
MyQToolButton::~MyQToolButton()
{

}
void MyQToolButton::mouseMoveEvent(QMouseEvent *event){
	event->accept();
}
}
