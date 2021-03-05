#include "BurnMessageWidget.h"
#include <QHBoxLayout>
BurnMessageWidget::BurnMessageWidget(QWidget *parent)
	: AbstractMessageWidget(parent)
{
	mLblMve = new QLabel(this);
	mBtnBurn = new QPushButton(this);
	mMovie = new QMovie(this);

	mMovie->setFileName(":/chat/burnMsg");
	mLblMve->setMovie(mMovie);
	mMovie->start();
	mBtnBurn->setText(transfer("µã»÷²é¿´"));
	mBtnBurn->setCursor(Qt::PointingHandCursor);
	mBtnBurn->setObjectName("ViewBurnBtn");
	connect(mBtnBurn,SIGNAL(clicked(bool)),this,SLOT(onViewBurnMsg()));

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(mLblMve);
	layout->addWidget(mBtnBurn);
	QWidget* widget = new QWidget(this);
	widget->setLayout(layout);
	setCentralWidget(widget);
	this->setFixedSize(160,60);
}

BurnMessageWidget::~BurnMessageWidget()
{

}

void BurnMessageWidget::setBurnMsg( CSharedPtr<data::Msg>&msg )
{
	if (msg)
	{
		AbstractMessageWidget::setMsg(msg);
		mRightMenu.setMenuState(MENU_TRANSPORT,false);
	}
}

QSize BurnMessageWidget::suggestWidth( int width )
{
	return this->sizeHint();
}

void BurnMessageWidget::onViewBurnMsg()
{
	emit viewBurnMsg(msg());
	emit deleteMsg(uiLocalId());
}
