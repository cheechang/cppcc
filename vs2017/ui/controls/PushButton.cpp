#include "PushButton.h"
#include <QPainter>
#include <QMouseEvent>
extern QString gCutScrenToolTips;
namespace ui{
PushButton::PushButton(QWidget *parent)
	:QPushButton(parent)
{	
	mUseCutScreen = false;
	status = NORMAL;
	mouse_press = false;
	mCanchecked = mChecked = false;

	this->setCursor(Qt::PointingHandCursor);
}

PushButton::~PushButton()
{

}

void PushButton::setPicName(QString pic_name)
{
	this->pic_name = pic_name;
	setFixedSize(QPixmap(pic_name).size());
}

void PushButton::setUseCutScreen(bool isUse)
{
	mUseCutScreen = isUse;
}
void PushButton::enterEvent(QEvent *)
{
	if (mUseCutScreen){
		setToolTip(gCutScrenToolTips);
	}
	status = ENTER;
	update();
}

void PushButton::mousePressEvent(QMouseEvent *event)
{
	//Èôµã»÷Êó±ê×ó¼ü
	if(event->button() == Qt::LeftButton)
	{
		if (mCanchecked)
		{
			mChecked =!mChecked;
		}
		mouse_press = true;
		status = PRESS;
		update();
		event->accept();
	}
}

void PushButton::mouseReleaseEvent(QMouseEvent *event)
{
	//Èôµã»÷Êó±ê×ó¼ü
	if(mouse_press  && this->rect().contains(event->pos()))
	{
		mouse_press = false;
		status = ENTER;
		update();
		emit clicked();
		event->accept();
	}
	
}
void PushButton::mouseMoveEvent(QMouseEvent *event){
	event->accept();
}

void PushButton::leaveEvent(QEvent *)
{
	status = NORMAL;
	update();

}

void PushButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QPixmap pixmap;
	if (mCanchecked)
	{
		QString name = !mChecked ?pic_name:pic_name+QString("-hover");
		pixmap.load(name);
		painter.drawPixmap(rect(), pixmap);
		return;
	}

	switch(status)
	{
	case NORMAL:
		{
			pixmap.load(pic_name);
			break;
		}    
	case ENTER:
		{
			pixmap.load(pic_name + QString("-hover"));
			break;
		} 
	case PRESS:
		{
			pixmap.load(pic_name + QString("-pressed"));	
			break;
		}   
	case NOSTATUS:
		{
			pixmap.load(pic_name);	
			break;
		}   
	default:
		pixmap.load(pic_name);
	}
	
	painter.drawPixmap(rect(), pixmap);
}

int PushButton::btnStatus()
{
	return status;
}

void PushButton::setCheckable( bool canCheckable,bool checked )
{
	mCanchecked = canCheckable;
	mChecked = checked;
	update();
}

bool PushButton::checkedStatus()
{
	return mChecked;
}

}
