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
			//�������ͼ��֮���ɿ�
		case QSystemTrayIcon::Trigger:{
				emit signalShow();
				break; 
			}
			//˫������ͼ��
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
		action_quit->setText(transfer("�˳�"));
	}
	void UpdateTray::showTipInfo(QString& content,bool isexittray){
		this->showMessage(transfer("��������"),content,Information,10000);
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
				errInfo = transfer("��������ԭ������������ʧ��,�������������Ƿ�����,�Ժ�����!");
				break;
			}
		case UpdateProgressWindow::ERR_CHECKCOMPLETEFAILED:
			{
				errInfo = transfer("��������ȫ��У��ʧ�ܣ�����ϵ����Ա!");
				break;
			}
		case UpdateProgressWindow::ERR_USERCANCEL:
			{
				errInfo = transfer("�û�ȡ������������");
				isexit = true;
				break;
			}
		default:
			{
				errInfo = transfer("δ֪ԭ��");
			}
		}
		showTipInfo(errInfo,isexit);
	}
}