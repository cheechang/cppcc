#pragma once
#include <QPushButton>
namespace ui{
class MyQPushButton : public QPushButton
{
	Q_OBJECT

public:
	explicit MyQPushButton(QWidget *parent = 0);
	~MyQPushButton();
protected:
	void mouseMoveEvent(QMouseEvent *event);
};
}


