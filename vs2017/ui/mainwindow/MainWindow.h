#pragma once
#include <core/BaseDialog.h>
#include "tray/SystemTray.h"
#include "chat/bubble/BurnMsgWin.h"
#include <QtWebEngineWidgets/QWebEngineView>
#include <QHBoxLayout>
class QLocalServer;
class QStackedWidget;

namespace ui{
	class TitleWidget;
	class ChatPage;
	class DefaultWidget;
	class ContactWidget;
	class ContactWidgetWeb;
	class ContactWidgetWeb_my;
	class LocalSearchListWidget;
	class LocalSearchLineEdit;
	class PushButton;
	class MainWeb;
	class Workbench;
	class CreateGroupContacts;
	class MainWindow:public BaseDialog{
		Q_OBJECT
	public:
	    enum Direction{
			UP = 0,
			DOWN=1,
			LEFT,
			RIGHT,
			LEFTTOP,
			LEFTBOTTOM,
			RIGHTBOTTOM,
			RIGHTTOP,
			NONE
		};
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		bool IsRunning();
		void ChangeSkin(QString skin_name);
		void setSupportStretch(bool isSupportStretch);
		static bool mIsCurChatPage;
	signals:
		void signalNotifyTrayFlash(bool flash);
		void showAvatar();
		void signalSerBeForcedToOffLine(const data::OnlineState&);
		void loginOut(bool restart);
		void signalSerUpFile(CSharedPtr<data::ChatInfo>&chat,QString filepath);
		void signalSerOpenChat(int64);
		void signalSerCloseWeb();
	public slots:
		void onNewLocalConnection();
		void onTurnPage(int current_page);
		void onIconIsActived(QSystemTrayIcon::ActivationReason reason);
		void ShowWidget();
		void onShowMax();
		void onShowMin();
		void onNotifyTrayFlash(bool flash);
		void onSerBeForcedToOffLine(const data::OnlineState&states);
		void onTurnChatPage();
		void onSearchTextChanged(const QString&text);
		void onSearchBtnClicked();
		void onShowAvatar();
		void onViewBurnMsg(CSharedPtr<data::Msg>& msg);
		void onBtnAdvaceSearch();

		//窗口抖动
		void StartShakeWindow();  
		void onStartShakeTimerOut();

		void onZxSerchResult(std::vector<data::ChatInfo>datas);
		void onSerOpenChatWidget(int64 targetid);
	protected:


		virtual void paintEvent(QPaintEvent *event);
		bool eventFilter(QObject *obj, QEvent *ev);
		void mousePressEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void region(const QPoint &cursorGlobalPoint);
		void updateWindowSize(QPoint& gloPoint,QMouseEvent *event);
	private:
		void InitLocalConnection();
		void initLocalSearchList();
		void initLocalSearchBox();
	private:
		bool		  m_isLeftPressDown;	  //按下鼠标左键
		Direction     m_direct;//朝向
	private:
		CSharedPtr<QStackedWidget> statked_widget;
		CSharedPtr<QLocalServer> server; 
		CSharedPtr<TitleWidget> title_widget;
		CSharedPtr<ChatPage> chat_widget; //聊天页面
		CSharedPtr<DefaultWidget> defalut_widget;
		CSharedPtr<ContactWidget> contact_widget;
		CSharedPtr<Workbench> m_WebWidget;
		CSharedPtr<ContactWidgetWeb> contact_widget_web;

	/////	CSharedPtr<ContactWidgetWeb_my> contact_widget_web_my;
		//////////QWebEngineView *m_webEngineView; // 2019
		//CSharedPtr<MainWeb> m_WebWidget;
		//CSharedPtr<Workbench> workbench_widget;
	    QString m_skin_name;//主窗口背景图片的名称
		bool m_is_running;
		bool m_isMax; //标示是否是最大化状态

		/***************以下本地搜索部分*********************/
	////	PushButton* m_searchBtnLogo;
    	QPushButton* mBtnLocalSearch;
	 	LocalSearchLineEdit* mLocalSearchLineEdit;
		QWidget*             mSearchBackground;
		IContactMgrControl_Ptr mContactMgrControl;
		LocalSearchListWidget* mLocalSearchList;
		/***************以上本地搜索部分*********************/
		//高级搜素
		QPushButton* mBtnAdvanceSearch;
		QWidget* mSearchBgWidget;
		CreateGroupContacts* mAdvanceWin;
		//窗口抖动
		QTimer* m_timer;
		QPoint m_curPos;
		int    m_nPosition;
		QPoint m_normalpos;



		QHBoxLayout  *initLocalSearchLayout();


		PushButton *m_max_button;
		QStackedWidget *search_stacked;


				/// 双击响应处理
		public:
			QTimer *mouse_timer;   //定时器
		signals:
			void clicked();
		public slots:
			void slotClicked();     //槽函数

			void mouseDoubleClickEvent(QMouseEvent * event);
	//双击
		public:
			void MaxWindow();
			int m_Current_Page;

	// 搜索
		QLabel *m_search_titleLabel;

	// web窗口调整
		public slots:
			void slotAdjustWebWindow(int action);
		/// 
			void closeMainWindow();

	};
}