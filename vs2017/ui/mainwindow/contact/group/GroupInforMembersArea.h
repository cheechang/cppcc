#ifndef GROUPINFORMEMBERSAREA_H
#define GROUPINFORMEMBERSAREA_H
#include <QListWidget>
#include <QVBoxLayout>
#include "interface/Defines.h"
#include "common/Controlptr.h"
#include <data/GroupData.h>
#include <data/ChatData.h>
#include "controls/TWidget.h"
#include "controls/BaseQListWidget.h"
#include "controls/PageSizeDataItem.hpp"
#include <QPushButton>
#include <QLabel>
#include <QMenu>
#include <QAction>
namespace ui{
	class GroupMemberListItemWidget;
	class CreateGroupWindow;
	class UserInfoWindow;
	class UserInfoCommon;
	class UserInfoCommitee;

	class GroupInforMembersArea : public TWidget
	{
		Q_OBJECT
	public:
		typedef CSharedPtr<data::Member> DataPtr;

		GroupInforMembersArea(QWidget *parent=CNull);
		~GroupInforMembersArea();

		void updateData(int64 groupId);
		void clearList();
		void hideInviteMemWidget(bool hide);
		void getMemberList(int64 groupId);
	signals:
		void startChat(CSharedPtr<data::ChatInfo>&);
		void itemClicked(QPoint);
		void signalSerGetMemberList(int, std::vector<CSharedPtr<data::Member> >&);
		void signalSerCallBack(int);
		void signalSerGrpMemRefreshCb(int, int64, std::vector<CSharedPtr<data::Member> >&); 
		void signalSerRemoveMember(int64);
		void signalSerSetAdminResult(int);
		void signalSerSetRemarkResult(int);
		void signalSerTransferGroupResult(int);
		void signalSerGrpMemInfoRefreshCb(int64 , const data::Member&);
		void signalSerGetUserInfo(int, data::UserData&, int64 id, QString name, QString avatar);
	public slots:
		void onSerGetUserInfo(int, data::UserData&, int64 id, QString name, QString avatar);
		void onSerGrpMemInfoRefreshCb(int64 groupId, const data::Member&memberInfo);
		void onSerGetMemberList(int code , std::vector<CSharedPtr<data::Member> >&mems);
		void onItemClicked();
		void onItemDoubleClicked(QListWidgetItem* item);
		void onInviteGroup();
		void onMenuItemClicked();
		void onMenuItemAdminClicked();
		void onMenuItemRemarkClicked();
		void onMenuItemTransferClicked();
		void onGroupSet(int code, int8 verify_type, int8 is_allow);
		void onSerGrpMemRefreshCb(int type, int64 groupId, std::vector<CSharedPtr<data::Member> >&mems);
		void onSerRemoveMember(int64 code);
		void onSerSetAdminResult(int code);
		void onSerSetRemarkResult(int code);
		void onSerTransferGroupResult(int code);
		void onLazyLoadMember();
	protected:
		void contextMenuEvent(QContextMenuEvent *e);
		void addMember();
		void addItemToUI(DataPtr data);
	private:
		void menuWidget();
		void refreshMenu();

		IChatMgrControl_Ptr			m_chatcontrol;
		IGroupMgrControl_Ptr m_groupmgrcontrol;
		uicontrols::BaseQListWidget* mListWidget;
		int64 mGroupId;
		QVBoxLayout*mainLayout;

		QLabel*m_pLoadData;
		QAction* mActionDel;//删除
		QAction* m_ActionAdmin;//设置管理员
		QAction* m_ActionRemark;//设置群名片
		QAction* m_ActionTransfer;//转让群
		QMenu*   mainMenu;
		UserInfoWindow* m_pUserInfoWidget;
		bool m_isLoadDataing;
		CSharedPtr<UserInfoCommon> m_pUserInfoCommomWidget;
		CSharedPtr<UserInfoCommitee> m_pUserInfoCommiteeWidget;
		int64 mCurMemId;
		PageSizeDataItem<DataPtr> m_memberpage;
	};
}
#endif // GROUPINFORMEMBERSAREA_H
