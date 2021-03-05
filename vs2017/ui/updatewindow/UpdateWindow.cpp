#include "UpdateWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCoreApplication>
#include <QSettings>
#include <QTimer>
#include <QDateTime>
#include <QDataStream>
#include <QProcess>
#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include "controls/PushButton.h"
#include "utils/common.h"
#include "UpdateFinishWindow.h"
#include "UpdateProgressWindow.h"
#include "common/ChineseInfos.h"
#include "UpdateTray.h"
#include <log.h>
#include "../common/Common.h"

#define OLD_DESKTOP_LINK "连豆豆.lnk"
#define NEW_DESKTOP_LINK "Linkdood.lnk"
namespace ui{
	UpdateWindow::UpdateWindow(QWidget *parent)
		: BaseDialog(parent),m_updatecontrol(CNull),
	 m_progresswin(CNull),m_finishwin(CNull),m_userdatapath(""),
	 m_uilocalid(0),m_updatetray(CNull)
	{
		setFixedSize(590,410);

		mBtnClose = new PushButton(this);
		mBtnClose->setPicName(QString(":/login/close"));

		mBtnMin = new PushButton(this);
		mBtnMin->setPicName(QString(":/login/min"));

		mBtnExit = new QPushButton(this);
		mBtnExit->setText(transfer("取消"));
		mBtnExit->setObjectName("updateCancel");
		mBtnExit->setMinimumSize(80,28);

		mBtnUpdate = new QPushButton(this);
		mBtnUpdate->setText(transfer("更新到最新版本"));
		mBtnUpdate->setObjectName("updateOk");
		mBtnUpdate->setMinimumSize(100,28);

		mText = new QTextEdit(this);
		mText->setObjectName("updateTextEdit");
		mText->setReadOnly(true);
		//mText->setMinimumWidth(420);
		//mText->setMaximumWidth(420);
		mText->setAlignment(Qt::AlignHCenter);
		mText->setText(transfer("更新内容：\n1.解决登录失败问题\n2.解决升级问题\n3.解决测试出来的问题"));

		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		mainLayout->setContentsMargins(10,10,10,10);
		mainLayout->setSpacing(0);
		setLayout(mainLayout);

		//标题栏
		QHBoxLayout* titleLayout = new QHBoxLayout(this);
		titleLayout->setContentsMargins(10,0,0,0);
		titleLayout->setSpacing(0);
		QLabel* logoText = new QLabel(this);
		logoText->setText(transfer("更新"));
		logoText->setObjectName("whiteLabel");
		titleLayout->addWidget(logoText,0,Qt::AlignLeft);
		titleLayout->addStretch();
		titleLayout->addWidget(mBtnMin);
		titleLayout->addWidget(mBtnClose,0,Qt::AlignRight);
		QWidget* widget = new QWidget(this);
		widget->setObjectName("updateTitleBg");
		widget->setMinimumHeight(30);
		widget->setMaximumHeight(30);
		widget->setLayout(titleLayout);
		mainLayout->addWidget(widget);

		//更新内容
		QVBoxLayout* contextLayout = new QVBoxLayout(this);
		contextLayout->setContentsMargins(0,40,0,0);
		contextLayout->setSpacing(10);
		QLabel* logoImg = new QLabel(this);
		logoImg->setPixmap(QPixmap(":/update/centerbg"));
		contextLayout->addWidget(logoImg,0,Qt::AlignHCenter);
		contextLayout->addWidget(mText,0,Qt::AlignHCenter);
		widget = new QWidget(this);
		widget->setObjectName("updateContextBg");
		widget->setLayout(contextLayout);
		mainLayout->addWidget(widget);

		//更新按钮
		QHBoxLayout* btnsLayout = new QHBoxLayout(this);
		btnsLayout->setContentsMargins(0,10,10,10);
		btnsLayout->setSpacing(20);
		btnsLayout->addStretch();
		btnsLayout->addWidget(mBtnUpdate);
		btnsLayout->addWidget(mBtnExit);
		widget = new QWidget(this);
		widget->setLayout(btnsLayout);
		mainLayout->addWidget(widget);

		connect(mBtnMin, SIGNAL(clicked()), this, SLOT(showMinimized()));
		connect(mBtnClose,SIGNAL(clicked()),this,SLOT(close()));
		connect(mBtnExit,SIGNAL(clicked()),this,SLOT(close()));
		connect(mBtnUpdate,SIGNAL(clicked()),this,SLOT(onUpdate()));

		m_updatecontrol = UPDATECONTROL;
		CONNECT_SERVICE(UpdateInfoNotice(data::UpdateInfo&));
		CONNECT_SERVICE(DownloadUpdate(int));
		CONNECT_SERVICE(ProgressUpdate(int32, int32, const std::string&,int64));
		CONNECT_SERVICE(CancelDownLoad(int));
		m_userdatapath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
		m_userdatapath.append("\\");
		m_userdatapath.replace("Linkdood", "CPPCC"); 
		std::string userdatapath = m_userdatapath.toLocal8Bit().data();
		m_updatecontrol->SetUpdateDataDir(userdatapath);
		this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
	}

