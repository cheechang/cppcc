#ifndef CHATLISTWIDGET_H
#define CHATLISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <data/ChatData.h>
#include <interface/IChatMgrControl.h>
#include <interface/ISysMsgMgrControl.h>
#include <data/GroupData.h>
#include <data/ContactData.h>
#include <common/Controlptr.h>
#include <QAction>
#include <QMenu>
namespace data{
	class ChatInfo;
	class UserData;
}
namespace ui {
	class ListWidgetItem;
    class ChatListWidget:public QListWidget
    {
		Q_OBJECT
     public:
		typedef CSharedPtr<data::ChatData> DataPtr;
		typedef QListWidgetItem* QListWidgetItemPtr;
		typedef ListWidgetItem*  WidgetItemPtr;

        ChatListWidget(QWidget*parent = 0);
		void insertNewItem(int row,DataPtr data,bool needConvertCode=true);
		void addItemOfLast(DataPtr data,bool needConvertCode=true);
		void addItemOfFirst(DataPtr data,bool needConvertCode=true);
		bool isValidIndex(int index);
		void clearList();
		void setSelectItem(int64 targetId);
	signals:
		void signalSerGetUserNoDisturbMode(int, int64, int8);
		void signalSerChatOperResult(int);
		void signalSerOperateBuddyCb(int, const data::Contact&);
		void signalSerGetUserInfo(int, data::UserData&);
		void signalSerChatListNotify(int flags, std::vector<CSharedPtr<data::ChatData>>&);
		void signalSerChatListHeadUpdate(int64 id,  const std::string&headPath);
		void signalSerRegLastSysMsg(const  data::SysMsg& sysMsg, int count);
		void signalSerRegGroupRefreshCb(int8 type, const data::Group&groupInfo);
		void startChat(CSharedPtr<data::ChatInfo>&chat);
		void RemoveChat(int64 targetId);
		void unreadMsgCount(int count);
		void noticeTrayMsgTip(CSharedPtr<data::ChatInfo>&chat);
		void noticeTrayMsgUpdateReaded(int64 targetId);
		void palySound();
		void noticeTrayFlash(bool);
	public slots:
		void onSerGetUserNoDisturbMode(int code, int64 userId, int8 msgMindMode);
		void onSerChatOperResult(int code);
		void onSerOperateBuddyCb(int type, const data::Contact& contact);
		void onSerRegGroupRefreshCb(int8 type, const data::Group&groupInfo);
		void onSerGetUserInfo(int code, data::UserData& user);
		void onSerChatListNotify(int flags, std::vector<CSharedPtr<data::ChatData>>&dataList);
		void onSerChatListHeadUpdate(int64 id, const std::string&headPath);
		void onSerRegLastSysMsg(const  data::SysMsg& sysMsg, int count);
		void onAddChatListItem(CSharedPtr<data::ChatInfo>&data);

		void onItemDelete(int64 targetId);
		void onItemClicked(QListWidgetItem *item);
		void onClickedItem(int64 targetId);
		void onDisturbMenuItemClicked();
		void onChatTopMenuItemClicked();
	protected:
		void enterEvent(QEvent* event);
		void leaveEvent(QEvent* event);
		void contextMenuEvent(QContextMenuEvent *e);
	private:
		void notifyUnreadMsgCount();
		void updateItemToChatList( DataPtr data ,bool needConvertCode=true,bool newMsg=true);
		void setWidgetItemData( WidgetItemPtr widget, DataPtr data, bool needConvertCode );

		void SetMsgMindType( DataPtr data, QString &avater );

		void addTrayMsgMindItem( DataPtr data, QString &avater );

		void removeItemFromChatList( DataPtr data );
		void removeItemNotSelectNextItem(int64 targetId);
		void deleteItem( int index );
		void initMenu();

		int getInsertPos(DataPtr data);
		QMap<int64,int64> mChatTopItems;
		QMap<int64,int64> mNotChatTopItems;


		QMap<int64,WidgetItemPtr> m_mapWidgetData;
		QMap<int64,QListWidgetItemPtr> m_mapItem;
		
		QMenu*  mainMenu;
		QAction* mActionChatTop;
		QAction*mActionDisturb;
		int64  mCurMenuItemId;
		int64 mCurrentUserId;

		CSharedPtr<control::IChatMgrControl> m_chatMgr; 
		CSharedPtr<control::ISysMsgMgrControl> m_sysMsgMgr; 
		IContactMgrControl_Ptr mContactControl;
		IGroupMgrControl_Ptr m_groupMbr;
		IUserControl_Ptr m_usercontrol;
	public:
		QMap<int64, DataPtr> m_mapData;
    };
}

#endif // CHATLISTWIDGET_H
