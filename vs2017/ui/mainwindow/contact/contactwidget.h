#ifndef CONTACTWIDGET_H
#define CONTACTWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QMenu>
#include <QAction>
#include "controls/ToolButton.h"

#include <data/entpriseInfo.h>
#include <data/GroupData.h>
#include <data/ContactData.h>
namespace data{
	class ChatInfo;
}
namespace control{
	class IEntMgrControl;
}

namespace ui{
	class DefaultWidget;
	class EnterpriseInfoWidget;
	class ContactTabWidgetArea;
	class GroupInforWidget;
	class FriendInfoWidget;
	class AppInfoWidget;
	class SearchContactWindow;
	class CreateGroupWindow;
	class EnterpriseAccountList;
	class AppAccountList;
	class ContactWidget : public QWidget
	{
		Q_OBJECT
			enum{
				LeftContentWidth = 290,//250,
				RightContentWidth = 730//550
		};
	public:
		ContactWidget(QWidget *parent=CNull);
		~ContactWidget();
	signals:
		 void startChat(CSharedPtr<data::ChatInfo>&chat);
		 void signalSerDelUiFile(int64,int64);
	protected:
		  virtual void resizeEvent(QResizeEvent *e);
	protected slots:
		void onShowOrgUserInfoPage(data::OrgAndUserInfo user);
		void onShowGroupInforPage(int64 groupId);
		void onShowContactInfoPage(data::Contact contact);
		void onShowAddContactOrCreateGroup(int type);
		void onBtnAddClicked();
		void onBtnCreateGroup();
		void onBtnAddFrindOrGroup();

	public slots:
	// 显示好友信息  5-18
		void onShowUserInfo(int64 uid);
	private:
		CSharedPtr<ContactTabWidgetArea> m_leftTabWidgetArea;
		CSharedPtr<EnterpriseInfoWidget> m_enterpriseInfoWidget;
		CSharedPtr<GroupInforWidget> m_groupInforWidget;
		CSharedPtr<FriendInfoWidget> m_contactInfoWidget;
		CSharedPtr<AppInfoWidget> m_appInfoWidget;
		CSharedPtr<EnterpriseAccountList> m_enterpriseAccountList;
		CSharedPtr<AppAccountList> m_appAccountList;
		CSharedPtr<SearchContactWindow> m_searchContactWin;
		CreateGroupWindow*   mWinCreateGroup;
;
		CSharedPtr<DefaultWidget>    m_defaultWidget;
		CSharedPtr<QHBoxLayout> m_mainLayout;
		CSharedPtr<ToolButton> m_btnAddContact;
		CSharedPtr<QMenu>      m_menuMain;
		CSharedPtr<QAction>    m_actionCreateGroup;
		CSharedPtr<QAction>    m_actionAddGroupOrFriend;
 	};
}
#endif // CONTACTWIDGET_H
