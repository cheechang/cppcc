#include "ChatListWidget.h"
#include "ListWidgetItem.h"
#include "common/controlptr.h"
#include "common/Connect.h"
#include "common/MsgTimeDeal.hpp"
#include "common/ChineseInfos.hpp"
#include "common/Common.h"
#include "log.h"
#include "../../../utils/common.h"
#include "../TrayUnreadMsgTipWin.h"
#include "../../systemmsg/SystemMsgPage.h"
//#include "core/WindowsManager.h"
#include <QWheelEvent>
#include <QScrollBar>
#include <QPropertyAnimation>
#include<QDebug>
#include<qmessagebox.h>
#include <QListWidget>
#include <QListWidgetItem>
#include <QWidget>
QStringList g_unreadcount;
namespace ui {

    ChatListWidget::ChatListWidget(QWidget*parent):QListWidget(parent)
    {
		mContactControl = CONTACTMGRCONTROL;
		m_chatMgr = CHATMGRCONTROL;
		m_groupMbr = GROUPMGRCONTROL;
		m_sysMsgMgr = SYSMSGCONTROL;
		m_usercontrol = USERCONTROL;

	 	this->setSortingEnabled(false);
		this->setMouseTracking(true);
		this->verticalScrollBar()->setValue(0);
		this->verticalScrollBar()->setVisible(false);
		this->horizontalScrollBar()->setVisible(false);

		ui::TrayUnreadMsgTipWin* trayMsgWin = ui::TrayUnreadMsgTipWin::Instance();
		connect(this,SIGNAL(noticeTrayMsgTip(CSharedPtr<data::ChatInfo>&)),trayMsgWin,SLOT(onNoticeTrayMsgTip(CSharedPtr<data::ChatInfo>&)));
		connect(this,SIGNAL(noticeTrayMsgUpdateReaded(int64 )),trayMsgWin,SLOT(onNoticeTrayMsgUpdateReaded(int64)));
		connect(trayMsgWin,SIGNAL(trayMsgClicked(int64 )),this,SLOT(onClickedItem(int64)));
 	
		CONNECT_SERVICE(ChatListNotify(int,std::vector<CSharedPtr<data::ChatData>>&));
		CONNECT_SERVICE(ChatListHeadUpdate(int64, const std::string&));
		CONNECT_SERVICE(GetUserInfo(int, data::UserData&));
		CONNECT_SERVICE(ChatOperResult(int));
		CONNECT_SERVICE(GetUserNoDisturbMode(int, int64, int8));

	
		CONNECT_SERVICE(RegGroupRefreshCb(int8 ,const data::Group&));
		if (m_groupMbr != CNull)
		{
			m_groupMbr->RegGroupRefreshCb(CBind
				(&ChatListWidget::signalSerRegGroupRefreshCb,this,CPlaceholders  _1,
				CPlaceholders  _2));
		}
		if(CNull != m_chatMgr){
			m_chatMgr->RegChatListNotify(CBind
				(&ChatListWidget::signalSerChatListNotify,this,CPlaceholders  _1,
				CPlaceholders  _2));
			m_chatMgr->RegChatListHeadUpdate(CBind
				(&ChatListWidget::signalSerChatListHeadUpdate,this,CPlaceholders  _1,
				CPlaceholders  _2));
		}
 		CONNECT_SERVICE(RegLastSysMsg(const  data::SysMsg& , int ));
		if (CNull != m_sysMsgMgr)
		{
			m_sysMsgMgr->regLastSysMsgCb(CBind(&ChatListWidget::signalSerRegLastSysMsg, this, CPlaceholders  _1, CPlaceholders  _2));
		}
 
		if (CNull != mContactControl)
		{
			CONNECT_SERVICE(OperateBuddyCb(int, const data::Contact&));
			mContactControl->RegOperateBuddyCb(CBind(&ChatListWidget::signalSerOperateBuddyCb,this,CPlaceholders _1,CPlaceholders _2));
		}
    	CSharedPtr<data::AccountInfo> tuserinfo;
	 	tuserinfo = m_usercontrol->GetAccountInfo();
 		mCurrentUserId = tuserinfo->id.value();
 
		mCurMenuItemId = 0;
		mChatTopItems.clear();
		mNotChatTopItems.clear();
		initMenu();
    }

