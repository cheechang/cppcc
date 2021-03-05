#include "BaseDialog.h"
#include <log.h>
#include <QDebug>
#include "common/Common.h"
#include <QApplication>
namespace ui{    
BaseDialog::BaseDialog(QWidget *parent):QDialog(parent),m_movePosition(QPoint(0,0)),m_isMoveWindow(false)
{
	setWindowFlags(Qt::FramelessWindowHint|Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint|Qt::Dialog);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowTitle(APP_NAME);
}

BaseDialog::~BaseDialog()
{

}

void BaseDialog::paintEvent(QPaintEvent *)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
	path.addRect(10, 10, this->width()-20, this->height()-20);

	QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 50);
    for(int i=0; i<10; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

void BaseDialog::mousePressEvent(QMouseEvent *event)
{
	m_isMoveWindow = true;  
    //��¼���������ڴ��ڵ�λ��  
    //event->globalPos()��갴��ʱ����������������Ļλ��  
    //pos() this->pos()��갴��ʱ�����������������Ļλ��  
    m_movePosition = event->globalPos() - pos();  
    return QDialog::mousePressEvent(event);  

/*	QPoint point = event->pos();
	QRect rect = this->rect();
	if (rect.contains(point))
	{
		m_isMoveWindow = true;
		m_movePosition = event->globalPos();
	}
	else
	{
		m_isMoveWindow = false;
	}
	return QDialog::mousePressEvent(event);*/
}

void BaseDialog::mouseReleaseEvent(QMouseEvent * event)
{
//BEGIN;
	m_isMoveWindow = false;
//END;
}

void BaseDialog::mouseMoveEvent(QMouseEvent *event)
{
//BEGIN;
	 //(event->buttons() && Qt::LeftButton)���������  
    //����ƶ��¼���Ҫ�ƶ����ڣ������ƶ��������أ�����Ҫ��ȡ����ƶ��У�������������Ļ�����꣬Ȼ��move��������꣬��ô��ȡ���ꣿ  
    //ͨ���¼�event->globalPos()֪��������꣬��������ȥ�������ڴ���λ�ã����Ǵ�����������Ļ������  
    if (m_isMoveWindow && (event->buttons() && Qt::LeftButton)  
        && (event->globalPos()-m_movePosition).manhattanLength() > QApplication::startDragDistance())   
    {    
       move(event->globalPos()-m_movePosition);  
        m_movePosition = event->globalPos() - pos(); 
    }  
    return QDialog::mouseMoveEvent(event);  
//END;
}
void BaseDialog::setSupportStretch(bool isSupportStretch){;
	this->setMinimumHeight(WINDOW_HEIGHT);
    this->setMinimumWidth(WINDOW_WIDTH);
	this->setMouseTracking(isSupportStretch);
}
bool BaseDialog::eventFilter(QObject *obj, QEvent *event)
{
	if ( event->type() == QEvent::WindowActivate)
	{
		this->repaint();
	}
	return QDialog::eventFilter(obj, event);
}
void BaseDialog::onMoveWindow(bool val){
	m_isMoveWindow = val;
}
}