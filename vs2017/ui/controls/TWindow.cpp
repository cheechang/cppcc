#include "TWindow.h"
#include "common/Common.h"
namespace ui{
	TWindow::TWindow(QWidget *parent)
		: QWidget(parent)
	{
		setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
		setAttribute(Qt::WA_TranslucentBackground);
		setWindowTitle(QString(APP_NAME));
	}

	TWindow::~TWindow()
	{

	}
	void TWindow::paintEvent(QPaintEvent *)
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
}