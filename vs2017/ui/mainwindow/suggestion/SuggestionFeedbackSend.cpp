#include "SuggestionFeedbackSend.h"
#include "common/Connect.h"
#include "../contact/friend/FriendListWidgetItem.h"
#include "../contact/localsearch/LocalSearchLineEdit.h"
#include "common/Common.h"
#include "../chat/ChatPage.h"
#include <QHBoxLayout>
#include <QDebug>

namespace ui{

	SuggestionFeedbackSendDialog::SuggestionFeedbackSendDialog(QWidget *parent):BaseWindow(parent)
	{				
		__super::setTitle(transfer("好友列表"));
		connect(this,SIGNAL(closeClicked()),this,SLOT(close()));
		SuggestionFeedSendInit();
	}

	SuggestionFeedbackSendDialog::~SuggestionFeedbackSendDialog()
	{

	}

	void SuggestionFeedbackSendDialog::SuggestionFeedSendInit()
	{
		mContactControl = CONTACTMGRCONTROL;
		mainLayout = CMakePtr<QVBoxLayout>(this);
		mSearchEdit = CMakePtr<LocalSearchLineEdit>(this,false);
		mFriendListWidget = CMakePtr<QListWidget>(this);
		mSearchEdit->setPlaceholderText(transfer("搜索：联系人、群"));
		mSearchEdit->setContentsMargins(0,5,0,5);
		QWidget* widget = new QWidget(this);
		widget->setObjectName("SearchBoxBg");
		widget->setStyleSheet("QWidget#SearchBoxBg{background:#f9f7f6;}");
		widget->setFixedSize(260,400);
		mainLayout->addWidget(mSearchEdit.get(),0,Qt::AlignHCenter);
		mainLayout->addWidget(mFriendListWidget.get());
		mainLayout->setStretchFactor(mSearchEdit.get(),1);
		mainLayout->setStretchFactor(mFriendListWidget.get(),12);
		mainLayout->setSpacing(0);
		mainLayout->setContentsMargins(2,2,0,2);
		//this->setLayout(mainLayout.get());
		widget->setLayout(mainLayout.get());
		//mMainLayout->addLayout(mainLayout.get());
		mMainLayout->addWidget(widget,0,Qt::AlignHCenter);
		mMainLayout->addStretch();
		//connect(mSearchEdit.get(),SIGNAL(textEdited(const QString&)),this, SLOT(onSearchFriend(const QString&)));
		connect(mSearchEdit.get(),SIGNAL(textChanged(const QString&)),this, SLOT(onSearchFriend(const QString&)));
		connect(mFriendListWidget.get(),SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(onItemDoubleClicked(QListWidgetItem*)));
		connect(mSearchEdit.get(), SIGNAL(clearBtnClicked()), this, SLOT(onEditClear()));

		CONNECT_SERVICE(GetLocalFriendInfo(int, std::vector<data::ChatInfo>&));
		ShowFriendList();
	}

	void SuggestionFeedbackSendDialog::ShowFriendList()
	{
		std::vector< CSharedPtr<data::Contact> > TempContacts;
		mContactControl->GetContactList(TempContacts);

		for (int i=0;i<TempContacts.size();++i)
		{
			addItemToList(*(TempContacts.at(i)));
		}
	}

	void SuggestionFeedbackSendDialog::onEditClear()
	{
		mSearchEdit->clearText();
	}
	void SuggestionFeedbackSendDialog::onSearchFriend(const QString& key)
	{
		if(key.isEmpty())
		{
			ClearFriendList();
			ShowFriendList();
		}else{
			if(mContactControl)
			{
				std::string TSearchKey = key.toUtf8().data();		
				mContactControl->searchFromLocal(TSearchKey,CBind(&SuggestionFeedbackSendDialog::signalSerGetLocalFriendInfo,this,CPlaceholders  _1,CPlaceholders  _2));		
			}	
		}
		
	}

