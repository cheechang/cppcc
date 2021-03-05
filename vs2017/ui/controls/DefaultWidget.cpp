#include "DefaultWidget.h"
#include "common/common.h"
#include <QLabel>
#include <QHBoxLayout>

namespace ui{
	DefaultWidget::DefaultWidget(QWidget *parent) :ui::TWidget(parent){
		//this->setMouseTracking(true);
		setObjectName("bg_fa");
		QLabel*lbl = new QLabel(this);
		lbl->setPixmap(QPixmap(":/base/default"));
		QHBoxLayout*layout = new QHBoxLayout(this);
		layout->addWidget(lbl,0,Qt::AlignCenter);
		this->setLayout(layout);

	}
	DefaultWidget::~DefaultWidget(){

	}
	/*
	void DefaultWidget::paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);
		painter.setPen(Qt::white);
		painter.setBrush(Qt::white);
		QPixmap pixmap(QString(":/base/default"));
		int x=SHADOW_WIDTH+(this->width()-pixmap.width())/2;
		int y=SHADOW_WIDTH+(this->height()-pixmap.height())/2;
		painter.drawPixmap(QRect(x, y, pixmap.width()-2*SHADOW_WIDTH, pixmap.height()-2*SHADOW_WIDTH), pixmap);
	}*/
}