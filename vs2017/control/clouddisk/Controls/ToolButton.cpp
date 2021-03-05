#include "ToolButton.h"
#include <QMouseEvent>
#include <QPainter>
namespace ui{
ToolButton::ToolButton(QString pic_name, QWidget *parent,bool hasText)
	:QToolButton(parent)
{
	//设置图标
	QPixmap pixmap(pic_name);
	setIcon(pixmap);
	setIconSize(pixmap.size());

	//设置大小
	setFixedSize(pixmap.width() + 25, pixmap.height() + 25);
	setAutoRaise(true);

	mouse_over = false;
	mouse_press = false;

	hasHoverColor = hasText;
	if(!hasText){
		return;
	}

	//设置文本颜色
	QPalette text_palette = palette();
	text_palette.setColor(QPalette::ButtonText,QColor(101,101,101));
	setPalette(text_palette);

	//设置文本粗体
	QFont &text_font = const_cast<QFont &>(font());
	text_font.setFamily("Microsoft YaHei");
	//text_font.setWeight(QFont::DemiBold);
	setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
}

ToolButton::~ToolButton()
{

}
void ToolButton::setSize(QSize size){
	this->setIconSize(QSize(25, 25));
	this->setFixedSize(size + QSize(25, 25));
}
void ToolButton::setTextColor(QColor color){
	QPalette text_palette = palette();
	text_palette.setColor(QPalette::ButtonText,color);
	setPalette(text_palette);
}
void ToolButton::enterEvent(QEvent *)
{
	mouse_over = true;
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

void ToolButton::setMousePress(bool mouse_press)
{
	this->mouse_press = mouse_press;
	update();
}

void ToolButton::paintEvent(QPaintEvent *event)
{
	if(mouse_over)
	{
		//绘制鼠标移到按钮上的按钮效果
		painterInfo(30, 100, 150);
	}
	else
	{
		if(mouse_press)
		{
			painterInfo(100, 100, 150);
		}
	}

	QToolButton::paintEvent(event);
}
void ToolButton::painterInfo(int top_color, int middle_color, int bottom_color)
{
	if(!hasHoverColor){
		return;
	}
	QPainter painter(this);
	QPen pen(Qt::NoBrush, 1);
	painter.setPen(pen);
	QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
	linear.setColorAt(0, QColor(189, 189, 189, top_color));
	linear.setColorAt(0.5, QColor(189, 189, 189, middle_color));
	linear.setColorAt(1, QColor(189, 189, 189, bottom_color));
	painter.setBrush(linear);
	painter.drawRect(rect());
}
}