	void ChatListWidget::insertNewItem(int row, DataPtr data,bool needConvertCode )
	{
		BEGIN;
		QListWidgetItemPtr item = new QListWidgetItem();//CMakePtr<QListWidgetItem>();
		if(item){
			WidgetItemPtr itemWidget = new ListWidgetItem(data->id.value(),this);//CMakePtr<ListWidgetItem>(data->id.value());
			connect(itemWidget,SIGNAL(signalDelItem(int64)),this,SLOT(onItemDelete(int64)));
			connect(itemWidget,SIGNAL(signalClicked(int64 )),this,SLOT(onClickedItem(int64)));
			setWidgetItemData(itemWidget, data, needConvertCode);
			itemWidget->setMsgTime(data->msgTime);
			this->insertItem(row,item);
			this->setItemWidget(item,itemWidget);
			int64 targetId = data->id.value();

			m_mapWidgetData.insert(data->id.value(),itemWidget);
			m_mapItem.insert(data->id.value(),item);
			m_mapData.insert(data->id.value(),data);

			//更新免打扰
			bool isBuddy = false;
			isBuddy = mContactControl->ContactIsBuddy(targetId);
			if (isBuddy|| data->chatType == 2)
			{
				m_chatMgr->getUserNoDisturbMode(targetId,CBind(&ChatListWidget::signalSerGetUserNoDisturbMode,this,CPlaceholders _1,CPlaceholders _2,CPlaceholders _3));
			}

			this->update();
			if(data->name.value().empty() && data->id.value() != SYSMSG_ID){
				m_chatMgr->getUserInfo(data->id.value(),0,CBind
					(&ChatListWidget::signalSerGetUserInfo,this,
					CPlaceholders  _1,CPlaceholders  _2));
			}
		}
		END;
	}

	void ChatListWidget::addItemOfLast( DataPtr data ,bool needConvertCode)
	{
		insertNewItem(this->count(),data,needConvertCode);
	}

	void ChatListWidget::addItemOfFirst(DataPtr data ,bool needConvertCode)
	{
		insertNewItem(0,data,needConvertCode);
	}

	bool ChatListWidget::isValidIndex( int index )
	{
		return (index>=0 && index <this->count());
	}

	void ChatListWidget::onSerChatListNotify(int flags, std::vector<CSharedPtr<data::ChatData>>&dataList)
	{
		BEGIN;
		if (flags == 0x40)
		{
			QList<int64> chats = m_mapData.keys();
			for (int i=0;i<chats.size();++i)
			{
				emit RemoveChat(chats.at(i));
			}
			//删除会话
			clearList();
			notifyUnreadMsgCount();
			return;
		}
		if((flags & 0x01)){
			clearList();
		}

		if(flags == 0x20){
			for(int i=dataList.size()-1;i>=0;--i){
				DataPtr data = dataList.at(i);
				removeItemFromChatList(data);
			}

		}else if(flags == 0x08 || flags == 0x10){
			for(int i=dataList.size()-1;i>=0;--i){
				DataPtr data = dataList.at(i);
				updateItemToChatList(data);
			}	

		}
		else {
			
			for(int i=dataList.size()-1;i>=0;--i){
				DataPtr data = dataList.at(i);
				int pos = getInsertPos(data);
				insertNewItem(pos,data);
			}
		}
		notifyUnreadMsgCount();
		END;
	}

	void ChatListWidget::onItemClicked( QListWidgetItem *item )
	{
		BEGIN;
		if(item != CNull){

			int row = this->indexFromItem(item).row();
			if(isValidIndex(row)){
				ListWidgetItem* itemWidget = (ListWidgetItem*)this->itemWidget(item);
				if(itemWidget != CNull){
					int64 targetId = itemWidget->targetId();
					if (itemWidget->unreadMsgCount()>0)
					{
						emit noticeTrayMsgUpdateReaded(targetId);
					}
					itemWidget->setUnreadCount("");
					DataPtr data = m_mapData.value(targetId);
					if(data == CNull){
						return ;
					}
					CSharedPtr<data::ChatInfo> chat = CMakePtr<data::ChatInfo>();
					chat->chatType = (data::ChatType)data->chatType;
					chat->avatar   = utils::FileIsExist(data->thumbAvatar.value().c_str())?data->thumbAvatar.value():"";
					chat->name = QString::fromUtf8(data->name.value().c_str()).toStdString();
					chat->targetid = data->id.value();
					chat->unreadcount = data->unReadCnt;
					chat->msgid = data->lastMsgId;
					//设置消息已读
					
					if (chat->unreadcount > 0){
						m_chatMgr->setMessageRead(chat->targetid, chat->msgid);
					}
					emit startChat(chat);
				}
			}
		}
		notifyUnreadMsgCount();
		END;
	}

