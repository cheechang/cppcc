#include "WindowsManager.h"
#include <QApplication>
#include <QTextCodec>
#include <QPixmapCache>
#include <QTranslator>
#include <QDesktopServices>
#include <log.h>
#include <interface/IControlClient.h>
#include <interface/IAuthControl.h>
#include <QDir>
#include <QProcess>
#include <QFontDatabase>
#include <QMessageBox>
#include "BaseDialog.h"
#include "loginwindow/LoginWindow.h"
#include "mainwindow/MainWindow.h"
#include "updatewindow/UpdateWindow.h"
#include "utils/common.h"
#include "common/controlptr.h"
#include "common/ServiceInfos.hpp"
#include "../mainwindow/tray/SystemTray.h"
#include "common/ChineseInfos.h"
#include "common/Common.h"
#include "qmessagebox.h"
#ifdef CLOUDDISK_ON
#include "../control/clouddisk/Interface/Exports.h"
#include "../control/clouddisk/Interface/ICloudDisk.h"
#endif

//�߷���
float gDdpi = 1.0;

QString gUserDataPath = "";
//�Զ���ȫ��ҵ������ָ��
CSharedPtr<control::IControlClient> g_controlclient = CNull;
#ifdef CLOUDDISK_ON
ICloudDiskControl_ptr m_clouddisk = nullptr;
#endif
CSharedPtr<service::IMClient> m_sdkPtr = nullptr;

int g_loginOut = 0; //���Ʋ��ظ��������µ�¼����Ϣ;  2019-5-30
namespace ui
{
	WindowsManager::WindowsManager(QObject* parent): QObject(parent),
	                                                 m_system_tray(CNull), m_isrestart(false)
	{
		QPixmapCache::setCacheLimit(1);
		InitSystemInfo();
		InitControlClient();
	}

	WindowsManager::~WindowsManager()
	{
		m_wndlist.clear();
		//ReleaseInstance(m_clouddisk.get());
	}

	//��ʼ��ϵͳϵͳ
	void WindowsManager::InitSystemInfo(void)
	{
		BEGIN;
		//���ñ����ʽ
		//QTextCodec *codec = QTextCodec::codecForName("System"); //System
		//QTextCodec::setCodecForLocale(codec); 
		///*QTextCodec::setCodecForTr(codec);
		//QTextCodec::setCodecForCStrings(codec);*/

		//�������԰�
		static QTranslator translator;
		bool bret = translator.load(QString(":/qm/qt_zh_CN"));
		qApp->installTranslator(&translator);

		//���ø߷���
		LoadHighDpiInfo();

		//�������԰�web��
		static QTranslator translatorWeb;
		bret = translatorWeb.load(QString(":/qm/web"));
		qApp->installTranslator(&translatorWeb);

		LoadLanguage();
		//����QSS��ʽ��
		QFile qss(":/qss/linkdood");
		bool flag = qss.open(QFile::ReadOnly);
		qApp->setStyleSheet(qss.readAll());
		qss.close();

		///QString info;
		///info = QString::number(bret) + "  " + QString::number(flag);

		////QMessageBox::information(0, "", info);

		//��������

		QFont font;
		font.setPixelSize(17); //������������С
		font.setFamily("Microsoft YaHei");
		font.setWeight(55);
		qApp->setFont(font);
		END;
	}

	void WindowsManager::LoadLanguage(void)
	{
		LOG_METHOD("WindowsManager::loadLanguage", LOG_FILE);
		static QTranslator translatortext;
		translatortext.load(QString(":/qm/widgets"));
		qApp->installTranslator(&translatortext);
	}

	//��ʼ��ҵ���
	void WindowsManager::InitControlClient(void)
	{
		BEGIN;
		ServiceInfos::Init();
		std::string userdatapath = QStandardPaths::writableLocation(QStandardPaths::DataLocation).toLocal8Bit().data();
		g_controlclient = control::getControlClient();
		if (CNull == g_controlclient)
		{
			AddLog(LOG_LEV_ERROR, "===��ʼ��ҵ������ʧ��=====");
			exit(-1);
		}
		utils::string_replace(userdatapath, "Linkdood", "CPPCC");
		g_controlclient->InitClient(userdatapath);
		//QString::fromLocal8Bit("");
		////gUserDataPath = QString::fromStdString(userdatapath); // 2019-5-28 ����ȫ��·��
		gUserDataPath = QString::fromLocal8Bit(userdatapath.c_str()); // 2019-9-5 ����ȫ��·��

		END;
	}