	int SuggestionFeedbackSendDialog::addItemToList(const data::Contact& data)
	{
		QListWidgetItem* item = new QListWidgetItem();
		FriendListWidgetItem* widget = new FriendListWidgetItem(this);
		int64 id = data.id.value();
		widget->setId(id);
		widget->setPingyin(data.pinyin.value());
		QString head = transfer(data.thumbAvatar.value().c_str());
		if(head.isEmpty()){
			head = (1==data.isApp.value()?DEFAULT_APP:DEFAULT_AVATAR);
		}
		QString name = data.remark.value().empty()?QString::fromUtf8(data.name.value().c_str()):QString::fromUtf8(data.remark.value().c_str());
		widget->setData(head,name,data.isStar.value()==1);
		int pos = mFriendListWidget->count();
		mFriendListWidget->insertItem(pos,item);
		item->setSizeHint(QSize(60,60));
		mFriendListWidget->insertItem(pos,item);
		mFriendListWidget->setItemWidget(item,widget);
		mMapData.insert(data.id.value(),data);
		return mFriendListWidget->row(item);
	}

	int SuggestionFeedbackSendDialog::SearchAddItemToList(const data::ChatInfo& data)
	{
		QListWidgetItem* Item = new QListWidgetItem();
		FriendListWidgetItem* widget = new FriendListWidgetItem();
		CSharedPtr<data::Contact> ContactData = CMakePtr<data::Contact>();
		QString Head = data.avatar.c_str();
		if(Head.isEmpty())
		{
			if(data.chatType == data::GROUP_CHAT)
			{
				Head = DEFAULT_GROUP;
			}else if(data.chatType == data::ENT_CHAT)
			{
				Head = DEFAULT_APP;
			}else
			{
				Head = DEFAULT_AVATAR;
			}
		}
		QString name = QString::fromUtf8(data.name.c_str());

		widget->setData(Head,name);
		widget->setId(data.targetid);
		ContactData->id.value() = data.targetid;
		if(data.targetid == -1){
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
			Item->setSizeHint(QSize(0,30));
			widget->showItemAsTeam(team);

		}else{
			Item->setSizeHint(QSize(0,50));
		}
		
		int pos = mFriendListWidget->count();
		mFriendListWidget->insertItem(pos, Item);
		mFriendListWidget->setItemWidget(Item,widget);
		mMapData.insert(data.targetid,*ContactData.get());
		return mFriendListWidget->row(Item);
	}

	void SuggestionFeedbackSendDialog::ClearFriendList()
	{
		int TCount = mFriendListWidget->count();
		for(int i=TCount-1; i>=0; i--)
		{
			QListWidgetItem* item = mFriendListWidget->item(i);
			QWidget* widget = mFriendListWidget->itemWidget(item);
			mFriendListWidget->removeItemWidget(item);
			if(item != NULL)
			{
				delete item;
				item = NULL;
			}

			if(widget != NULL)
			{
				delete widget;
				widget = NULL;
			}
		}
	}

	void SuggestionFeedbackSendDialog::onSerGetLocalFriendInfo(int ptype, std::vector<data::ChatInfo>& contacts)
	{
		if(contacts.size()>0)
		{
			ClearFriendList();
			for(int i=0; i<contacts.size(); i++)
			{
				SearchAddItemToList(contacts.at(i));   
			}			
		}		
	}

	void SuggestionFeedbackSendDialog::onItemDoubleClicked(QListWidgetItem* item)
	{
		FriendListWidgetItem* widget = (FriendListWidgetItem*)mFriendListWidget->itemWidget(item);
		if(widget != CNull){
			data::Contact data = mMapData.value(widget->id());
			if (data.remark.value().empty())
			{
				data.remark = data.name.value();
			}
			CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
			if(data.isApp.value() == 1){
				chat->chatType = data::ENT_CHAT;
			}else{
				chat->chatType = data::BUDDY_CHAT;
			}
			chat->isStartChat = true;
			chat->avatar   = data.thumbAvatar.value();
			chat->name     = QString::fromUtf8(data.remark.value().c_str()).toStdString();
			if (chat->name.empty())
			{
				chat->name     = QString::fromUtf8(data.name.value().c_str()).toStdString();
			}
			chat->targetid = data.id.value();
			emit startChat(chat);
			accept();

		}
	}
}
