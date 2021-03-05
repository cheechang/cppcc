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
* @brief ��ʼ������ģ��
* @param[in] serviceclient sdk�����ͻ���ָ�����
***********************************************/
void CloudDisk::InitCloudDisk(void*serviceclient,void* appInstance){
	//LOG_METHOD("CloudDisk::InitCloudDisk", LOG_FILE);
	if (nullptr != appInstance){
		//����QSS��ʽ��
		QFile qss(":/qss/clouddisk");
		qss.open(QFile::ReadOnly);
		QString str = QString::fromLocal8Bit(qss.readAll())+ static_cast<QApplication*>(appInstance)->styleSheet();
		static_cast<QApplication*>(appInstance)->setStyleSheet(str);
		qss.close();

		//��������
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
* @brief ��ʾ����UI
* @param[in] parent ���븸���ھ��
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
* @brief ��ʾ����ѡ���ϴ�Ŀ¼����
* @param[in] parent ���븸���ھ��
* @param[in] encrptkey ������Կ
* @param[in] filePath �����ļ�·��
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