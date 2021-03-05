#include "LoadingDataWidget.h"
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include "../common/Common.h"
namespace ui{
	LoadingDataWidget::LoadingDataWidget(QWidget *parent)
		: QWidget(parent)
	{
		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		mTipText = new QLabel(this);
		mTipText->setObjectName("white15Label");
		mainLayout->addWidget(mTipText,0,Qt::AlignCenter);
		mainLayout->setContentsMargins(0,0,0,0);
		setLayout(mainLayout);

		setTipText(transfer("正在发送数据，请稍等..."));
	}

	LoadingDataWidget::~LoadingDataWidget()
	{

	}
	void LoadingDataWidget::paintEvent(QPaintEvent* event)
	{
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

		this->setAttribute(Qt::WA_TranslucentBackground, true);
		p.setBrush(QColor(0, 0, 0, 120));
		p.drawRect(0,0, this->width(), this->height());
	}

	void LoadingDataWidget::setTipText( QString text )
	{
		mTipText->setText(text);
	}

}
