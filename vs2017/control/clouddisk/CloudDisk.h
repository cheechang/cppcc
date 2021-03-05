#pragma once
#include "Interface/ICloudDisk.h"
#include <memory>
namespace ui{
	class CloudDiskWidget;
}
class CloudDisk :public ICloudDisk{
public:
	CloudDisk();
	~CloudDisk();
	/**********************************************
	* @brief ��ʼ������ģ��
	* @param[in] serviceclient sdk�����ͻ���ָ�����
	***********************************************/
	virtual void InitCloudDisk(void*serviceclient,void* appInstance);
#ifdef _WIN32

	/**********************************************
	* @brief ��ʾ����UI
	* @param[in] parent ���븸���ھ��
	***********************************************/
	virtual void ShowCloudDisk(HWND parent);


	/**********************************************
	* @brief ��ʾ����ѡ���ϴ�Ŀ¼����
	* @param[in] parent ���븸���ھ��
	* @param[in] encrptkey ������Կ
	* @param[in] filePath �����ļ�·��
	***********************************************/
	virtual void ShowSelectUploadDirWnd(HWND parent, std::string&encrptkey, std::string&filePath);
#endif
private:
	std::shared_ptr<ui::CloudDiskWidget> m_diskwnd;
};