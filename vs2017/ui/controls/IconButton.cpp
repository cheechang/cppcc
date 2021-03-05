#include "IconButton.h"
#include <QPainter>
#include <QMouseEvent>

namespace uicontrols{
	IconButton::IconButton(QWidget *parent)
		:QToolButton(parent),m_pic_name("")
	{	
		m_status = NORMAL;
		m_bMousePressed = false;
		m_btnCanchecked = m_btnChecked = false;

		//设置文本颜色
		QPalette text_palette = palette();
		text_palette.setColor(QPalette::ButtonText, QColor(0, 0, 0));
		setPalette(text_palette);

		this->setCursor(Qt::PointingHandCursor);
	}

	IconButton::~IconButton()
	{

	}

	void IconButton::setPicName(QString pic_name)
	{
		m_pic_name = pic_name;
		setFixedSize(QPixmap(pic_name).size());
	}

	void IconButton::enterEvent(QEvent *)
	{
		m_status = ENTER;
		update();
	}

	void IconButton::mousePressEvent(QMouseEvent *event)
	{
		//若点击鼠标左键
		if(event->button() == Qt::LeftButton)
		{
			if (m_btnCanchecked)
			{
				m_btnChecked =!m_btnChecked;
			}
			emit clicked();
			m_bMousePressed = true;
			m_status = PRESS;
			update();
			event->accept();
		}
	}

	void IconButton::mouseReleaseEvent(QMouseEvent *event)
	{
		//若点击鼠标左键
		if(m_bMousePressed && event->button() == Qt::LeftButton)
		{
			m_bMousePressed = false;
			m_status = NORMAL;
			update();
			event->accept();
		}

	}
	void IconButton::mouseMoveEvent(QMouseEvent *event){
		event->accept();
	}

	void IconButton::leaveEvent(QEvent *)
	{
		m_status = NORMAL;
		update();

	}

	void IconButton::paintEvent(QPaintEvent *e)
	{
		if(m_pic_name.isEmpty()){
			QToolButton::paintEvent(e);
			return;
		}
		QPainter painter(this);
		QPixmap pixmap;
		if (m_btnCanchecked)
		{
			QString name = !m_btnChecked ?m_pic_name:m_pic_name+QString("-hover");
			pixmap.load(name);
			painter.drawPixmap(rect(), pixmap);
			return;
		}

		switch(m_status)
		{
		case NORMAL:
			{
				pixmap.load(m_pic_name);
				break;
			}    
		case ENTER:
			{
				bool  ret = pixmap.load(m_pic_name + QString("-hover"));
				if(!ret){
					pixmap.load(m_pic_name);
				}
				break;
			} 
		case PRESS:
			{
				bool  ret = pixmap.load(m_pic_name + QString("-pressed"));
				if(!ret){
					pixmap.load(m_pic_name);
				}
				break;
			}   
		case NOSTATUS:
			{
				pixmap.load(m_pic_name);	
				break;
			}   
		default:
			pixmap.load(m_pic_name);
		}
		pixmap = pixmap.scaled(this->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
		painter.drawPixmap(rect(), pixmap);
	}

	uicontrols::IconButton::ButtonStatus IconButton::btnStatus()
	{
		return m_status;
	}

	void IconButton::setCheckable( bool canCheckable,bool checked )
	{
		m_btnCanchecked = canCheckable;
		m_btnChecked = checked;
		update();
	}

	bool IconButton::checkedStatus()
	{
		return m_btnChecked;
	}
	void IconButton::mouseDoubleClickEvent(QMouseEvent* event)
	{
		emit signalDoubleClicked();
		event->accept();
	}
	void IconButton::setBtnStatus(ButtonStatus status){
		m_status =  status;
		update();
	}
}