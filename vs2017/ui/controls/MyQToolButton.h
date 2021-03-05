#pragma once
#include <QToolButton>
namespace ui{
class MyQToolButton : public QToolButton
{
	Q_OBJECT

public:
	explicit MyQToolButton(QWidget *parent = 0);
	~MyQToolButton();
protected:
	void mouseMoveEvent(QMouseEvent *event);
};
}


