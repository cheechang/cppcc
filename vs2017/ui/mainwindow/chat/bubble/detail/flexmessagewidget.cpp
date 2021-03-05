#include "flexmessagewidget.h"
#include "../abstractmessagewidget.h"
#include "avatarround.h"
#include "../MsgBubbleConfig.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <qmath.h>
#include <QPainter>
#include <QStyleOption>
#include <QStackedWidget>
#include <QDateTime>

class FlexMessageWidgetPrivate
{
public:
	FlexMessageWidgetPrivate(): messageWidget(nullptr), burnLabel(CNull), secrtLock(nullptr)
	{
	}

	void init(bool);

	FlexMessageWidget* q_ptr;
	QLabel* nameLabel;
	AvatarRound* avatarWidget;
	AbstractMessageWidget* messageWidget;
	BurnLabel* burnLabel;
	QVBoxLayout* messageLayout;
	QLabel* secrtLock;
	QLabel* delayTime;
	QHBoxLayout* mainLayout;
	ChickFeatherLabel* ChickFeatherOrMsgStatusLbl;
};

void FlexMessageWidgetPrivate::init(bool alignLeft)
{
	nameLabel = new QLabel(q_ptr);
	nameLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	nameLabel->setText(QObject::tr("Default Name"));
	nameLabel->setFixedHeight(25); //20（2020年8月25日）
	nameLabel->setAlignment(alignLeft ? Qt::AlignLeft : Qt::AlignRight);

	avatarWidget = new AvatarRound(q_ptr);
	avatarWidget->setStyleSheet("border: 1px solid red;");
	avatarWidget->setFixedWidth(40); //40（2020年8月25日）
	avatarWidget->setFixedHeight(40);

	delayTime = new QLabel(q_ptr);
	delayTime->setObjectName("DelayMsg");
	delayTime->setVisible(false);
	delayTime->setFixedHeight(20); //20（2020年8月25日）

	mainLayout = new QHBoxLayout;
	mainLayout->setContentsMargins(10, 1, 10, 1);
	mainLayout->setSpacing(4);

	messageLayout = new QVBoxLayout;
	messageLayout->setSpacing(1);
	messageLayout->addWidget(nameLabel);
	messageLayout->setContentsMargins(0, 0, 0, 0);

	secrtLock = new QLabel(q_ptr);
	secrtLock->setFixedSize(0, 0);
	secrtLock->setPixmap(QPixmap(":/chat/privateChatBtn-hover"));

	ChickFeatherOrMsgStatusLbl = new ChickFeatherLabel(q_ptr);
	ChickFeatherOrMsgStatusLbl->setVisible(false);
	ChickFeatherOrMsgStatusLbl->setText(transfer("未读"));
	ChickFeatherOrMsgStatusLbl->setFixedWidth(0 * gDdpi);
	if (alignLeft)
	{
		mainLayout->addWidget(avatarWidget, 0, Qt::AlignTop);
		mainLayout->addLayout(messageLayout);
		mainLayout->addWidget(secrtLock, 0, Qt::AlignBottom);
	}
	else
	{
		mainLayout->setSpacing(0);
		mainLayout->addWidget(secrtLock, 0, Qt::AlignBottom);
		mainLayout->addWidget(ChickFeatherOrMsgStatusLbl, 0, Qt::AlignBottom);
		mainLayout->addLayout(messageLayout);
		mainLayout->addWidget(avatarWidget, 0, Qt::AlignTop);
	}
	q_ptr->setLayout(mainLayout);
	q_ptr->setStyleSheet("background-color:transparent;");

	q_ptr->connect(avatarWidget, SIGNAL(clicked()), q_ptr, SLOT(onAvatarClicked()));
}

FlexMessageWidget::FlexMessageWidget(bool alignLeft, QWidget* parent) :
	QWidget(parent)
{
	m_alignLeft = alignLeft;
	d_ptr = new FlexMessageWidgetPrivate;
	d_ptr->q_ptr = this;
	d_ptr->init(alignLeft);
	connect(d_ptr->ChickFeatherOrMsgStatusLbl, SIGNAL(clicked()), this, SLOT(onShowMsgStatus()));
}

void FlexMessageWidget::onShowMsgStatus()
{
	if (d_ptr->messageWidget)
	{
		d_ptr->messageWidget->onMessageStatus();
	}
}

FlexMessageWidget::~FlexMessageWidget()
{
	delete d_ptr;
}

