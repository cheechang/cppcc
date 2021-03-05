#ifndef GROUPLISTWIDGET_H
#define GROUPLISTWIDGET_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QWidget>
#include <QVBoxLayout>
#include "interface/Defines.h"
#include "controls/TWidget.h"
namespace data{
	class TinyGroup;
	class AccountInfo;
	class Group;
	class ChatInfo;
}
namespace control{
	class IGroupMgrControl;
	class IUserControl;
}

namespace uicontrols{
	class SortListWidget;
	class SortListWidgetItem;
}
namespace ui{
	class GroupListItemWidget;
	class GroupListWidget : public TWidget
	{
		Q_OBJECT
	public:
		typedef CSharedPtr<data::TinyGroup> DataPtr;
		typedef CSharedPtr<QListWidgetItem> ItemPtr;
		typedef CSharedPtr<GroupListItemWidget> ItemWidgetPtr;

		GroupListWidget(QWidget *parent=CNull);
		~GroupListWidget();

		void clearList();
		void removeItem(int row);
	signals:
		void startChat(CSharedPtr<data::ChatInfo>&chat);
		void showGroupInforPage(int64 groupId);
		void signalSerGroupListNotify(std::vector<CSharedPtr<data::TinyGroup> >&); 
		void signalSerGroupHeadImgNotify(int64, const std::string&);
		void signalSerGroupOpertorNotify(int);
		void signalSerGroupRefreshNotify(int8, const data::Group&);
		void signalSerTransferGroupNotify(int64, const std::string&, int64, const std::string&);
	protected:
		void contextMenuEvent(QContextMenuEvent *e);
		void initMenuItem();
		void updateItem(DataPtr data);
		void addListNewItem( DataPtr data ,int pos =-1);
		void deleteMenuSelItemAndShowNextItemInfo();
		void deleteItemAndSelNextItemInfo( int &row );
		int  getPosByName(std::string pingyin);
		CSharedPtr<data::TinyGroup> makeDataPtr(const data::Group &group );
	public slots:
		void onSerGroupListNotify(std::vector<CSharedPtr<data::TinyGroup> >&groups);
		void onSerGroupHeadImgNotify(int64 groupId, const std::string& head);
		void onSerGroupOpertorNotify(int code);
		void onSerGroupRefreshNotify(int8 type, const data::Group&group);//操作类型 1.添加 2.更新，31.解散 32.移除 33.退出
		void onSerTransferGroupNotify(int64 creatorId, const std::string& creatorName,
			int64 groupId, const std::string& groupName);

		void updateItemAndSelItemInfo(DataPtr data);

		void onItemClicked(QListWidgetItem*item);
		void onItemDoubleClicked(QListWidgetItem*item);
		void onExistGroupClicked();
		void onTransferGroupClicked();
		void onDissolutionGroupClicked();

		void onSerSetVGroupClicked();
		void onSerCancelVGroupClicked();
		void onSerSetVGroupCallback(int Error);
		void onGetVGroupSign(std::vector<CSharedPtr<data::TinyGroup>> groups);
	private:
		CSharedPtr<control::IGroupMgrControl> m_groupmgrcontrol;
		int64 mAccountId;
		
		QMap<int64,DataPtr> m_mapData;
		QMap<int64,ItemPtr> m_mapItem;
		QMap<int64,ItemWidgetPtr> m_mapItemWidget;
		QMap<int64, bool> m_mapVSign;
		CSharedPtr<QAction> m_actionExistGroup,m_actionTransferGroup,m_actionDissolutionGroup;
		CSharedPtr<QAction> m_actionSetVGroup, m_actionCancelVGroup;
		int64 mMenuSelectItemGroupId;//右键菜单选择项
		CSharedPtr<QMenu> popMenu;
		uicontrols::SortListWidget* mListWidget;
		CSharedPtr<QVBoxLayout> mMainLayout;
		int64 mCurSelectItemId;
	};
}
#endif // GROUPLISTWIDGET_H
