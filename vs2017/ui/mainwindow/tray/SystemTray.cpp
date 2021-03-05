#include "SystemTray.h"
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QWidgetAction>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include <utils/common.h>
#include <QTimer>
#include <QDesktopWidget>
#include <QApplication>
#include "log.h"
#include "common/Common.h"
#include "../chat/TrayUnreadMsgTipWin.h"
namespace ui{
SystemTray::SystemTray(QWidget *parent):QSystemTrayIcon(parent),m_isloginoff(false)
{
	this->createAction();
	//this->createTopAction();
	//this->createBottomAction();
	this->addActions();
	this->translateLanguage();
	m_authcontrol = AUTHCONTROL;
}

SystemTray::~SystemTray()
{

}

void SystemTray::createAction()
{
	this->setIconState(OffLine);

	tray_menu = new QMenu();
	//action_open = new QAction(this);
	//action_help_center = new QAction(this);
	//action_kill_mummy = new QAction(this);
	//action_clear = new QAction(this);
	//action_optimize = new QAction(this);
	//action_fireproof = new QAction(this);
	//action_show_speed = new QAction(this);
	//action_soft_manage = new QAction(this);
	//action_safe_notice = new QAction(this);
	//action_rise = new QAction(this);
	//action_login = new QAction(this);
	//action_separate = new QAction(this);
	action_logout = new QAction(this);
	action_loginoff = new QAction(this);
	m_pTimer = new QTimer(this);

	mMsgTipWinTimer = new QTimer(this);
	mMsgTipWinTimer->setInterval(200);
	mMsgTipWinTimer->setSingleShot(false);
	connect(mMsgTipWinTimer, SIGNAL(timeout()), this, SLOT(onMouseEnterIconEvent()));
	mMsgTipWinTimer->start();

	tray_menu->setFixedWidth(80);
	m_pTimer->setSingleShot(false);
	m_pTimer->setInterval(650);
	
	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
		SLOT(onActivated(QSystemTrayIcon::ActivationReason)));
	connect(action_logout, SIGNAL(triggered()), this, SLOT(onLoginOut()));
	connect(action_loginoff, SIGNAL(triggered()), this, SLOT(onLoginOff()));
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(flash()));
	this->setContextMenu(tray_menu);
}

void SystemTray::createTopAction()
{/*
	top_widget = new QWidget();
	top_widget_action = new QWidgetAction(tray_menu);
	protect_label = new QLabel();
    open_button = new QPushButton();
    enter_button = new QPushButton();

	protect_label->setObjectName("whiteLabel");
	open_button->setObjectName("trayButton");
	enter_button->setObjectName("trayButton");

	open_button->setCursor(Qt::PointingHandCursor);
	enter_button->setCursor(Qt::PointingHandCursor);

	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(open_button);
	layout->addStretch();
	layout->addWidget(enter_button);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout *v_layout = new QVBoxLayout();
	v_layout->addWidget(protect_label);
	v_layout->addLayout(layout);
	v_layout->setSpacing(10);
	v_layout->setContentsMargins(10, 5, 10, 5);
	top_widget->setLayout(v_layout);
	top_widget_action->setDefaultWidget(top_widget);
	top_widget->installEventFilter(this);*/

}

void SystemTray::createBottomAction()
{/*
	bottom_widget = new QWidget();
	bottom_widget_action = new QWidgetAction(tray_menu);
    game_mode_button = new QPushButton();
    online_mode_button = new QPushButton();

	game_mode_button->setObjectName("trayButton");
	online_mode_button->setObjectName("trayButton");

	game_mode_button->setCursor(Qt::PointingHandCursor);
	online_mode_button->setCursor(Qt::PointingHandCursor);

	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(game_mode_button);
	layout->addStretch();
	layout->addWidget(online_mode_button);
	layout->setSpacing(0);
	layout->setContentsMargins(10, 5, 10, 5);

	bottom_widget->setLayout(layout);
	bottom_widget_action->setDefaultWidget(bottom_widget);
	bottom_widget->installEventFilter(this);
	*/
}

void SystemTray::addActions()
{
	//添加菜单项
	//tray_menu->addAction(top_widget_action);
	//tray_menu->addAction(action_open);
	//tray_menu->addAction(action_help_center);
	//tray_menu->addSeparator();
	//tray_menu->addAction(action_kill_mummy);
	//tray_menu->addAction(action_clear);
	//tray_menu->addSeparator();
	//tray_menu->addAction(action_optimize);
	//tray_menu->addAction(action_fireproof);
	//tray_menu->addAction(action_show_speed);
	//tray_menu->addAction(action_soft_manage);
	//tray_menu->addSeparator();
	//tray_menu->addAction(action_safe_notice);
	//tray_menu->addAction(action_rise);
	//tray_menu->addAction(action_login);
	//tray_menu->addAction(action_separate);
	tray_menu->addAction(action_loginoff);
	tray_menu->addAction(action_logout);
	//tray_menu->addAction(bottom_widget_action);
}

void SystemTray::translateLanguage()
{
	//放在托盘图标上时候显示
	this->setToolTip(APP_NAME);

	//protect_label->setText(transfer("protect") + QString::number(3) + transfer("day"));
    //open_button->setText(transfer("firewall start"));
    //enter_button->setText(transfer("enter"));

	//game_mode_button->setText(transfer("game mode"));
    //online_mode_button->setText(transfer("online mode"));

	//action_open->setText(transfer("open"));
	//action_help_center->setText(transfer("help center"));
	//action_kill_mummy->setText(transfer("kill mummy"));
	//action_clear->setText(transfer("clear"));
	//action_optimize->setText(transfer("optimize"));
	//action_fireproof->setText(transfer("fireproof"));
	//action_show_speed->setText(transfer("show speed"));
	//action_soft_manage->setText(transfer("soft manage"));
	//action_safe_notice->setText(transfer("safe notice"));
	//action_rise->setText(transfer("rise"));
	//action_login->setText(transfer("login"));
	//action_separate->setText(transfer("separate"));
	action_loginoff->setText(transfer("注销"));
	action_logout->setText(transfer("退出"));
}

