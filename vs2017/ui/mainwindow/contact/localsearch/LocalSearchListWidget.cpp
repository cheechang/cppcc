#include "LocalSearchListWidget.h"
#include "LocalSearchListItemWidget.h"
#include <QPainter>
#include <qmath.h>
#include <memory>
#include <QLabel>
#include <QGraphicsDropShadowEffect>

#include <QCoreApplication>
#include "common/Connect.h"
#include "common/Common.h"
#include "controls/UserInfoWindow.h"
namespace ui{
	LocalSearchListWidget::LocalSearchListWidget(QWidget *parent,bool isShadowEffect,bool isDbSendMsg)
		: QWidget(parent)
	{
		this->installEventFilter(this);
		
		mListWidget = new QListWidget(this);
		mClickAvatarShowInfo = isDbSendMsg;
		if (isDbSendMsg)
		{
			//connect(mListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onItemClicked(QListWidgetItem*)));
			connect(mListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(onItemDoubleClicked(QListWidgetItem *)));
		}
		else
		{
			connect(mListWidget,SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(onItemDoubleClicked(QListWidgetItem *)));
		}
		
		
		///// m_tipLbl = new QLabel();

		m_noninfo = new QWidget();
		m_noninfo->setObjectName("bg_fa_n");
		m_tipLbl = new  QLabel(m_noninfo);
		m_tipLbl->setText(transfer("无搜索结果..."));
		m_tipLbl->setAlignment(Qt::AlignCenter | Qt::AlignTop);
		m_mainStactkedWidget = new QStackedWidget(this);

		////m_mainStactkedWidget->addWidget(m_tipLbl);
		m_mainStactkedWidget->addWidget(m_noninfo);
		m_noninfo->setContentsMargins(0, 0, 0, 0); ///<===2019=6

		m_mainStactkedWidget->addWidget(mListWidget);
		m_mainStactkedWidget->setCurrentWidget(mListWidget);

		mMainLayout = new QVBoxLayout();
		mMainLayout->setContentsMargins(0, 0, 2, 2);
		mMainLayout->addWidget(m_mainStactkedWidget);

		setLayout(mMainLayout);

		mListWidget->setSelectionMode(QAbstractItemView::NoSelection);

		if (isShadowEffect)
		{
			QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
			shadow_effect->setOffset(2, 2);
			shadow_effect->setColor(Qt::gray);
			shadow_effect->setBlurRadius(4);
			this->setGraphicsEffect(shadow_effect);
			mListWidget->setStyleSheet("QListWidget{border-right:1px solid gray;}");
		}

		mContactControl = CONTACTMGRCONTROL;
		if(mContactControl){
			CONNECT_SERVICE(SearchFromLocal(int, std::vector<data::ChatInfo>&));
		}

		m_pUserInfoWidget = new UserInfoWindow(this);
		connect(m_pUserInfoWidget, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),
			this, SLOT(onInfoStartChat(CSharedPtr<data::ChatInfo>&)));
	}

	LocalSearchListWidget::~LocalSearchListWidget()
	{
		clearList();
	}

	void LocalSearchListWidget::searchFromLocal( const QString& text )
	{
		clearList();
		if(!text.isEmpty()){
			mContactControl->searchFromLocal(text.toUtf8().data(),
				CBind(&LocalSearchListWidget::signalSerSearchFromLocal,this,
				CPlaceholders  _1,CPlaceholders  _2));
		}else{

		}
	}/*
		CHAT_INIT=0,
		BUDDY_CHAT = 1,        ///<好友聊天
		GROUP_CHAT = 2,        ///<群组聊天
		APP_CHAT = 3,		   ///<公众号
		SYSTEM_MSG = 4,        ///<系统消息
		STRANGER_CHAT = 5,     ///<陌生人聊天
		ENT_USER_CHAT = 6,     ///<企业成员聊天
		PHONE_CHAT = 7,        ///<我的设备
		ENT_CHAT,				///<企业号
		APPLICATION_CHAT,		///<应用号
		*/
	void LocalSearchListWidget::addItemToList(data::ChatInfo& data )
	{
		QListWidgetItem* item = new QListWidgetItem();
		LocalSearchListItemWidget* widget = new LocalSearchListItemWidget(this);
		QString head = transfer(data.avatar.c_str());
		if (head.startsWith(":/")){
			head = "";
		}
		if(head.isEmpty()){
			if(data.chatType == data::GROUP_CHAT){
				head = DEFAULT_GROUP;
			}else if(data.chatType == data::ENT_CHAT){
				head = DEFAULT_APP;
			}else{
				head = DEFAULT_AVATAR;
			}
			data.avatar = head.toStdString();
		}
		QString name = QString::fromUtf8(data.name.c_str());
		widget->setData(head,name);
		widget->setId(data.targetid);
		if(data.targetid == TeamItem){
			QString team;
			if(data.chatType == data::BUDDY_CHAT){
				team =transfer("联系人");
			}else if(data.chatType == data::GROUP_CHAT){
				team =transfer("群组");
			}else if(data.chatType == data::ENT_USER_CHAT){
				team =transfer("组织成员");
			}
			else if(data.chatType == data::ENT_CHAT){
				team =transfer("企业号");
			}else{
				team =transfer("其他");
			}
			item->setSizeHint(QSize(0,30));
			widget->showItemAsTeam(team);
			
		}else{
			item->setSizeHint(QSize(0,50));
			if (mClickAvatarShowInfo)
			{
				connect(widget,SIGNAL(headClicked(int64)),this,SLOT(onHeadClicked(int64)));
			}
			
		}
		mListWidget->addItem(item);		
		mListWidget->setItemWidget(item,widget);

		mMapData.insert(data.targetid,data);
	}

	void LocalSearchListWidget::onSerSearchFromLocal( int code, std::vector<data::ChatInfo>&list )
	{
		clearList();
		if(list.size()>0){
			for(int i=0;i<list.size();++i){
				addItemToList(list.at(i));
			}
			mListWidget->setCurrentRow(1);
			//mListWidget->setFocus();
			m_mainStactkedWidget->setCurrentWidget(mListWidget);
		}else{
			resetTipItem();

		}
	}
	void LocalSearchListWidget::clearList()
	{
		for (int i=0;i<mListWidget->count();)
		{
			QListWidgetItem* item = mListWidget->item(i);
			QWidget* widget = mListWidget->itemWidget(item);
			mListWidget->removeItemWidget(item);
			if(item != CNull){
				delete item;
			}
			if(widget != CNull){
				delete widget;
			}
			//QCoreApplication::processEvents();
		}
		mListWidget->clear();
		mMapData.clear();
	}

	void LocalSearchListWidget::onItemClicked(QListWidgetItem *item)
	{
		LocalSearchListItemWidget* widget = 
			qobject_cast<LocalSearchListItemWidget*>(mListWidget->itemWidget(item));
		data::ChatInfo data = mMapData.value(widget->id());
		if(widget != CNull && data.chatType !=  2)
		{
			m_pUserInfoWidget->show(widget->id(), widget->name(), widget->head());
		}else{
			//startChat(item);
		}
	}

	void LocalSearchListWidget::onItemDoubleClicked( QListWidgetItem *item )
	{
		startChat(item);
	}

	void LocalSearchListWidget::paintEvent( QPaintEvent *event )
	{
		QWidget::paintEvent(event);
	}

	void LocalSearchListWidget::resetTipItem()
	{
		m_mainStactkedWidget->setCurrentWidget(m_noninfo);
		return;
	}

	void LocalSearchListWidget::keyPressEvent( QKeyEvent *event )
	{
		int keyValue = event->key();
		if(keyValue == Qt::Key_Return || keyValue == Qt::Key_Enter){
			startChat(mListWidget->currentItem());
			event->accept();
		}
	}

	void LocalSearchListWidget::startChat( QListWidgetItem * item )
	{
		LocalSearchListItemWidget* widget = (LocalSearchListItemWidget*)mListWidget->itemWidget(item);
		if(widget){
			data::ChatInfo data = mMapData.value(widget->id());
			if(data.targetid == TeamItem){
				return;
			}
			CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
			chat->chatType    = data.chatType;
			chat->isStartChat = true;
			chat->avatar      = data.avatar;
			chat->name		  = widget->name().toStdString();
			chat->targetid    = data.targetid;
			chat->unreadcount = 0;
			chat->msgid = 0;
			emit startChat(chat);
			emit hideLocalSearchList();
		}
	}

	void LocalSearchListWidget::onInfoStartChat(CSharedPtr<data::ChatInfo>& chatInfo)
	{
		data::ChatInfo data = mMapData.value(chatInfo->targetid);
		chatInfo->chatType = data.chatType;
		emit startChat(chatInfo);
		emit hideLocalSearchList();
	}

	void LocalSearchListWidget::setData( std::vector<data::ChatInfo>&list )
	{
		onSerSearchFromLocal(0,list);
	}

	void LocalSearchListWidget::onHeadClicked( int64 id )
	{
		data::ChatInfo data = mMapData.value(id);
		if (data.chatType !=  2)
		{
			m_pUserInfoWidget->show(id, QString::fromUtf8(data.name.c_str()), data.avatar.c_str());
		}
	}

}