void FlexMessageWidget::setName(const QString& name)
{
	if (!this->name().contains("-") || this->name() != name)
	{
		d_ptr->nameLabel->setText(name);
	}
}

QString FlexMessageWidget::name() const
{
	return d_ptr->nameLabel->text();
}

void FlexMessageWidget::setNameVisible(bool visible)
{
	d_ptr->nameLabel->setVisible(visible);
}

bool FlexMessageWidget::nameVisible() const
{
	return d_ptr->nameLabel->isVisible();
}

void FlexMessageWidget::setAvatar(const QPixmap& pixmap)
{
	d_ptr->avatarWidget->setAvatar(pixmap);
}

QPixmap FlexMessageWidget::avatar() const
{
	return d_ptr->avatarWidget->avatar();
}

void FlexMessageWidget::setMessageWidget(AbstractMessageWidget* message)
{
	if (message && message != d_ptr->messageWidget)
	{
		if (d_ptr->messageWidget)
		{
			d_ptr->messageLayout->removeWidget(d_ptr->messageWidget);
			d_ptr->messageWidget->deleteLater();
		}
		d_ptr->messageWidget = message;
		d_ptr->messageLayout->addWidget(d_ptr->messageWidget);

		if (d_ptr->messageWidget->msg() && (d_ptr->messageWidget->msg()->isDelay || d_ptr->messageWidget->msg()->msgType
			== data::MSG_TYPE_TASK))
		{
			setDelayMsgTime();
		}

		int msgtype = d_ptr->messageWidget->msgType();
		if (data::MSG_TYPE_TIP == msgtype || data::MSG_TYPE_PICTEXT == msgtype)
		{
			d_ptr->nameLabel->setVisible(false);
			d_ptr->avatarWidget->setVisible(false);
		}
		if (message->msg() && message->msg()->isBurn && !message->msg()->isRecvMsg)
		{
			d_ptr->burnLabel = new BurnLabel(this, message->msg()->localId);
			connect(d_ptr->burnLabel,SIGNAL(timeOut(int64)), this,SIGNAL(burnMsg(int64)));
			d_ptr->burnLabel->move(d_ptr->messageWidget->x() + 6, d_ptr->messageWidget->y() + 6);
		}
		if (message->msg() && message->msg()->isPrivateMsg == 2)
		{
			d_ptr->secrtLock->setFixedSize(30, 30);
		}
		if (message->msg() && message->msg()->body == SHAKE_TEXT)
		{
			d_ptr->secrtLock->setPixmap(QPixmap(":/chat/shake"));
			d_ptr->secrtLock->setFixedSize(30, 30);
		}

		if (message->msg() && message->msg()->isReceipt && message->msg()->msgType == data::MSG_TYPE_TEXT)
		{
			d_ptr->secrtLock->setPixmap(QPixmap(":/chat/receipt"));
			d_ptr->secrtLock->setFixedSize(20, 20);
		}
		if (message->msg() && message->msg()->isFeather && !message->msg()->isRecvMsg)
		{
			d_ptr->ChickFeatherOrMsgStatusLbl->setVisible(true);
		}
		//d_ptr->ChickFeatherOrMsgStatusLbl->move(d_ptr->messageWidget->x()+10,d_ptr->messageWidget->y());
	}
}

AbstractMessageWidget* FlexMessageWidget::messageWidget() const
{
	return d_ptr->messageWidget;
}