	void ChatListWidget::onItemDelete( int64 targetId )
	{
		BEGIN;
		QListWidgetItemPtr item = m_mapItem.value(targetId,CNull);
		bool isDeleteLast = false;
		if(item != CNull){
			int index = this->indexFromItem(item).row();
			bool isCurIndex = index == currentIndex().row();
			isDeleteLast = (count()-1 == index);
			if(isValidIndex(index)){
				deleteItem(index);

			}
			if(isDeleteLast){
				index = count() -1;
			}
			if(isValidIndex(index)&& isCurIndex){
				QListWidgetItem* nextItem = this->item(index);
				if(nextItem != CNull){
					onItemClicked(nextItem);
					setCurrentItem(nextItem);
				}
			}
			emit RemoveChat(targetId);
		}
		notifyUnreadMsgCount();
		END;
	}
	void ChatListWidget::clearList(){
		BEGIN;
		for(int i=0;i< count();){
			deleteItem(i);
		}
		END;
	}

	void ChatListWidget::deleteItem( int index )
	{
		BEGIN;
		
		QListWidgetItem* item = this->item(index);
		ListWidgetItem* itemWidget = (ListWidgetItem*)this->itemWidget(item);
		if(itemWidget == CNull){
			return ;
		}
	    this->takeItem(index);

		int64 targetId = itemWidget->targetId();
		DataPtr data = m_mapData.value(targetId);
		mChatTopItems.remove(data->msgTime);
		mNotChatTopItems.remove(data->msgTime);
		m_mapItem.remove(targetId);
		m_mapData.remove(targetId);
		m_mapWidgetData.remove(targetId);
		delete item;
		END;
	}

	void ChatListWidget::removeItemFromChatList( DataPtr data )
	{
		if(data != CNull){
			QListWidgetItemPtr item = m_mapItem.value(data->id.value(),CNull);
			if (item != CNull)
			{
				if (item == currentItem())
				{
					onItemDelete(data->id.value());	
				}else{
					removeItemNotSelectNextItem(data->id.value());
				}
			}
		}
	}

	void ChatListWidget::updateItemToChatList( DataPtr data ,bool needConvertCode,bool newMsg)
	{
		BEGIN;
		DataPtr oldItem = m_mapData.value(data->id.value());
		bool isSelect = false;
		if(oldItem){
			if(data != CNull){
				QListWidgetItemPtr curItem = m_mapItem.value(oldItem->id.value());
				/*
				bool needChangedPos = data->msgTime>oldItem->msgTime;
				if(data->realUnReadCnt <=0 && newMsg && !needChangedPos){
					WidgetItemPtr widget = m_mapWidgetData.value(data->id.value());
					if(widget == CNull){
						return;
					}
					setWidgetItemData(widget, data, needConvertCode);
					m_mapData.remove(data->id.value());
					m_mapData.insert(data->id.value(),data);
					return;
				}*/
				if(curItem != CNull && currentItem() == curItem){
					isSelect = true;
				}
				removeItemNotSelectNextItem(data->id.value());
			}
		}
		int pos = getInsertPos(data);
		insertNewItem(pos,data,needConvertCode);
		if(isSelect){
			setSelectItem(data->id.value());
		}
		END;
	}

	void ChatListWidget::onSerChatListHeadUpdate( int64 id,  const std::string&headPath )
	{
		Log(LOG_LEV_DEBUG, LOG_FILE, "onSerChatListHeadUpdate id=%lld,headPath=%s", id, headPath.c_str());
		WidgetItemPtr item = m_mapWidgetData.value(id);
		if(item){
			item->updateHead(headPath.c_str());
			DataPtr data = m_mapData.value(id);
			data->thumbAvatar = headPath.c_str();
			m_mapData.insert(id,data);
		}
	}

	void ChatListWidget::onAddChatListItem(CSharedPtr<data::ChatInfo>&data)
	{
		BEGIN;
		DataPtr itemData = CMakePtr<data::ChatData>();
		itemData->thumbAvatar = data->avatar.c_str();
		itemData->id = data->targetid;
		itemData->name = data->name.c_str();
		itemData->chatType = data->chatType;
		itemData->lastMsg = data->lastMsg;
		itemData->lastMsgId = data->msgid;
		itemData->msgTime = data->msgtime;
		updateItemToChatList(itemData,false,false);
		setSelectItem(data->targetid);
		END;
	}