	UpdateWindow::~UpdateWindow()
	{

	}
	void UpdateWindow::CheckUpdate(){
		QString url("");
		m_updatecontrol->RegUpdateInfoNotice(CBind(&UpdateWindow::signalSerUpdateInfoNotice,this,CPlaceholders  _1));
		url = GetUrlByLocalFile();
		m_updatecontrol->CheckUpdate(url.toStdString());
	}
	void UpdateWindow::onSerUpdateInfoNotice(data::UpdateInfo&info){
		bool bIsUpdate = false;
		bIsUpdate = (data::FORCE_UPDATE == info.force || data::ADVICE_UPDATE == info.force)?true:false;
		if ( bIsUpdate)
		{
			m_updateinfo = info;
			QString content = QString::fromUtf8(info.desc.c_str());
			content.replace(";", "\r\n");
			mText->setText(content);
			if (data::ADVICE_UPDATE == info.force && !info.ischeckupdate)
			{
			   QTimer::singleShot(1000 * 30, this, SLOT(onTimerShowUpdateWindow()));
			}
			else{
				onTimerShowUpdateWindow();
			}
		}
	}
	void UpdateWindow::onUpdate()
	{
	BEGIN;
		this->hide();
		//开始下载文件并显示进度条
		if (CNull == m_progresswin)
		{
			m_progresswin = CMakePtr<UpdateProgressWindow>();
			CONNECT_SUBCTRL(m_progresswin,CancelDownLoad());
			QObject::connect(m_progresswin.get(),SIGNAL(ReDownLoad()),this,SLOT(onUpdate()));
			m_progresswin->showMinimized();
		}
	
		//创建托盘
		if ( CNull == m_updatetray)
		{
			m_updatetray = CMakePtr<UpdateTray>();
			QObject::connect(m_updatetray.get(),SIGNAL(signalQuit()),this,SLOT(onCancelDownLoad()));
			QObject::connect(m_updatetray.get(),SIGNAL(signalShow()),m_progresswin.get(),SLOT(onShow()));
			QObject::connect(m_progresswin.get(),SIGNAL(ShowErrInfo(int)),m_updatetray.get(),SLOT(onShowErrInfo(int)));
		}
		m_updatetray->show();
		m_updatetray->showTipInfo(transfer("正在准升级数据,请稍后..."));

		QString localPath = m_userdatapath+QString("/Linkdood.mar");
		std::string localpath= localPath.toUtf8().data();
		utils::string_replace(localpath,"\\","/");
		m_uilocalid = QDateTime::currentDateTime().toMSecsSinceEpoch();
		m_marfileid = m_updatecontrol->DownLoadUpdateFile(
			localpath,
			m_updateinfo.url,
			CBind(&UpdateWindow::signalSerDownloadUpdate,this,CPlaceholders  _1),
			CBind(&UpdateWindow::signalSerProgressUpdate,this,CPlaceholders  _1,
			CPlaceholders  _2,CPlaceholders  _3,m_uilocalid));
	END;
	}
	void UpdateWindow::onSerDownloadUpdate(int err){
	BEGIN;
		if ( !err)
		{
			WriteMd5ToFile();
			QString localPath = m_userdatapath+QString("/Linkdood.mar");
			bool bIsComplete = CheckMarComplete(localPath, QString::fromStdString(m_updateinfo.md5));
			if ( !bIsComplete)
			{
				//不删除临时记录，为断点下载准备
				if (QFile::exists(localPath)){
					QFile::remove(localPath);
				}
				//设置错误提示信息
				m_progresswin->seterrtip(UpdateProgressWindow::ERR_CHECKCOMPLETEFAILED);
			}
			else{
				m_updatetray->hide();
				m_progresswin->onBtnCloseClicked();
				CreateReplaceTipWnd();
			}
		}
		else{
			AddLog(LOG_LEV_ERROR,"download file failed,%d,%d",err);
			if ( -16777213  == err)
			{
				m_progresswin->seterrtip(UpdateProgressWindow::ERR_USERCANCEL);
				m_progresswin->close();
				this->close();
			}
			else{
				//失败要给提示
				m_progresswin->seterrtip(UpdateProgressWindow::ERR_DOWNLOADFAILED);
			}
		}
	END;
	}
	void UpdateWindow::onSerProgressUpdate(int32 extra, int32 progress, const std::string& info,int64 uilocalid){
		if (m_uilocalid == uilocalid)
		{
			m_progresswin->updateProgress(progress);
		}
	}
	QString UpdateWindow::GetUrlByLocalFile()
	{
	 BEGIN;
		QString systemdbPath = QCoreApplication::applicationDirPath() + QString::fromLocal8Bit("/UpdateUrl.ini");
		QSettings settings(systemdbPath, QSettings::IniFormat);
		QString strUrl("");
#ifdef _WIN32
		strUrl = settings.value("WINDOWS_URL").toString();
#elif defined(__APPLE__)
		strUrl = settings.value("MAC_URL").toString();
#elif defined(__linux__)
		strUrl = settings.value("LINUX_URL").toString();
#endif
		END;
		return strUrl;
	}
	 void UpdateWindow::ShowWindow(){
		 this->showNormal();
		 this->raise();
		 this->activateWindow();
	 }
	 void UpdateWindow::onTimerShowUpdateWindow(){
		 ShowWindow();
	 }
	 void UpdateWindow::RestartClient(){
		 utils::KillProcess(SCREENSHOTAPPNAME);
		 utils::KillProcess(APPNAME);
		 utils::KillProcess(SIGNLESERVERNAME);
		 emit signalExitClient(true);
		 this->close();
	 }
	void UpdateWindow::WriteMd5ToFile(){
	BEGIN;
	QString filePath("");
	filePath = m_userdatapath + QString::fromLocal8Bit("/binary.dat");
	QFile file(filePath);
	quint32 logicNumber = 0xA0B0C0D0;
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		Log(LOG_LEV_ERROR, LOG_FILE, "open file failed!");
		return;
	}
	//写入的顺序依次是全量包或者增量包Md5 核心库包MD5
	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_4_8);
	out << quint32(logicNumber) << QString::fromStdString(m_updateinfo.md5)<< QString::fromStdString(m_updateinfo.dependMd5);
	file.close();
	END;
}
void UpdateWindow::StartReplace(){
	BEGIN;
	     QString replaceExe("");
	     QString cmd;
		 QString marname("Linkdood.mar");
		 QString appDirPath;


		 appDirPath = QCoreApplication::applicationDirPath();
		 appDirPath.append("/");

		 //	拼接replace路径
		 cmd += "xx";
		 cmd += ";";

		 //	拼接MAR包所在目录
		 cmd += m_userdatapath;
		 cmd += ";";

		 //	拼接MAR包名称
		 cmd += marname;
		 cmd += ";";

		 //	拼接升级进程ID
		 cmd += QString::number(GetCurrentProcessId());
		 cmd += ";";
		 
		 //	拼接主程序目录
		 cmd += appDirPath;
		 cmd += ";";
		 

		 //	拼接主程序名称
		 cmd += QString::fromStdString(APPNAME);
		 cmd += ";";
		 

		 //	拼接升级后是否重启主进程
		 cmd += QString::fromStdString("start");
		 cmd += ";";
		 

		 replaceExe.append("\"");
		 replaceExe.append(appDirPath+ QString::fromStdString("replace.exe"));
		 replaceExe.append("\"");
		 AddLog(LOG_LEV_INFO,"==============Replace Path:%s,cmd=%s================", replaceExe.toLocal8Bit().data(),cmd.toLocal8Bit().data());
#ifdef _WIN32
		 HINSTANCE hinstance = NULL;
		 hinstance = ShellExecuteA(NULL, "open", replaceExe.toLocal8Bit().data(), cmd.toLocal8Bit().data(), NULL, SW_SHOW);
		 if ((int)(hinstance) > 32)
		 {
			 exit(0);
			 AddLog(LOG_LEV_DEBUG,"*****************repalce.exe start success!*************");
		 }
		 else
		 {
			 AddLog(LOG_LEV_ERROR,"*****************repalce.exe start failed!,errorcode(%d)*************", (int)(hinstance));
		 }
#endif
	END;
}
int UpdateWindow::IsNeedReplace()
{
BEGIN;
	QString marPath;
	QString md5FilePath;
	QString md5;
	QStringList md5List;
	bool isExist = false;
	bool isComplete = false;

	marPath = m_userdatapath;
	marPath += "Linkdood.mar";

	md5FilePath = m_userdatapath + QString::fromLocal8Bit("binary.dat");
	md5List = GetMd5FromRecordFile(md5FilePath);

	md5 = md5List.size() >= 1 ? md5List.at(0) : "";
	isExist = utils::FileIsExist(marPath.toLocal8Bit().data());
	isComplete = CheckMarComplete(marPath,md5);

	AddLog(LOG_LEV_DEBUG,"Md5=%s,fileMd5=%s",GetFileMD5(marPath).toLocal8Bit().data(),md5.toLocal8Bit().data());
	if (isExist &&isComplete )
	{
		return 1;
	}
	else if (!isComplete)
	{
		AddLog(LOG_LEV_ERROR, "升级mar包文件异常，无法完成替换");
	}
	else{
		AddLog(LOG_LEV_ERROR, "不需要替换");
	}
	return 0;
}
int UpdateWindow::CheckReplace(){
	BEGIN;
	int ret = IsNeedReplace();
	AddLog(LOG_LEV_DEBUG, "ret=%d",ret);
	if (1 == ret){
		//设置应用程序的当前工作目录
		QDir::setCurrent(QCoreApplication::applicationDirPath());
		StartReplace();
	}
	else{
		SetDesktopLinkNew();
		//替换replace
		ReplaceSelf();
	}
	return ret;
  END;
}
void UpdateWindow::SetDesktopLinkNew(){
	BEGIN;
	QString appPath = QCoreApplication::applicationDirPath() + QString::fromLocal8Bit("/")+ QString("Linkdood.exe");
	QString deskPath =QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+ QString::fromLocal8Bit("/") + QString::fromLocal8Bit(NEW_DESKTOP_LINK);
	QString oldLink = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + QString::fromLocal8Bit("/") + QString::fromLocal8Bit(OLD_DESKTOP_LINK);;

	AddLog(LOG_LEV_DEBUG, "applicationName=%s", appPath.toLocal8Bit().data());
	if (QFile::exists(oldLink)){
		AddLog(LOG_LEV_INFO, "appname=Linkdood,修改快捷方式%s to %s",OLD_DESKTOP_LINK,NEW_DESKTOP_LINK);
		bool bret = QFile::remove(oldLink);
		bret = QFile::link(appPath, deskPath);
		if (!bret){
			AddLog(LOG_LEV_ERROR, "update desktop failed");
		}
	}
	END;
}
void UpdateWindow::ReplaceSelf(){
  BEGIN;
	QString filePath;
	bool bret = false;
	QString oldName("replace.exe");
	QString newName("replace_update.exe");

	filePath = QCoreApplication::applicationDirPath();
	filePath.append("/");
	bret = utils::FileIsExist((filePath+newName).toLocal8Bit().data());
	if ( bret)
	{
		if (QFile::exists(filePath+oldName)){
			QFile::remove(filePath+oldName);
		}
		bool bret = QFile::rename(filePath+newName,filePath+oldName);
		if ( !bret)
		{
			AddLog(LOG_LEV_ERROR, "[ERROR:-----rename file from(%s)-to(%s) failed-----].\n",(filePath+newName).toLocal8Bit().data(),
				(filePath+oldName).toLocal8Bit().data());
		}
	}
END;
}
void UpdateWindow::onCancelDownLoad(){
	BEGIN;
	     m_updatecontrol->CancelDownLoadUpdateFile(m_marfileid,CBind(&UpdateWindow::signalSerCancelDownLoad,this,CPlaceholders  _1));
	END;
}
void UpdateWindow::onSerCancelDownLoad(int err){
	BEGIN;
	    if(CNull == m_updatetray || CNull == m_progresswin) return;
		QObject::disconnect(m_updatetray.get(),SIGNAL(signalShow()),m_progresswin.get(),SLOT(onShow()));
	END;
}
void UpdateWindow::CreateReplaceTipWnd(){
	BEGIN;
		if (CNull == m_finishwin)
		{
			m_finishwin = CMakePtr<UpdateFinishWindow>();
			CONNECT_SUBCTRL(m_finishwin,RestartApp());
		}
		m_finishwin->show();
	END;
}
void UpdateWindow::onRestartApp(){
	BEGIN;
	     RestartClient();
	END;
}
}

