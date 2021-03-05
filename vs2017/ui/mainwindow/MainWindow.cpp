#include "MainWindow.h"
#include <QStackedWidget>
#include <QCoreApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QLocalServer>
#include <QLocalSocket>
#include <QIcon>
#include <QLayout>
#include "TitleWidget.h"
#include "common/common.h"
#include "chat/ChatPage.h"
#include "controls/DefaultWidget.h"
#include "contact/contactwidget.h"
#include "contact/contactwidgetWeb.h"
#include "contact/contactwidgetWeb_my.h"
#include "log.h"
#include "localsearch/LocalSearchListWidget.h"
#include  "localsearch/LocalSearchLineEdit.h"
#include  "controls/PushButton.h"
#include "./chat/TrayUnreadMsgTipWin.h"
#include "contact/createGroup/CreateGroupContacts.h"
#include "MainWeb.h"
#include <QSettings>
#include <QMessageBox>

int my_question_3(QString buttonYesText, QString buttonNoText, QString title, QString content)
{
	QMessageBox msg(QMessageBox::Question, title, content, QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	msg.setButtonText(QMessageBox::Yes, buttonYesText);
	msg.setButtonText(QMessageBox::No, buttonNoText);
	msg.setButtonText(QMessageBox::Cancel, transfer("取消"));
	msg.exec();
	if (msg.clickedButton() == msg.button(QMessageBox::Yes)) { return 0; }
	if (msg.clickedButton() == msg.button(QMessageBox::No)) { return 1; }
	return 2;
}

QWidget* g_MainWidget = nullptr;

namespace ui
{
	enum { MaxLimitTimes = 15 };

	enum { MaxLimitSpace = 5 };

	bool MainWindow::mIsCurChatPage = true;

	MainWindow::MainWindow(QWidget* parent): BaseDialog(parent), m_isLeftPressDown(false), m_direct(NONE),
	                                         statked_widget(CNull), server(CNull), m_WebWidget(CNull),
	                                         m_skin_name(DEFAULT_SKIN), m_is_running(false), m_isMax(false),
	                                         mAdvanceWin(CNull)
	{
		qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "7777"); /// 2019-4-14 
		this->setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		/////	QMessageBox::warning(this, transfer("提示"), transfer("1"));

		////setStyleSheet(QString::fromUtf8("border:1px solid grey"));
		setObjectName("mainWindow");
		///this->setMinimumSize(700, 690);
		InitLocalConnection();

		////		IUserControl_Ptr m_usercontrol; 
		/////		m_usercontrol = USERCONTROL;
		//////		CSharedPtr<data::AccountInfo> tuserinfo;
		/////		tuserinfo = m_usercontrol->GetAccountInfo();
		//////		int64 mCurrentUserId = tuserinfo->id.value();

		setWindowIcon(QIcon(":/base/linkdood"));
		m_skin_name = DEFAULT_SKIN;
		statked_widget = CMakePtr<QStackedWidget>(this); //层叠

		chat_widget = CMakePtr<ChatPage>(this); //对话框

		defalut_widget = CMakePtr<DefaultWidget>(this);

		title_widget = CMakePtr<TitleWidget>();

		contact_widget_web = CMakePtr<ContactWidgetWeb>(this);
		contact_widget = CMakePtr<ContactWidget>(this);

		////	contact_widget_web_my = CMakePtr<ContactWidgetWeb_my>(this);


		////m_webEngineView = NULL;
		//m_WebWidget = CMakePtr<MainWeb>();

		//workbench_widget = CMakePtr<Workbench>(this);

		QPalette palette;
		palette.setBrush(QPalette::Window, QBrush(Qt::gray));
		statked_widget->setPalette(palette);
		statked_widget->setAutoFillBackground(true);

		//statked_widget->addWidget(workbench_widget.get());
		statked_widget->addWidget(chat_widget.get());
		statked_widget->addWidget(contact_widget.get());
		statked_widget->addWidget(contact_widget_web.get());
		statked_widget->addWidget(defalut_widget.get());
		/////	statked_widget->addWidget(contact_widget_web_my.get());
		statked_widget->setContentsMargins(0, 0, 2, 2);
		/////statked_widget->setFixedWidth(800);


		QVBoxLayout* center_layout = new QVBoxLayout(); //中心区域
		/*
			 PushButton *min_button = new PushButton(this);
			PushButton *max_button = new PushButton(this);
			PushButton *close_button = new PushButton(this);
			min_button->setPicName(QString(":/title/min"));
			max_button->setPicName(QString(":/title/max"));
			close_button->setPicName(QString(":/title/close"));
	
			connect(min_button, SIGNAL(clicked()), this, SIGNAL(ShowWidget()));
			connect(max_button, SIGNAL(clicked()), this, SLOT(maxWiget()));
			connect(close_button, SIGNAL(clicked()), this, SIGNAL(hide()));
			close_button->setMinimumHeight(35);
			close_button->setMaximumHeight(35);
			QHBoxLayout *top_layout = new QHBoxLayout();
			top_layout->addStretch();
			top_layout->addWidget(min_button, 0, Qt::AlignVCenter);
			top_layout->setSpacing(5);
			top_layout->addWidget(max_button, 0, Qt::AlignVCenter);
			top_layout->setSpacing(5);
			top_layout->addWidget(close_button, 0, Qt::AlignVCenter);
			top_layout->setSpacing(5);
			top_layout->setContentsMargins(0, 0, 10, 0);
			center_layout->addLayout(top_layout); 
			*/
		center_layout->addLayout(initLocalSearchLayout());
		/////center_layout->setSpacing(20);
		center_layout->addWidget(statked_widget.get());
		///center_layout->setSpacing(0);
		center_layout->setContentsMargins(0, 0, 0, 0);


		QVBoxLayout* title_layout = new QVBoxLayout(); //title


		title_layout->addWidget(title_widget.get());


		title_layout->setContentsMargins(0, 0, 0, 0);

		QWidget* title_widget_pre = new QWidget(this);
		title_widget_pre->setLayout(title_layout);
		title_widget_pre->setObjectName("TitleBg");
		/// 左边框的宽度设置
		title_widget->setFixedWidth(80); // 60);
		title_widget_pre->setFixedWidth(80); // (60);


		//QVBoxLayout *main_layout = new QVBoxLayout();
		QHBoxLayout* main_layout = new QHBoxLayout();
		//main_layout->addStretch();
		///main_layout->addLayout(title_layout);
		main_layout->addWidget(title_widget_pre);
		main_layout->addLayout(center_layout);
		main_layout->setSpacing(0);
		main_layout->setContentsMargins(0, 0, 2, 2);
		setLayout(main_layout);

		connect(chat_widget.get(),SIGNAL(signalShakeWin()), this,SLOT(StartShakeWindow()));
		connect(chat_widget.get(), SIGNAL(viewBurnMsg(CSharedPtr<data::Msg>&)),
		        this, SLOT(onViewBurnMsg(CSharedPtr<data::Msg>&)));
		connect(chat_widget.get(),SIGNAL(signalNotifyTrayFlash(bool)), this,SLOT(onNotifyTrayFlash(bool)));
		connect(this, SIGNAL(signalWindowDeactivate()), chat_widget.get(), SLOT(onMainWindowDeactivate()));
		/// 2019-3
		connect(contact_widget_web.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),
		        chat_widget.get(), SLOT(onStartChat(CSharedPtr<data::ChatInfo>&)));
		connect(contact_widget_web.get(), SIGNAL(signalGroupRefreshSecret(int8, const data::Group&)),
		        chat_widget.get(), SLOT(signalGroupRefreshSecret(int8, const data::Group&)));
		connect(contact_widget_web.get(), SIGNAL(signalSerDelUiFile(int64, int64)), chat_widget.get(),
		        SLOT(onSerDelUiFile(int64, int64)));

		connect(contact_widget_web.get(), SIGNAL(closeWidget()), this, SLOT(hide()));
		connect(contact_widget_web.get(), SIGNAL(maxWiget()), this, SLOT(onShowMax()));
		connect(contact_widget_web.get(), SIGNAL(loginOut(bool)), this, SIGNAL(loginOut(bool)));

		//<==
		/// 调整窗口收缩消息

		connect(title_widget.get(), SIGNAL(signalAdjustWebWindow(int)), contact_widget_web.get(),
		        SLOT(slotAdjustWebWindow(int )));
		connect(title_widget.get(), SIGNAL(signalAdjustWebWindow(int)), this, SLOT(slotAdjustWebWindow(int)));
		///<=====


		connect(contact_widget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),
		        chat_widget.get(), SLOT(onStartChat(CSharedPtr<data::ChatInfo>&)));
		connect(contact_widget.get(), SIGNAL(signalGroupRefreshSecret(int8, const data::Group&)),
		        chat_widget.get(), SLOT(signalGroupRefreshSecret(int8, const data::Group&)));
		connect(contact_widget.get(), SIGNAL(signalSerDelUiFile(int64,int64)), chat_widget.get(),
		        SLOT(onSerDelUiFile(int64,int64)));


		connect(chat_widget.get(), SIGNAL(turnPage(int)), title_widget.get(), SLOT(onTurnPage(int)));
		connect(title_widget.get(), SIGNAL(showMin()), this, SLOT(onShowMin()));
		connect(title_widget.get(), SIGNAL(closeWidget()), this, SLOT(hide()));
		connect(title_widget.get(), SIGNAL(maxWiget()), this, SLOT(onShowMax()));
		connect(title_widget.get(), SIGNAL(turnPage(int)), this, SLOT(onTurnPage(int)));
		connect(title_widget.get(),SIGNAL(startScreenShotProcess()), chat_widget.get(),SLOT(onStartScreenShot()));
		connect(title_widget.get(), SIGNAL(moveWindow(bool)), this, SLOT(onMoveWindow(bool)), Qt::DirectConnection);
		connect(chat_widget.get(),SIGNAL(unreadMsgCount(int)), title_widget.get(),SLOT(onUnreadMsgCountNotify(int)));
		connect(title_widget.get(), SIGNAL(signalSendMsgShot(int)), chat_widget.get(),SIGNAL(signalSendMsgShot(int)));
		connect(title_widget.get(), SIGNAL(startChat(CSharedPtr<data::ChatInfo>&, QString&)), chat_widget.get(),
		        SLOT(onSendSuggestionMsg(CSharedPtr<data::ChatInfo>&, QString&)));
		connect(title_widget.get(),SIGNAL(signalPlaySound(bool)), chat_widget.get(),SLOT(onMsgSoundPlay(bool)));
		connect(title_widget.get(),SIGNAL(showMsgWidget()), this,SLOT(ShowWidget()));
		connect(title_widget.get(),SIGNAL(sendMsgHotKeyUpdate(int)), chat_widget.get(),
		        SIGNAL(sendMsgHotKeyUpdate(int)));
		connect(title_widget.get(),SIGNAL(addContactOrCreateGroup(int)), contact_widget.get(),
		        SLOT(onShowAddContactOrCreateGroup(int)));
		////2019-3
		connect(title_widget.get(), SIGNAL(addContactOrCreateGroup(int)), contact_widget_web.get(),
		        SLOT(onShowAddContactOrCreateGroup(int)));

		connect(title_widget.get(), SIGNAL(turnPage(int)), contact_widget_web.get(), SLOT(onTurnPage(int)));


		connect(title_widget.get(), SIGNAL(turnPage(int)), contact_widget_web.get(), SLOT(onTurnPage(int)));


		title_widget->InitSetting();


		title_widget->turnPage("0");
		installEventFilter(this);

		///	initLocalSearchList();
		///	initLocalSearchBox();


		TrayUnreadMsgTipWin* trayWin = TrayUnreadMsgTipWin::Instance();
		connect(trayWin,SIGNAL(showMainWin()), this,SLOT(ShowWidget()));
		connect(trayWin,SIGNAL(signalNotifyTrayFlash(bool)), this,SIGNAL(signalNotifyTrayFlash(bool)));
		connect(trayWin,SIGNAL(trayMsgClicked(int64)), this,SLOT(onTurnChatPage()));

		mContactMgrControl = CONTACTMGRCONTROL;
		CONNECT_SERVICE(BeForcedToOffLine(const data::OnlineState&));
		if (mContactMgrControl)
		{
			mContactMgrControl->RegPresentCb(CBind(&MainWindow::signalSerBeForcedToOffLine, this,CPlaceholders _1));
		}

		//开启窗口拉升
		setSupportStretch(true);


		///this->showMinimized();

		// 计时器
		m_timer = new QTimer(this);
		connect(m_timer, SIGNAL(timeout()), this, SLOT(onStartShakeTimerOut()));
		m_timer->setInterval(40);

		////	QMessageBox::warning(this, transfer("提示"), transfer("初始化完成"));

		///
		///
		///mouse_timer = new QTimer(this);
		////connect(mouse_timer, SIGNAL(timeout()), this, SLOT(slotClicked()));
	}

	void MainWindow::slotAdjustWebWindow(int action)
	{
		if (m_Current_Page == APP_PAGE || m_Current_Page == WORKBENCH_PAGE)
		{
			search_stacked->setVisible((action) ? true : false);
		}
	}

	void MainWindow::slotClicked()
	{
		///mouse_timer->stop();
	}


	void MainWindow::mouseDoubleClickEvent(QMouseEvent* event)
	{
		///mouse_timer->stop();
		MaxWindow();
	}


	MainWindow::~MainWindow()
	{
	}

	void MainWindow::ShowWidget()
	{
		this->showNormal();
		this->raise();
		this->activateWindow();
		this->repaint();
	}

	void MainWindow::onTurnChatPage()
	{
		if (!mIsCurChatPage)
		{
			contact_widget_web.get()->HideWeb(); ///2019-5-19
			onTurnPage(CHAT_PAGE);
		}
	}

	void MainWindow::closeMainWindow()
	{
		int ret = my_question_3(transfer("退出"), transfer("最小化"), transfer("提示!"),transfer("是否退出应用?"));
		if (ret == 1)
		{
			emit hide();
			return;
		}
		if (ret == 0)
		{
			extern void LogLoginMode(QString mode);
			//LogLoginMode("MANUAL");  //设置下次为刷新手工登陆模式; 
			emit loginOut(false);
		}
	}

	void MainWindow::InitLocalConnection()
	{
		m_is_running = false;
		//QCoreApplication::setApplicationName(APP_NAME);  

		QCoreApplication::setApplicationName(APP_MARK);
		QString serverName = QCoreApplication::applicationName();

		QLocalSocket socket;
		socket.connectToServer(serverName);

		if (socket.waitForConnected(500))
		{
			m_is_running = true;
			return;
		}

		//连接不上服务器，就创建一个
		server = CMakePtr<QLocalServer>(this);
		connect(server.get(), SIGNAL(newConnection()), this, SLOT(onNewLocalConnection()));
		if (server->listen(serverName))
		{
			//防止程序崩溃时,残留进程服务,移除之  
			if (server->serverError() == QAbstractSocket::AddressInUseError && QFile::exists(server->serverName()))
			{
				QFile::remove(server->serverName());
				server->listen(serverName);
			}
		}
	}

	void MainWindow::onNewLocalConnection()
	{
		QLocalSocket* socket = server->nextPendingConnection();
		if (!socket)
			return;
		socket->waitForReadyRead(1000);
		delete socket;
		socket = CNull;
	}

	bool MainWindow::IsRunning()
	{
		return m_is_running;
	}

	void MainWindow::paintEvent(QPaintEvent* event)
	{
		BaseDialog::paintEvent(event);
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing); // 反锯齿;
		QPixmap pixmap(m_skin_name);
		pixmap = pixmap.scaled(this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH);
		painter.setBrush(QBrush(pixmap));
		painter.setPen(Qt::darkGray); //边框色
		painter.drawRoundedRect(
			QRect(SHADOW_WIDTH,SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH),
			SHADOW_WIDTH, SHADOW_WIDTH);

		if (mLocalSearchList)
		{
			int h = this->height() - 10;//-32
			mLocalSearchList->setFixedHeight(h);
		}
	}

	void MainWindow::ChangeSkin(QString skin_name)
	{
		this->m_skin_name = skin_name;
		update();
	}

	QString GetConfigContent()
	{
		QString systemdbPath = QCoreApplication::applicationDirPath() + QString::fromLocal8Bit("/ZXConfig.ini");
		if (UIUtils::IsFileExist(systemdbPath))
		{
			QSettings settings(systemdbPath, QSettings::IniFormat);
			return settings.value("addr/url").toString();
		}
		return "";
	}

	void mySleep(unsigned int msec)
	{
		QTime dieTime = QTime::currentTime().addMSecs(msec);
		while (QTime::currentTime() < dieTime)
			QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}

	void MainWindow::onTurnPage(int current_page)
	{
		extern int g_webRunning;
		int waittimes = 0;
		while (g_webRunning)
		{
			///  等待网页打开处理完成后才能切换. 30s 等待时间
			mySleep(100);
			if (waittimes > 300) break;
			waittimes++;
		}

		onShowAvatar(); //屏蔽搜索功能  2019-6-5

		if (CNull == statked_widget) return;
		mIsCurChatPage = (current_page == CHAT_PAGE) ? true : false;


		m_Current_Page = current_page;
		if (current_page == APP_PAGE)
		{
			mBtnAdvanceSearch->show();
			g_MainWidget = this;
			m_search_titleLabel->setText(transfer("搜索")); ///<=====
			mBtnAdvanceSearch->setText(transfer(" ")); //<=== 2019-814
			statked_widget->setCurrentWidget(contact_widget_web.get());
			mBtnLocalSearch->setToolTip(transfer("搜索内容"));
		}
		else if (current_page == CHAT_PAGE)
		{
			mBtnAdvanceSearch->show();
			m_search_titleLabel->setText(transfer("搜索"));
			mBtnAdvanceSearch->setText(transfer(" "));
			statked_widget->setCurrentWidget(chat_widget.get());
			mBtnLocalSearch->setToolTip(transfer("搜索联系人、组织成员和群"));
		}
		else if (current_page == CONTACT_PAGE)
		{
			mBtnAdvanceSearch->show();
			m_search_titleLabel->setText(transfer("搜索"));
			mBtnAdvanceSearch->setText(transfer(" "));
			statked_widget->setCurrentWidget(contact_widget.get());
			mBtnLocalSearch->setToolTip(transfer("搜索联系人、组织成员和群"));
		}
			/*else if(current_page == WORKBENCH_PAGE)
			{
				 statked_widget->setCurrentWidget(defalut_widget.get());
			}*/
		else if (current_page == WORKBENCH_PAGE)
		{
			mBtnAdvanceSearch->show();
			g_MainWidget = this;
			m_search_titleLabel->setText(transfer("搜索"));
			mBtnAdvanceSearch->setText(transfer(" "));
			statked_widget->setCurrentWidget(contact_widget_web.get());
			mBtnLocalSearch->setToolTip(transfer("搜索内容"));
		}
		this->update();
		//mBtnAdvanceSearch->hide();
	}

	void MainWindow::onIconIsActived(QSystemTrayIcon::ActivationReason reason)
	{
		switch (reason)
		{
			//点击托盘图标之后松开
		case QSystemTrayIcon::Trigger:
			//双击托盘图标
		case QSystemTrayIcon::DoubleClick:
			{
				ShowWidget();
				TrayUnreadMsgTipWin::Instance()->RemoveAllItems();
				break;
			}
		default:
			break;
		}
	}

	void MainWindow::MaxWindow()
	{
		QRect screenrect = QApplication::desktop()->availableGeometry();
		if (!m_isMax)
		{
			this->setGeometry(-SHADOW_WIDTH, -SHADOW_WIDTH, screenrect.width() + 2 * SHADOW_WIDTH,
			                  screenrect.height() + 2 * SHADOW_WIDTH);
			m_isMax = true;
			m_max_button->setPicName(QString(":/title/restore"));
		}
		else
		{
			int x = screenrect.x() + (screenrect.width() - WINDOW_WIDTH) / 2;
			int y = screenrect.y() + (screenrect.height() - WINDOW_HEIGHT) / 2;
			this->setGeometry(x, y, WINDOW_WIDTH, WINDOW_HEIGHT);
			m_isMax = false;
			m_max_button->setPicName(QString(":/title/max"));
		}
		//开启窗口拉升
		setSupportStretch(!m_isMax);
	}

	void MainWindow::onShowMax()
	{
		MaxWindow();
	}

	void MainWindow::onShowMin()
	{
		this->showMinimized();
	}

	bool MainWindow::eventFilter(QObject* obj, QEvent* event)
	{
		if (event->type() == QEvent::WindowActivate)
		{
			//ui::TrayUnreadMsgTipWin::isRrayFlash = false;
			emit signalNotifyTrayFlash(false);
		}
		if (event->type() == QEvent::MouseButtonRelease)
		{
			if (mLocalSearchList->isVisible())
			{
				emit showAvatar();
			}
		}
		if (event->type() == QEvent::Resize)
		{
			this->update();
		}
		return BaseDialog::eventFilter(obj, event);
	}

	void MainWindow::onNotifyTrayFlash(bool flash)
	{
		if (!isVisible() || !isActiveWindow() || !mIsCurChatPage)
		{
			//ui::TrayUnreadMsgTipWin::isRrayFlash = flash;
			emit signalNotifyTrayFlash(flash);
		}
	}

	void MainWindow::initLocalSearchList()
	{
		mLocalSearchList = new LocalSearchListWidget(this);
		mLocalSearchList->setVisible(false);
		//mLocalSearchList->setFixedSize(QSize(260,this->height()-title_widget->height()-10));
		//mLocalSearchList->setMinimumSize(QSize(240,this->height()-title_widget->height()-10));
		mLocalSearchList->setMinimumSize(QSize(290, 800)); // QSize(250, 700));
		//mLocalSearchList->move(5,title_widget->height()+5);

		mLocalSearchList->move(80, 32); // 60, 32);
		mLocalSearchList->setVisible(false);

		connect(mLocalSearchList, SIGNAL(hideLocalSearchList()), this, SLOT(onShowAvatar()));
		connect(this, SIGNAL(showAvatar()), this, SLOT(onShowAvatar()));

		connect(mLocalSearchList, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)),
		        chat_widget.get(), SLOT(onStartChat(CSharedPtr<data::ChatInfo>&)));
	}

	void MainWindow::onSearchTextChanged(const QString& text)
	{
		mLocalSearchList->searchFromLocal(text);
		mLocalSearchList->setVisible(true);
	}

	void MainWindow::onSearchBtnClicked()
	{
		//mSearchBackground->setVisible(true);
		if (m_Current_Page == APP_PAGE || m_Current_Page == WORKBENCH_PAGE)
		{
			contact_widget_web.get()->onSearchWeb();
			/// mBtnAdvanceSearch->hide();    2019-8-14
		}
		else
		{
			//mBtnAdvanceSearch->show();
			mLocalSearchList->setVisible(true);
			search_stacked->setCurrentWidget(mSearchBackground); //
		}
	}

	void MainWindow::onShowAvatar()
	{
		mSearchBackground->setVisible(false);
		mLocalSearchLineEdit->clearText();

		mLocalSearchList->setVisible(false);
		mLocalSearchList->clearList();
		search_stacked->setCurrentWidget(mSearchBgWidget); //mBtnLocalSearch
		////mBtnLocalSearch->setVisible(true);
	}

	void MainWindow::initLocalSearchBox()
	{
		/*mBtnLocalSearch = new QPushButton(this);
		mBtnLocalSearch->setObjectName("localsearchbtn");
		mBtnLocalSearch->setFixedHeight(22);
		m_searchBtnLogo = new PushButton(mBtnLocalSearch);
		m_searchBtnLogo->setPicName(":/title/search");
		m_searchBtnLogo->move(8,5);
		mBtnLocalSearch->setToolTip(transfer("搜索联系人、组织成员和群"));
		connect(mBtnLocalSearch,SIGNAL(clicked(bool)),this,SLOT(onSearchBtnClicked()));
		///mBtnLocalSearch->move(80,24);
		mBtnLocalSearch->move(100, 18);
		*/
		/*	mSearchBackground = new QWidget(this);
			mSearchBackground->setFixedSize(QSize(200,55));
			///mSearchBackground->setStyleSheet("background:rgb(19,52,83)");
			///mSearchBackground->setStyleSheet("background:rgb(39,104,194)");
			mSearchBackground->setStyleSheet("background:rgb(28,28,28");
			mSearchBackground->move(78,2);
		
			LocalSearchLineEdit *mLocalSearchLineEdit = new LocalSearchLineEdit(mSearchBackground);
			mSearchBackground->setVisible(false);
			mLocalSearchLineEdit->move(0,15);
			mLocalSearchLineEdit->setFixedSize(QSize(220,28));
			mLocalSearchLineEdit->setStyleSheet("background:white;border-radius:14px;");
			connect(mLocalSearchLineEdit,SIGNAL(clearBtnClicked()),this,SLOT(onShowAvatar()));
			connect(mLocalSearchLineEdit,SIGNAL(textChanged(const QString &)),this,SLOT(onSearchTextChanged( const QString&)));
			*/

		///	mBtnLocalSearch->setVisible(false);
		///	m_searchBtnLogo->setVisible(false);
	}

	void MainWindow::setSupportStretch(bool isSupportStretch)
	{
		return;
		this->setMouseTracking(isSupportStretch);

		if (CNull != title_widget)
		{
			title_widget->setSupportStretch(isSupportStretch);
		}
		if (CNull != chat_widget)
		{
			chat_widget->setSupportStretch(isSupportStretch);
		}
		if (CNull != statked_widget)
		{
			statked_widget->setMouseTracking(isSupportStretch);
			int count = statked_widget->count();
			for (int index = 0; index < count; ++index)
			{
				QList<QWidget*> widgetList = statked_widget->widget(index)->findChildren<QWidget*>();
				for each (QWidget* widget in widgetList)
				{
					widget->setMouseTracking(isSupportStretch);
				}

				QList<QListWidget*> widgetListList = statked_widget->widget(index)->findChildren<QListWidget*>();
				for each (QListWidget* widget in widgetListList)
				{
					widget->setMouseTracking(isSupportStretch);
				}
			}
		}
	}

	void MainWindow::onSerBeForcedToOffLine(const data::OnlineState& states)
	{
		IUserControl_Ptr userControl = USERCONTROL;
		int64 myseftId = 0;
		if (userControl != CNull)
		{
			CSharedPtr<data::AccountInfo> accountInfo = userControl->GetAccountInfo();
			if (accountInfo)
			{
				myseftId = accountInfo->id.value();
			}
		}
		if (states.userID == myseftId && states.deviceType == 1 && states.flag == 7)
		{
			QMessageBox msgBox;
			msgBox.setText(QString::fromLocal8Bit("修改密码成功,请重新登录"));
			msgBox.exec();
			emit loginOut(true);
			return;
		}

		if (states.userID == myseftId && states.deviceType == 1 && states.flag != 1)
		{
			extern void LogLoginMode(QString mode);
			QMessageBox::warning(this,transfer("提示"),transfer("您的账号已在另外一台电脑登录，您已被挤下线！"));
			LogLoginMode("MANUAL"); //设置下次为刷新手工登陆模式; 
			emit loginOut(true);
		}
	}

	void MainWindow::onViewBurnMsg(CSharedPtr<data::Msg>& msg)
	{
		BurnMsgWin burnMsgWin(CNull, msg);
		connect(&burnMsgWin, SIGNAL(startChat(CSharedPtr<data::ChatInfo>&)), chat_widget.get(),
		        SLOT(onStartChat(CSharedPtr<data::ChatInfo>&)));
		burnMsgWin.setParent(this);
		burnMsgWin.setFixedSize(width(), height());
		burnMsgWin.move(0, 0);
		burnMsgWin.exec();
	}

	void MainWindow::region(const QPoint& cursorGlobalPoint)
	{
		QRect rect = this->rect();
		QPoint tl = mapToGlobal(rect.topLeft());
		QPoint rb = mapToGlobal(rect.bottomRight());
		int x = cursorGlobalPoint.x();
		int y = cursorGlobalPoint.y();

		if (tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y)
		{
			// 左上角
			m_direct = LEFTTOP;
			this->setCursor(QCursor(Qt::SizeFDiagCursor));
		}
		else if (x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y())
		{
			// 右下角
			m_direct = RIGHTBOTTOM;
			this->setCursor(QCursor(Qt::SizeFDiagCursor));
		}
		else if (x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y())
		{
			//左下角
			m_direct = LEFTBOTTOM;
			this->setCursor(QCursor(Qt::SizeBDiagCursor));
		}
		else if (x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING)
		{
			// 右上角
			m_direct = RIGHTTOP;
			this->setCursor(QCursor(Qt::SizeBDiagCursor));
		}
		else if (x <= tl.x() + PADDING && x >= tl.x())
		{
			// 左边
			m_direct = LEFT;
			this->setCursor(QCursor(Qt::SizeHorCursor));
		}
		else if (x <= rb.x() && x >= rb.x() - PADDING)
		{
			// 右边
			m_direct = RIGHT;
			this->setCursor(QCursor(Qt::SizeHorCursor));
		}
		else if (y >= tl.y() && y <= tl.y() + PADDING)
		{
			// 上边
			m_direct = UP;
			this->setCursor(QCursor(Qt::SizeVerCursor));
		}
		else if (y <= rb.y() && y >= rb.y() - PADDING)
		{
			// 下边
			m_direct = DOWN;
			this->setCursor(QCursor(Qt::SizeVerCursor));
		}
		else
		{
			// 默认
			m_direct = NONE;
			this->setCursor(QCursor(Qt::ArrowCursor));
		}
	}

	void MainWindow::updateWindowSize(QPoint& gloPoint, QMouseEvent* event)
	{
		QRect rect = this->rect();
		QPoint tl = mapToGlobal(rect.topLeft());
		QPoint rb = mapToGlobal(rect.bottomRight());

		if (NONE != m_direct)
		{
			QRect rMove(tl, rb);
			switch (m_direct)
			{
			case LEFT:
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				break;
			case RIGHT:
				rMove.setWidth(gloPoint.x() - tl.x());
				break;
			case UP:
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case DOWN:
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			case LEFTTOP:
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case RIGHTTOP:
				rMove.setWidth(gloPoint.x() - tl.x());
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case LEFTBOTTOM:
				rMove.setHeight(gloPoint.y() - tl.y());
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				break;
			case RIGHTBOTTOM:
				rMove.setWidth(gloPoint.x() - tl.x());
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			default:
				break;
			}
			this->setGeometry(rMove);
		}
		else
		{
			BaseDialog::mouseMoveEvent(event);
		}
	}

	void MainWindow::mousePressEvent(QMouseEvent* event)
	{
		// 当前鼠标进入了以上指定的8个区域，并且是左键按下时才开始进行窗口拉伸;


		if (Qt::LeftButton == event->button())
		{
			m_isLeftPressDown = true;
			if (NONE != m_direct)
			{
				this->mouseGrabber();
			}
		}
		////mouse_timer->start(1000);
		BaseDialog::mousePressEvent(event);
	}

	void MainWindow::mouseReleaseEvent(QMouseEvent* event)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_isLeftPressDown = false;
			if (m_direct != NONE)
			{
				this->releaseMouse();
				this->setCursor(QCursor(Qt::ArrowCursor));
			}
		}
		BaseDialog::mouseReleaseEvent(event);
	}

	void MainWindow::mouseMoveEvent(QMouseEvent* event)
	{
		QPoint gloPoint = event->globalPos();
		if (!m_isLeftPressDown)
		{
			this->region(gloPoint);
		}
		else
		{
			if (m_isMax && m_isLeftPressDown && NONE == m_direct && title_widget->geometry().contains(
				event->pos()))
			{
				onShowMax();
				m_isLeftPressDown = false;
			}
			else if (!m_isMax && m_isLeftPressDown && NONE == m_direct && title_widget->geometry().contains(
				event->pos()))
			{
				BaseDialog::mouseMoveEvent(event);
				chat_widget->mainWinPosChanged();
			}
			updateWindowSize(gloPoint, event);
		}
		//if (m_isMax){
		//	onShowMax();
		//}
	}

	void MainWindow::StartShakeWindow()
	{
		BEGIN;
		if (m_timer->isActive())
		{
			return;
		}

		if (Qt::WindowMinimized == this->windowState() || !this->isVisible())
		{
			this->showNormal();
		}

		m_nPosition = 0;
		m_curPos = this->pos();

		this->raise();
		m_timer->start();
		END;
	}

	void MainWindow::onStartShakeTimerOut()
	{
		m_timer->stop();
		this->raise();
		if (m_nPosition < MaxLimitTimes)
		{
			++m_nPosition;
			AddLog(LOG_LEV_INFO,LOG_FILE, "onStartShakeTimerOut m_nPosition = %d", m_nPosition);
			switch (m_nPosition % 4)
			{
			case 1:
				{
					QPoint tmpPos(m_curPos.x(), m_curPos.y() - MaxLimitSpace);
					this->move(tmpPos);
					break;
				}
			case 2:
				{
					QPoint tmpPos(m_curPos.x() - MaxLimitSpace, m_curPos.y() - MaxLimitSpace);
					this->move(tmpPos);
					break;
				}
			case 3:
				{
					QPoint tmpPos(m_curPos.x() - MaxLimitSpace, m_curPos.y());
					this->move(tmpPos);
					break;
				}
			case 0:
			default:
				{
					this->move(m_curPos);
					break;
				}
			}
			m_timer->start();
		}
		else
		{
			this->move(m_curPos);
		}
	}

	void MainWindow::onSerOpenChatWidget(int64 targetid)
	{
		//signalSerOpenChat(targetid);
		//emit signalSerCloseWeb();
	}


	QHBoxLayout* MainWindow::initLocalSearchLayout()
	{
		QHBoxLayout* ql = new QHBoxLayout();
		search_stacked = new QStackedWidget();

		///	QPalette palette;
		////	palette.setBrush(QPalette::Window, QBrush(Qt::gray));
	   /// 	search_stacked->setPalette(palette);
		search_stacked->setObjectName("bg_fa");
		////	search_stacked->setAutoFillBackground(true);
			///search_stacked->setStyleSheet("background:rgb(247,247,247)");


		mBtnLocalSearch = new QPushButton();
		mBtnLocalSearch->setObjectName("localsearchbtn");
		////	mBtnLocalSearch->setStyleSheet("background:rgb(247,247,247)");
		////	mBtnLocalSearch->setFixedSize(QSize(180, 25));
			/////mBtnLocalSearch->move(2, 2);

		PushButton* m_searchBtnLogoWeb = new PushButton(mBtnLocalSearch);
		m_searchBtnLogoWeb->setPicName(":/title/search");
		m_searchBtnLogoWeb->move(8, 9);
		m_searchBtnLogoWeb->setFixedSize(10, 10);

		m_search_titleLabel = new QLabel(mBtnLocalSearch);
		QFont ft;
		ft.setPixelSize(11); //搜索框“‘搜索’字体大小”2020-8-24
		m_search_titleLabel->setFont(ft);
		m_search_titleLabel->setStyleSheet("color:black;");
		m_search_titleLabel->setText(transfer("搜索"));
		m_search_titleLabel->move(30, 5); //90，7搜索框位置坐标2020-8-24

		mBtnLocalSearch->setFixedWidth(300); // 240);// LeftContentWidth - 60);

		//mBtnLocalSearch->setToolTip(transfer("搜索联系人、组织成员和群"));
		connect(mBtnLocalSearch, SIGNAL(clicked(bool)), this, SLOT(onSearchBtnClicked()));


		//mBtnLocalSearch->setMinimumHeight(28);
		///mBtnLocalSearch->setMaximumHeight(35);

		mBtnAdvanceSearch = new QPushButton();
		mBtnAdvanceSearch->setText(transfer("    "));
		QHBoxLayout* layout = new QHBoxLayout(this);
		mBtnAdvanceSearch->setStyleSheet("QPushButton{background:transparent;font-size:12px;}");
		layout->addWidget(mBtnLocalSearch);
		layout->addWidget(mBtnAdvanceSearch);
		layout->setContentsMargins(0, 0, 0, 0);
		mBtnAdvanceSearch->setFixedSize(1, 30);
		mBtnAdvanceSearch->hide();
		//// mBtnAdvanceSearch->hide();       ///<===2019-8-14
		connect(mBtnAdvanceSearch, SIGNAL(clicked(bool)), this, SLOT(onBtnAdvaceSearch()));

		mBtnAdvanceSearch->setCursor(QCursor(Qt::PointingHandCursor)); //<===  2019-8-14
		mBtnLocalSearch->setCursor(QCursor(Qt::PointingHandCursor)); //<===


		mSearchBgWidget = new QWidget();
		mSearchBgWidget->setLayout(layout);
		search_stacked->addWidget(mSearchBgWidget);

		mSearchBackground = new QWidget();
		/////mSearchBackground->setFixedSize(QSize(260, 45));

		//////mSearchBackground->setStyleSheet("background:rgb(19,52,83");
		////mSearchBackground->move(0, 2);

		mLocalSearchLineEdit = new LocalSearchLineEdit(mSearchBackground);

		mSearchBackground->setVisible(false);

		mLocalSearchLineEdit->setFixedWidth(290); // (240);
		/////mLocalSearchLineEdit->setStyleSheet("background:white;border-radius:14px;");
		connect(mLocalSearchLineEdit, SIGNAL(clearBtnClicked()), this, SLOT(onShowAvatar()));
		connect(mLocalSearchLineEdit, SIGNAL(textChanged(const QString &)), this,
		        SLOT(onSearchTextChanged(const QString&)));

		search_stacked->addWidget(mSearchBackground);


		QHBoxLayout* search_layout = new QHBoxLayout();

		search_layout->addWidget(search_stacked);
		//search_layout->addWidget(mBtnAdvanceSearch);


		//search_layout->addStretch();
		search_stacked->setFixedSize(QSize(290, 32)); // QSize(250, 32));
		//////search_stacked->setMaximumSize(QSize(260, 32));

		PushButton* min_button = new PushButton(this);
		PushButton* max_button = new PushButton(this);
		PushButton* close_button = new PushButton(this);

		min_button->setPicName(QString(":/title/min"));
		max_button->setPicName(QString(":/title/max"));
		m_max_button = max_button;

		close_button->setPicName(QString(":/title/close"));

		connect(min_button, SIGNAL(clicked()), this, SLOT(onShowMin()));
		connect(max_button, SIGNAL(clicked()), this, SLOT(onShowMax()));
		////connect(close_button, SIGNAL(clicked()), this, SLOT(hide()));   

		connect(close_button, SIGNAL(clicked()), this, SLOT(closeMainWindow())); // 2019-7-6
		QWidget* top = new QWidget();
		//top->setObjectName("bg_fa");
		top->setObjectName("groupinfobackground");

		QHBoxLayout* top_layout = new QHBoxLayout();
		top_layout->addStretch();
		top_layout->addWidget(min_button, 0, Qt::AlignVCenter);
		top_layout->setSpacing(5);
		top_layout->addWidget(max_button, 0, Qt::AlignVCenter);
		top_layout->setSpacing(5);
		top_layout->addWidget(close_button, 0, Qt::AlignVCenter);
		top_layout->setSpacing(5);
		top_layout->setContentsMargins(0, 0, 5, 0);
		close_button->setFixedSize(30,30);//（2020年8月31日）
		min_button->setFixedSize(30, 30);//（2020年8月31日）
		max_button->setFixedSize(30, 30);//（2020年8月31日）

		top->setLayout(top_layout);

		// search_layout->addLayout(top_layout);
		search_layout->addWidget(top);

		search_layout->setContentsMargins(0, 0, 0, 0);

		initLocalSearchList();
		initLocalSearchBox();


		return search_layout;


		///return search_layout;
		///mBtnLocalSearch->move(80,24);
		/*mBtnLocalSearch->move(100, 18);
		mSearchBackground = new QWidget(this);
		mSearchBackground->setFixedSize(QSize(240, 55));
		///mSearchBackground->setStyleSheet("background:rgb(19,52,83)");
		///mSearchBackground->setStyleSheet("background:rgb(39,104,194)");
		mSearchBackground->setStyleSheet("background:rgb(28,28,28");
		mSearchBackground->move(78, 2);
	
		mLocalSearchLineEdit = new LocalSearchLineEdit(mSearchBackground);
		mSearchBackground->setVisible(false);
		mLocalSearchLineEdit->move(0, 15);
		mLocalSearchLineEdit->setFixedSize(QSize(220, 28));
		mLocalSearchLineEdit->setStyleSheet("background:white;border-radius:14px;");
		connect(mLocalSearchLineEdit, SIGNAL(clearBtnClicked()), this, SLOT(onShowAvatar()));
		connect(mLocalSearchLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(onSearchTextChanged(const QString&)));
		*/
	}

	void MainWindow::onBtnAdvaceSearch()
	{
		if (m_Current_Page == APP_PAGE || m_Current_Page == WORKBENCH_PAGE)
		{
			///<=======2019-8-14
			contact_widget_web.get()->onSearchWeb();
			return;
		}


		if (mAdvanceWin == CNull)
		{
			mAdvanceWin = new CreateGroupContacts;
			mAdvanceWin->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
			connect(mAdvanceWin, SIGNAL(signalZxSerchResult(std::vector<data::ChatInfo>)),
			        this, SLOT(onZxSerchResult(std::vector<data::ChatInfo>)));
		}
		mAdvanceWin->setHighSearch();
		mAdvanceWin->showNormal();
	}

	void MainWindow::onZxSerchResult(std::vector<data::ChatInfo> datas)
	{
		mAdvanceWin->close();
		mLocalSearchList->setVisible(true);
		mLocalSearchList->setData(datas);
	}
}
