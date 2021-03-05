#pragma once
#include <QWidget>
#include "controls/TWidget.h"
class QPainter;
namespace ui{
	class DefaultWidget : public ui::TWidget
{
	Q_OBJECT
public:
	explicit DefaultWidget(QWidget *parent = 0);
	~DefaultWidget();
protected:
	//void paintEvent(QPaintEvent *event);
};
}


