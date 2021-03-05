#include "TrayUnreadMsgTipWin.h"
#include <QDesktopWidget>
#include <QApplication>
#include "../controls/MyQPushButton.h"
#include "../controls/TWidget.h"
#include "../controls/UnreadMsgLabel.h"
#include "../controls/headimage.h"
#include "../controls/ElidedLabel.h"
#include "common/Connect.h"
#include "common/Controlptr.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include "../../common/Common.h"
namespace ui{
	bool TrayUnreadMsgTipWin::isRrayFlash = false;
	TrayUnreadMsgTipWin* TrayUnreadMsgTipWin::mPInstance = CNull;
	TrayUnreadMsgTipWin::TrayUnreadMsgTipWin(QWidget *parent)
		: BaseDialog(parent)
	{
		Qt::WindowFlags flags = this->windowFlags();
		flags |= Qt::WindowStaysOnTopHint;
		flags |= Qt::Tool;
		this->setWindowFlags(flags);

        mBtnIgnoreAll = new MyQPushButton(this);
		connect(mBtnIgnoreAll,SIGNAL(clicked(bool)),this,SLOT(onIgnoreAllMsg()));
		mBtnIgnoreAll->setText(transfer("忽略全部"));
		mBtnIgnoreAll->setMinimumHeight(30);
		mBtnIgnoreAll->setObjectName("BtnIgnoreMsg");
		mBtnIgnoreAll->setCursor(Qt::PointingHandCursor);
		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->addWidget(mBtnIgnoreAll);
		layout->addStretch();
		layout->setContentsMargins(0,0,0,0);
		QWidget* widget = new QWidget(this);
		widget->setLayout(layout);
		widget->setFixedSize(240,30);

		QVBoxLayout* bgLayout = new QVBoxLayout(this);
		bgLayout->setContentsMargins(10,0,10,0);
		bgLayout->setSpacing(0);
		mMsgListWidget = new QListWidget(this);
		mMsgListWidget->setFixedWidth(240);
		connect(mMsgListWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onItemClicked(QListWidgetItem*)));

		mTitle = new QLabel(this);
		mTitle->setText(transfer("新消息"));
		mTitle->setMinimumHeight(30);
		mTitle->setMinimumWidth(240);

