#ifndef CONTACTTABWIDGETAREA_WEB_H
#define CONTACTTABWIDGETAREA_WEB_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <data/entpriseInfo.h>
#include <data/ContactData.h>
#include <data/ChatData.h>
namespace ui{
	class EnterpriseWidget;
	class GroupListWidget;
	class FriendListWidgetWeb;

	class ContactTabWidgetAreaWeb : public QWidget
	{
		Q_OBJECT

	public:
		ContactTabWidgetAreaWeb(QWidget *parent = CNull);
		~ContactTabWidgetAreaWeb();
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
		FriendListWidgetWeb * m_friendListWidget;

		CSharedPtr<QVBoxLayout> m_mainLayout;
		CSharedPtr<QTabWidget> m_tabWidget;
	};
}

#endif // CONTACTTABWIDGETAREA_WEB_H
