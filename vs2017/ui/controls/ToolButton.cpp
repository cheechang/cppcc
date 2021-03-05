#include "ToolButton.h"
#include <QMouseEvent>
#include <QPainter>
namespace ui{
ToolButton::ToolButton(QString pic_name, QWidget *parent,bool hasText)
	:QToolButton(parent)
{
	//����ͼ��
	QPixmap pixmap(pic_name);
	setIcon(pixmap);
	setIconSize(pixmap.size());

	//���ô�С
	setFixedSize(pixmap.width(), pixmap.height());
	setAutoRaise(true);
	setObjectName("transparentToolButton");

	mouse_over = false;
	mouse_press = false;
	m_pic_name = pic_name;
	mHasText = hasText;
	if(!hasText){
		return;
	}
	//�����ı���ɫ
	QPalette text_palette = palette();
	text_palette.setColor(QPalette::ButtonText, QColor(255, 255, 255));
	setPalette(text_palette);

	//�����ı�����
	QFont &text_font = const_cast<QFont &>(font());
	text_font.setWeight(QFont::Normal);
	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

}

ToolButton::~ToolButton()
{

}
void ToolButton::setSize(QSize size){
	this->setIconSize(size);
	this->setFixedSize(size);
}
void ToolButton::enterEvent(QEvent *)
{
	mouse_over = true;
	emit mouseEnter();
}

void ToolButton::leaveEvent(QEvent *)
{
	mouse_over = false;
}

void ToolButton::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		emit clicked();
		event->accept();
	}
}
void ToolButton::mouseMoveEvent(QMouseEvent *event){
	event->accept();
}
void ToolButton::setMousePress(bool mouse_press)
{
	this->mouse_press = mouse_press;
	update();
}

void ToolButton::paintEvent(QPaintEvent *event)
{
	if(!mHasText){
		painterInfo(0, 0, 0);
		QToolButton::paintEvent(event);
		return;
	}
	if(mouse_over)
	{
		//��������Ƶ���ť�ϵİ�ťЧ��
		painterInfo(0, 100, 150);
	}
	else
	{
		if(mouse_press)
		{
			painterInfo(0, 100, 150);
		}
	}

	QToolButton::paintEvent(event);
}

void ToolButton::painterInfo(int top_color, int middle_color, int bottom_color)
{
	QPainter painter(this);
	if(!mHasText){
		QPixmap pixmap(m_pic_name);
		painter.drawPixmap(rect(),pixmap);
		return;
	}
	
	QPen pen(Qt::NoBrush, 1);
	painter.setPen(pen);
	QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
	linear.setColorAt(0, QColor(0, 103, 175, top_color));
	linear.setColorAt(0.5, QColor(0, 103, 175, middle_color));
	linear.setColorAt(1, QColor(0, 103, 175, bottom_color));
	painter.setBrush(linear);
	painter.drawRect(rect());
}
}