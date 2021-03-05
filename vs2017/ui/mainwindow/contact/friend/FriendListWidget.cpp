#include "FriendListWidget.h"

#include <QCoreApplication>
#include <QMessageBox>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QListWidget>
#include <QVBoxLayout>

#include <ui/common/UIUtils.h>
#include <ui/common/ChineseInfos.hpp>
#include <ui/common/Common.h>
#include <ui/common/Connect.h>
#include <utils/functionconfig.h>
#include <controls/SortListWidget.h>
#include <controls/SortListWidgetItem.h>
#include <controls/WeMessageBox.h>
#include <log/log.h>
const  int		   LIST_ITEM_HEIGHT = 62;
const  int		   LIST_ITEM_WIDTH = 226;
namespace ui{
	FriendListWidget::FriendListWidget(QWidget *parent)
		: TWidget(parent)
	{
		mContactControl = CONTACTMGRCONTROL;
		m_usercontrol = USERCONTROL;
		mListWidget = new uicontrols::SortListWidget();
		mListWidget->setAutoSelectNextAfterRemovingItem(true);

		mainLayout = new QVBoxLayout(this);
		mainLayout->setContentsMargins(0,2*gDdpi,0,0);
		mainLayout->addWidget(mListWidget);

		connect(mListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onItemClicked(QListWidgetItem*)));
		connect(mListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(onItemDoubleClicked(QListWidgetItem*)));
		connect(mListWidget,SIGNAL(currentRowChanged(int)),this,SLOT(onListWidgetCurrentRowChanged(int)));
		connect(mListWidget,SIGNAL(signalSrcollToBottom()),this,SLOT(onLazyLoadMember()));

		if(mContactControl){
			CONNECT_SERVICE(OperateBuddyCb(int, const data::Contact&));
			CONNECT_SERVICE(BuddyListCb(int, std::vector<data::Contact>&));
			CONNECT_SERVICE(BuddyOnlineState(const data::OnlineState&));
			CONNECT_SERVICE(ContactHeadImgUpdateCb(int64,const std::string&));
			CONNECT_SERVICE(AddBlacklistCb(int));
			CONNECT_SERVICE(GetBuddyOnline(int, std::vector<data::OnlineState>&));
			CONNECT_SERVICE(RemoveContactCb(int));
			mContactControl->RegOperateBuddyCb(CBind(&FriendListWidget::signalSerOperateBuddyCb,this,CPlaceholders _1,CPlaceholders _2));
			mContactControl->RegBuddyListCb(CBind(&FriendListWidget::signalSerBuddyListCb,this,CPlaceholders  _1,CPlaceholders  _2));
			mContactControl->RegPresentCb(CBind(&FriendListWidget::signalSerBuddyOnlineState,this,CPlaceholders  _1));
			mContactControl->RegContactHeadImgUpdateCb(CBind(&FriendListWidget::signalSerContactHeadImgUpdateCb,this,CPlaceholders  _1,CPlaceholders  _2));
		}
		
		setLayout(mainLayout);
		setObjectName("bg_fa");
		initMenu();
		m_userinfo = *m_usercontrol->GetAccountInfo().get();

