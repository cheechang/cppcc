#ifndef FRIENDLISTWIDGET_H
#define FRIENDLISTWIDGET_H
#include <controls/TWidget.h>
#include <data/ContactData.h>
#include <data/ChatData.h>
#include <ui/common/Controlptr.h>
#include <ui/controls/PageSizeDataItem.hpp>
#include <QMap>
class QAction;
class QVBoxLayout;
class QMenu;
class QListWidgetItem;
namespace uicontrols{
	class SortListWidget;
	class SortListWidgetItem;
}
namespace ui{
	class FriendListWidget : public TWidget
	{
		Q_OBJECT
	public:
		FriendListWidget(QWidget *parent=CNull);
		~FriendListWidget();
	signals:
		void startChat(CSharedPtr<data::ChatInfo>&chat);
		void signalSerBuddyListCb(int, std::vector<data::Contact>&);
		void signalSerOperateBuddyCb(int, const data::Contact&);
		void signalSerRemoveContactCb(int code);
		void signalUpdateContactCb(int code);
		void showContactInfoPage(data::Contact);
		void signalSerBuddyOnlineState(const data::OnlineState&);
		void signalSerContactHeadImgUpdateCb(int64,const std::string&);
		void signalSerGetBuddyOnline(int, std::vector<data::OnlineState>&);
		void signalRemark(QString);
	public slots:
		void onSerGetBuddyOnline(int code, std::vector<data::OnlineState>&states);
		void onSerBuddyOnlineState(const data::OnlineState&state);
		void onSerRemoveContactCb(int code);
		void onSerBuddyListCb(int type, std::vector<data::Contact>&contacts);
		void onSerOperateBuddyCb(int type, const data::Contact& data);
		void onItemClicked(QListWidgetItem*item);
		void onItemDoubleClicked(QListWidgetItem*item);
		void onDeleteMenuItemClicked();
		void onRemarkMenuItemClicked();
		void onVipMenuItemClicked();
		void onShowRemarkWinResult(QString remark);
		void onSerContactHeadImgUpdateCb(int64 id,const std::string& head);
		void onListWidgetCurrentRowChanged(int row);
		void onLazyLoadMember();
	protected:
		void contextMenuEvent(QContextMenuEvent *e);
		void addFriend();
		QString getHeadImgBygender(data::Contact data);
	private:
		void editItemFromIist( const data::Contact &data );
		void removeItemFromList( const data::Contact &data,bool selectNextItem = true);
		int addItemToList(const data::Contact& data);
		void clearList();
		void initMenu();
		void addConstantItems();
		void getContactList();
		uicontrols::SortListWidget* mListWidget;
		QVBoxLayout*mainLayout;
		QMenu*  mainMenu;
		QAction* mActionSetVip;
		QAction* mActionRemark;
		QAction* mActionDel;
		
		int64 mCurCickItemId;
		data::AccountInfo m_userinfo;
		QMap<int64, data::Contact> mMapData;

		IUserControl_Ptr m_usercontrol;
		IContactMgrControl_Ptr mContactControl;
	private:
		PageSizeDataItem<data::Contact> m_memberpage;
	};
}

#endif // FRIENDLISTWIDGET_H
