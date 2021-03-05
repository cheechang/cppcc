#ifndef CONTACTWIDGET_WEB_MY_H
#define CONTACTWIDGET_WEB_MY_H

#include <QWidget>
#include <QHBoxLayout>
#include <QMenu>
#include <QAction>
#include "controls/ToolButton.h"

#include <data/entpriseInfo.h>
#include <data/GroupData.h>
#include <data/ContactData.h>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebChannel/qwebchannel.h>
#include <QtWebEngineWidgets/QWebEngineProfile>
#include "friend/FriendListWidgetWeb.h"
namespace data{
	class ChatInfo;
}
namespace control{
	class IEntMgrControl;
}
#include "contactwidgetWeb.h"

namespace ui{
	class DefaultWidgetWeb;
	class EnterpriseInfoWidget;
	class ContactTabWidgetAreaWeb;
	class GroupInforWidget;
	class FriendInfoWidgetWeb;
	class AppInfoWidget;
	class SearchContactWindow;
	class CreateGroupWindow;
	class EnterpriseAccountList;
	class AppAccountList;
	class PushButton;
	class ContactWidgetWeb_my : public QWidget
	{
		Q_OBJECT
			enum{
				LeftContentWidth = 250,
				RightContentWidth = 550
		};
	public:
		ContactWidgetWeb_my(QWidget *parent = CNull);
		~ContactWidgetWeb_my();
	signals:
		void startChat(CSharedPtr<data::ChatInfo>&chat);
		 ///void signalSerDelUiFile(int64,int64);
		void MySelectListItem(int item);
	protected:
		  virtual void resizeEvent(QResizeEvent *e);
	protected slots:
		//void onShowOrgUserInfoPage(data::OrgAndUserInfo user);
		///void onShowGroupInforPage(int64 groupId);
		void onShowContactInfoPage(data::Contact contact);
		///void onShowAddContactOrCreateGroup(int type);
		///void onBtnAddClicked();
		///void onBtnCreateGroup();
		///void onBtnAddFrindOrGroup();
		void onTurnPage(int i);
	private:
		///CSharedPtr<ContactTabWidgetAreaWeb> m_leftTabWidgetArea;
		///CSharedPtr<EnterpriseInfoWidget> m_enterpriseInfoWidget;
		////CSharedPtr<GroupInforWidget> m_groupInforWidget;


		////CSharedPtr<FriendInfoWidgetWeb> m_contactInfoWidget;


		/////CSharedPtr<AppInfoWidget> m_appInfoWidget;
		CSharedPtr<EnterpriseAccountList> m_enterpriseAccountList;
		////CSharedPtr<AppAccountList> m_appAccountList;
		/////CSharedPtr<SearchContactWindow> m_searchContactWin;
		/////CreateGroupWindow*   mWinCreateGroup;
;
		CSharedPtr<DefaultWidgetWeb>    m_defaultWidget;
		CSharedPtr<QHBoxLayout>         m_mainLayout;
		////CSharedPtr<ToolButton> m_btnAddContact;
		////CSharedPtr<QMenu>      m_menuMain;
		////CSharedPtr<QAction>    m_actionCreateGroup;
		////CSharedPtr<QAction>    m_actionAddGroupOrFriend;
		CSharedPtr<FriendListWidgetWeb> m_listWidget;

	public:
	 
		QWidget *m_MainWindow;
		QPoint  m_Pos;

	///  Js 交互
	CSharedPtr<QWebChannel> m_webchannel;  // 2019-3-23
    /// 接收的槽函

	public slots:
		void sendTextToCpp(const QString &text);
		 
	signals:
		void closeWidget();
		void maxWiget();

		void sendToWeb(const QString &taskid,const QString &text);

		void GetControlInfo(const QString &text);


	public slots:
		void OnGetControlInfo(const QString &text);

		void callQTProcess(const QString &taskid, const QString &text);

		void onMaxWiget();
	public:
		void onGetAppInfo(int64 code,data::EntAppinfo& app);

		void Reflush();
		QString m_AppInfo;
		QString m_TaskID;
 
		QHBoxLayout  *initLocalSearchLayout();



		bool m_ismax;
		PushButton *m_max_button;




 	};
}
#endif // CONTACTWIDGET_WEB_MY_H