void FlexMessageWidget::suggestWidth(int width)
{
	if (d_ptr->messageWidget)
	{
		QSize flexWidgetSize;
		QSize msgWidgetSize = d_ptr->messageWidget->suggestWidth(width - 60); // minus avatar space
		int max = qMax<int>(MsgBubbleConfig::MinMessageHeight(), msgWidgetSize.height());
		int msgtype = d_ptr->messageWidget->msgType();
		if (data::MSG_TYPE_TIP == msgtype || data::MSG_TYPE_PICTEXT == msgtype)
		{
			flexWidgetSize = QSize(msgWidgetSize.width(), max);
		}
		else
		{
			int lockWidth = -10;
			/*if (d_ptr->secrtLock->width() >= 0)
			{
				lockWidth = d_ptr->secrtLock->width()-5;
			}
			flexWidgetSize= QSize(lockWidth+d_ptr->avatarWidget->width()+msgWidgetSize.width(),max+d_ptr->nameLabel->height());
			if (d_ptr->messageWidget->msg() && (d_ptr->messageWidget->msg()->isDelay||d_ptr->messageWidget->msg()->msgType == data::MSG_TYPE_TASK))
			{
				flexWidgetSize += QSize(0,d_ptr->delayTime->height()) ;
			}*/
			if (d_ptr->ChickFeatherOrMsgStatusLbl->width() >= 0)
			{
				lockWidth = d_ptr->ChickFeatherOrMsgStatusLbl->width() - 5 * gDdpi;
			}
			int secrtLockWidth = 0;
			if (d_ptr->messageWidget->isRecv() && d_ptr->secrtLock->isVisible() && d_ptr->secrtLock->width() > 0)
			{
				secrtLockWidth = 18 * gDdpi;
			}
			flexWidgetSize = QSize(secrtLockWidth + lockWidth + d_ptr->avatarWidget->width() + msgWidgetSize.width(),
			                       max + d_ptr->nameLabel->height());
			if (d_ptr->messageWidget->msg() && (d_ptr->messageWidget->msg()->isDelay || d_ptr->messageWidget->msg()->
				msgType == data::MSG_TYPE_TASK))
			{
				flexWidgetSize += QSize(0, d_ptr->delayTime->height());
			}
		}
		this->resize(flexWidgetSize);
	}
}

void FlexMessageWidget::setMsgStatusLblText(QString text)
{
	AbstractMessageWidget* message = messageWidget();

	if (message && message->msg() && (message->msg()->isFeather || message->msg()->msgType == data::MSG_TYPE_TIP || text
		.isEmpty()))
	{
		d_ptr->ChickFeatherOrMsgStatusLbl->setVisible(false);
		return;
	}
	setMsgStatusWidgetFixedWidth(text);
	d_ptr->ChickFeatherOrMsgStatusLbl->setText(text, false);
	if (!d_ptr->ChickFeatherOrMsgStatusLbl->isVisible())
	{
		d_ptr->ChickFeatherOrMsgStatusLbl->setVisible(true);
	}
	emit sizechanged();
}

void FlexMessageWidget::setMsgStatusWidgetFixedWidth(QString text)
{
	int w = d_ptr->ChickFeatherOrMsgStatusLbl->fontMetrics().width(text);
	d_ptr->ChickFeatherOrMsgStatusLbl->setFixedWidth(w);
}

void FlexMessageWidget::onAvatarClicked()
{
	if (d_ptr->messageWidget && m_alignLeft)
	{
		emit showUserInfoWidget(d_ptr->messageWidget->sendId(), d_ptr->messageWidget->name(),
		                        d_ptr->messageWidget->avatar());
	}
}

void FlexMessageWidget::startBurnTimer(int time)
{
	if (d_ptr->burnLabel)
	{
		d_ptr->burnLabel->start(time);
		d_ptr->ChickFeatherOrMsgStatusLbl->hide();
	}
}

bool FlexMessageWidget::isBurning()
{
	if (d_ptr && d_ptr->burnLabel && d_ptr->burnLabel->isVisible())
	{
		return true;
	}
	return false;
}

void FlexMessageWidget::addMessageWidget(AbstractMessageWidget* message)
{
	if (message && message != d_ptr->messageWidget)
	{
		if (d_ptr->messageWidget)
		{
			d_ptr->messageLayout->removeWidget(d_ptr->messageWidget);
			d_ptr->messageWidget->deleteLater();
		}
		d_ptr->messageWidget = message;
		d_ptr->messageLayout->addWidget(d_ptr->messageWidget);
		connect(message,SIGNAL(sizechanged()), this,SIGNAL(sizechanged()));
		message->update();
		int msgtype = d_ptr->messageWidget->msgType();
		if (data::MSG_TYPE_TIP == msgtype || data::MSG_TYPE_PICTEXT == msgtype)
		{
			d_ptr->nameLabel->setVisible(false);
			d_ptr->avatarWidget->setVisible(false);
		}
		if (message->msg() && message->msg()->isBurn && !message->msg()->isRecvMsg)
		{
			d_ptr->burnLabel = new BurnLabel(this, message->msg()->localId);
			connect(d_ptr->burnLabel,SIGNAL(timeOut(int64)), this,SIGNAL(burnMsg(int64)));
			d_ptr->burnLabel->move(d_ptr->messageWidget->x() + 6, d_ptr->messageWidget->y() + 6);
		}
		d_ptr->secrtLock->setFixedSize(30, 30);
		this->update();
	}
}

