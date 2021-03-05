#pragma once
#include <QToolButton>
class QPaintEvent;
namespace ui{
class ToolButton : public QToolButton
{
	Q_OBJECT
public:

	explicit ToolButton(QString pic_name, QWidget *parent = 0,bool hasText=true);
	~ToolButton();
	void setMousePress(bool mouse_press);
	void setSize(QSize size);
signals:
	void mouseEnter();
protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void painterInfo(int top_color, int middle_color, int bottom_color);
public:
	QString m_pic_name;
	bool mouse_over; //鼠标是否移过
	bool mouse_press; //鼠标是否按下
	bool mHasText;
};
}