	void ChatListWidget::setSelectItem( int64 targetId )
	{
		QListWidgetItemPtr curItem = m_mapItem.value(targetId,CNull);
		if(curItem != CNull){
			setCurrentItem(curItem);
		}
	}

	void ChatListWidget::removeItemNotSelectNextItem(int64 targetId )
	{
		BEGIN;
		QListWidgetItemPtr item = m_mapItem.value(targetId,CNull);
		if(item != CNull){
			int index = this->indexFromItem(item).row();
			if(isValidIndex(index)){
				deleteItem(index);

			}
		}

		END;
	}

	void ChatListWidget::setWidgetItemData( WidgetItemPtr widget, DataPtr data, bool needConvertCode )
	{
		if(widget == CNull){
			return;
		}
		QString strDateTime = DealMsgTime(data->msgTime,CHATLIST_TIME);
		QString avater = transfer(data->thumbAvatar.value().c_str());
		if(avater.isEmpty() || !utils::FileIsExist(data->thumbAvatar.value())){
			if(data->chatType == data::GROUP_CHAT){
				avater = ":/base/group_head";
			}else if(data->chatType == data::APP_CHAT || data->chatType == data::ENT_CHAT){
				avater = ":/base/app_default";
			}
			if (data->id.value() == SYSMSG_ID)
			{
				avater = ":/chat/sysMsg";
			}
		}
		
		if (needConvertCode)
		{
			widget->setChatTop(data->subType == 4);//置顶
			widget->setNotDisturb(data->disturbSet == 3);
		}
		if (data->unReadCnt<0){
			data->unReadCnt = 0;
		}
		QString unreadMsg = data->unReadCnt >= 99 ? "99+" : QString::number(data->unReadCnt);
		bool showAtWin = data->unReadCnt>0 && data->lastAtMsgID != 0;

		QString name("");
		if (data->id.value() == SYSMSG_ID)
		{
			name = QString(transfer("系统消息"));
		}

		if(data->id.value() == mCurrentUserId)
		{
			name = QString(transfer("我的设备"));
			avater = ":/base/device";
		}
		else
		{
			name  = QString::fromUtf8(data->name.value().c_str());
		}
		
		if(needConvertCode){
			widget->setData(
				name,
				QString::fromUtf8(data->lastMsg.c_str()),
				strDateTime,
				avater,
				unreadMsg,
				data->unReadCnt, showAtWin);
		}else{
			widget->setData(
				QString(data->name.value().c_str()),
				QString(data->lastMsg.c_str()),
				strDateTime,
				avater,
				unreadMsg,
				data->unReadCnt);
		}
		if (data->unReadCnt >0)
		{
			SetMsgMindType(data, avater);
		}
	}

	void ChatListWidget::onSerGetUserInfo( int code, data::UserData& user )
	{
		if(code == 0){
			WidgetItemPtr widget = m_mapWidgetData.value(user.id.value());
			if(widget){
				widget->updateHead(transfer(user.thumbAvatar.value().c_str()));
				widget->updateName(QString::fromUtf8(user.name.value().c_str()));

				DataPtr data = m_mapData.value(user.id.value());
				data->thumbAvatar =user.thumbAvatar.value();
				data->name =user.name.value();
				m_mapData.insert(user.id.value(),data);
			}
		}
	}
	void ChatListWidget::onSerRegLastSysMsg(const  data::SysMsg& sysMsg, int count)
	{
		BEGIN;
		AddLog(LOG_LEV_DEBUG,"ChatListWidget::onSerRegLastSysMsg count = %d",count);
		if (count >=1 )
		{
			if(SystemMsgPage::isSysPageSelect){
				count = 0;
			}
			if (m_mapData.contains(SYSMSG_ID))
			{
				//更新未读
				DataPtr data = m_mapData.value(SYSMSG_ID);
				data->unReadCnt = count;
				data->msgTime = sysMsg.time;
				m_mapData.insert(SYSMSG_ID,data);
				updateItemToChatList(data);
			}
			else
			{
				//添加系统消息
				DataPtr tempdata = CMakePtr<data::ChatData>();
				tempdata->id = SYSMSG_ID;
				tempdata->name = QString::fromLocal8Bit("系统消息").toUtf8().data();
				tempdata->chatType =data::SYSTEM_MSG;
				tempdata->unReadCnt = count;
				tempdata->msgTime = sysMsg.time;
				int pos = getInsertPos(tempdata);
				insertNewItem(pos,tempdata);
			}
			notifyUnreadMsgCount();
		}
		END;
	}
	void ChatListWidget::notifyUnreadMsgCount()
	{
		int count = 0;
		QList<WidgetItemPtr> list = m_mapWidgetData.values();
		g_unreadcount.clear();
		for(int i=0;i<list.size();++i){
			WidgetItemPtr widget = list.at(i);
			if(widget){
				count+=widget->unreadMsgCount();
				data::ChatData data;
				QString info;
				info = QString::number(widget->targetId()) + "," + QString::number(widget->unreadMsgCount());
				g_unreadcount.append(info);
			}
		}
		emit unreadMsgCount(count);
	}
	void ChatListWidget::enterEvent(QEvent* event)
	{
		Q_UNUSED(event)
		this->verticalScrollBar()->setVisible(true);
	}

