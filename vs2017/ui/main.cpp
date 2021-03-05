#include <QApplication>
#include <QDesktopServices>
#include <QDir>
#include <QDate>
#include <log.h>
#include <QProcess>
#include <qfont.h>
#include "core/WindowsManager.h"
std::string  g_accountname;

int main(int argc, char *argv[])
{
	//	初始化日志
	std::string logfilename("");
	QString  logdirPath("");

	//获取根目录
#if(QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
	logdirPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#else
	logdirPath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#endif
	if (!logdirPath.contains("/CPPCC")){
		logdirPath.append("/CPPCC");
	}

#if defined(__APPLE__)
	logdirPath = logdirPath.replace("Application Support", "Containers/com.vrv.linkood/Data");
#endif

	logdirPath.append("/log/");
	QDir dir;
	dir.setPath(logdirPath);
	if (!dir.exists()){
		bool bret = dir.mkdir(logdirPath);
	}
#ifdef _WIN32
	logfilename = logdirPath.toLocal8Bit().data() + QDate::currentDate().toString("yyyy.MM.dd-").toStdString();
	logfilename.append("pc-win-xp.log");

#elif defined (__linux__)
	logfilename = logdirPath.toLocal8Bit().data() + QDate::currentDate().toString("yyyy.MM.dd-").toStdString();
	logfilename.append("pc-linux-xp.log");
#elif defined (__APPLE__)
	logfilename = logdirPath.toLocal8Bit().data() + QDate::currentDate().toString("yyyy.MM.dd-").toStdString();
	logfilename.append("pc-mac-xp.log");
#endif

	QDir::setCurrent(logdirPath);
	g_accountname = logdirPath.toStdString();
	InitLogger(logfilename);

	////初始化日志目录
	//QString logdirpath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
	//logdirpath.append("\\Linkdood-Xp\\");
	//QDir::setCurrent(logdirpath);
	//InitLogger(logdirpath.toStdString());

BEGIN;
AddLog(LOG_LEV_DEBUG, "logdirpath=%s", logdirPath.toLocal8Bit().data());
	QApplication a(argc, argv);

 
	a.setQuitOnLastWindowClosed(false);
	ui::WindowsManager manager;
	manager.Init();
	int ret = a.exec();
	if ( 888 == ret)
	{
	   manager.restart_process();
	   return 0;
	}
END;
	return ret;

}