		addConstantItems();
		getContactList();

	}

	FriendListWidget::~FriendListWidget()
	{
		mListWidget->disconnect();
		disconnect(this, 0, 0, 0); 
		if(mainMenu){
			delete mainMenu;
			mainMenu = CNull;
		}
		if(mActionDel){
			delete mActionDel;
			mActionDel = CNull;
		}
		if(mActionSetVip){
			delete mActionSetVip;
			mActionSetVip = CNull;
		}
		if(mActionRemark){
			delete mActionRemark;
			mActionRemark = CNull;
		}
		clearList();
	}

	void FriendListWidget::onSerBuddyListCb(int type, std::vector<data::Contact>&contacts)
	{
		std::vector<int64> ids;
		if ((type & 0x01)){
			clearList();

			data::Contact data;

			data.name = transfer("我的设备").toUtf8().data();
			data.thumbAvatar = ":/base/device";
			data.emails.value().push_back(m_userinfo.email.value());
			data.phones.value().push_back(m_userinfo.phone.value());
			data.id.value() = m_userinfo.id.value();
			data.extends = m_userinfo.extends.value();
			data.mydevice.value() = MYDEVICE_SIGN;
			data.pinyin = "@";
			addItemToList(data);

			data.name = transfer("政协服务").toUtf8().data();
			data.thumbAvatar = DEFAULT_APP;
			data.id = ENTERPRISE_ACCOUNT_ID;
			data.pinyin = "@";
			addItemToList(data);

			for (int i = 0; i<contacts.size(); ++i)
			{
				if (contacts.at(i).isApp.value() == 2)
				{
					addItemToList(contacts.at(i));
					ids.push_back(contacts.at(i).id.value());
				}
			}
		}else if (type & 0x10){
			for (int i = 0; i<contacts.size(); ++i)
			{
				if (contacts.at(i).isApp.value() == 2)
				{
					removeItemFromList(contacts.at(i), false);
				}
			}
		}
		else{
			for (int i = 0; i<contacts.size(); ++i)
			{
				if (contacts.at(i).isApp.value() == 2)
				{
					addItemToList(contacts.at(i));
					ids.push_back(contacts.at(i).id.value());
				}
			}
		}

		if (ids.size()>0)
		{
			mContactControl->GetContactOnline(ids, CBind(&FriendListWidget::signalSerGetBuddyOnline, this, CPlaceholders  _1, CPlaceholders  _2));
		}

		ids.clear();

		////设置分页加载参数
		//m_memberpage.setPageSize(8);
		//m_memberpage.clearData();
		//m_memberpage.setData(contacts);
		////加载第一页
		//addFriend();

	}

	void FriendListWidget::onLazyLoadMember(){
		if(m_memberpage.isLoadFinished()){
			m_memberpage.clearData();
			return;
		}
		addFriend();
	}
	void FriendListWidget::addFriend(){
		std::vector<int64> ids;
		std::vector<data::Contact>contacts;
		m_memberpage.getPageData(contacts);
		for(int i =0; i<contacts.size();++i)
		{
			addItemToList(contacts.at(i));
			ids.push_back(contacts.at(i).id.value());
		}
		if (ids.size()>0)
		{
			mContactControl->GetContactOnline(ids,CBind(&FriendListWidget::signalSerGetBuddyOnline,this,CPlaceholders  _1,CPlaceholders  _2));
		}
		ids.clear();
	}

	void FriendListWidget::clearList()
	{
		mListWidget->removeAllItems();
	}

	QString FriendListWidget::getHeadImgBygender(data::Contact data)
	{
		QString head = transfer(data.thumbAvatar.value().c_str());
		if(!head.isEmpty() && UIUtils::IsFileExist(head))
			return head;
		if(1==data.isApp.value())
			return (head = DEFAULT_APP);
		int type = data.gender.value();
		switch(type){
		case 0: //保密
			head = ":/chat/default_unknow_head";;
			break;
		case 1://男
			head = ":/chat/default_head";
			break;
		case 2://女
			head = ":/chat/default_female_head";
			break;
		case 4://公众号
			head = ":/chat/app_default";
			break;
		default:
			head = ":/chat/default_unknow_head";;
			break;
		}
		return head;
	}

	int FriendListWidget::addItemToList( const data::Contact& data )
	{
		BEGIN;
		if(data.isApp.value() == 1) return 0;
		int64 id = data.id.value();
		uicontrols::SortListWidgetItem* widget = mListWidget->widgetById(id);
		if (widget)
		{
			Log(LOG_LEV_INFO,LOG_FILE,"%lld has existed.",id);
			return 0;
		}
		widget = new uicontrols::SortListWidgetItem(uicontrols::SortListWidget::Use_ContactList,this);
		widget->setFixedSize(LIST_ITEM_WIDTH,LIST_ITEM_HEIGHT);
		QString head = getHeadImgBygender(data);
		QString name = data.remark.value().empty()?QString::fromUtf8(data.name.value().c_str()):QString::fromUtf8(data.remark.value().c_str());
		widget->setTextWidth(155*gDdpi);
		widget->setItemData(id,name,head);

		QString team = mListWidget->makeSection(data.pinyin.value().c_str(),data.isStar.value() == 1);
		widget->setTeamKey(team);
		widget->setVip(data.isStar.value() == 1);
		//widget->setOnlineStatus(-1);
		widget->setFlagVisible(false);
		mListWidget->addNewItem(widget);
		mMapData.insert(data.id.value(), data);
		END;
		return 0;
	}

	void FriendListWidget::onItemClicked( QListWidgetItem*item )
	{
		uicontrols::SortListWidgetItem* widget = mListWidget->itemToWidget(item);
		if(widget != CNull){
			data::Contact con;
			con.id = widget->id();
			emit showContactInfoPage(mMapData.value(widget->id()));
		}
	}

	void FriendListWidget::initMenu()
	{
		mainMenu = new QMenu(this);
		mActionDel = new QAction(TEXT_TIP200, this);
		mActionSetVip = new QAction(TEXT_TIP201, this);
		mActionRemark = new QAction(TEXT_TIP202, this);
		connect(mActionDel,SIGNAL(triggered(bool)),this,SLOT(onDeleteMenuItemClicked()));
		connect(mActionSetVip,SIGNAL(triggered(bool)),this,SLOT(onVipMenuItemClicked()));
		connect(mActionRemark,SIGNAL(triggered(bool)),this,SLOT(onRemarkMenuItemClicked()));
	}

	void FriendListWidget::contextMenuEvent( QContextMenuEvent *e )
	{
		QListWidgetItem* item = mListWidget->itemAt(mapFromGlobal(QCursor::pos()));
		if(item != CNull){
			uicontrols::SortListWidgetItem*widget = mListWidget->itemToWidget(item);
			if(widget){
				mainMenu->clear();
				if (widget->id() == APP_ACCOUNT_ID || widget->id() == ENTERPRISE_ACCOUNT_ID || widget->id() == m_userinfo.id.value())
				{
					return;
				}
				mCurCickItemId = widget->id();
				mActionRemark->setText(TEXT_TIP202);
				mActionDel->setText(TEXT_TIP200);
				mainMenu->addAction(mActionRemark);
				if(widget->isVip()){
					mActionSetVip->setText(TEXT_TIP205);
					mainMenu->addAction(mActionSetVip);
				}
				else{
					mActionSetVip->setText(TEXT_TIP201);
					mainMenu->addAction(mActionSetVip);
				}	
				if(!utils::FunctionConfig::isChangeUserName()){
					mainMenu->removeAction(mActionRemark);
				}
				mainMenu->addAction(mActionDel);
				mainMenu->exec(QCursor::pos());
			}
		}
	}

	void FriendListWidget::onSerOperateBuddyCb( int type, const data::Contact& data )
	{
		Log(LOG_LEV_INFO,LOG_FILE,"contact info changed:%d,remark:%s",type,QString::fromUtf8(data.remark.value().c_str()).toStdString().c_str());
		std::vector<int64>ids;
		if(type == 3){
			removeItemFromList(data);
		}else if(type == 1){
			addItemToList(data);
			ids.push_back(data.id.value());
		}else if(type == 2){
			editItemFromIist(data);
			ids.push_back(data.id.value());
		}
		if (ids.size()>0)
		{
			mContactControl->GetContactOnline(ids,CBind(&FriendListWidget::signalSerGetBuddyOnline,this,CPlaceholders  _1,CPlaceholders  _2));
		}
	}

	void FriendListWidget::editItemFromIist( const data::Contact &data )
	{
		uicontrols::SortListWidgetItem*widget = mListWidget->widgetById(data.id.value());
		int64 id = data.id.value();
		if (widget)
		{
			if(data.remark.isSet()){
				bool isVip = widget->isVip();
				if(data.isStar.isSet()){
					isVip = (data.isStar.value() == 1);
				}
				QString name = data.remark.value().empty()?QString::fromUtf8(data.name.value().c_str()):QString::fromUtf8(data.remark.value().c_str());
				QString section = mListWidget->makeSection(data.pinyin.value().c_str(),isVip);
				mListWidget->updateItemName(id,name,section);
				mListWidget->updateVip(id,isVip);
			}else if(data.isStar.isSet()){
				QString name = widget->name();
				bool isVip = widget->isVip();
				QString section = mListWidget->makeSection(data.pinyin.value().c_str(),isVip);
				mListWidget->updateItemName(id,name,section);
				mListWidget->updateVip(id,isVip);
			}

			if(data.thumbAvatar.isSet()){
				QString head = transfer(data.thumbAvatar.value().c_str());
				if(head.isEmpty()){
					head = data.isApp.value()?DEFAULT_APP:DEFAULT_AVATAR;
				}
				mListWidget->updateAvatar(id,head);
			}
		}
		emit showContactInfoPage(data);
	}

	void FriendListWidget::removeItemFromList( const data::Contact &data ,bool selectNextItem)
	{
		mListWidget->removeItem(data.id.value(),true);
	}

	void FriendListWidget::onItemDoubleClicked( QListWidgetItem*item )
	{
		uicontrols::SortListWidgetItem* widget = mListWidget->itemToWidget(item);
		if(widget != CNull)
		{
			if (widget->id() == APP_ACCOUNT_ID || widget->id() == ENTERPRISE_ACCOUNT_ID)
			{
				return;
			}
			data::Contact data;
			mContactControl->GetContactInfo(widget->id(),data);
			if (data.remark.value().empty())
			{
				data.remark = data.name.value();
			}
			CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
			if(widget->id() == m_userinfo.id.value())
			{
				chat->chatType = data::PHONE_CHAT;
			}
			else
			{
				if(data.isApp.value() == 1){
					chat->chatType = data::ENT_CHAT;
				}else{
					chat->chatType = data::BUDDY_CHAT;
				}
			}
			
			chat->isStartChat = true;
			chat->avatar = data.thumbAvatar.value();
			chat->name   = QString::fromUtf8(data.remark.value().c_str()).toStdString();
			if (chat->name.empty())
			{
				chat->name  = QString::fromUtf8(data.name.value().c_str()).toStdString();
			}
			chat->targetid = data.id.value();
			if(widget->id() == m_userinfo.id.value())
			{
				chat->avatar = chat->avatar;
				chat->name = widget->name().toStdString();
				chat->targetid = widget->id();

			}
			emit startChat(chat);
		}
	}

	void FriendListWidget::onDeleteMenuItemClicked()
	{
		uicontrols::SortListWidgetItem*widget = mListWidget->widgetById(mCurCickItemId);
		if(!widget)return;
		QString TipInfo;
		TipInfo = TEXT_TIP_DELETECONTACT + " " + widget->name() + " ?";
		int Res = uicontrols::WeMessageBox::showTipInformation(CNull,PROMPT,TipInfo,false,true);
		if(uicontrols::WeMessageBox::Cancel == Res) return;

		if(mContactControl){
			mContactControl->RemoveContact(mCurCickItemId,CBind
				(&FriendListWidget::signalSerRemoveContactCb,this,CPlaceholders  _1));
		}
	}

	void FriendListWidget::onRemarkMenuItemClicked()
	{
		uicontrols::SortListWidgetItem*widget = mListWidget->widgetById(mCurCickItemId);
		if(widget){
			emit signalRemark(widget->name());
		}
	}

	void FriendListWidget::onVipMenuItemClicked()
	{
		data::Contact newData;
		newData.id = mCurCickItemId;
		uicontrols::SortListWidgetItem* widget = mListWidget->widgetById(mCurCickItemId);
		if(widget){
			newData.isStar = widget->isVip()?2:1;
			if(mContactControl){
				mContactControl->UpdateContactInfo(newData,CBind
					(&FriendListWidget::signalUpdateContactCb,this,CPlaceholders _1));
			}
		}
	}

	void FriendListWidget::onSerRemoveContactCb( int code )
	{

	}

	void FriendListWidget::onShowRemarkWinResult( QString remark )
	{
		UIUtils::removeSpaceBeforeCharacter(remark);
		data::Contact newData;
		newData.id = mCurCickItemId;
		newData.remark = remark.toUtf8().data();
		if(mContactControl){
			mContactControl->UpdateContactInfo(newData,CBind
				(&FriendListWidget::signalUpdateContactCb,this,CPlaceholders _1));
		}
	}

	void FriendListWidget::onSerBuddyOnlineState( const data::OnlineState&state )
	{
		uicontrols::SortListWidgetItem* widget = mListWidget->widgetById(state.userID);
		if(widget){
			int type=0;
			if (state.flag == 1)
			{
				type = state.deviceType;
			}
			widget->setOnlineStatus(type);
		}
	}

	void FriendListWidget::onSerContactHeadImgUpdateCb( int64 id,const std::string& head )
	{
		qDebug()<<Q_FUNC_INFO<<"id:"<<id<<",th:"<<head.c_str();
		uicontrols::SortListWidgetItem* widget = mListWidget->widgetById(id);
		if(widget){
			widget->setAvatarPath(head.c_str());
		}
	}

	void FriendListWidget::onListWidgetCurrentRowChanged(int row)
	{
		if (row<0)
		{
			return;
		}
		QListWidgetItem*item = mListWidget->item(row);
		if(item){
			onItemClicked(item);
		}
	}

	void FriendListWidget::onSerGetBuddyOnline( int code, std::vector<data::OnlineState>&states )
	{
		for (int i=0;i<states.size();++i)
		{
			onSerBuddyOnlineState(states.at(i));
		}
	}

	void FriendListWidget::addConstantItems()
	{
		data::Contact data;

		data.name = MY_PHONE_TIP.toUtf8().data();
		data.thumbAvatar = ":/base/device";
		data.emails.value().push_back(m_userinfo.email.value());
		data.phones.value().push_back(m_userinfo.phone.value());
		data.id.value() = m_userinfo.id.value();
		data.mydevice.value() = MYDEVICE_SIGN;
		data.pinyin = "@";
		addItemToList(data);

		data.name = transfer("政协服务").toUtf8().data();
		data.thumbAvatar = DEFAULT_APP;
		data.id = ENTERPRISE_ACCOUNT_ID;
		data.pinyin = "@";
		addItemToList(data);
	}

	void FriendListWidget::getContactList()
	{
		/*if(mContactControl != CNull)
		{
			std::vector<CSharedPtr<data::Contact>> ContactUser;
			mContactControl->GetContactList(ContactUser,true);
			if(ContactUser.size() > 0)
			{
				std::vector<data::Contact> vcontactList;
				for each (CSharedPtr<data::Contact> var in ContactUser)
				{
					vcontactList.push_back(*var.get());
				}
				onSerBuddyListCb(vcontactList);
			}
		}*/
	}

}
