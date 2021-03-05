#include "CombineMessageWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include "../CombineMsgWin.h"

CombineMessageWidget::CombineMessageWidget(QWidget* parent)
	: AbstractMessageWidget(parent)
{
	d_ptr = new CombineMessageWidgetPrivate(this, m_chatcontrol);
	connect(d_ptr,SIGNAL(clicked()), this,SLOT(onShowMsgWin()));
}

CombineMessageWidget::~CombineMessageWidget()
{
}

void CombineMessageWidget::setCombineMsg(CSharedPtr<data::Msg>& msg)
{
	setMsg(msg);
	if (msg->msgType == data::MSG_TYPE_COMBINE)
	{
		d_ptr->setData(static_cast<data::MsgCombine*>(msg.get())->mVt_msg);
		this->setCentralWidget(d_ptr);
	}
}

QSize CombineMessageWidget::suggestWidth(int width)
{
	Q_UNUSED(width);
	QSize size = d_ptr->size();
	return size;
}

CombineMessageWidgetPrivate::CombineMessageWidgetPrivate(QWidget* parent, IChatMgrControl_Ptr chatCtrl): TWidget(parent)
{
	mListwidget = new QListWidget(this);
	mChatCtrl = chatCtrl;

	this->setObjectName("Bg");
	this->setStyleSheet("QWidget#Bg{background:#f7f6fc;border-radius:6px;}");
	mListwidget->setEnabled(false);
	QVBoxLayout* hLayout = new QVBoxLayout(this);
	hLayout->setContentsMargins(0, 6, 4, 6);//内容边界
	hLayout->setSpacing(2); //控件之间的上下间距
	mBtnViewInfo = new ClickLabel(this);
	mBtnViewInfo->setText(transfer("消息记录详情>"));
	mBtnViewInfo->setTextColor(QColor(35, 155, 219));
	mBtnViewInfo->setUnderlined(true);
	connect(mBtnViewInfo,SIGNAL(clicked()), this,SIGNAL(clicked()));

	mBtnViewInfo->setFixedHeight(40);//40（2020年8月26日）
	hLayout->addWidget(mListwidget);
	hLayout->addWidget(mBtnViewInfo, 0, Qt::AlignRight | Qt::AlignBottom);
	this->setLayout(hLayout);

	CONNECT_SERVICE(GetUserInfor(int, data::UserData&));
}

void CombineMessageWidgetPrivate::setData(std::vector<CSharedPtr<data::Msg>> data)
{
	for (int i = 0; i < data.size(); ++i)
	{
		CSharedPtr<data::Msg> msg = data.at(i);
		CombineMessageItem* widget = new CombineMessageItem(this);
		widget->mFromId = msg->fromId;
		QString context = QString::fromUtf8(msg->context.c_str());
		context = context.replace(SHAKE_TEXT,transfer("[抖一抖]"));
		widget->mLblContext->setText(transfer(":") + context);
		widget->mLblName->setText(QString::number(msg->fromId));
		QListWidgetItem* item = new QListWidgetItem();
		mListwidget->insertItem(0, item);
		mListwidget->setItemWidget(item, widget);
		item->setSizeHint(QSize(200, 24));
		mNeedGetItems.push_back(msg->fromId);
	}
	mListwidget->setFixedSize(200, data.size() * 24);
	mListwidget->setSpacing(0);
	mListwidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	if (mNeedGetItems.size() > 0)
	{
		int64 userId = mNeedGetItems.takeFirst();
		mChatCtrl->getUserInfo(userId, 0,CBind(&CombineMessageWidgetPrivate::signalSerGetUserInfor, this,
		                                       CPlaceholders _1,CPlaceholders _2));
	}
}

QSize CombineMessageWidgetPrivate::size()
{
	QSize sz(240, mListwidget->height() + mBtnViewInfo->height() + 10);
	return sz;
}

void CombineMessageWidgetPrivate::onSerGetUserInfor(int code, data::UserData& data)
{
	qDebug() << Q_FUNC_INFO << data.id.value() << ",====================:" << QString::fromUtf8(
		data.name.value().c_str()).toStdString().c_str();
	mMapUser.insert(data.id.value(), data);
	for (int i = 0; i < mListwidget->count(); ++i)
	{
		QListWidgetItem* item = mListwidget->item(i);
		CombineMessageItem* widget = static_cast<CombineMessageItem*>(mListwidget->itemWidget(item));
		if (widget && widget->mFromId == data.id.value())
		{
			widget->mLblName->setText(QString::fromUtf8(data.name.value().c_str()));
		}
	}
	if (mNeedGetItems.size() > 0)
	{
		int64 userId = mNeedGetItems.takeFirst();
		mChatCtrl->getUserInfo(userId, 0,CBind(&CombineMessageWidgetPrivate::signalSerGetUserInfor, this,
		                                       CPlaceholders _1,CPlaceholders _2));
	}
}

QMap<int64, data::UserData> CombineMessageWidgetPrivate::users()
{
	return mMapUser;
}

void CombineMessageWidget::onShowMsgWin()
{
	ui::CombineMsgWin win;
	win.setTitle(transfer("消息记录详情列表"));
	CSharedPtr<data::Msg> cur = msg();
	data::MsgCombine* msgCb = static_cast<data::MsgCombine*>(cur.get());
	for (int i = 0; i < msgCb->mVt_msg.size(); ++i)
	{
		win.addMsg(msgCb->mVt_msg.at(i));
	}
	win.updateUserInfo(d_ptr->users());
	win.exec();
}

CombineMessageItem::CombineMessageItem(QWidget* parent): QWidget(parent)
{
	mLblName = new ElidedLabel(this);
	mLblContext = new ElidedLabel(this);
	mLblContext->setFixedWidth(110);
	mLblName->setFixedWidth(60);
	QFont font;
	font.setBold(true);
	mLblName->setFont(font);
	mLblName->setStyleSheet("background-color:#f7f6fc;");
	mLblContext->setStyleSheet("background-color:#f7f6fc;");

	QWidget* widget = new QWidget(this);
	QHBoxLayout* hLayout = new QHBoxLayout(this);
	hLayout->setContentsMargins(6, 0, 0, 0);
	hLayout->setSpacing(0);
	hLayout->addWidget(mLblName);
	hLayout->addWidget(mLblContext, 0, Qt::AlignLeft);
	this->setLayout(hLayout);
	this->setFixedSize(166, 24);
}
