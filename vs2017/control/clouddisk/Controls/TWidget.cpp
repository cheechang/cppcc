#include "TWidget.h"
#include <QPainter>
#include <QStyleOption>
#include <qmath.h>
#include <qfile.h>
namespace ui{
	TWidget::TWidget(QWidget *parent)
		: QWidget(parent)
	{
		this->resize(620, 600);
	}

	TWidget::~TWidget()
	{

	}

	void TWidget::paintEvent( QPaintEvent *event )
	{
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

		p.setRenderHint(QPainter::Antialiasing);  // ·´¾â³Ý;
		p.setBrush(QBrush(Qt::white));
		p.setPen(Qt::gray);  //±ß¿òÉ«
		p.drawRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);

		QWidget::paintEvent(event);

	}

}