void FlexMessageWidget::setDelayTime(QString time)
{
	d_ptr->delayTime->setText(time);
}

QString FlexMessageWidget::getDelayTime()
{
	return d_ptr->delayTime->text();
}

void FlexMessageWidget::setDelayMsgTime()
{
	QString icon = ":/chat/delayMsgTip";
	QString text;
	if (d_ptr->messageWidget->msg()->msgType == data::MSG_TYPE_TASK)
	{
		icon = ":/chat/task";
		CSharedPtr<data::Msg> msg = d_ptr->messageWidget->msg();
		data::MsgTask* delayMsg = static_cast<data::MsgTask*>(msg.get());
		QString taskTime = QString::fromUtf8(delayMsg->timeTask.c_str());
		QString resultDate;
		if (taskTime.length() >= 14)
		{
			QString nearStr = taskTime.left(4);
			QString monStr = taskTime.mid(4, 2);
			QString dayStr = taskTime.mid(6, 2);
			QString hourStr = taskTime.mid(8, 2);
			QString minStr = taskTime.mid(10, 2);
			resultDate = nearStr + "-" + monStr + "-" + dayStr + " " + hourStr + ":" + minStr;
		}
		text = transfer("任务消息:") + resultDate;
	}
	else
	{
		CSharedPtr<data::Msg> msg = d_ptr->messageWidget->msg();
		data::MsgText* delayMsg = static_cast<data::MsgText*>(msg.get());

		QDateTime time = QDateTime::fromMSecsSinceEpoch(delayMsg->delayTime);
		QString format = time.toString("MM-dd hh:mm");
		text = transfer("延时消息:") + format;
	}
	/*QPixmap pix = QPixmap(icon);
	pix.scaled(d_ptr->secrtLock->size(),Qt::KeepAspectRatio);
	d_ptr->secrtLock->setScaledContents(true);
	d_ptr->secrtLock->setPixmap(pix);
	d_ptr->secrtLock->setFixedSize(18,18);*/
	d_ptr->delayTime->setVisible(true);


	d_ptr->delayTime->setText(text);
	if (d_ptr->messageWidget->isRecv())
	{
		d_ptr->messageLayout->addWidget(d_ptr->delayTime, 0, Qt::AlignRight);
	}
	else
	{
		d_ptr->messageLayout->addWidget(d_ptr->delayTime, 0, Qt::AlignLeft);
	}
}

void FlexMessageWidget::SetChickFeather()
{
	d_ptr->ChickFeatherOrMsgStatusLbl->setText(transfer("已读"));
}

void FlexMessageWidget::SetChickSendedMsg()
{
	d_ptr->ChickFeatherOrMsgStatusLbl->setText(transfer("已发送短信"));
};

BurnLabel::BurnLabel(QWidget* parent, int64 localId): QLabel(parent)
{
	this->setFont(QFont("", 8));
	setFixedSize(QSize(20, 20));
	QPalette color;
	color.setColor(QPalette::Text, Qt::white);
	this->setPalette(color);
	this->setAlignment(Qt::AlignCenter);
	this->setObjectName("whiteLabel");
	mLocalId = localId;
	mCount = 0;
	hide();
	connect(&mTimer,SIGNAL(timeout()), this,SLOT(onTimerOut()));
}

BurnLabel::~BurnLabel()
{
}

void BurnLabel::paintEvent(QPaintEvent* e)
{
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing, true);

	painter.setBrush(QColor("#133453"));

	QRect rectangle(0, 0, 20, 20);

	QPainterPath path;
	path.addEllipse(rectangle);
	painter.setClipPath(path);

	painter.drawEllipse(rectangle);
	QPoint pos = rectangle.center();
	if (mCount > 9)
	{
		pos.setX(pos.x() - 4);
	}
	else
	{
		pos.setX(pos.x() - 2);
	}
	pos.setY(pos.y() + 4);
	painter.drawText(pos, QString::number(mCount));
	QLabel::paintEvent(e);
}

void BurnLabel::start(int time)
{
	mTimer.setInterval(1000);
	mCount = time;
	this->setText(QString::number(mCount));
	show();
	mTimer.start();
}

void BurnLabel::onTimerOut()
{
	mCount--;
	if (mCount == 0)
	{
		mTimer.stop();
		emit timeOut(mLocalId);
	}
	else
	{
		this->setText(QString::number(mCount));
	}
}