		bgLayout->addWidget(mTitle);
        bgLayout->addWidget(mMsgListWidget);
		bgLayout->addWidget(widget);
		bgLayout->addStretch();
		QWidget* bgWidget = new QWidget(this);
		bgWidget->setObjectName("BgF5");
		bgWidget->setStyleSheet("QWidget#BgF5{background:#f5f5f5;}");
		bgWidget->setLayout(bgLayout);

		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		mainLayout->setContentsMargins(0,0,0,0);
		mainLayout->addWidget(bgWidget);
		this->setLayout(mainLayout);
		setFixedSize(250,1);
		hide();

	}

	TrayUnreadMsgTipWin::~TrayUnreadMsgTipWin()
	{

	}

	TrayUnreadMsgTipWin* TrayUnreadMsgTipWin::Instance()
	{
		if (CNull == mPInstance)
		{
			mPInstance = new TrayUnreadMsgTipWin();
		}
		return mPInstance;
	}

	void TrayUnreadMsgTipWin::showWin(int x)
	{
		if (mPInstance)
		{
			QRect screenrect = QApplication::desktop()->availableGeometry();
			int y = screenrect.height() -mPInstance->height();
			mPInstance->move(x,y);
			mPInstance->update();
			mPInstance->show();
			mPInstance->activateWindow();
		}
	}

	void TrayUnreadMsgTipWin::hideWin()
	{
		if (mPInstance)
		{
			mPInstance->hide();
		}
	}

	void TrayUnreadMsgTipWin::mouseMoveEvent( QMouseEvent *event )
	{

	}

	void TrayUnreadMsgTipWin::paintEvent( QPaintEvent *event )
	{
		//setWinSize();
	}

	void TrayUnreadMsgTipWin::onNoticeTrayMsgTip( CSharedPtr<data::ChatInfo>&chat )
	{
		int64 targetId = chat->targetid;
		if (mMsgDatas.contains(targetId))
		{
			removeItem(targetId);
		}

		QListWidgetItem* item = new QListWidgetItem();
		item->setSizeHint(QSize(0,ItemHeight));
		TrayUnreadMsgTipWidgetItem* widget = new TrayUnreadMsgTipWidgetItem(this);
		connect(widget,SIGNAL(ignoreMsg(int64)),this,SLOT(onBtnIgnoreMsg(int64)));
		widget->setData(QString::fromUtf8(chat->avatar.c_str()),QString::fromUtf8(chat->name.c_str()),QString::number(chat->unreadcount),chat->targetid);
		mMsgListWidget->insertItem(0,item);
		mMsgListWidget->setItemWidget(item,widget);
		mMsgDatas.insert(targetId,chat);

		updateTitleText();

	}

	void TrayUnreadMsgTipWin::onNoticeTrayMsgUpdateReaded( int64 targetId )
	{
		if (mMsgDatas.contains(targetId))
		{
			removeItem(targetId);
			updateTitleText();
		}
	}

	void TrayUnreadMsgTipWin::removeItem( int64 targetId )
	{
		for (int i=0;i<mMsgListWidget->count();++i)
		{
			QListWidgetItem* item =  mMsgListWidget->item(i);
			TrayUnreadMsgTipWidgetItem* widget = (TrayUnreadMsgTipWidgetItem*)mMsgListWidget->itemWidget(item);
			if (widget && widget->id() == targetId)
			{
				mMsgListWidget->takeItem(i);
				delete item;
				mMsgDatas.remove(targetId);
				return;
			}
		}
	}

	void TrayUnreadMsgTipWin::onItemClicked( QListWidgetItem*item )
	{
		TrayUnreadMsgTipWidgetItem* widget = (TrayUnreadMsgTipWidgetItem*)mMsgListWidget->itemWidget(item);
		if (widget)
		{
			int64 targetId = widget->id();
			emit trayMsgClicked(targetId);
		}
		RemoveAllItems();
		emit showMainWin();
		this->hide();
	}

	void TrayUnreadMsgTipWin::onIgnoreAllMsg()
	{
		IChatMgrControl_Ptr chatControl = CHATMGRCONTROL;
		if (chatControl != CNull)
		{
			QList<CSharedPtr<data::ChatInfo>> chats = mMsgDatas.values();
			for (int i=0;i<chats.size();++i)
			{
				CSharedPtr<data::ChatInfo> chat = chats.at(i);
				chatControl->setMessageRead(chat->targetid,chat->msgid);
			}
			RemoveAllItems();
		}
		emit signalNotifyTrayFlash(false);
		this->hideWin();
	}

	void TrayUnreadMsgTipWin::RemoveAllItems()
	{
		QList<int64> keys = mMsgDatas.keys();
		for (int i=0;i<keys.size();++i)
		{
			removeItem(keys.at(i));
		}
	}

	void TrayUnreadMsgTipWin::updateTitleText()
	{
		QList<CSharedPtr<data::ChatInfo>> chats= mMsgDatas.values();
		int allUnreadMsgsCount = 0;
		for (int i=0;i<chats.size();++i)
		{
			allUnreadMsgsCount +=chats.at(i)->unreadcount;
		}
		mTitle->setText(transfer("新消息(")+QString::number(allUnreadMsgsCount)+transfer(")"));
	}

	void TrayUnreadMsgTipWin::onBtnIgnoreMsg( int64 targetId )
	{
		IChatMgrControl_Ptr chatControl = CHATMGRCONTROL;
		if (chatControl != CNull)
		{
			CSharedPtr<data::ChatInfo> chat = mMsgDatas.value(targetId);
			chatControl->setMessageRead(chat->targetid,chat->msgid);
			removeItem(targetId);
			if (mMsgDatas.size() == 0)
			{
				emit signalNotifyTrayFlash(false);
			}
			this->hideWin();
		}
	}

	void TrayUnreadMsgTipWin::setWinSize()
	{
		if (mMsgListWidget != CNull)
		{
			int maxHeight = 6 * ItemHeight;
			if (mMsgDatas.size()<6)
			{
				mMsgListWidget->setFixedHeight(mMsgDatas.size() * ItemHeight);
			}else{
				mMsgListWidget->setFixedHeight(maxHeight);
			}
			if (mMsgDatas.size()>0 && isRrayFlash)
			{
				int64 h = 70;
				this->setFixedSize(250,mMsgListWidget->height()+h);
				setVisible(true);

			}else{
				this->setFixedSize(0,0);
				setVisible(false);

			}
		}
	}

	void TrayUnreadMsgTipWidgetItem::setData( QString head,QString name,QString unreadMsgCount,int64 targetId )
	{
		mAvatar->setAvatarPath(head);
		mName->setText(name);
		mMsgCount->setText(unreadMsgCount);
		mTargetId = targetId;
	}

	TrayUnreadMsgTipWidgetItem::TrayUnreadMsgTipWidgetItem( QWidget*parent /*= 0*/ ):TWidget(parent)
	{
		mAvatar = new HeadImage(this,QSize(24,24));
		mTargetId = 0;
		mMsgCount = new UnreadMsgLabel(this);
		mName = new ElidedLabel(this);
		mBtnIgnore = new MyQPushButton(this);
		mBtnIgnore->setText(transfer("忽略"));
		mBtnIgnore->setMinimumWidth(20);
		mBtnIgnore->hide();
		mBtnIgnore->setObjectName("BtnIgnoreMsg");
		mBtnIgnore->setCursor(Qt::PointingHandCursor);
		connect(mBtnIgnore,SIGNAL(clicked(bool)),this,SLOT(onBtnIgnoreMsg()));

		QGridLayout* layout = new QGridLayout(this);
		layout->addWidget(mAvatar,0,0,1,1);
		layout->addWidget(mName,0,1,1,1);
		layout->addWidget(mMsgCount,0,2,1,1,Qt::AlignRight);
		layout->addWidget(mBtnIgnore,0,2,1,1,Qt::AlignRight);
		layout->setContentsMargins(2,0,12,0);
		this->setLayout(layout);
	}

	void TrayUnreadMsgTipWidgetItem::enterEvent( QEvent *e )
	{
		mBtnIgnore->setVisible(true);
		mMsgCount->setVisible(false);
		//TWidget::enterEvent(e);
	}

	void TrayUnreadMsgTipWidgetItem::leaveEvent( QEvent *e )
	{
		mBtnIgnore->setVisible(false);
		mMsgCount->setVisible(true);
		//TWidget::leaveEvent(e);
	}

	void TrayUnreadMsgTipWidgetItem::onBtnIgnoreMsg()
	{
		emit ignoreMsg(mTargetId);
	}

}