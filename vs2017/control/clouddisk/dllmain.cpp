#include <qdatetime.h>
#include <QDesktopServices>
#include <qdir.h>
#include <log/log.h>
#include <Windows.h>
const char * filename = 0;
int line = 0;
void InitLogInfo(std::string logpath){
	//	初始化日志
	std::string logfilename("");
	std::string logdirPath(logpath);
	logdirPath.append("/Linkdood");
	logdirPath.append("/log/");
	QDir dir;
	dir.setPath(QString::fromLocal8Bit(logdirPath.data()));
	if (!dir.exists()){
		bool bret = dir.mkdir(QString::fromLocal8Bit(logdirPath.data()));
	}
#ifdef _WIN32
	logfilename = logdirPath + QDate::currentDate().toString("yyyy.MM.dd-").toStdString();
	logfilename.append("pc-win-standard.log");

#elif defined (__linux__)
	logfilename = logdirPath + QDate::currentDate().toString("yyyy.MM.dd-").toStdString();
	logfilename.append("pc-linux-standard.log");
#elif defined (__APPLE__)
	logfilename = logdirPath + QDate::currentDate().toString("yyyy.MM.dd-").toStdString();
	logfilename.append("pc-mac-standard.log");
#endif
	InitLogger(logfilename);
}
BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:{
		//获取根目录
		std::string root_path = QDesktopServices::storageLocation(QDesktopServices::DataLocation).toUtf8().data();
		//std::string root_path = QStandardPaths::writableLocation(QStandardPaths::DataLocation).toUtf8().data();
		#if defined(__APPLE__)
				utils::string_replace(root_path, "Application Support", "Containers/com.vrv.linkood/Data");
		#endif
		InitLogInfo(root_path);
		Log(LOG_LEV_INFO, LOG_FILE, "=================云盘模块（loaded clouddisk）=========================");
		break;
	   }	
	case DLL_PROCESS_DETACH:
		Log(LOG_LEV_INFO, LOG_FILE, "=================云盘模块（unloaded clouddisk）=========================");
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return (TRUE);
}