	void ChatListWidget::leaveEvent(QEvent* event)
	{
		Q_UNUSED(event)
		this->verticalScrollBar()->setVisible(false);
	}

	void ChatListWidget::onSerRegGroupRefreshCb( int8 type, const data::Group&groupInfo )
	{
		if (type == 2)//缇や俊鎭洿鏂?
		{
			if (groupInfo.info.value().groupName.isSet())
			{
				int64 groupId = groupInfo.info.value().groupId.value();
				WidgetItemPtr widget = m_mapWidgetData.value(groupId,CNull);
				if(widget != CNull){
					widget->updateName(QString::fromUtf8(groupInfo.info.value().groupName.value().c_str()));

					DataPtr data = m_mapData.value(groupId);
					data->name = groupInfo.info.value().groupName.value();
					m_mapData.insert(groupId,data);
				}
			}
		}
	}

	void ChatListWidget::onClickedItem( int64 targetId )
	{
		QListWidgetItemPtr item = m_mapItem.value(targetId,CNull);
		if (item != CNull)
		{
			onItemClicked(item);
		}
	}

	void ChatListWidget::onSerOperateBuddyCb( int type, const data::Contact& contact )
	{
		if (type == 2)//更新
		{
			QString name = QString::fromUtf8(contact.remark.value().c_str());
			if (contact.remark.isSet())
			{
				if (contact.remark.value().empty())
				{
					name = QString::fromUtf8(contact.name.value().c_str());
				}
				WidgetItemPtr widget = m_mapWidgetData.value(contact.id.value(),CNull);
				if(widget != CNull){
					widget->updateName(name);

					DataPtr data = m_mapData.value(contact.id.value());
					data->name = name.toUtf8().data();
					m_mapData.insert(contact.id.value(),data);
				}
			}
		}else if(type == 3)//删除
		{
			onItemDelete(contact.id.value());
		}
	}

	void ChatListWidget::onDisturbMenuItemClicked()
	{
		if (mCurMenuItemId != 0)
		{
			DataPtr data = m_mapData.value(mCurMenuItemId);
			int type =1;
			if (data->disturbSet == 1)
			{
				type = 3;
			}
			m_chatMgr->setUserNoDisturbMode(mCurMenuItemId,type,CBind(&ChatListWidget::signalSerChatOperResult,this,CPlaceholders _1));
			WidgetItemPtr widget = m_mapWidgetData.value(mCurMenuItemId);
			if (widget)
			{
				widget->setNotDisturb(type == 3);
				m_mapData.remove(mCurMenuItemId);
				data->disturbSet = type;
				m_mapData.insert(mCurMenuItemId,data);
			}
			mCurMenuItemId = 0;
		}
	}

	void ChatListWidget::onChatTopMenuItemClicked()
	{
		if (mCurMenuItemId != 0)
		{
			DataPtr data = m_mapData.value(mCurMenuItemId);
			bool isTop = data->subType != 4;
			m_chatMgr->chatTop(mCurMenuItemId,isTop,CBind(&ChatListWidget::signalSerChatOperResult,this,CPlaceholders _1));
			mCurMenuItemId = 0;
		}
	}

