#ifndef CONTACTWIDGET_WEB_H
#define CONTACTWIDGET_WEB_H

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
#include "qdialog.h"
namespace data{
	class ChatInfo;
}
namespace control{
	class IEntMgrControl;
}
namespace ui{
	class WebDlg : public QDialog
	{
	Q_OBJECT
		public slots:
		   void callQTProcess(const QString &taskid, const QString &text);

		signals:
			void sendToWeb(const QString &taskid, const QString &text);
		public:
			QWebEngineView *m_webView;
			explicit  WebDlg(QWidget *parent = 0);
			~WebDlg();
			void init();
 			void openUrl(QString urlpath);
 	};
}




namespace ui{
	class ContactWidgetWeb;
	class DefaultWidgetWeb : public QWidget
	{
		Q_OBJECT
	public:
		explicit DefaultWidgetWeb(QWidget *parent = 0);
		~DefaultWidgetWeb();
		void setUrl(data::Contact  contact, QPoint pos, CSharedPtr<QWebChannel> *Channel);

		
	public slots:
		void loadFinished(bool flag);
		void downloadRequested(QWebEngineDownloadItem *download);

		void downloadFinished();

	public:
		////CSharedPtr<QWebEngineView> m_webEngineView;
		//void paintEvent(QPaintEvent *event);
		QWebEngineView *m_webEngineView;
		void resize();
		QPoint  m_pos;
		bool m_bUsing;

		bool m_bFinished;
 
	};
	class WebTitleWidget : public QWidget
	{
		Q_OBJECT
	public:
		explicit WebTitleWidget(QWidget *parent = 0);
		~WebTitleWidget();

	};
}
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
	class UserInfoCommon;
	class UserInfoCommitee;
	class ContactWidgetWeb : public QWidget
	{
		Q_OBJECT
			enum{
				LeftContentWidth = 290 ,// 250,
				RightContentWidth = 840// 550
		};
	public:
		ContactWidgetWeb(QWidget *parent = CNull);
		~ContactWidgetWeb();
	signals:
		void startChat(CSharedPtr<data::ChatInfo>&chat);
		 ///void signalSerDelUiFile(int64,int64);
		void MySelectListItem(int item);
	protected:
		  virtual void resizeEvent(QResizeEvent *e);
		  void ContactWidgetWeb::UnClockProcess();
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
		CSharedPtr<FriendListWidgetWeb> m_listWidget_my;

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
		void loginOut(bool restart);

	public slots:
		void OnGetControlInfo(const QString &text);

		void callQTProcess(const QString &taskid, const QString &text);

		void onMaxWiget();

	public:
		void onGetAppInfo(int64 code,data::EntAppinfo& app);
		
		void Reflush();
		QString m_AppInfo;
		QString m_TaskID;

		QString m_GroupID; //群ID
 
		QHBoxLayout  *initLocalSearchLayout();



		bool m_ismax;
		PushButton *m_max_button;


		void HideWeb();

		//get user info
	public:
		CSharedPtr<UserInfoCommon> m_pUserInfoCommomWidget;
		CSharedPtr<UserInfoCommitee> m_pUserInfoCommiteeWidget;
		void GetUserInfo(int64 UserID);
		IChatMgrControl_Ptr mChatMgrControl;
	signals:
		void signalSerGetUserInfo(int, data::UserData&);
		void signalSerChatListNotify(int flags, std::vector<CSharedPtr<data::ChatData>>&);
	protected slots:
		void onSerGetUserInfo(int, data::UserData&);
		void onSerChatListNotify(int flags, std::vector<CSharedPtr<data::ChatData>>&dataList);
		 

    // search
	public:
		void onSearchWeb();
		int  m_curApp;
	//adjust widnow

	public  slots:
	    void slotAdjustWebWindow(int action);
		
 	};
}
#endif // CONTACTWIDGET_WEB_H
