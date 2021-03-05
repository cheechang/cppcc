#include "PushButton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include "CloudDiskMenu.h"
namespace ui{
	PushButton::PushButton(QWidget *parent,bool showmenu):m_isshowmenu(showmenu),
	QPushButton(parent)
{	
	status = NORMAL;
	mouse_press = false;
}

PushButton::~PushButton()
{

}

void PushButton::setPicName(QString pic_name)
{
	this->pic_name = pic_name;
	setFixedSize(QPixmap(pic_name).size());
}

void PushButton::enterEvent(QEvent *)
{
	setCursor(Qt::PointingHandCursor);
	status = ENTER;
	update();
}

void PushButton::mousePressEvent(QMouseEvent *event)
{
	//Èôµã»÷Êó±ê×ó¼ü
	if(event->button() == Qt::LeftButton)
	{
		mouse_press = true;
		status = PRESS;
		update();
	}
	if (event->button() == Qt::RightButton && m_isshowmenu)
	{
		//m_menu.reset(new CloudDiskMenu(this));
		//connect(m_menu.data(), SIGNAL(signalRenameMenu()), this, SIGNAL(signalRenameMenu()));
		//connect(m_menu.data(), SIGNAL(signalDelMenu()), this, SIGNAL(signalDelMenu()));
		//connect(m_menu.data(), SIGNAL(signalRefresh()), this, SIGNAL(signalRefresh()));
		//connect(m_menu.data(), SIGNAL(signalSortByTime()), this, SLOT(onSortByTime()));
		//m_menu->show(QCursor::pos()+ QPoint(5, 10));
		QPoint pos = QCursor::pos() + QPoint(5, 10);
		emit signalShowMenu(pos);
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
	}
}

void PushButton::leaveEvent(QEvent *)
{
	qApp->restoreOverrideCursor();
	status = NORMAL;
	update();
}

void PushButton::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QPixmap pixmap;
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

}