	void WindowsManager::Init()
	{
		BEGIN;
		g_loginOut = 0;
		//������������
		/*CSharedPtr<UpdateWindow> updatewnd = CMakePtr<UpdateWindow>();
		connect(updatewnd.get(), SIGNAL(signalExitClient(bool)),this, SLOT(onExitClient(bool)));
		m_wndlist.insert(UPDATE_WINDOW,updatewnd);
		updatewnd->CheckReplace();
		updatewnd->CheckUpdate();
		*/

		//����ϵͳ����
		m_system_tray = CMakePtr<SystemTray>();
		connect(m_system_tray.get(), SIGNAL(signalExitClient(bool)), this, SLOT(onExitClient(bool)));
		m_system_tray->show();

		//������½����
		CSharedPtr<LoginWindow> loginwindow = CMakePtr<LoginWindow>();
		connect(m_system_tray.get(),
		        SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		        loginwindow.get(),
		        SLOT(onIconIsActived(QSystemTrayIcon::ActivationReason)));
		CONNECT_SUBCTRL(loginwindow, loginSuccess());
		loginwindow->show();
		m_wndlist.insert(LOGIN_WINDOW, loginwindow);
		END;
	}

	void WindowsManager::onloginSuccess()
	{
		BEGIN;
		g_loginOut = 0;
		//���ٵ�½����
		m_wndlist.remove(LOGIN_WINDOW);

		//����������
		CSharedPtr<MainWindow> mainwindow = CMakePtr<MainWindow>();
		connect(mainwindow.get(), SIGNAL(loginOut(bool)), this, SLOT(onExitClient(bool)));
		if (CNull != m_system_tray)
		{
			IUserControl_Ptr userPtr = USERCONTROL;
			std::shared_ptr<data::AccountInfo> acc = userPtr->GetAccountInfo();

			IAuthControl_Ptr auth = AUTHCONTROL;
			std::vector<data::AuthInfo> account = auth->getLoginInfos();
			data::AuthInfo curent;
			if (account.size() > 0)
			{
				curent = account.at(0);
			}
			m_system_tray->SetTrayToolTip(acc->name.value(), curent.server);
			m_system_tray->setIconState(SystemTray::Online);
			connect(m_system_tray.get(), SIGNAL(activated(QSystemTrayIcon::ActivationReason)), mainwindow.get(),
			        SLOT(onIconIsActived(QSystemTrayIcon::ActivationReason)));
			connect(mainwindow.get(), SIGNAL(signalNotifyTrayFlash(bool)), m_system_tray.get(), SLOT(setFlash(bool)));
		}
		mainwindow->ShowWidget();

		m_system_tray->resetMsgTipWinPos();
		m_wndlist.insert(MAIN_WINDOW, mainwindow);
		END;
	}

	void WindowsManager::restart_process()
	{
		QString appPath("");
		BEGIN;
		if (!m_isrestart)
		{
			AddLog(LOG_LEV_DEBUG, "����Ҫ�������̣��˳�");
			return;
		}
		appPath = QCoreApplication::applicationDirPath();
#if  defined(__linux__) || defined(__APPLE__)
		if ( -1 != g_accountname.find("Global@") && !access((char*)g_accountname.data(), F_OK))
		{
			int ret = remove((char*)g_accountname.c_str());
			if (-1 == ret)
			{
				Log(LOG_LEV_ERROR, LOG_FILE, "delete file[%s] failed", g_accountname.c_str());
			}
		}
#endif
#ifdef WIN32
		appPath.append("/CPPCC.exe");
#else
		appPath.append("/CPPCC");
#endif // WIN32
		bool bret = QProcess::startDetached(appPath, QStringList(appPath));
		if (!bret)
		{
			AddLog(LOG_LEV_ERROR, "restart progress failed,[appPath=%s],errcode=%d", appPath.toLocal8Bit().data(),
			       GetLastError());
		}
		END;
	}

	void WindowsManager::onExitClient(bool isrestart)
	{
		BEGIN;
		if (g_loginOut) return;
		///utils::is_same_account_ReleaseMutex();
		g_loginOut = 1;
		m_isrestart = isrestart;

		qApp->exit(888); //����exit()���˳�Ӧ�ó��� 
		END;
	}
}