	void ChatListWidget::contextMenuEvent( QContextMenuEvent *e )
	{
		QListWidgetItem* item = this->itemAt(mapFromGlobal(QCursor::pos()));
		if (item)
		{
			mainMenu->clear();
			WidgetItemPtr widget = (WidgetItemPtr)this->itemWidget(item);
			if (widget)
			{
				int64 targetId = widget->targetId();
				DataPtr data = m_mapData.value(targetId);
				if (targetId == SYSMSG_ID || data->chatType == data::ENT_CHAT || data->chatType == data::APP_CHAT)
				{
					return;
				}
				mCurMenuItemId = targetId;

				bool isBuddy = false;
				if (data->chatType != 2)
				{
					isBuddy = mContactControl->ContactIsBuddy(targetId);
				}
				if (isBuddy ||data->chatType == 2)
				{

					QString topText = data->subType == 4?transfer("取消会话置顶"):transfer("会话置顶");
					mActionChatTop->setText(topText);
					mainMenu->addAction(mActionChatTop);

					QString disturbText = data->disturbSet != 3?transfer("开启消息免打扰"):transfer("关闭消息免打扰");
					mActionDisturb->setText(disturbText);
					mainMenu->addAction(mActionDisturb);
				}
				mainMenu->exec(QCursor::pos());
			}
		}
	}

	void ChatListWidget::initMenu()
	{
		mainMenu = new QMenu(this);
		mActionChatTop = new QAction(transfer("会话置顶"),this);
		mActionDisturb = new QAction(transfer("消息免打扰"),this);

		connect(mActionChatTop,SIGNAL(triggered(bool)),this,SLOT(onChatTopMenuItemClicked()));
		connect(mActionDisturb,SIGNAL(triggered(bool)),this,SLOT(onDisturbMenuItemClicked()));
	}

	void ChatListWidget::onSerChatOperResult( int code )
	{

	}

	int ChatListWidget::getInsertPos( DataPtr data )
	{
		int64 targetId = data->id.value();
		if (data->subType == 4)
		{
			mChatTopItems.insert(data->msgTime,targetId);
			QList<int64>  chats = mChatTopItems.keys();
			for (int i = 0;i<chats.count();++i)
			{
				if (data->msgTime == chats.at(i))
				{
					int index = chats.count() - i-1;
					if (index>=chats.count())
					{
						index = 0;
					}
					return index;
				}
			}
		}else{
			mNotChatTopItems.insert(data->msgTime,targetId);
			QList<int64>  chats = mNotChatTopItems.keys();
			for (int i = 0;i<chats.count();++i)
			{
				QString name = QString::fromUtf8(data->name.value().c_str());
				if (data->msgTime == chats.at(i))
				{
					int index = chats.count() - i-1;
					if (index>=chats.count())
					{
						index = 0;
					}
					return index+mChatTopItems.count();
				}
			}
		}
		return mChatTopItems.count();
	}

	void ChatListWidget::onSerGetUserNoDisturbMode( int code, int64 userId, int8 msgMindMode )
	{
		DataPtr data = m_mapData.value(userId);
		if (data != CNull)
		{
			data->disturbSet = msgMindMode;
			m_mapData.insert(userId,data);
		}
		WidgetItemPtr widget = m_mapWidgetData.value(userId);
		if (widget)
		{
			widget->setNotDisturb(msgMindMode == 3);
		}
	}

	void ChatListWidget::SetMsgMindType( DataPtr data, QString &avater )
	{
		switch (data->msgRemindMode)
		{
		case 0:
		case 5:
			{
			//支持系统消息
			if (data->id.value() == SYSMSG_ID) {
				data->name = SYSTEM_MSG_TIP.toUtf8().data();
				addTrayMsgMindItem(data, avater);
			}
			break;
			}
		case 1:
		case 3:
			{
				//声音提醒
				emit palySound();
				//托盘闪烁
				addTrayMsgMindItem(data, avater);
				break;
			}
		case 2:
			{
				//托盘闪烁
				addTrayMsgMindItem(data, avater);
				break;
			}
		case 4:
			{
				//抖一抖
				break;
			}
		default:
			break;
		}
	}

	void ChatListWidget::addTrayMsgMindItem( DataPtr data, QString &avater )
	{
		CSharedPtr<data::ChatInfo> chatinfo= CMakePtr<data::ChatInfo>();
		chatinfo->targetid = data->id.value();
		chatinfo->avatar = avater.toUtf8().data();
		chatinfo->unreadcount = data->unReadCnt;
		chatinfo->name = data->name.value();
		chatinfo->msgid = data->lastMsgId;
		emit noticeTrayMsgTip(chatinfo);
		
		emit noticeTrayFlash(true);
	}
}
