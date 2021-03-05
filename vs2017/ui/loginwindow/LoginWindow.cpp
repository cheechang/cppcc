#include "LoginWindow.h"
#include <QDesktopServices>
#include <QApplication>
#include <QUrl>
#include <QPropertyAnimation>
#include <interface/IControlClient.h>
#include <interface/IAuthControl.h>
#include "controls/headimage.h"
#include "controls/PushButton.h"
#include "controls/MyQComboBox.h"
#include "RegisterWindow.h"
#include "common/common.h"
#include "utils/common.h"
#include "TipWidget.h"
#include "log.h"
#include "../utils/functionconfig.h"
#include "LockoutAccount.h"
#include "ActivationAccount.h"
#include <QDateTime>
#include <qdir.h>

#include <QtGlobal>
#include <utils/Error.h>
#include "json.h"
#include "../common/Md5.h"
#include <QMessageBox>
#include <QNetworkInterface>
#include <QList>
#include <QTextCodec>
#include "../mainwindow/systemsetting/AboutInfo.h"
extern std::string gaccount;

extern QString gUserDataPath;
QString login_info; //  登陆返回权限内容
QString access_info; //  APP权限
QString g_access_token = "";
QString g_Mac = "12345678";
QString g_WebServerIP = "114.255.32.34"; //114.255.32.33
#define WEBSERVER_INI "web.ip"
#define LOGINUSER "login.user"
#define MAC_LOG   "mac.dat"

#define LOINGMODE "login.md"
// 获得当前登陆模式
// "0" 手动, "1" 自动, "2" , fe_Auto

QString APP_VERSION = "1.0.5"; //版本号    执行程序版本号

QString CUR_UPDATE_VERSION = "1.0.5"; //安装包版本号  (安装包的版本信息) version


ui::MyUpdateWindow* mUpdateWindows = nullptr;

void utf2gbk(QString& str, QByteArray& ch)
{
	QTextCodec* gbk = QTextCodec::codecForName("gbk");
	QTextCodec* utf8 = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForLocale(utf8);
	QString strUnicode1 = utf8->toUnicode(str.toLocal8Bit().data());
	ch = gbk->fromUnicode(strUnicode1);
	QTextCodec::setCodecForLocale(gbk);
}

QString LoadLastUpdateVersion()
{
	QString mpath = gUserDataPath + "/version.dat";
	QString version = APP_VERSION;
	QFile file(mpath);
	BOOL flag = file.open(QIODevice::ReadOnly | QIODevice::Text);
	if (flag)
	{
		version = file.readAll();
		file.close();
	}
	return version;
}

/*
void SaveLastUpdateVersion(QString info)
{
	QString mpath = gUserDataPath + "/version";
	QFile f(mpath);
	if (f.open(QIODevice::WriteOnly)){
		QByteArray str = info.toLatin1();
		f.write(str);
		f.close();
	}
	return;
}
*/
void SaveUpdateVersionLog(QString info)
{
	QString mpath = gUserDataPath + "/update/updatelast.log";
	QFile f(mpath);
	if (f.open(QIODevice::WriteOnly))
	{
		QByteArray str = info.toLatin1();
		f.write(str);
		f.close();
	}
}

void LogLoginMode(QString mode)
{
	QString mpath = gUserDataPath + "/" + LOINGMODE; ///// QCoreApplication::applicationDirPath() + " / login.user";
	QFile f(mpath);
	if (f.open(QIODevice::WriteOnly))
	{
		QByteArray str = mode.toLatin1();
		f.write(str);
		f.close();
	}
}


QString GetCurrentLoginMode()
{
	QString mpath = gUserDataPath + "/" + LOINGMODE;
	QString info = "AUTO";
	QFile file(mpath);
	BOOL flag = file.open(QIODevice::ReadOnly | QIODevice::Text);
	if (flag)
	{
		info = file.readAll();
		file.close();
	}
	return info;
}

//保存当前登陆成功的MAC
void saveMacLog(QString mac)
{
	QString mpath = gUserDataPath + "/" + MAC_LOG; ///// QCoreApplication::applicationDirPath() + " / login.user";
	QFile f(mpath);
	if (f.open(QIODevice::WriteOnly))
	{
		QByteArray str = mac.toLatin1();
		f.write(str);
		f.close();
	}
}

//读取最后登陆成功的MAC
QString loadMacLog()
{
	QString mpath = gUserDataPath + "/" + MAC_LOG;
	QString mac = "";
	QFile file(mpath);
	BOOL flag = file.open(QIODevice::ReadOnly | QIODevice::Text);
	if (flag)
	{
		mac = file.readAll();
		file.close();
	}
	return mac;
}

