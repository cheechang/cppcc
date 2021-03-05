#ifndef CONTACTTABWIDGETAREA_H
#define CONTACTTABWIDGETAREA_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <data/entpriseInfo.h>
#include <data/ContactData.h>
#include <data/ChatData.h>
namespace ui{
	class EnterpriseWidget;
	class GroupListWidget;
	class FriendListWidget;

	class ContactTabWidgetArea : public QWidget
	{
		Q_OBJECT

	public:
		ContactTabWidgetArea(QWidget *parent=CNull);
		~ContactTabWidgetArea();
	signals:
		void startChat(CSharedPtr<data::ChatInfo>&chat);
		void showOrgUserInfoPage(data::OrgAndUserInfo user);
		void showGroupInforPage(int64 groupId);
		void showContactInfoPage(data::Contact);
	protected:
		void paintEvent(QPaintEvent *event);
	private:
		void initEnterpriseWidget();
		EnterpriseWidget* m_enterpriseWidget;

		void initGroupWidget();
		GroupListWidget* m_groupListWidget;

		void initFriendWidget();
		FriendListWidget* m_friendListWidget;

		CSharedPtr<QVBoxLayout> m_mainLayout;
		CSharedPtr<QTabWidget> m_tabWidget;
	};
}

#endif // CONTACTTABWIDGETAREA_H
