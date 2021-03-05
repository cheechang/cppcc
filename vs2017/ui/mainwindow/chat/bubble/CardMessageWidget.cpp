#include "CardMessageWidget.h"
#include "../../controls/ElidedLabel.h"
#include <QGridLayout>
CardMessageWidget::CardMessageWidget(QWidget *parent)
: AbstractMessageWidget(parent), m_isBurn(false)
{
	mName = new ElidedLabel(this);
	mHead = new ui::HeadImage(this,QSize(45,45));
	mHead->setMouseInStyle(true);
	connect(mHead,SIGNAL(clicked(QPoint)),this,SLOT(onHeadClicked()));
	QGridLayout* mainLayout = new QGridLayout(this);
	QLabel* lbl = new QLabel(this);
	lbl->setText(transfer("¸öÈËÃûÆ¬"));

	QLabel*lblLine = new QLabel(this);
	lblLine->setStyleSheet("QLabel{background:gray;}");
	lblLine->setFixedSize(185,1);

	mainLayout->addWidget(lbl,0,0,1,1);
	mainLayout->addWidget(lblLine,1,0,1,2);
	mainLayout->addWidget(mHead,2,0,1,1);
	mainLayout->addWidget(mName,2,1,1,1);
	QWidget* widget = new QWidget(this);
	widget->setStyleSheet("QWidget{background:white;}");
	widget->setLayout(mainLayout);
	this->setCentralWidget(widget);
	this->setFixedSize(220,100);
	CONNECT_SERVICE(GetUserInfo(int, data::UserData&));
}

CardMessageWidget::~CardMessageWidget()
{

}

void CardMessageWidget::setIsBurnCard(bool isBurn)
{
	m_isBurn = isBurn;
}

QSize CardMessageWidget::suggestWidth( int width )
{
	return this->sizeHint();
}

void CardMessageWidget::setCardMsg( CSharedPtr<data::Msg>&msg )
{
	data::MsgCard* cardMsg = (data::MsgCard*)(msg.get());
	if (cardMsg != CNull)
	{
		AbstractMessageWidget::setMsg(msg);
		QString id = cardMsg->mediaUrl.c_str();
		mUserId = id.toLongLong();
		if (m_chatcontrol)
		{
			m_chatcontrol->getUserInfo(mUserId,0,CBind(&CardMessageWidget::signalSerGetUserInfo,this,CPlaceholders _1,CPlaceholders _2));
		}
	}
	AbstractMessageWidget::setMsg(msg);
}

void CardMessageWidget::onSerGetUserInfo( int code, data::UserData&user )
{
	if (code == 0&& user.id.value() == mUserId)
	{
		mName->setText(QString::fromUtf8(user.name.value().c_str()));
		mHead->setAvatarPath(transfer(user.thumbAvatar.value().c_str()));
	}
}

void CardMessageWidget::onHeadClicked()
{
	if (m_isBurn){
		emit signalSerShowUserInfo(mUserId, mName->text(), mHead->AvatarPath());
	}
	else{
		emit showUserInfoWidget(mUserId, mName->text(), mHead->AvatarPath());
	}
}
