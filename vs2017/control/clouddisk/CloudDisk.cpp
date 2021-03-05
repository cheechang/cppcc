#include "CloudDisk.h"
#include "CloudDiskWidget.h"
#include <qfile.h>
#include <qapplication.h>
#include <log.h>
#include "interface/IMClient.h"
#include "Common/RegisterUserData.h"
service::IMClient* g_client = nullptr;
CloudDisk::CloudDisk() :m_diskwnd(nullptr){
	//LOG_METHOD("CloudDisk::CloudDisk", LOG_FILE);
}
CloudDisk::~CloudDisk(){
	//LOG_METHOD("CloudDisk::~CloudDisk", LOG_FILE);
	if (nullptr != m_diskwnd){
		m_diskwnd->close();
		m_diskwnd->deleteLater();
	}
}
/**********************************************
* @brief 初始化云盘模块
* @param[in] serviceclient sdk服务层客户端指针对象
***********************************************/
void CloudDisk::InitCloudDisk(void*serviceclient,void* appInstance){
	//LOG_METHOD("CloudDisk::InitCloudDisk", LOG_FILE);
	if (nullptr != appInstance){
		//加载QSS样式表
		QFile qss(":/qss/clouddisk");
		qss.open(QFile::ReadOnly);
		QString str = QString::fromLocal8Bit(qss.readAll())+ static_cast<QApplication*>(appInstance)->styleSheet();
		static_cast<QApplication*>(appInstance)->setStyleSheet(str);
		qss.close();

		//设置字体
		QFont font("Microsoft Yahei");
		font.setPixelSize(10 * 90 / 72);
		static_cast<QApplication*>(appInstance)->setFont(font);
		RegisterUserData::Init();
	}
	if (nullptr != serviceclient){
		g_client = static_cast<service::IMClient*>(serviceclient);
	}
}
#ifdef _WIN32

/**********************************************
* @brief 显示云盘UI
* @param[in] parent 传入父窗口句柄
***********************************************/
void CloudDisk::ShowCloudDisk(HWND parent){
	//LOG_METHOD("CloudDisk::ShowCloudDisk", LOG_FILE);
	if (nullptr == m_diskwnd){
		m_diskwnd = std::make_shared<ui::CloudDiskWidget>();
	}
	else{
		m_diskwnd->ReInitData();
	}
	m_diskwnd->ShowWindow();
}
/**********************************************
* @brief 显示云盘选择上传目录窗口
* @param[in] parent 传入父窗口句柄
* @param[in] encrptkey 加密密钥
* @param[in] filePath 传入文件路径
***********************************************/
void CloudDisk::ShowSelectUploadDirWnd(HWND parent, std::string&encrptkey, std::string&filePath){
	//LOG_METHOD("CloudDisk::ShowSelectUploadDirWnd", LOG_FILE);
	if (nullptr == m_diskwnd){
		m_diskwnd = std::make_shared<ui::CloudDiskWidget>();
	}
	m_diskwnd->ShowUploadSelectDirWnd(QString::fromUtf8(filePath.data()), QString::fromUtf8(encrptkey.data()));
}
#endif

extern "C" CLOUDDISK_EXPORT_API ICloudDisk* GetInstance(){
	return  new CloudDisk;
}
extern "C" CLOUDDISK_EXPORT_API void  ReleaseInstance(ICloudDisk* obj){
	if (nullptr != obj){
		delete obj;
		obj = nullptr;
	}
}