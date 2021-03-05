#include "UpdateTray.h"
#include <QMenu>
#include <QTimer>
#include "UpdateProgressWindow.h"
#include "../common/Common.h"
namespace ui{
	UpdateTray::UpdateTray(QObject*parent):QSystemTrayIcon(parent){
	  tray_menu = new QMenu();
	  tray_menu->setFixedWidth(80);

	  action_quit = new QAction(this);
	  tray_menu->addAction(action_quit);
	  connect(action_quit, SIGNAL(triggered()), this, SIGNAL(signalQuit()));
	  connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
		  SLOT(onActivated(QSystemTrayIcon::ActivationReason)));
	  this->setIcon(QIcon(":/base/update"));
	  this->setContextMenu(tray_menu);
	  translateLanguage();
	}
	UpdateTray::~UpdateTray(){

	}
	void UpdateTray::onActivated(QSystemTrayIcon::ActivationReason reason)
	{
		switch(reason)
		{
			//点击托盘图标之后松开
		case QSystemTrayIcon::Trigger:{
				emit signalShow();
				break; 
			}
			//双击托盘图标
		case QSystemTrayIcon::DoubleClick:
			{
				emit signalShow();
				break; 
			}               
		default:
			break;
		}
	}
	void UpdateTray::translateLanguage(){
		action_quit->setText(transfer("退出"));
	}
	void UpdateTray::showTipInfo(QString& content,bool isexittray){
		this->showMessage(transfer("升级更新"),content,Information,10000);
		if (isexittray)
		{
			QTimer::singleShot(10000,this,SLOT(onQuit()));
		}
	}
	void UpdateTray::onQuit(){
		this->hide();
	}
	void UpdateTray::onShowErrInfo(int errtype){
		QString errInfo;
		bool isexit = false;
		switch(errtype){
		case UpdateProgressWindow::ERR_DOWNLOADFAILED:
			{
				errInfo = transfer("由于网络原因升级包下载失败,请检查您的网络是否正常,稍后重试!");
				break;
			}
		case UpdateProgressWindow::ERR_CHECKCOMPLETEFAILED:
			{
				errInfo = transfer("升级包安全性校验失败，请联系管理员!");
				break;
			}
		case UpdateProgressWindow::ERR_USERCANCEL:
			{
				errInfo = transfer("用户取消升级包下载");
				isexit = true;
				break;
			}
		default:
			{
				errInfo = transfer("未知原因");
			}
		}
		showTipInfo(errInfo,isexit);
	}
}