QString getHostMacAddress()
{
	////return "12345678";
	QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces(); // 获取所有网络接口列表
	int nCnt = nets.count();
	QString strMacAddr = "";

	QString oldMac = loadMacLog();

	//////// 检查如果最后登陆的mac,在当前设备中存在,则使用这个mac ;
	if (oldMac != "")
	{
		for (int i = 0; i < nCnt; i++)
		{
			strMacAddr = nets[i].hardwareAddress();
			strMacAddr.replace(":", "");
			strMacAddr.replace("-", "");
			if (strMacAddr == oldMac)
			{
				return strMacAddr;
			}
		}
	}

	// 如果此网络接口被激活并且正在运行并且不是回环地址，则就是我们需要找的Mac地址
	for (int i = 0; i < nCnt; i++)
	{
		if (nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning)
			&& !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
		{
			strMacAddr = nets[i].hardwareAddress();
			strMacAddr.replace(":", "");
			strMacAddr.replace("-", "");
			if (oldMac != "" && oldMac != strMacAddr)
			{
				QMessageBox::information(nullptr, transfer("提醒"), transfer("登录设备和上次不一样,如果登录失败,设备没有注册过,请通知服务人员"));
			}
			/////QMessageBox::information(0, transfer("提醒"), transfer("设备登录和上次不一样,如果登录失败,没有注册过,请通知服务人员"));
			break;
		}
	}
	return strMacAddr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace ui
{
	MyUpdateWindow::MyUpdateWindow(void)
	{
		CUR_UPDATE_VERSION = LoadLastUpdateVersion();

		m_httpManager = new QNetworkAccessManager(this);
		m_httRrequest = new QNetworkRequest();

		connect(m_httpManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onSerUnicomRepResult(QNetworkReply*)));
		m_bShowCheckFlag = 0;

		GetVersionInfo();
	}

	MyUpdateWindow::~MyUpdateWindow(void)
	{
	}

	void MyUpdateWindow::GetVersionInfo()
	{
		QString url = "http://" + g_WebServerIP + "/cppcc-management/api/getnewest/getrn";
		m_httRrequest->setUrl(QUrl(url));
		m_httpManager->get(*m_httRrequest);
	}


	void MyUpdateWindow::onSerUnicomRepResult(QNetworkReply* preplay)
	{
		QByteArray bytes = preplay->readAll();
		QString RepContent(bytes);
		//	QMessageBox::information(this, transfer("提示"), RepContent);
		///	return;
		if (preplay->error() == QNetworkReply::NoError)
		{
			SaveUpdateVersionLog(RepContent);
			///QMessageBox::information(this, transfer("提示"), RepContent);
			///return;
			Json::Reader reader;
			Json::Value root, data;
			std::string ExtendInfoJson = RepContent.toStdString();
			bool ret = reader.parse(ExtendInfoJson, root);
			data = root["data"];
			QString id = QString::fromStdString(data["softwareId"].asString());
			QString ver = QString::fromStdString(data["versionCode"].asString());
			QString info = QString::fromStdString(data["explain"].asString());
			QString md5 = QString::fromStdString(data["md5"].asString()).toUpper();
			if (ver == CUR_UPDATE_VERSION)
			{
				//比较是否和当前版本一直
				if (m_bShowCheckFlag)
				{
					// 检查相同,弹出提示.
					QMessageBox::information(this, transfer("提示"), transfer("当前版本是最新的,没有更新信息!"));
				}
				return;
			}
			QString outinfo;

			outinfo = transfer("当前版本:   ") + CUR_UPDATE_VERSION;

			outinfo += transfer("\n更新版本:   ") + ver;

			outinfo += transfer("\n更新内容:\n    ") + info; //+ "\nMD5:" + md5 + "\n\n";   ///2019-8-21 4
			////QMessageBox::information(this, transfer("提示"), id);
			extern bool my_question(QString buttonYesText, QString buttonNoText, QString title, QString content);
			bool flag = my_question(transfer("更新"), transfer("不更新"), transfer("更新系统"), outinfo.toUtf8());
			if (flag == true)
			{
				// QMessageBox::Yes){
				QString url = "http://" + g_WebServerIP + "/cppcc-management/api/show/file?id=" + id +
					"&need-download=1";
				//QString url =  "//"+g_WebServerIP + "/cppcc-management/api/show/file?id=" + id;
				QString path = gUserDataPath + "update/" + "setup._xe";
				DeleteFile(path.toStdString().c_str());
				QDir dir;
				dir.mkdir(gUserDataPath + "update/");
				m_downloadDlg = new DownloadDialog();
				m_downloadDlg->m_fileMD5 = md5.toUpper();
				//QMessageBox::information(this, transfer("提示"), url);
				m_downloadDlg->Download(url, path);
				m_downloadDlg->UrlDownload();
				m_downloadDlg->show();
			}
		}
		else
		{
			QMessageBox::information(this, transfer("提示"), transfer("下载更新信息失败!"));
		}
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace ui
{
	const int LOCK_ERR = -11;

	enum ACOOUNT_TYPE
	{
		ACCOUNT_PHONE = 1,
		ACCOUNT_EMAIL = 3,
		ACCOUNT_DOODNUM = 4,
		ACCOUNT_DOUDOUID = 6,
		ACCOUNT_OTHERWAY= 7
	};

	LoginWindow::LoginWindow(void)
		: m_pMainLayout(nullptr)
		  , m_pBackground(nullptr)
		  , m_pInputLayout(nullptr)
		  , m_pAccountBackground(nullptr)
		  , m_pServerBackground(nullptr)
		  , m_pWaitingBackground(nullptr)
		  , m_pTitleBtnLayout(nullptr)
		  , m_pAccountLayout(nullptr)
		  , m_pSerBackgroundLayout(nullptr)
		  , m_pLoginTypeLayout(nullptr)
		  , m_pServerLayout(nullptr)
		  , m_pMinButton(nullptr)
		  , m_pCloseButton(nullptr)
		  , m_pAvatar(nullptr)
		  , m_pAccountInput(nullptr)
		  , m_pPasswordInput(nullptr)
		  , m_pRememberCheck(nullptr)
		  , m_pAutoLoginCheck(nullptr)
		  , m_pRegisterButton(nullptr)
		  , m_pForgetButton(nullptr)
		  , m_pLoginButton(nullptr)
		  , m_pSwitchButton(nullptr)
		  , m_pServerLabel(nullptr)
		  , m_pServerInput(nullptr)
		  , m_pCountryCombo(nullptr)
		  , m_pLoginTypecombo(nullptr)
		  , m_pLoginTypeLabel(nullptr)
		  , m_pLoadingAvatar(nullptr)
		  , m_pAbortButton(nullptr)
		  , m_pLoginResultTip(nullptr)
		  , m_registerWin(nullptr)
		  , m_lockoutAccount(nullptr)
	{
		CONNECT_SERVICE(LoginResult(int, long long,const std::string&));
		m_pAuthCtrl = AUTHCONTROL;

		g_Mac = getHostMacAddress();

		m_LoginMode = GetCurrentLoginMode(); // 获得当前登陆模式
		///m_LoginMode = "MANUAL";

		loadMyConfig();

		if (mUpdateWindows == nullptr)
		{
			///<=== 2019-8-21 5   读完配置文件再更新检查
			mUpdateWindows = new MyUpdateWindow();
		}


		initWidget();
		setAttribute();
		layout();
		setConnections();
		setPreviousLoginInfo();

		getTelePhoneInfo();


		connect(this,SIGNAL(lockoutAccount()), this,SLOT(onLockedOutAccount()));
		connect(this,SIGNAL(activeAccount()), this,SLOT(onActiveAccount()));

		////m_pInputLayout->setCurrentWidget(m_pAccountBackground);
	}


	LoginWindow::~LoginWindow(void)
	{
		if (m_pMinButton != nullptr)
		{
			delete m_pMinButton;
			m_pMinButton = nullptr;
		}
		if (m_pCloseButton != nullptr)
		{
			delete m_pCloseButton;
			m_pCloseButton = nullptr;
		}
		if (m_pTitleBtnLayout != nullptr)
		{
			delete m_pTitleBtnLayout;
			m_pTitleBtnLayout = nullptr;
		}
		if (m_pBackground != nullptr)
		{
			delete m_pBackground;
			m_pBackground = nullptr;
		}
		if (m_pSwitchButton != nullptr)
		{
			delete m_pSwitchButton;
			m_pSwitchButton = nullptr;
		}
		if (m_pAvatar != nullptr)
		{
			delete m_pAvatar;
			m_pAvatar = nullptr;
		}
		if (m_pAccountInput != nullptr)
		{
			delete m_pAccountInput;
			m_pAccountInput = nullptr;
		}
		if (m_pPasswordInput != nullptr)
		{
			delete m_pPasswordInput;
			m_pPasswordInput = nullptr;
		}
		if (m_pRememberCheck != nullptr)
		{
			delete m_pRememberCheck;
			m_pRememberCheck = nullptr;
		}
		if (m_pAutoLoginCheck != nullptr)
		{
			delete m_pAutoLoginCheck;
			m_pAutoLoginCheck = nullptr;
		}
		if (m_pRegisterButton != nullptr)
		{
			delete m_pRegisterButton;
			m_pRegisterButton = nullptr;
		}

		if (m_pLoginTypecombo != nullptr)
		{
			delete m_pLoginTypecombo;
			m_pLoginTypecombo = nullptr;
		}

		if (m_pLoginTypeLabel != nullptr)
		{
			delete m_pLoginTypeLabel;
			m_pLoginTypeLabel = nullptr;
		}

		if (m_pForgetButton != nullptr)
		{
			delete m_pForgetButton;
			m_pForgetButton = nullptr;
		}
		if (m_pLoginButton != nullptr)
		{
			delete m_pLoginButton;
			m_pLoginButton = nullptr;
		}
		if (m_pAccountLayout != nullptr)
		{
			delete m_pAccountLayout;
			m_pAccountLayout = nullptr;
		}
		if (m_pAccountBackground != nullptr)
		{
			delete m_pAccountBackground;
			m_pAccountBackground = nullptr;
		}
		if (m_pServerLabel != nullptr)
		{
			delete m_pServerLabel;
			m_pServerLabel = nullptr;
		}
		if (m_pServerInput != nullptr)
		{
			delete m_pServerInput;
			m_pServerInput = nullptr;
		}
		if (m_pCountryCombo != nullptr)
		{
			delete m_pCountryCombo;
			m_pCountryCombo = nullptr;
		}
		if (m_pLoginTypeLayout != nullptr)
		{
			delete m_pLoginTypeLayout;
			m_pLoginTypeLayout = nullptr;
		}
		if (m_pSerBackgroundLayout != nullptr)
		{
			delete m_pSerBackgroundLayout;
			m_pSerBackgroundLayout = nullptr;
		}
		if (m_pServerLayout != nullptr)
		{
			delete m_pServerLayout;
			m_pServerLayout = nullptr;
		}
		if (m_pServerBackground != nullptr)
		{
			delete m_pServerBackground;
			m_pServerBackground = nullptr;
		}
		if (m_pInputLayout != nullptr)
		{
			delete m_pInputLayout;
			m_pInputLayout = nullptr;
		}
		if (m_pLoginResultTip != nullptr)
		{
			delete m_pLoginResultTip;
			m_pLoginResultTip = nullptr;
		}
		if (m_pLoadingAvatar != nullptr)
		{
			delete m_pLoadingAvatar;
			m_pLoadingAvatar = nullptr;
		}
		if (m_pAbortButton != nullptr)
		{
			delete m_pAbortButton;
			m_pAbortButton = nullptr;
		}
		if (m_pWaitingBackground != nullptr)
		{
			delete m_pWaitingBackground;
			m_pWaitingBackground = nullptr;
		}
		if (m_pMainLayout != nullptr)
		{
			delete m_pMainLayout;
			m_pMainLayout = nullptr;
		}
	}

	void LoginWindow::initWidget(void)
	{
		m_pMainLayout = new QVBoxLayout(this);
		m_pBackground = new QLabel(this);
		m_pInputLayout = new QStackedLayout(this);
		m_pAccountBackground = new QWidget(this);
		m_pServerBackground = new QWidget(this);
		m_pWaitingBackground = new QWidget(this);
		m_pTitleBtnLayout = new QHBoxLayout(this);
		m_pMinButton = new PushButton(this);
		m_pCloseButton = new PushButton(this);

		m_pAccountLayout = new QGridLayout(m_pAccountBackground);
		m_pAvatar = new HeadImage(m_pAccountBackground, QSize(80, 80));
		m_pAccountInput = new QLineEdit(m_pAccountBackground);
		m_pPasswordInput = new QLineEdit(m_pAccountBackground);
		m_pRememberCheck = new QCheckBox(m_pAccountBackground);
		m_pAutoLoginCheck = new QCheckBox(m_pAccountBackground);
		m_pAutoLoginCheck->setVisible(false);

		m_pVerifyNumInput = new QLineEdit(m_pAccountBackground);
		m_pShowVerifyBtn = new ElidedLabel(m_pAccountBackground);
		m_pShowVerifyBtn->setAlignment(Qt::AlignCenter);

		m_pRegisterButton = new QPushButton(m_pAccountBackground);
		m_pForgetButton = new QPushButton(m_pAccountBackground);
		m_pRegisterButton->setVisible(false);
		m_pForgetButton->setVisible(false);

		m_pLoginButton = new QPushButton(m_pAccountBackground);
		m_pSwitchButton = new PushButton(this);
		m_pServerLayout = new QVBoxLayout();
		m_pLoginTypeLayout = new QVBoxLayout();

		m_pSerBackgroundLayout = new QHBoxLayout(m_pServerBackground);
		m_pServerLabel = new QLabel(m_pServerBackground);
		m_pServerInput = new QLineEdit(m_pServerBackground);
		m_pServerLabelWeb = new QLabel(m_pServerBackground);
		m_pServerInputWeb = new QLineEdit(m_pServerBackground);

		m_pCountryCombo = new MyQComboBox(m_pServerBackground);

		m_pLoginTypecombo = new MyQComboBox(m_pServerBackground);
		m_pLoginTypeLabel = new QLabel(m_pServerBackground);

		m_pLoadingAvatar = new HeadImage(m_pWaitingBackground, QSize(80, 80));
		m_pAbortButton = new QPushButton(m_pWaitingBackground);
		m_pLoginWaittingInfo = new QLabel(m_pWaitingBackground);
		m_pLoginWaittingInfo->setFixedSize(QSize(200, 50));

		m_pLoginResultTip = new TipWidget(this);

		m_pBackground->setObjectName("loginBackground");
		m_pAccountInput->setObjectName("accountEdit");
		m_pPasswordInput->setObjectName("passwordEdit");
		m_pRegisterButton->setObjectName("blueButton");

		m_pForgetButton->setObjectName("blueButton");
		m_pLoginButton->setObjectName("sendbtn");
		m_pAbortButton->setObjectName("sendbtn");
		m_pLoginButton->setFocus();
	}

	void LoginWindow::saveMyConfig()
	{
		QString mpath = gUserDataPath + "/" + WEBSERVER_INI;
		///// QCoreApplication::applicationDirPath() + " / login.user";
		QFile f(mpath);
		if (f.open(QIODevice::WriteOnly))
		{
			QByteArray str = g_WebServerIP.toLatin1();
			f.write(str);
			f.close();
		}
	}

	void LoginWindow::loadMyConfig()
	{
		QString mpath = gUserDataPath + "/" + WEBSERVER_INI;

		QFile file(mpath);
		BOOL flag = file.open(QIODevice::ReadOnly | QIODevice::Text);
		if (flag)
		{
			g_WebServerIP = file.readAll();
			file.close();
		}
	}

	void LoginWindow::setAttribute(void)
	{
		m_pBackground->setTextFormat(Qt::PlainText);
		m_pBackground->setScaledContents(true);
		m_pMinButton->setPicName(QString(":/login/min"));
		m_pCloseButton->setPicName(QString(":/login/close"));
		m_pMinButton->setToolTip(transfer("最小化"));
		m_pCloseButton->setToolTip(transfer("关闭"));

		//登录界面
		m_pAccountInput->setPlaceholderText(transfer("用户名"));
		m_pAccountInput->setMaxLength(11);
		m_pAccountInput->setContextMenuPolicy(Qt::NoContextMenu);
		QRegExp regx("[0-9]+$");
		QValidator* validator = new QRegExpValidator(regx, m_pAccountInput);
		m_pAccountInput->setValidator(validator);
		m_pPasswordInput->setPlaceholderText(transfer("密码"));
		m_pPasswordInput->setContextMenuPolicy(Qt::NoContextMenu);
		m_pPasswordInput->setEchoMode(QLineEdit::Password);

		m_pVerifyNumInput->setPlaceholderText(transfer("请输入验证码"));
		m_pVerifyNumInput->setVisible(false);

		m_pRememberCheck->setText(transfer("记住密码"));
		m_pAutoLoginCheck->setText(transfer("自动登录"));

		m_pRegisterButton->setText(transfer("  注册账号 "));
		m_pRegisterButton->setFixedSize(QSize(80, 30));
		m_pForgetButton->setText(transfer("  忘记密码 "));
		m_pForgetButton->setFixedSize(QSize(80, 30));
		m_pRegisterButton->setCursor(Qt::PointingHandCursor);
		m_pForgetButton->setCursor(Qt::PointingHandCursor);

		m_pLoginButton->setText(transfer("登    录"));
		m_pSwitchButton->setPicName(QString(":/login/serverSetting"));
		m_pSwitchButton->setVisible(false);
		m_pLoginResultTip->setVisible(false);

		//服务器界面

		m_pServerLabel->setText(transfer("即时聊天服务器"));
		////m_pLoginTypeLabel->setText(transfer("登录方式设置三"));
		m_pServerInput->setPlaceholderText(transfer("服务器"));

		m_pServerLabelWeb->setText(transfer("履职平台服务器"));
		m_pServerInputWeb->setPlaceholderText(transfer("服务器"));

		connect(m_pLoginTypecombo, SIGNAL(currentIndexChanged(QString)), this, SLOT(onCurrentIndexChanged(QString)));
		connect(m_pServerInput,SIGNAL(editingFinished()), this,SLOT(onServerLineditFinishi()));
		connect(m_pServerInputWeb, SIGNAL(editingFinished()), this, SLOT(onServerLineditFinishiWeb()));
		m_pLoginTypecombo->setVisible(false);
		//m_pServerInput->setText(QString::fromLocal8Bit(utils::FunctionConfig::getDefaultServer().data()));
		m_pServerInput->setText(DEAFALT_SERVER);

		m_pServerInputWeb->setText(g_WebServerIP);
		m_pCountryCombo->addItem(transfer("中国"));
		m_pCountryCombo->setVisible(false);

		setLoginType();
		//等待界面
		m_pLoadingAvatar->setAvatarPath(":/login/login_head");
		m_pAvatar->setAvatarPath(":/login/login_head");
		m_pAbortButton->setText(transfer("取  消"));
		m_pAbortButton->setVisible(false);
	}

	void LoginWindow::onCurrentIndexChanged(QString name)
	{
		BEGIN;
		AddLog(LOG_LEV_INFO,LOG_FILE, "onCurrentIndexChanged name =%s", name.toLocal8Bit().data());
		bool haschange = false;
		std::string sname = name.toLocal8Bit().data();
		for (std::list<data::LoginType>::iterator it = m_listType.begin(); it != m_listType.end(); ++it)
		{
			if (it->type_name == sname && sname != m_curentLoginType.type_name)
			{
				haschange = true;
				m_curentLoginType.type_name = it->type_name;
				//m_curentLoginType.type_num  = it->type_num;

				m_curentLoginType.type_num = 10; //政协固定类型不做处理
				break;
			}
		}

		setUserEditRegExp(m_curentLoginType.type_num);
		m_pLoginTypecombo->setEditText(name);
		//m_pAccountInput->setPlaceholderText(QString::fromLocal8Bit(m_curentLoginType.type_name.data()));
		m_pAccountInput->setPlaceholderText(transfer("用户名"));

		if (haschange)
		{
			m_pAccountInput->setText("");
			m_pPasswordInput->setText("");
			m_pAvatar->setAvatarPath("");
			m_pLoadingAvatar->setAvatarPath("");
		}
		END;
	}


	void LoginWindow::setLoginType()
	{
		BEGIN;
		m_listType.clear();
		int size = m_pLoginTypecombo->count();
		for (int i = size - 1; i >= 0; --i)
		{
			m_pLoginTypecombo->removeItem(i);
		}

		m_pAuthCtrl->getLoginExtData(m_listType, m_pServerInput->text().toStdString());
		if (m_listType.empty())
		{
			std::map<int, std::string> loginMap = utils::FunctionConfig::getLoginType();
			std::map<int, std::string>::iterator iter = loginMap.begin();
			while (iter != loginMap.end())
			{
				data::LoginType tmp;
				tmp.type_name = iter->second;
				tmp.type_num = iter->first;
				m_listType.push_back(tmp);
				++iter;
			}
		}


		for (std::list<data::LoginType>::iterator it = m_listType.begin(); it != m_listType.end(); ++it)
		{
			m_pLoginTypecombo->addItem(QString::fromLocal8Bit((it->type_name).data()));
		}

		onCurrentIndexChanged("ID");
		m_pLoginTypecombo->setCurrentIndex(3);
		END;
	}

	void LoginWindow::layout(void)
	{
		//this->setFixedSize(420, 320);
		///this->setFixedSize(440, 440);  /// <==== 2019-5-29

		//this->setFixedSize(456, 344);  /// <==== 2019-5-29
		this->setFixedSize(580, 438);
		//标题栏
		m_pTitleBtnLayout->setContentsMargins(0, 0, 0, 0);
		m_pTitleBtnLayout->addStretch(1);
		m_pTitleBtnLayout->addWidget(m_pMinButton, 0, Qt::AlignTop);
		m_pTitleBtnLayout->addWidget(m_pCloseButton, 0, Qt::AlignTop);

		//背景图


		//m_pTitleBtnLayout->addWidget(label);

		///QPalette palette = m_pBackground->palette();
		///palette.setBrush(backgroundRole(), QBrush(pixmap));
		////setPalette(palette);

		///m_pBackground->setPalette(palette);

		//m_pBackground->setLayout(m_pTitleBtnLayout);
		///m_pBackground->setMinimumSize(400, 150);
		/*	QFont font("Microsoft YaHei", 20, 45); //第一个属性是字体（微软雅黑），第二个是大小，第三个是加粗（权重是75） 
			m_pBackground->setFont(font);
			m_pBackground->setAlignment(Qt::AlignCenter);
			m_pBackground->setContentsMargins(0, 0, 0, 0);
	
	
			m_pBackground->setText(transfer("全 国 政 协 履 职 平 台"));
	*/
		//登录界面
		m_pAccountBackground->setMinimumSize(this->width(), this->height() / 2);
		m_pAvatar->setMinimumSize(80, 80);


		m_pAccountInput->setMinimumSize(180, 35);
		m_pPasswordInput->setMinimumSize(180, 35);
		m_pVerifyNumInput->setMinimumSize(180, 35);
		m_pLoginButton->setMinimumSize(190, 35);

		m_pRegisterButton->setFixedWidth(80);
		m_pForgetButton->setFixedWidth(80);
		m_pShowVerifyBtn->setFixedSize(80, 35);

		m_pAccountLayout->addWidget(m_pAvatar, 0, 0, 3, 2, Qt::AlignTop);

		m_pAccountLayout->addWidget(m_pAccountInput, 0, 1, 1, 2);
		//m_pAccountLayout->addWidget(m_pRegisterButton, 0, 3, Qt::AlignLeft);
		//m_pAccountLayout->addWidget(m_pForgetButton, 1, 3, Qt::AlignLeft);
		m_pAccountLayout->addWidget(m_pRememberCheck, 1, 3, Qt::AlignLeft);

		m_pAccountLayout->addWidget(m_pShowVerifyBtn, 2, 3, Qt::AlignLeft);
		m_pAccountLayout->addWidget(m_pVerifyNumInput, 2, 1, 1, 2);

		m_pAccountLayout->addWidget(m_pPasswordInput, 1, 1, 1, 2);

		/*	m_pAccountLayout->addWidget(m_pRememberCheck, 3, 1,
				Qt::AlignLeft | Qt::AlignBottom);
			m_pAccountLayout->addWidget(m_pAutoLoginCheck, 3, 2,
				Qt::AlignRight | Qt::AlignBottom);*/


		m_pAccountLayout->addWidget(m_pLoginButton, 3, 1, 1, 2);
		m_pAccountLayout->addWidget(m_pSwitchButton, 3, 3, Qt::AlignRight | Qt::AlignBottom);


		m_pAccountLayout->setHorizontalSpacing(10);
		m_pAccountLayout->setVerticalSpacing(0);
		m_pAccountLayout->setRowMinimumHeight(0, 45);
		m_pAccountLayout->setRowMinimumHeight(1, 45);
		m_pAccountLayout->setRowMinimumHeight(2, 45);
		m_pAccountLayout->setRowMinimumHeight(3, 45);
		//m_pAccountLayout->setRowMinimumHeight(4, 65);
		m_pAccountLayout->setContentsMargins(30, 10, 30, 30);
		m_pAccountBackground->setLayout(m_pAccountLayout);

		//服务器界面
		m_pServerBackground->setMinimumSize(this->width(), this->height() / 2);
		m_pServerInput->setMinimumSize(180, 30);
		m_pServerInputWeb->setMinimumSize(180, 30);
		m_pCountryCombo->setMinimumSize(180, 30);
		m_pLoginTypecombo->setMinimumSize(130, 30);

		m_pServerLayout->setContentsMargins(0, 10, 0, 0);
		m_pServerLayout->setSpacing(10);
		m_pServerLayout->addWidget(m_pServerLabel, 0, Qt::AlignLeft);
		m_pServerLayout->addWidget(m_pServerInput, 0, Qt::AlignLeft);
		m_pServerLayout->addWidget(m_pServerLabelWeb, 0, Qt::AlignLeft);
		m_pServerLayout->addWidget(m_pServerInputWeb, 0, Qt::AlignLeft);
		m_pServerLayout->addWidget(m_pCountryCombo, 0, Qt::AlignLeft);
		m_pServerLayout->addStretch();

		m_pLoginTypeLayout->setContentsMargins(0, 10, 15, 13);
		m_pLoginTypeLayout->setSpacing(10);
		m_pLoginTypeLayout->addWidget(m_pLoginTypeLabel, 0, Qt::AlignLeft);
		m_pLoginTypeLayout->addWidget(m_pLoginTypecombo, 0, Qt::AlignLeft);

		//m_pLoginTypeLayout->addStretch();

		//m_pServerLayout->addWidget(m_pSwitchButton, 0,
		//Qt::AlignRight | Qt::AlignBottom);
		QWidget* left = new QWidget;
		left->setLayout(m_pServerLayout);

		QWidget* rigth = new QWidget();
		rigth->setLayout(m_pLoginTypeLayout);

		m_pSerBackgroundLayout->setContentsMargins(15, 10, 15, 10);
		m_pSerBackgroundLayout->setSpacing(10);
		m_pSerBackgroundLayout->addWidget(left);
		m_pSerBackgroundLayout->addStretch();
		m_pSerBackgroundLayout->addWidget(rigth);
		m_pSerBackgroundLayout->addSpacing(5);

		m_pServerBackground->setLayout(m_pSerBackgroundLayout);

		//等待界面
		m_pWaitingBackground->setMinimumSize(this->width(), this->height() / 2);
		m_pLoadingAvatar->setMinimumSize(110, 110);
		//m_pAbortButton->setMinimumSize(190, 35);
		m_pLoadingAvatar->move((m_pWaitingBackground->width() - m_pLoadingAvatar->width()) / 2, 0);
		//m_pAbortButton->move((m_pWaitingBackground->width() - m_pAbortButton->width())/2,
		//m_pWaitingBackground->height() - m_pAbortButton->height() - 20);
		m_pLoginWaittingInfo->move(m_pWaitingBackground->width() / 2 - 100, this->height() / 2 - 60);

		m_pInputLayout->addWidget(m_pAccountBackground);
		m_pInputLayout->addWidget(m_pServerBackground);
		m_pInputLayout->addWidget(m_pWaitingBackground);
		m_pInputLayout->setContentsMargins(0, 0, 0, 0);

		//m_pLoginResultTip->setMinimumSize(200, 150);
		m_pLoginResultTip->move((this->width() - m_pLoginResultTip->width()) / 2,
		                        (this->height() - m_pLoginResultTip->height()) / 2 - 10);


		QPixmap pixmap(QString(":/login/login-title")); //当前文件夹下面的图片
		//////	QLabel *label = new QLabel();
		m_pBackground->setPixmap(pixmap);
		m_pBackground->setLayout(m_pTitleBtnLayout);
		m_pBackground->setFixedHeight(190);

		m_pMainLayout->setSpacing(0);
		m_pMainLayout->setContentsMargins(10, 10, 10, 10);
		m_pMainLayout->addWidget(m_pBackground, 1, Qt::AlignTop);
		m_pMainLayout->addLayout(m_pInputLayout, 1);


		QHBoxLayout* hBox = new QHBoxLayout;

		QLabel* m_telepinfo = new QLabel();
		m_telepinfo->setFixedHeight(30);
		m_telepinfo->setText(transfer("如果需要帮助请拨打服务电话:  "));
		m_telepinfo->setAlignment(Qt::AlignRight);


		hBox->addWidget(m_telepinfo);

		m_telephone = new QLabel();
		m_telephone->setAlignment(Qt::AlignLeft);
		m_telephone->setFixedHeight(30);
		QPalette pa;
		pa.setColor(QPalette::WindowText, Qt::red);
		m_telephone->setPalette(pa);
		hBox->addWidget(m_telephone);

		/////hBox->addWidget(m_pSwitchButton,0,Qt::AlignRight);


		m_pMainLayout->addLayout(hBox); // addWidget(m_telepinfo);
		///m_pMainLayout->addWidget(m_telephone);
		//m_pMainLayout->addWidget(m_pSwitchButton, 0, Qt::AlignRight);
		//m_pMainLayout->setStretch(0,1);
		//m_pMainLayout->setStretch(1,2);

		this->setLayout(m_pMainLayout);
		installEventFilter(this);
	}

	///电话号码申请任务
	void LoginWindow::getTelePhoneInfo()
	{
		m_telePhoneManager = new QNetworkAccessManager(this);
		m_telePhoneRrequest = new QNetworkRequest();

		QString url = "http://" + g_WebServerIP + "/cppcc-management/dic/system/telephone"; //// +userName;
		connect(m_telePhoneManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(ontelePhoneRsp(QNetworkReply*)));
		m_telePhoneRrequest->setUrl(QUrl(url));
		m_telePhoneManager->get(*m_telePhoneRrequest);
	}

	//电话号码应答服务
	void LoginWindow::ontelePhoneRsp(QNetworkReply* preplay)
	{
		///	if (preplay->error() == QNetworkReply::NoError)
		{
			QByteArray bytes = preplay->readAll();
			QString RepContent(bytes);
			/////QMessageBox::information(this, "", RepContent);

			std::string ExtendInfoJson = RepContent.toStdString();
			Json::Reader reader;
			Json::Value root, data;
			bool ret = reader.parse(ExtendInfoJson, root);
			data = root["data"];
			QString tel = QString::fromStdString(data["codeText"].asString());
			m_telephone->setText(tel);

			if (m_LoginMode != "MANUAL")
			{
				//  自动登陆
				login_ext();
			}
		}
	}

	void LoginWindow::setConnections(void)
	{
		connect(m_pSwitchButton, SIGNAL(clicked()), this, SLOT(onSwitchButtonClicked()));
		connect(m_pMinButton, SIGNAL(clicked()), this, SLOT(showMinimized()));
		connect(m_pCloseButton, SIGNAL(clicked()), this, SLOT(close()));
		connect(m_pCloseButton, SIGNAL(clicked()), qApp, SLOT(quit()));
		connect(m_pLoginButton, SIGNAL(clicked()), this, SLOT(onLoginBtnClicked()));
		connect(m_pRegisterButton, SIGNAL(clicked()), this,
		        SLOT(onRegisterBtnClicked()));
		connect(m_pForgetButton, SIGNAL(clicked()), this,
		        SLOT(onForgetBtnClicked()));
		connect(m_pRememberCheck, SIGNAL(clicked(bool)), this,
		        SLOT(onRememberCheckChanged(bool)));
		connect(m_pAutoLoginCheck, SIGNAL(clicked(bool)), this,
		        SLOT(onAutoLoginCheckChanged(bool)));
		connect(this, SIGNAL(showLoginResultTip(QString)), this,
		        SLOT(onShowLoginResultTip(QString)));
		connect(m_pAbortButton, SIGNAL(clicked()), this,
		        SLOT(onAbortBtnClicked()));
		connect(this, SIGNAL(swithAccountUI(QWidget*)), m_pInputLayout,
		        SLOT(setCurrentWidget(QWidget*)));

		//connect(m_pShowVerifyBtn, SIGNAL(clicked()), this , SLOT(onSerGetVerifyImag()));
		connect(m_pShowVerifyBtn, SIGNAL(clicked()), this, SLOT(onSerGetNextVerifyCode()));
		m_pLoginButton->setFocus(Qt::BacktabFocusReason);
		m_pSwitchButton->setFocusPolicy(Qt::NoFocus);
	}

	// 预读最后一次保存的登陆信息
	void LoginWindow::setPreviousLoginInfo(void)
	{
		BEGIN;
		std::vector<data::AuthInfo> vecAuthInfos = m_pAuthCtrl->getLoginInfos();

		if (vecAuthInfos.size() > 0)
		{
			data::AuthInfo lastAuthInfo = vecAuthInfos.at(0);

			if (lastAuthInfo.curType == 0)
			{
				lastAuthInfo.curType = 1;
			}
			m_authInfo = lastAuthInfo;


			m_curentLoginType.type_num = lastAuthInfo.curType;
			switch (m_curentLoginType.type_num)
			{
			case ACCOUNT_PHONE:
				m_curentLoginType.type_name = lastAuthInfo.phone;
				break;
			case ACCOUNT_EMAIL:
				m_curentLoginType.type_name = lastAuthInfo.email;
				break;
			case ACCOUNT_DOUDOUID:
				m_curentLoginType.type_name = lastAuthInfo.userId;
				break;
			case ACCOUNT_OTHERWAY:
			case ACCOUNT_DOODNUM:
				m_curentLoginType.type_name = lastAuthInfo.account;
				break;
			default:
				break;
			}


			setUserEditRegExp(lastAuthInfo.curType);
			// m_pAccountInput->setText(QString::fromStdString(m_curentLoginType.type_name));


			{
				////QString CurentPath = QString::fromStdString(USERFILEPATH);

				QString mpath = gUserDataPath + "/" + LOGINUSER;


				QFile file(mpath);
				BOOL flag = file.open(QIODevice::ReadOnly | QIODevice::Text);
				if (flag)
				{
					lastAuthInfo.account = file.readAll();
					file.close();
				}
			}
			m_pAccountInput->setText(QString::fromStdString(lastAuthInfo.account));
			//m_pAccountInput->setText(QString::fromLocal8Bit(m_curentLoginType.type_name.data()));

			if (lastAuthInfo.isRemberPwd)
			{
				m_pPasswordInput->setText(QString::fromStdString(lastAuthInfo.pwd));
				m_pRememberCheck->setChecked(lastAuthInfo.isRemberPwd);
			}
			m_pServerInput->setText(QString::fromStdString(lastAuthInfo.server));


			if (lastAuthInfo.isAutoLogin)
			{
				m_pAutoLoginCheck->setChecked(lastAuthInfo.isAutoLogin);
				m_pInputLayout->setCurrentWidget(m_pWaitingBackground);
				IdentityNewVerify(lastAuthInfo); // 自动登陆


				//////LockedProcess(lastAuthInfo);
			}
		}
		END;
	}

	void LoginWindow::login_ext(void)
	{
		if (m_pLoginResultTip->isVisible())
		{
			m_pLoginResultTip->setVisible(false);
		}

		if (m_pAccountInput->text().count() == 0)
		{
			if (m_LoginMode != "MANUAL")
			{
				m_LoginMode = "MANUAL";
				return;
			}
			m_pLoginResultTip->setTipText(transfer("请输入账号"));
			m_pLoginResultTip->setVisible(true);
			m_pLoginResultTip->raise();
			return;
		}

		QString account = m_pAccountInput->text();

		m_pAccountInput->setText(account.toUpper());

		if (m_pPasswordInput->text().count() == 0)
		{
			if (m_LoginMode != "MANUAL")
			{
				m_LoginMode = "MANUAL";
				return;
			}
			m_pLoginResultTip->setTipText(transfer("请输入密码"));
			m_pLoginResultTip->setVisible(true);
			m_pLoginResultTip->raise();
			return;
		}

		/*if (m_pVerifyNumInput->text().count() == 0)
		{
		m_pLoginResultTip->setTipText(transfer("请输入验证码"));
		m_pLoginResultTip->setVisible(true);
		m_pLoginResultTip->raise();
		return;
		}*/

		if (m_pServerInput->text().count() == 0)
		{
			m_pLoginResultTip->setTipText(transfer("请输入服务器"));
			m_pLoginResultTip->setVisible(true);
			m_pLoginResultTip->raise();
			return;
		}

		m_pLoginButton->setEnabled(false);
		m_pAccountInput->setEnabled(false);
		m_pPasswordInput->setEnabled(false);
		m_pInputLayout->setCurrentWidget(m_pWaitingBackground);
		loginAnimation();

		authInfo = getLoginAccount();

		IdentityNewVerify(authInfo);
	}

	void LoginWindow::onLoginBtnClicked(void)
	{
		m_LoginMode = "MANUAL";
		login_ext();
	}

	void LoginWindow::loginAccount()
	{
		SetLoginInfo();
		LockedProcess(authInfo);
		saveMacLog(g_Mac);
		LogLoginMode("AUTO"); // 设置下次登陆默认模式
	}

	void LoginWindow::onSerLoginResult(int err, long long userID,
	                                   const std::string& errStr)
	{
		AddLog(LOG_LEV_INFO, "err = %d,  errStr = %s", err, errStr.data());
		if (err != err_ok)
		{
			UnLockedProcess();
		}
		switch (err)
		{
		case err_ok:
			emit loginSuccess();
			break;
		case err_lock_verfiyimg:
		case err_verfiyimg:
			emit lockoutAccount();
			break;
		case err_needChgPassWord:
			emit activeAccount();
			break;
		default:
			emit showLoginResultTip(transfer(errStr.data()));
			break;
		}
	}

	void LoginWindow::onShowLoginResultTip(QString tipText)
	{
		m_pInputLayout->setCurrentWidget(m_pAccountBackground);
		m_pLoginResultTip->setTipText(tipText);
		if (!tipText.isEmpty())
		{
			m_pLoginResultTip->setVisible(true);
		}

		m_pLoginResultTip->raise();
		m_pLoginButton->setEnabled(true);
		m_pAccountInput->setEnabled(true);
		m_pPasswordInput->setEnabled(true);
	}

	void LoginWindow::onSwitchButtonClicked()
	{
		m_pLoginResultTip->setVisible(false);
		if (m_pInputLayout->currentWidget() == m_pAccountBackground)
		{
			m_pSwitchButton->setPicName(QString(":/login/back"));
			m_pInputLayout->setCurrentWidget(m_pServerBackground);
			m_pLoginTypeLayout->addStretch();
			m_pLoginTypeLayout->addWidget(m_pSwitchButton, 0, Qt::AlignRight | Qt::AlignBottom);
		}
		else
		{
			m_pInputLayout->setCurrentWidget(m_pAccountBackground);
			m_pAccountLayout->addWidget(m_pSwitchButton, 4, 3,
			                            Qt::AlignRight | Qt::AlignBottom);
			m_pSwitchButton->setPicName(QString(":/login/serverSetting"));
		}
	}

	void LoginWindow::onRegisterBtnClicked()
	{
		//登录错误提示，注册时隐藏错误提醒
		if (m_pLoginResultTip->isVisible())
		{
			m_pLoginResultTip->setVisible(false);
		}

		m_registerWin = new RegisterWindow();
		connect(m_registerWin,SIGNAL(closeClicked()),SLOT(onCloseClicked()));
		connect(m_registerWin, SIGNAL(signalSignResult(std::string&, std::string&, std::string&))
		        , this, SLOT(onSerSignResult(std::string&, std::string&, std::string&)));
	}

	void LoginWindow::onForgetBtnClicked()
	{
		std::string postfix = "/server-securitycenter/password/goAccountCheck.vrv";
		m_pAuthCtrl->getSecUrl(m_pServerInput->text().toUtf8().data(),
		                       CBind(&LoginWindow::onGetSecUrlResult, this,
		                             CPlaceholders _1, postfix));
	}

	void LoginWindow::onGetSecUrlResult(const std::string& url,
	                                    const std::string postfix)
	{
		QString Url = QString::fromUtf8((url + postfix).c_str());
		bool bRet = QDesktopServices::openUrl(QUrl(Url));
		AddLog(LOG_LEV_INFO, LOG_FILE, Url.toStdString().data());
		if (!bRet)
		{
			AddLog(LOG_LEV_INFO, LOG_FILE, "QDesktopServices open ForgetPwdUrl failed");

			bool bIEOpen = utils::OpenLinkAddress(url + postfix);
			if (!bIEOpen)
			{
				AddLog(LOG_LEV_INFO, LOG_FILE, "OpenLinkAddress() open fail");
			}
		}
	}

	void LoginWindow::onRememberCheckChanged(bool checked)
	{
		if (!checked)
		{
			m_pAutoLoginCheck->setChecked(checked);
		}
	}

	void LoginWindow::onAutoLoginCheckChanged(bool checked)
	{
		if (checked)
		{
			m_pRememberCheck->setChecked(checked);
		}
	}

	void LoginWindow::onAbortBtnClicked(void)
	{
		m_pAuthCtrl->abortLogin(CBind(&LoginWindow::onAbortLoginResult,
		                              this, CPlaceholders _1));
	}

	void LoginWindow::onAbortLoginResult(const int err)
	{
		if (err == 0)
		{
			emit swithAccountUI(m_pAccountBackground);
		}
	}

	void LoginWindow::mouseReleaseEvent(QMouseEvent* event)
	{
		m_pLoginResultTip->setVisible(false);
	}

	void LoginWindow::paintEvent(QPaintEvent* event)
	{
		BaseDialog::paintEvent(event);
	}

	void LoginWindow::loginAnimation(void)
	{
		QString account = m_pAccountInput->text();
		/////		m_pLoadingAvatar->SetInfo(account);

		m_pLoginWaittingInfo->setText(transfer("用户:") + account + transfer(" 正在登录"));
		//m_pLoginWaittingInfo->setText(transfer("用户: ") + account + transfer("  正在登录 ......"));
		QPropertyAnimation* animal = new QPropertyAnimation(m_pLoadingAvatar, "pos");
		animal->setDuration(300);
		animal->setStartValue(m_pAvatar->pos());
		animal->setEndValue(QPoint((m_pWaitingBackground->width() - m_pLoadingAvatar->width()) / 2, 10));
		animal->start();
	}

	void LoginWindow::onIconIsActived(QSystemTrayIcon::ActivationReason reason)
	{
		switch (reason)
		{
			//点击托盘图标之后松开
		case QSystemTrayIcon::Trigger:
			//双击托盘图标
		case QSystemTrayIcon::DoubleClick:
			{
				this->showNormal();
				this->raise();
				this->activateWindow();
				m_LoginMode = "AUTO"; // 2019-7-19 双击自动登陆
				this->login_ext(); // 2019-7-19 双击自动登陆
				break;
			}
		default:
			break;
		}
	}

	bool LoginWindow::eventFilter(QObject* obj, QEvent* event)
	{
		if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent* ke = static_cast<QKeyEvent*>(event);
			if (ke->key() == Qt::Key_Enter || ke->key() == Qt::Key_Return)
			{
				onLoginBtnClicked();
			}
		}
		return BaseDialog::eventFilter(obj, event);
	}

	void LoginWindow::onServerLineditFinishiWeb()
	{
		BEGIN;
		if (g_WebServerIP == m_pServerInputWeb->text())
		{
			return;
		}
		g_WebServerIP = m_pServerInputWeb->text();
		saveMyConfig();
		END;
	}

	void LoginWindow::onServerLineditFinishi()
	{
		BEGIN;
		if (m_authInfo.server == m_pServerInput->text().toStdString())
		{
			return;
		}
		setLoginType();
		END;
	}

	data::AuthInfo LoginWindow::getLoginAccount()
	{
		data::AuthInfo info; // = m_authInfo;
		info.server = m_pServerInput->text().toUtf8().data();

		info.curType = m_curentLoginType.type_num;
		info.account = m_pAccountInput->text().toUtf8().data();
		info.pwd = m_pPasswordInput->text().toUtf8().data();

		if (m_curentLoginType.type_num == 1)
		{
			info.nation = QString("0086").toUtf8().data();
			info.phone = info.account;
		}

		info.isRemberPwd = m_pRememberCheck->isChecked();
		info.isAutoLogin = m_pAutoLoginCheck->isChecked();

		info.VerifyNum = m_pVerifyNumInput->text().toUtf8().data();
		gaccount = info.account;
		return info;
	}

	void LoginWindow::setUserEditRegExp(int type)
	{
		BEGIN;
		AddLog(LOG_LEV_INFO,LOG_FILE, "setUserEditRegExp type = %d", type);
		//QRegExp regx("[0-9]+$"); 
		QRegExp regx("[a-zA-Z0-9_-]+$");
		QString boxdefault = QString::fromLocal8Bit("手机号");
		switch (type)
		{
		case ACCOUNT_PHONE:
			{
				m_pAccountInput->setMaxLength(11);
				break;
			}
		case ACCOUNT_EMAIL:
			{
				QRegExp tmp("^[a-zA-Z0-9_.-]+@[a-zA-Z0-9-]+(\.[a-zA-Z0-9-]+)*\.[a-zA-Z0-9]{2,6}$");
				m_pAccountInput->setMaxLength(32);
				regx.swap(tmp);
				boxdefault = QString::fromLocal8Bit("邮箱");
				break;
			}
		case ACCOUNT_DOUDOUID:
			{
				m_pAccountInput->setMaxLength(32);
				QRegExp tmp("[a-zA-Z0-9_./-]+$");
				boxdefault = QString::fromLocal8Bit("豆豆账号");
				regx.swap(tmp);
				break;
			}
		case ACCOUNT_OTHERWAY:
			{
				QRegExp tmp("[a-zA-Z0-9_-]+$");
				m_pAccountInput->setMaxLength(32);
				boxdefault = QString::fromLocal8Bit("自定义账号");
				regx.swap(tmp);
				break;
			}
		default:
			break;
		}

		QValidator* validator = new QRegExpValidator(regx, m_pAccountInput);
		m_pAccountInput->setValidator(validator);
		m_pLoginTypecombo->setEditText(boxdefault);
		END;
	}

	void LoginWindow::onSerSignResult(std::string& ser, std::string& account, std::string& pwd)
	{
		AddLog(LOG_LEV_INFO, "onSerSignResult ser =%s ,account = %s", ser.data(), account.data());
		if (m_registerWin != nullptr)
		{
			delete m_registerWin;
			m_registerWin = nullptr;
		}

		setUserEditRegExp(ACCOUNT_PHONE);
		//m_pAvatar->setAvatarPath("");
		m_pAccountInput->setText(QString::fromStdString(account));
		m_pPasswordInput->setText(QString::fromStdString(pwd));
		m_pServerInput->setText(QString::fromStdString(ser));
		//m_pAvatar->setAvatarPath("");
	}

	void LoginWindow::onCloseClicked()
	{
		if (m_registerWin != nullptr)
		{
			m_registerWin->close();
			delete m_registerWin;
			m_registerWin = nullptr;
		}

		if (m_lockoutAccount)
		{
			QString err = QString::fromLocal8Bit("重试次数太多,需要输入验证码");
			onShowLoginResultTip(err);
			m_lockoutAccount->close();
		}

		if (m_activeAccount)
		{
			QString err = QString::fromLocal8Bit("需要修改密码才能登录");
			onShowLoginResultTip(err);
			m_activeAccount->close();
		}
	}

	void LoginWindow::onLockedOutAccount()
	{
		BEGIN;
		std::string account = m_pAccountInput->text().toStdString();
		account = "0086" + account;
		m_lockoutAccount = CMakePtr<LockoutAccount>(account);
		connect(m_lockoutAccount.get(),SIGNAL(closeClicked()), this,SLOT(onCloseClicked()));
		connect(m_lockoutAccount.get(),SIGNAL(signalLockout()), this, SLOT(onAccountLockedOut()));
		END;
	}

	void LoginWindow::onAccountLockedOut()
	{
		BEGIN;
		if (m_lockoutAccount)
		{
			m_lockoutAccount->close();
			onShowLoginResultTip("");
		}
		END;
	}

	void LoginWindow::LockedProcess(data::AuthInfo auth)
	{
		BEGIN;
		std::string name = auth.account;
		name.append(auth.server);
		name.append(":");
		name.append(auth.email);
		name.append(":");
		name.append(auth.phone);
		name.append("@");

		if (nullptr != m_pAuthCtrl)
		{
			bool bFlag;

#ifdef _WIN32
			bFlag = utils::is_same_account_login(name);
#else
            bFlag = !SingleApplication::getInstance()->createSharedMemery(name);
#endif // _WIN32

			if (bFlag)
			{
				utils::Error::InitErrInfo(true);
				std::string strErr = utils::Error::GetErrMsg(LOCK_ERR);
				onShowLoginResultTip(transfer(strErr.data()));
				return;
			}
			if (auth.curType == 1)
			{
				auth.account = auth.phone;
			}
			m_pAuthCtrl->Login(auth,
			                   CBind(&LoginWindow::signalSerLoginResult, this, CPlaceholders _1,
			                         CPlaceholders _2, CPlaceholders _3));
		}
		END;
	}

	void LoginWindow::UnLockedProcess()
	{
		BEGIN;
		//取消登陆，取消锁
#ifdef _WIN32
		utils::is_same_account_ReleaseMutex();
#else
        SingleApplication *single = SingleApplication::getInstance();
        single->detachApplication();
#endif // _WIN32
		END;
	}

	void LoginWindow::onActiveAccount()
	{
		BEGIN;
		m_activeAccount = CMakePtr<ActivationAccount>();
		connect(m_activeAccount.get(),SIGNAL(closeClicked()), this,SLOT(onCloseClicked()));
		connect(m_activeAccount.get(),SIGNAL(signalHasChanged(QString)), this, SLOT(onPasswordHasChanged(QString)));
		END;
	}

	void LoginWindow::onPasswordHasChanged(QString pwd)
	{
		BEGIN;
		m_pPasswordInput->setText(pwd);
		onShowLoginResultTip("");
		m_pLoginButton->setFocus();
		END;
	}

	//获取指掌易验证码
	bool LoginWindow::GetZZYVerifyCodeInfo()
	{
		/*	m_httpManager = new QNetworkAccessManager(this);
			m_httRrequest = new QNetworkRequest();		
			mRanddata = qrand();
			m_VerifyRandData = "CBA" + QString::number(mRanddata) + "ZYX";	
			QString url = "http://114.255.32.30:8080/sms/getCodePicture?uuid=" + m_VerifyRandData;
			connect(m_httpManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onSerDealVerifyCode(QNetworkReply*)));
			m_httRrequest->setUrl(QUrl(url));
			m_httpManager->get(*m_httRrequest);
			*/

		return true;
	}

	void LoginWindow::GetNewVerifyCodeInfo(QString userName)
	{
		m_httpManager = new QNetworkAccessManager(this);
		m_httRrequest = new QNetworkRequest();

		QString url = "http://" + g_WebServerIP +
			"/cppcc-iam-user/api/v1/sign/images/imagecode?deviceType=pc&client_id=mrhcapp&deviceId=" + g_Mac +
			"&tid=a7e1ee6f40d6502fabf4878fa0ea2584&userName=" + userName;
		connect(m_httpManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onSerDealVerifyCode(QNetworkReply*)));
		m_httRrequest->setUrl(QUrl(url));
		m_httpManager->get(*m_httRrequest);

		//////"http://114.255.32.34/cppcc-iam-user/api/v1/sign/images/imagecode?tid=a7e1ee6f40d6502fabf4878fa0ea2584&userName=S000010"
	}

	void LoginWindow::onSerDealVerifyCode(QNetworkReply* preplay)
	{
		if (preplay->error() == QNetworkReply::NoError)
		{
			QByteArray bytes = preplay->readAll();
			QPixmap newimage;
			QImage image;
			image.loadFromData(bytes);
			newimage = QPixmap::fromImage(image);
			m_pShowVerifyBtn->setPixmap(newimage);
		}
	}

	//获取下一张验证码
	void LoginWindow::onSerGetNextVerifyCode()
	{
		/////GetZZYVerifyCodeInfo();
		// GetNewVerifyCodeInfo("S000010");
		GetNewVerifyCodeInfo(authInfo.account.c_str());
	}

	void LoginWindow::SetLoginInfo()
	{
		////authInfo.pwd = LOGINPASSWD;
		data::AuthInfo vecAuthInfos;
		vecAuthInfos.account = authInfo.account;
		vecAuthInfos.avatar = authInfo.avatar;
		vecAuthInfos.curType = authInfo.curType;
		vecAuthInfos.email = authInfo.email;
		vecAuthInfos.isAutoLogin = authInfo.isAutoLogin;
		vecAuthInfos.isRemberPwd = authInfo.isRemberPwd;
		vecAuthInfos.name = authInfo.name;
		vecAuthInfos.phone = authInfo.phone;
		vecAuthInfos.pwd = authInfo.account + ":" + authInfo.pwd;
		vecAuthInfos.nation = authInfo.nation;
		vecAuthInfos.server = authInfo.server;
		vecAuthInfos.userId = authInfo.userId;


		QString mpath = gUserDataPath + "/" + LOGINUSER; ///// QCoreApplication::applicationDirPath() + " / login.user";


		QFile f(mpath);

		if (f.open(QIODevice::WriteOnly))
		{
			QByteArray str(vecAuthInfos.account.c_str(), vecAuthInfos.account.length()); //;
			f.write(str);
			f.close();
		}


		m_pAuthCtrl->setLoginInfo(vecAuthInfos);
	}

	//指掌易身份验证
	bool LoginWindow::ZZYIdentityVerify(data::AuthInfo userinfo)
	{
		m_httpManagerIdVerify = new QNetworkAccessManager(this);
		m_httRrequestIdVerify = new QNetworkRequest();
		MD5 md5;
		md5.update(userinfo.pwd);
		std::string pwd = md5.toString();

		QString data = "auth=" + QString::fromStdString(userinfo.account) + '|' +
			QString::fromStdString(pwd) + '|' + m_VerifyRandData +
			"&code=" + QString::fromStdString(userinfo.VerifyNum);
		QByteArray Bytedata = data.toLatin1();
		connect(m_httpManagerIdVerify, SIGNAL(finished(QNetworkReply*)), this, SLOT(onSerIdVerifyRep(QNetworkReply*)));
		m_httRrequestIdVerify->setRawHeader("VRVPC", "vrvpcverify");
		m_httRrequestIdVerify->setUrl(QUrl("http://114.255.32.34:8080/user/login"));
		m_httpManagerIdVerify->post(*m_httRrequestIdVerify, Bytedata);
		return true;
	}


	// 新验证策略


	extern char* rxjRSAMessage(char* info, int mode);

	bool LoginWindow::IdentityNewVerify(data::AuthInfo userinfo)
	{
		m_httpManagerIdVerify = new QNetworkAccessManager(this);
		m_httRrequestIdVerify = new QNetworkRequest();


		QString path = QCoreApplication::applicationDirPath() + "/rsa/";

		char tmp[520];
		////sprintf(tmp, "{\"tid\":\"a7e1ee6f40d6502fabf4878fa0ea2584\",\"userName\":\"%s\",\"password\":\"%s\",\"code\":\"\"}", userinfo.account.c_str(), userinfo.pwd.c_str());
		QString mac = g_Mac;
		if (mac.isEmpty())
		{
			onShowLoginResultTip(transfer("设备错误!"));
			return false;
		}
		FILE* fp;

		QDir dir;
		dir.mkdir(gUserDataPath + "/rsa/");
		QString infileName = QString::fromStdString(userinfo.account) + ".in";
		///QString outfileName = QString::fromStdString(userinfo.account) + ".out";

		QString inFile = gUserDataPath + "/rsa/" + infileName;
		QString outFile = inFile + ".rsa";

		/////	QMessageBox::information(this, "", inFile + " " + outFile);

		QByteArray inFile_ch;
		utf2gbk(inFile, inFile_ch); /// 2019-9-5 

		if ((fp = fopen(inFile_ch, "wb")) == nullptr)
		{
			onShowLoginResultTip(transfer("文件错误! ") + inFile + " " + inFile_ch);
			return false;
		}
		fprintf(fp, "{");
		fprintf(fp, "\"tid\":\"a7e1ee6f40d6502fabf4878fa0ea2584\"");
		fprintf(fp, ",");
		fprintf(fp, "\"userName\":\"%s\"", userinfo.account.c_str());
		fprintf(fp, ",");
		fprintf(fp, "\"password\":\"%s\"", userinfo.pwd.c_str());
		fprintf(fp, ",");
		fprintf(fp, "\"code\":\"%s\"", userinfo.VerifyNum.c_str());
		fprintf(fp, ",");
		fprintf(fp, "\"deviceId\":\"%s\"", mac.toStdString().c_str());
		fprintf(fp, ",");
		fprintf(fp, "\"deviceModel\":\"pc\", \"deviceIp\":\"127.0.0.1\"");
		fprintf(fp, "}");
		fclose(fp);

		sprintf(tmp, "%s %s %s", userinfo.account.c_str(), userinfo.pwd.c_str(), mac.toStdString().c_str()); // DeviceId
		//////QMessageBox::information(this, transfer("提示"), tmp);
		QString batFile = path + "getRSA.exe";


		SHELLEXECUTEINFO ShExecInfo = {0};
		QByteArray bat_c = batFile.toLatin1();

		QByteArray path_c = path.toLatin1();

		QString Parameters = "\"" + inFile + "\"";
		//// QByteArray  Para_c = Parameters.toLatin1();

		QByteArray Para_c;
		utf2gbk(Parameters, Para_c);
		dir.remove(outFile); // 2019-9-5    =>dir.remove 删除旧的.

		QString oldpath = dir.currentPath(); // 2019-8-14
		dir.setCurrent(path); //


		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = nullptr;
		ShExecInfo.lpVerb = "open"; //多种类别有 "explorer" "print" 等
		ShExecInfo.lpFile = "getRSA.exe"; //bat_c.data();//exe 路径    
		ShExecInfo.lpParameters = Para_c; //参数
		ShExecInfo.lpDirectory = ""; //path_c.data();
		ShExecInfo.nShow = SW_HIDE; //
		ShExecInfo.hInstApp = nullptr;
		ShellExecuteEx(&ShExecInfo);

		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

		dir.setCurrent(oldpath); //

		/////// QMessageBox::information(this, transfer("提示"), "完成");

		QByteArray t;
		QFile file(outFile);
		BOOL flag = file.open(QIODevice::ReadOnly | QIODevice::Text);
		if (flag)
		{
			t = file.readAll();
			file.close();
		}
		///QString data = "tid=a7e1ee6f40d6502fabf4878fa0ea2584&client_id=mrhcapp&client_secret=98890563be65564991e223b6eadc5c0a&scope=read&grant_type=password&ciphertext="+QString(t);
		dir.remove(inFile); // 2019-9-5    
		dir.remove(outFile);

		AddLog(LOG_LEV_INFO, LOG_FILE, "loginType=%s", m_LoginMode.toLocal8Bit().data());


		QString data =
			"tid=a7e1ee6f40d6502fabf4878fa0ea2584&client_id=mrhcapp&client_secret=98890563be65564991e223b6eadc5c0a&scope=read&grant_type=password&deviceType=pc&loginType="
			+ m_LoginMode + "&ciphertext=" + QString(t);

		QString PostData = data + QString(t);
		QByteArray Bytedata = PostData.toLatin1();
		connect(m_httpManagerIdVerify, SIGNAL(finished(QNetworkReply*)), this,
		        SLOT(onIdentityNewVerifyRsp(QNetworkReply*)));
		/* 
		char tmp[520];
		sprintf(tmp, "{\"tid\":\"a7e1ee6f40d6502fabf4878fa0ea2584\", \"userName\" : \"%s\", \"password\" : \"%s\", \"code\" :\"\" }", userinfo.account.c_str(), userinfo.pwd.c_str());
		char *url = rxjRSAMessage(tmp,1);
		if (url == NULL){
			QMessageBox::information(this, "提示", "RAS ERROR!");
			return false;
		}
		
		QString data = "tid=a7e1ee6f40d6502fabf4878fa0ea2584&client_id=mrhcapp&client_secret=e685cb8f606f5a7a8720cc45236a130a&scope=read&grant_type=password&ciphertext=" + QString(url);
		QByteArray Bytedata = data.toLatin1();
		*/
		m_httRrequestIdVerify->setUrl(QUrl("http://" + g_WebServerIP + "/cppcc-iam-user/uoauth/token?" + data));
		m_httpManagerIdVerify->post(*m_httRrequestIdVerify, Bytedata);
		return true;
	}

	// 新验证策略应答
	void LoginWindow::onIdentityNewVerifyRsp(QNetworkReply* preplay)
	{
		QNetworkReply::NetworkError err;
		err = preplay->error();

		QByteArray bytes = preplay->readAll();
		QString RepContent(bytes);
		//////QMessageBox::information(this, "提示", RepContent);
        /////QMessageBox::information(this, "提示",RepContent);
		std::string ExtendInfoJson = RepContent.toStdString();
		Json::Reader reader;
		Json::Value root, fieldsarry, mJvalue;
		bool ret = reader.parse(ExtendInfoJson, root);
		if (!ret)
		{
			onShowLoginResultTip(RepContent);
			return;
		}

		if (err != QNetworkReply::NoError)
		{
			QString resMsg = QString::fromStdString(root["resultMsg"].asString());
			if (resMsg.isEmpty())
			{
				resMsg = QString::fromStdString(root["message"].asString());
				if (resMsg.isEmpty())
				{
					resMsg = transfer("登录失败!");
				}
			}
			int resultCode = root["resultCode"].asInt();
			switch (resultCode)
			{
			case 412:
				m_pVerifyNumInput->setVisible(true);
				GetNewVerifyCodeInfo(authInfo.account.c_str());
				break;
			case 500:
				resMsg = transfer("提示用户服务器错误(500), 请联系管理员!");
				break;
			case 404:
				resMsg = transfer("提示用户服务器错误(404), 请联系管理员!");
				break;
			default:
				break;
			}
			onShowLoginResultTip(resMsg);
			return;
		}


		qDebug() << "onIdentityNewVerifyRsp";
		login_info = RepContent;
		QString addstr = ",\"deviceId\":\"" + g_Mac + "\",\"deviceModel\":\"pc\"}";
		login_info.replace("}", addstr);

		/////QMessageBox::information(this, "提示", login_info);
		////loginAccount();
		getAccessInfo();
	}

	//获得access 权限信息申请信息
	bool LoginWindow::getAccessInfo()
	{
		Json::Reader reader;
		Json::Value root, fieldsarry, mJvalue;
		std::string ExtendInfoJson = login_info.toStdString();
		bool ret = reader.parse(ExtendInfoJson, root);
		if (!ret)
		{
			onShowLoginResultTip(transfer("getToken error!"));
			return false;
		}

		QString mac = g_Mac;
		if (mac.isEmpty())
		{
			onShowLoginResultTip(transfer("设备错误!"));
			return false;
		}

		QString token = QString::fromStdString(root["access_token"].asString());


		g_access_token = token; // 全局复制 
		m_accessManager = new QNetworkAccessManager(this);
		m_accessRrequest = new QNetworkRequest();
		connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onAccessInfoRsp(QNetworkReply*)));

		QString data = "tid=a7e1ee6f40d6502fabf4878fa0ea2584&deviceModel=pc&deviceId=" + mac + "&token=";


		QString PostData = data + QString(token);

		/////QMessageBox::information(this, transfer("提示"), PostData);
		QByteArray Bytedata = PostData.toLatin1();
		/////QMessageBox::information(this, "提示", PostData);
		m_accessRrequest->setUrl(QUrl("http://" + g_WebServerIP + "/cppcc-iam-user/oauth/check_token?" + PostData));
		m_accessManager->post(*m_accessRrequest, Bytedata);
		return true;
	}

	//获得access 权限信息应答信息
	void LoginWindow::onAccessInfoRsp(QNetworkReply* preplay)
	{
		QNetworkReply::NetworkError err;
		err = preplay->error();
		QByteArray bytes = preplay->readAll();
		QString RepContent(bytes);
		///QMessageBox::information(this, transfer("提示123"), RepContent);
		if (err != QNetworkReply::NoError)
		{
			onShowLoginResultTip(RepContent);
			return;
		}
		///QMessageBox::information(this, "提示",RepContent);
		std::string ExtendInfoJson = RepContent.toStdString();
		Json::Reader reader;
		Json::Value root, fieldsarry, mJvalue;
		bool ret = reader.parse(ExtendInfoJson, root);
		if (!ret)
		{
			onShowLoginResultTip(transfer("获得access 权限 error!"));
			return;
		}
		qDebug() << "onAccessInfoRsp";
		access_info = RepContent;
		loginAccount();
	}

	void LoginWindow::onSerSaveAccount(int type, QString& pAccount)
	{
		//QFile file();
	}

	//指掌易身份验证
	void LoginWindow::onSerIdVerifyRep(QNetworkReply* preplay)
	{
		if (preplay->error() == QNetworkReply::NoError)
		{
			QByteArray bytes = preplay->readAll();
			QString RepContent(bytes);
			///QMessageBox::information(this, "提示",RepContent);
			std::string ExtendInfoJson = RepContent.toStdString();
			Json::Reader reader;
			Json::Value root, fieldsarry, mJvalue;
			bool ret = reader.parse(ExtendInfoJson, root);
			qDebug() << "onSerIdVerifyRep";
			if (!ret)
			{
				onShowLoginResultTip(transfer(""));
				return;
			}

			if (root["code"].isInt())
			{
				int code = root["code"].asInt();
				if (code == 0)
				{
					loginAccount();
				}
				else
				{
					QString ErrorInfo;
					switch (code)
					{
					case 101:
						ErrorInfo = transfer("请求参数错误");
						break;

					case 102:
						ErrorInfo = transfer("认证失败");
						break;

					case 103:
						ErrorInfo = transfer("服务器时间相差超过5分钟");
						break;
					case 104:
						ErrorInfo = transfer("用户被禁用");
						break;
					case 105:
						ErrorInfo = transfer("用户不存在");
						break;
					case 106:
						ErrorInfo = transfer("验证码校验错误");
						break;
					case 107:
						ErrorInfo = transfer("用户被锁定");
						break;
					case 108:
						ErrorInfo = transfer("无效用户");
						break;
					case 109:
						ErrorInfo = transfer("验证码失效");
						break;
					default:
						break;
					}
					//QString ErrorTip = transfer("指掌易校验失败") + QString::number(code);
					onShowLoginResultTip(ErrorInfo);
				}
			}
		}
	}

	//联通登陆验证
	void LoginWindow::UnicomLoginVerify(data::AuthInfo userinfo)
	{
		m_httpManager = new QNetworkAccessManager(this);
		m_httRrequest = new QNetworkRequest();

		connect(m_httpManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onSerUnicomRepResult(QNetworkReply*)));
		/*QDateTime current_date_time = QDateTime::currentDateTime();
		QString current_date =current_date_time.toString("yyyy-MM-dd hh:mm:ss");
		QString data = "api_user=" + QString::fromStdString(userinfo.account) + "&api_ts=" + current_date + "&api_sign=sdcncsi_ict_oa";
		QByteArray Bytedata= data.toLatin1();*/

		QString url =
			"http://172.16.61.78:8080/ydlz_zx/khd/login.do?method=login&mei=123456789&device=U9200*android_4.0.3&msi=46001123456&username=18900000020&password=123456&channelId=defaultId";
		m_httRrequest->setUrl(QUrl(url));
		m_httpManager->get(*m_httRrequest);
	}

	//联通登陆验证
	void LoginWindow::onSerUnicomRepResult(QNetworkReply* preplay)
	{
		if (preplay->error() == QNetworkReply::NoError)
		{
			QByteArray bytes = preplay->readAll();
			QString RepContent(bytes);
		}
	}
}