void SystemTray::onActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch(reason)
	{
	//点击托盘图标之后松开
	case QSystemTrayIcon::Trigger:
		{
			setFlash(false);
			break;
		}    
	//双击托盘图标
	case QSystemTrayIcon::DoubleClick:
		{
			setFlash(false);
			break; 
		}               
	default:
		break;
	}
}

//设置图标闪烁
void SystemTray::setFlash(bool flash)
{
	ui::TrayUnreadMsgTipWin::isRrayFlash = flash;
	if (flash)
	{
		m_pTimer->start();
	}
	else
	{
		m_pTimer->stop();
		this->setIconState(Online);
	}
}

//图标闪烁动作
void SystemTray::flash(void)
{
	static bool flag = true;
	if(flag)
	{
		this->setIconState(Unread);
	}
	else
	{
		this->setIconState(None);
	}
	flag = !flag;
}

bool SystemTray::eventFilter(QObject *obj, QEvent *event)
{
	//if(obj == top_widget || obj == bottom_widget)
	//{
	//	if(event->type() == QEvent::Paint)
	//	{
	//		QPainter top_painter(top_widget);
	//		top_painter.setPen(Qt::NoPen);
	//		top_painter.setBrush(QColor(14, 116, 116));
	//		top_painter.drawRect(top_widget->rect());	

	//		QPainter bottom_painter(bottom_widget);
	//		bottom_painter.setPen(Qt::NoPen);
	//		bottom_painter.setBrush(QColor(14, 116, 116));
	//		bottom_painter.drawRect(bottom_widget->rect());	
	//	}
	//}
	return QSystemTrayIcon::eventFilter(obj, event);
}

void SystemTray::setIconState(TrayIconState state)
{
	switch(state)
	{
	//在线
	case Online:
		{
			this->setIcon(QIcon(":/base/tray"));
			break;
		}    
	//离线
	case OffLine:
		{
			this->setIcon(QIcon(":/base/tray-leave"));
			break; 
		}
	//未读
	case Unread:
		{
			this->setIcon(QIcon(":/base/tray-unread"));
			break; 
		}
	//空
	case None:
		{
			this->setIcon(QIcon());
			break; 
		}
	default:
		{
			this->setIcon(QIcon(":/base/tray"));
			break;
		}
	}
}
void SystemTray::logOut(){
	if (CNull != m_authcontrol)
	{
	   CONNECT_SERVICE(Logout(int));
	   m_authcontrol->logout(CBind(&SystemTray::signalSerLogout,this,CPlaceholders  _1));
	}

}
void SystemTray::onSerLogout(int err){
    UnClockProcess();
}
void SystemTray::onLoginOff(){

	extern void LogLoginMode(QString mode);
	LogLoginMode("MANUAL");  //设置下次为手动登陆; 

	m_isloginoff = true;
	m_authcontrol->logoff();
	UnClockProcess();
}
void SystemTray::onLoginOut(){
	logOut();
}

void SystemTray::SetTrayToolTip( const std::string name, const std::string ser )
{
    QString tool;
    tool.append(APP_NAME);
    tool.append("-");
    tool.append(QString::fromUtf8(name.data()));
    tool.append("@");
    tool.append(QString::fromUtf8(ser.data()));
    this->setToolTip(tool);
}

void SystemTray::UnClockProcess()
{
    BEGIN;
    //取消登陆，取消锁
#ifdef _WIN32
    utils::is_same_account_ReleaseMutex();
#else
    SingleApplication *single = SingleApplication::getInstance();
    single->detachApplication();
#endif // _WIN32
    emit signalExitClient(m_isloginoff);
    END;
}

void SystemTray::onMouseEnterIconEvent()
{
	QRect trayRect;
	trayRect = this->geometry();
	QPoint mouse = QCursor::pos();
	QRect winRect = ui::TrayUnreadMsgTipWin::Instance()->geometry();
	QRect screenrect = QApplication::desktop()->availableGeometry();
	if (trayRect.contains(mouse) && ui::TrayUnreadMsgTipWin::isRrayFlash)
	{
		//计算位置
		int dx = screenrect.width()-(trayRect.x()+trayRect.width());
		int x=0;
		if (dx>winRect.width())
		{
			x = trayRect.x() - winRect.width()/2;
		}else{
			x = screenrect.width() -winRect.width();
		}
		ui::TrayUnreadMsgTipWin::Instance()->setWinSize();
		ui::TrayUnreadMsgTipWin::Instance()->showWin(x);
	}else if (winRect.contains(mouse))
	{
		//
	}else
	{
		ui::TrayUnreadMsgTipWin::Instance()->hideWin();
	}
}

void SystemTray::resetMsgTipWinPos()
{
	QRect trayRect = this->geometry();
	QRect winRect = ui::TrayUnreadMsgTipWin::Instance()->geometry();
	QRect screenrect = QApplication::desktop()->availableGeometry();
	//计算位置
	int dx = screenrect.width()-(trayRect.x()+trayRect.width());
	int x=0;
	int y = screenrect.height() - winRect.height();
	if (dx>winRect.width())
	{
		x = trayRect.x() - winRect.width()/2;
	}else{
		x = screenrect.width() -winRect.width();
	}
	ui::TrayUnreadMsgTipWin::Instance()->move(x,y);
}

}